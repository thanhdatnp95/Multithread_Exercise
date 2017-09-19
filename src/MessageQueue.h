/*****************************************************************************/
/*! @file MessageQueue.h
 * @brief A queue
 *
 * @details Store data (message) in a queue
 */
/*****************************************************************************/

#ifndef _MESSAGEQUEUE_H_
#define _MESSAGEQUEUE_H_

#define        MAX_MESSAGES        10   // Maximum number of messages in the queue

#include <iostream>
#include <list>
using namespace std;

/*!
 * @brief An object of Message struct is an element of message queue.
 *
 * Consist of:
 * Identifer (sequence number of message)
 * Data of the message
 * 
 */
struct Message
{
    int id;
    string data;
};

/*!
 * @brief The MessageQueue class is the implementation of an queue.
 *
 * Provide a method for adding an element to the queue.
 * Provide a method for removing an element from the queue.
 * Provide a method for checking if the queue is empty.
 * Provide a method for checking if the queue is full.
 * 
 */
class MessageQueue
{
    /*!
     * @brief the queue (linked list)
     */
    list<Message*> queue;
public:
    /*!
     * @brief Constructor
     */
    MessageQueue();
    /*!
     * @brief Destructor
     */
    ~MessageQueue();

    /*!
     * @brief Check empty
     *
     * The function check if the queue is empty.
     *
     * @return true if the queue is empty, false otherwise
     */
    bool IsEmpty();
    /*!
     * @brief Check full
     *
     * The function check if the queue is full.
     *
     * @return true if the queue is full, false otherwise
     */
    bool IsFull();
    /*!
     * @brief Enqueue
     *
     * The function will take a message as arguemnt and add it at the end of the queue.
     *
     * @param[in] message the message needing to be added to the queue
     * @return no value
     */
    void Enqueue(Message* message);
     /*!
     * @brief Dequeue
     *
     * The function will remove the element at front of the queue.
     *
     * @return the first element of the queue (front)
     */
    Message* Dequeue();
};

#endif // _MESSAGEQUEUE_H_