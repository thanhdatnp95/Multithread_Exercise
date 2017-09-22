/*****************************************************************************/
/*! @file Producer.cpp
 * @brief Produce data
 *
 * @details Produce data as a high-speed IO and write it to the message queue
 */
/*****************************************************************************/

#include "Producer.h"

/*
 * @internal Implement constructor
 */
Producer::Producer(MessageQueue* queue)
{
    this->queue = queue;
}

/*
 * @internal Implement destructor
 */
Producer::~Producer() { }

/*
 * @internal Start the producer
 */
void Producer::Start(string dataIn, unsigned int size, pthread_mutex_t* queueMutex, pthread_cond_t* fullVar, pthread_cond_t* emptyVar)
{
    unsigned int seqNum = 0;
    // Print debug infomation
    #ifdef DEBUG
    cout << "PRODUCER: STARTED" << endl;
    #endif

    while (seqNum < size)
    {
        // Read data from a high-speed I/O
        sleep(1);
        Message* message = new Message();
        message->id = seqNum++;
        message->data = dataIn[message->id];

        // Synchronization
        pthread_mutex_lock(queueMutex);
        
        while(queue->IsFull())
        {
            // Print debug infomation
            #ifdef DEBUG
            cout << "PRODUCER: Suspended" << endl;
            #endif
            // Wait for signal (NOT FULL)
            pthread_cond_wait(fullVar, queueMutex);
            // Print debug infomation
            #ifdef DEBUG
            cout << "PRODUCER: Waken up" << endl;
            #endif
        }
        // Add message to queue
        queue->Enqueue(message);

        // Print debug infomation
        #ifdef DEBUG
        cout << "PRODUCER: Package #" << message->id << " was sent" << endl;
        #endif
        
        // Signal any waiting thread (NOT EMPTY)
        pthread_cond_signal(emptyVar);

        pthread_mutex_unlock(queueMutex);        
    }
}
