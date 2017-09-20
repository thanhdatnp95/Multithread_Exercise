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
    if (queue == NULL)
    {
        cout << "WARNING: Invalid message queue" << endl;
    }

    this->queue = queue;
}

/*
 * @internal Implement destructor
 */
Producer::~Producer() { }

/*
 * @internal Start the producer
 */
void Producer::Start(unsigned int size, pthread_mutex_t* queueMutex, pthread_cond_t* fullVar, pthread_cond_t* emptyVar)
{
    unsigned int seqNum = 0;
    cout << "PRODUCER: STARTED" << endl;

    while (seqNum < size)
    {
        // Read data from a high-speed I/O
        sleep(1);
        Message* message = new Message();
        message->id = seqNum++;
        message->data = "xyz";

        // Synchronization
        pthread_mutex_lock(queueMutex);
        
        while(queue->IsFull())
        {
            cout << "PRODUCER: Suspended" << endl;
            // Wait for signal (NOT FULL)
            pthread_cond_wait(fullVar, queueMutex);
            cout << "PRODUCER: Waken up" << endl;
        }
        // Add message to queue
        queue->Enqueue(message);
        cout << "PRODUCER: Package #" << message->id << " was sent" << endl;
        // Signal any waiting thread (NOT EMPTY)
        pthread_cond_signal(emptyVar);

        pthread_mutex_unlock(queueMutex);        
    }
}
