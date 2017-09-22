/************************************************************************/
/*! @file ThreadMaterial.h
 * @brief Some thread variables
 *
 * @details To declare some thread variables and functions
 */
/************************************************************************/

#ifndef _THREADMATERIAL_H_
#define _THREADMATERIAL_H_

#include <pthread.h>

/*
 * @brief The ProducerInput struct is to save input for producer thread
 */
struct ProducerInput
{
    pthread_mutex_t* queueMutex;
    pthread_cond_t* fullVar;
    pthread_cond_t* emptyVar;

    unsigned int size;
    Producer* producer;
    MessageQueue* messageQueue;
    string dataIn;
};

/*
 * @brief The ConsumerInput struct is to save input for consumer thread
 */
struct ConsumerInput
{
    pthread_mutex_t* queueMutex;
    pthread_cond_t* fullVar;
    pthread_cond_t* emptyVar;

    unsigned int size;
    Consumer* consumer;
    MessageQueue* messageQueue;
    string dataOut;
};

/*
 * @brief This is the thread handler for the producer
 */
void* StartProducer(void *input)
{
    ProducerInput* producerInput = (ProducerInput*)input;
    // Start the producer
    Producer* producer = producerInput->producer;
    producer->Start(producerInput->dataIn, producerInput->size, producerInput->queueMutex,
                    producerInput->fullVar, producerInput->emptyVar);

    // Print debug infomation
    #ifdef DEBUG
    cout << "PRODUCER: TERMINATED" << endl;
    #endif

    pthread_exit(NULL);
}

/*
 * @brief This is the thread handler for the consumer
 */
void* StartConsumer(void *input)
{
    ConsumerInput* consumerInput = (ConsumerInput*)input;
    // Start the comsumer
    Consumer* consumer = consumerInput->consumer;
    consumer->Start(consumerInput->dataOut, consumerInput->size, consumerInput->queueMutex,
                    consumerInput->fullVar, consumerInput->emptyVar);

    // Print debug infomation
    #ifdef DEBUG
    cout << "CONSUMER: TERMINATED" << endl;
    #endif

    pthread_exit(NULL);
}

#endif // _THREADMATERIAL_H_