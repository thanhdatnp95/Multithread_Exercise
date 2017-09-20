/*****************************************************************************/
/*! @file Consumer.h
 * @brief Consume data
 *
 * @details Read it from the message queue and consume it as a low-speed IO
 */
/*****************************************************************************/

#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "MessageQueue.h"
#include <pthread.h>
#include <unistd.h>

/*!
 * @brief The Consumer class is used to read data from the queue
 *
 * Provide a method for starting the operation.
 * 
 */
class Consumer 
{
    /*!
     * @brief the message queue
     */
    MessageQueue* queue;
public:
    /*!
     * @brief Constructor
     */
    Consumer(MessageQueue* queue);
    /*!
     * @brief Destructor
     */
    ~Consumer();

    /*!
     * @brief Start
     *
     * The function will start the consumer.
     *
     * @param[in] size number of data blocks
     * @param[in,out] mutexQueue the MUTEX variable for synchronization
     * @param[in,out] fullVar the condition variable for checking the full status
     * @param[in,out] emptyVar the condition variable for checking the empty status
     * @return no value
     */
    void Start(unsigned int size, pthread_mutex_t* mutexQueue, pthread_cond_t* fullVar, pthread_cond_t* emptyVar);
};

#endif // _CONSUMER_H_