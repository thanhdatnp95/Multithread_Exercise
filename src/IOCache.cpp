/*****************************************************************************/
/*! @file IOCache.cpp
 * @brief demo program
 *
 * @details Implement an I/O cache
 */
/*****************************************************************************/

#include "Producer.h"
#include "Consumer.h"

pthread_t producerThread;   // Thread ID of producer
pthread_t consumerThread;   // Thread ID of consumer
pthread_mutex_t queueMutex; // Mutex
pthread_cond_t fullVar;     // Condition variable
pthread_cond_t emptyVar;    // Condition variable

/*
 * @internal This is the thread handler for the producer
 */
void* StartProducer(void *p)
{
    if (p == NULL)
    {
        cout << "WARNING: Invalid producer" << endl;
        pthread_exit(NULL);
    }

    Producer* producer = (Producer*)p;
    // Start the producer
    producer->Start(queueMutex, fullVar, emptyVar);

    cout << "PRODUCER: TERMINATED" << endl;
    pthread_exit(NULL);
}

/*
 * @internal This is the thread handler for the consumer
 */
void* StartConsumer(void *c)
{
    if (c == NULL)
    {
        cout << "WARNING: Invalid consumer" << endl;
        pthread_exit(NULL);
    }

    Consumer* consumer = (Consumer*)c;
    // Start the comsumer
    consumer->Start(queueMutex, fullVar, emptyVar);

    cout << "CONSUMER: TERMINATED" << endl;
    pthread_exit(NULL);
}

int main()
{
    // Init data
    MessageQueue* messageQueue = new MessageQueue();
    Producer* producer = new Producer(messageQueue);
    Consumer* consumer = new Consumer(messageQueue);

    // Init pthread variables
    pthread_mutex_init(&queueMutex, NULL);
    pthread_cond_init (&emptyVar, NULL);
    pthread_cond_init (&fullVar, NULL);    
    void* status;
    
    // Create producer thread
    if (pthread_create(&producerThread, NULL, StartProducer, (void *) producer) != 0)
    {
        cerr << "Could not create Producer" << endl;
    }

    // Create consumer thread
    if (pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumer) != 0)
    {
        cerr << "Could not create Consumer" << endl;
    }

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);

    // Release resources
    delete messageQueue;
    delete producer;
    delete consumer;
}