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
    if (queue == NULL)
    {
        cout << "WARNING: Invalid message queue" << endl;
    }

    this->queue = queue;
}

/*
 * @internal Implement destructor
 */
Consumer::~Consumer() { }

/*
 * @internal Start the consumer
 */
void Consumer::Start(pthread_mutex_t& queueMutex, pthread_cond_t& fullVar, pthread_cond_t& emptyVar)
{
    cout << "CONSUMER: STARTED" << endl;

    while (true)
    {
        // Synchronization
        pthread_mutex_lock(&queueMutex);

        while(queue->IsEmpty())
        {
            cout << "CONSUMER: Suspended" << endl;
            // Wait for signal (NOT EMPTY)
            pthread_cond_wait(&emptyVar, &queueMutex);
            cout << "CONSUMER: Waken up" << endl;
        }
        // Read and remove message from queue
        Message* message = queue->Dequeue();
        // Signal any waiting thread (NOT FULL)
        pthread_cond_signal(&fullVar);
        
        pthread_mutex_unlock(&queueMutex);

        // Write data to a low-speed IO
        cout << "CONSUMER: Package #" << message->id << " was received" << endl;
        delete message;
        sleep(2);     
    }
}
