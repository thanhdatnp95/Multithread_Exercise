/*****************************************************************************/
/*! @file Producer.h
 * @brief Produce data
 *
 * @details Produce data as a high-speed IO and write it to the message queue
 */
/*****************************************************************************/

#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "MessageQueue.h"
#include <pthread.h>
#include <unistd.h>

/*!
 * @brief The Producer class is used to produce data and write it to the queue
 *
 * Provide a method for starting the operation.
 * 
 */
class Producer 
{
    /*!
     * @brief the message queue
     */
    MessageQueue* queue;
public:
    /*!
     * @brief Constructor
     */
    Producer(MessageQueue* queue);
    /*!
     * @brief Destructor
     */
    ~Producer();

    /*!
     * @brief Start
     *
     * The function will start the producer.
     *
     * @param[in,out] mutexQueue the MUTEX variable for synchronization
     * @param[in,out] fullVar the condition variable for checking the full status
     * @param[in,out] emptyVar the condition variable for checking the empty status
     * @return no value
     */
    void Start(pthread_mutex_t& mutexQueue, pthread_cond_t& fullVar, pthread_cond_t& emptyVar);
};

#endif // _PRODUCER_H_