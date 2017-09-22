/*****************************************************************************/
/*! @file IOCache.cpp
 * @brief demo program
 *
 * @details Implement an I/O cache
 */
/*****************************************************************************/

#include "Producer.h"
#include "Consumer.h"
#include "ThreadMaterial.h"

int main()
{
    // Input variables for threads
    ProducerInput* producerInput = new ProducerInput();
    ConsumerInput* consumerInput = new ConsumerInput();

    // Thread variables
    pthread_t producerThread;
    pthread_t consumerThread;
    pthread_mutex_t queueMutex;
    pthread_cond_t fullVar;
    pthread_cond_t emptyVar;
    void* status;

    // Init main objects
    MessageQueue* messageQueue = new MessageQueue();
    Producer* producer = new Producer(messageQueue);
    Consumer* consumer = new Consumer(messageQueue);

    // Init pthread variables
    pthread_mutex_init(&queueMutex, NULL);
    pthread_cond_init(&emptyVar, NULL);
    pthread_cond_init(&fullVar, NULL);   

    // Init thread input
    producerInput->producer = producer;
    producerInput->messageQueue = messageQueue;
    producerInput->queueMutex = &queueMutex;
    producerInput->fullVar = &fullVar;
    producerInput->emptyVar = &emptyVar;

    consumerInput->consumer = consumer;
    consumerInput->messageQueue = messageQueue;
    consumerInput->queueMutex = &queueMutex;
    consumerInput->fullVar = &fullVar;
    consumerInput->emptyVar = &emptyVar;

    // User enter input data
    cout << "BUFFER SIZE = 8" << endl;
    cout << "Enter data to send (string): ";
    getline(cin, producerInput->dataIn);
    cout << endl << "======== DEBUG INFORMATION ========" << endl;

    // Init data
    producerInput->size = producerInput->dataIn.length();
    
    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();
    
    // Create producer thread
    if (pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput) != 0)
    {
        cerr << "Could not create Producer" << endl;
    }

    // Create consumer thread
    if (pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput) != 0)
    {
        cerr << "Could not create Consumer" << endl;
    }

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);

    cout << "======== DEBUG INFORMATION ========" << endl << endl;
    cout << "Data received is: " <<  consumerInput->dataOut << endl;

    // Release resources
    delete messageQueue;
    delete producer;
    delete consumer;

    delete producerInput;
    delete consumerInput;    
}