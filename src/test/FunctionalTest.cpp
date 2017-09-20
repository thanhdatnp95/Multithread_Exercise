/************************************************************************/
/*! @file FunctionalTest.cpp
 * @brief Test Program
 *
 * @details To run funtional test
 */
/************************************************************************/

#include "gtest/gtest.h"
#include "Producer.h"
#include "Consumer.h"
#include <pthread.h>

union ThreadInput
{
    // For producer
    struct
    {
        pthread_mutex_t* queueMutexP;
        pthread_cond_t* fullVarP;
        pthread_cond_t* emptyVarP;

        unsigned int sizeP;
        Producer* producer;
        MessageQueue* messageQueueP;
        MessageQueue* dataIn;
    };
    //For consumer
    struct
    {
        pthread_mutex_t* queueMutexC;
        pthread_cond_t* fullVarC;
        pthread_cond_t* emptyVarC;

        unsigned int sizeC;
        Consumer* consumer;
        MessageQueue* messageQueueC;
        MessageQueue* dataOut;
    };
};

/*
* @internal This is the thread handler for the producer
*/
void* StartProducer(void *input)
{
    if (input == NULL)
    {
        cout << "WARNING: Invalid producer" << endl;
        pthread_exit(NULL);
    }

    ThreadInput* threadInput = (ThreadInput*)input;
    // Start the producer
    Producer* producer = threadInput->producer;
    producer->Start(threadInput->sizeP, threadInput->queueMutexP, threadInput->fullVarP, threadInput->emptyVarP);

    cout << "PRODUCER: TERMINATED" << endl;
    pthread_exit(NULL);
}

/*
* @internal This is the thread handler for the consumer
*/
void* StartConsumer(void *input)
{
    if (input == NULL)
    {
        cout << "WARNING: Invalid consumer" << endl;
        pthread_exit(NULL);
    }

    ThreadInput* threadInput = (ThreadInput*)input;
    // Start the comsumer
    consumer->Start(threadInput->sizeC, threadInput->queueMutexC, threadInput->fullVarC, threadInput->emptyVarC);

    cout << "CONSUMER: TERMINATED" << endl;
    pthread_exit(NULL);
}

class FunctionalTest : public ::testing::Test
{
protected:
    ThreadInput* producerInput = new ThreadInput();
    ThreadInput* consumerInput = producerInput;

    pthread_t producerThread;
    pthread_t consumerThread;
    pthread_mutex_t queueMutex;
    pthread_cond_t fullVar;
    pthread_cond_t emptyVar;

    Producer* producer;
    Consumer* consumer;
    MessageQueue* messageQueue;

    void* status;

    virtual void SetUp()
    {
        // Init pthread variables
        pthread_mutex_init(&queueMutex, NULL);
        pthread_cond_init(&emptyVar, NULL);
        pthread_cond_init(&fullVar, NULL);

        // Init thread input
        producerInput->queueMutexP = &queueMutex;
        producerInput->fullVarP = &fullVar;
        producerInput->emptyVarP = &emptyVar;
    }

    virtual void TearDown()
    {
        delete producerInput;
    }     
};

TEST_F(FunctionalTest, NoData)
{
    // Init data
    messageQueue = new MessageQueue();
    producer = new Producer(messageQueue);
    consumer = new Consumer(messageQueue);

    producerInput->producer = producer;
    producerInput->messageQueueP = messageQueue;
    producerInput->sizeP = 0;

    // Create producer thread
    if (pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput) != 0)
    {
        cerr << "Could not create Producer" << endl;
    }

    consumerInput->consumer = consumer;

    // Create consumer thread
    if (pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput) != 0)
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

TEST_F(FunctionalTest, DataNotOverflow)
{
    // Init data
    messageQueue = new MessageQueue();
    producer = new Producer(messageQueue);
    consumer = new Consumer(messageQueue);

    producerInput->producer = producer;
    producerInput->messageQueueP = messageQueue;
    producerInput->sizeP = 10;

    // Create producer thread
    if (pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput) != 0)
    {
        cerr << "Could not create Producer" << endl;
    }

    consumerInput->consumer = consumer;

    // Create consumer thread
    if (pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput) != 0)
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

TEST_F(FunctionalTest, DataOverflow)
{

}

TEST_F(FunctionalTest, ProducerStartLate)
{

}

TEST_F(FunctionalTest, ConsumerStartLate)
{

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}