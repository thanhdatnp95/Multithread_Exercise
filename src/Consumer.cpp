/*****************************************************************************/
/*! @file Consumer.cpp
 * @brief Consume data
 *
 * @details Read it from the message queue and consume it as a low-speed IO
 */
/*****************************************************************************/

#include "Consumer.h"

/*
 * @internal Implement constructor
 */
Consumer::Consumer(MessageQueue* queue)
{
    this->queue = queue;
}

/*
 * @internal Implement destructor
 */
Consumer::~Consumer() { }

/*
 * @internal Start the consumer
 */
void Consumer::Start(string& dataOut, unsigned int size, pthread_mutex_t* queueMutex, pthread_cond_t* fullVar, pthread_cond_t* emptyVar)
{
    unsigned int seqNum = 0;
    // Print debug infomation
    #ifdef DEBUG
    cout << "CONSUMER: STARTED" << endl;
    #endif

    while (seqNum < size)
    {
        // Synchronization
        pthread_mutex_lock(queueMutex);

        while(queue->IsEmpty())
        {
            // Print debug infomation
            #ifdef DEBUG
            cout << "CONSUMER: Suspended" << endl;
            #endif
            // Wait for signal (NOT EMPTY)
            pthread_cond_wait(emptyVar, queueMutex);
            // Print debug infomation
            #ifdef DEBUG
            cout << "CONSUMER: Waken up" << endl;
            #endif
        }
        // Read and remove message from queue
        Message* message = queue->Dequeue();
        // Signal any waiting thread (NOT FULL)
        pthread_cond_signal(fullVar);
        
        pthread_mutex_unlock(queueMutex);

        // Print debug infomation
        #ifdef DEBUG
        cout << "CONSUMER: Package #" << message->id << " was received" << endl;
        #endif

        // Write data to a low-speed IO
        dataOut += message->data;
        seqNum++;
        delete message;
        sleep(2);     
    }
}
