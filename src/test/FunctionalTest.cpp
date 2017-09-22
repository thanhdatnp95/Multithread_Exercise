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
#include "ThreadMaterial.h"

/*!
 * @brief The FunctionalTest class is used to test the operation of the
 * program.
 * 
 */
class FunctionalTest : public ::testing::Test
{
protected:
    // Input variables for threads
    ProducerInput* producerInput;
    ConsumerInput* consumerInput;

    // Thread variables
    pthread_t producerThread;
    pthread_t consumerThread;
    pthread_mutex_t queueMutex;
    pthread_cond_t fullVar;
    pthread_cond_t emptyVar;
    void* status;

    // Main objects
    Producer* producer;
    Consumer* consumer;
    MessageQueue* messageQueue;    

    FunctionalTest()
    {
        // Not implemented
    }
    ~FunctionalTest()
    {
        // Not implemented
    }

    virtual void SetUp()
    {   
        // Init thread variables
        pthread_mutex_init(&queueMutex, NULL);
        pthread_cond_init(&emptyVar, NULL);
        pthread_cond_init(&fullVar, NULL);

        // Init essential variables
        messageQueue = new MessageQueue();
        producer = new Producer(messageQueue);
        consumer = new Consumer(messageQueue);

        // Init thread input
        producerInput = new ProducerInput();
        consumerInput = new ConsumerInput();

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
    }

    virtual void TearDown()
    {
        //Release resources
        delete producerInput;
        delete consumerInput;
        delete messageQueue;
        delete producer;
        delete consumer;
    }     
};

/*!
 * @internal This test will test when no data is entered.
 */
TEST_F(FunctionalTest, NoData)
{
    // Init data   
    producerInput->dataIn = "";
    producerInput->size = producerInput->dataIn.length();    
    
    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();

    // Create producer thread
    pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput);

    // Create consumer thread
    pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput);

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);
    
    // Compare data
    EXPECT_EQ(producerInput->dataIn, consumerInput->dataOut);
}

/*!
 * @internal This test will test when data size is smaller than buffer size
 */
TEST_F(FunctionalTest, DataNotOverflow)
{
    // Init data
    producerInput->dataIn = "The first test";
    producerInput->size = producerInput->dataIn.length();

    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();

    // Create producer thread
    pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput);

    // Create consumer thread
    pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput);

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);
    
    // Compare data
    EXPECT_EQ(producerInput->dataIn, consumerInput->dataOut);
}

/*!
 * @internal This test will test when data size is bigger than buffer size
 */
TEST_F(FunctionalTest, DataOverflow)
{
    //Init data
    producerInput->dataIn = "The second test (Overflow)";
    producerInput->size = producerInput->dataIn.length();

    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();

    // Create producer thread
    pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput);

    // Create consumer thread
    pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput);

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);
    
    // Compare data
    EXPECT_EQ(producerInput->dataIn, consumerInput->dataOut);
}

/*!
 * @internal This test will test when Producer starts afer Consumer
 */
TEST_F(FunctionalTest, ProducerStartLate)
{
    //Init data
    producerInput->dataIn = "The third test";
    producerInput->size = producerInput->dataIn.length();

    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();

    // Create consumer thread
    pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput);

    // Producer start 5 secs later than comsumer
    sleep(5);

    // Create producer thread
    pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput);

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);
    
    // Compare data
    EXPECT_EQ(producerInput->dataIn, consumerInput->dataOut);
}

/*!
 * @internal This test will test when Consumer starts afer Producer
 */
TEST_F(FunctionalTest, ConsumerStartLate)
{
    //Init data
    producerInput->dataIn = "The final test";
    producerInput->size = producerInput->dataIn.length();

    consumerInput->dataOut = "";
    consumerInput->size = producerInput->dataIn.length();

    // Create producer thread
    pthread_create(&producerThread, NULL, StartProducer, (void *) producerInput);

    // Consumer start 5 secs later than producer
    sleep(5);

    // Create consumer thread
    pthread_create(&consumerThread, NULL, StartConsumer, (void *) consumerInput);

    // Wait for all threads are terminated
    pthread_join(producerThread, &status);
    pthread_join(consumerThread, &status);
    
    // Compare data
    EXPECT_EQ(producerInput->dataIn, consumerInput->dataOut);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}