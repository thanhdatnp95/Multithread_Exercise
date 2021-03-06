/*****************************************************************************/
/*! @file MessageQueue.cpp
 * @brief A queue
 *
 * @details Implement a MessageQueue class
 */
/*****************************************************************************/

#include "MessageQueue.h"

/*
 * @internal Implement constructor
 */
MessageQueue::MessageQueue() { }

/*
 * @internal Implement destructor
 */
MessageQueue::~MessageQueue()
{
    for (list<Message*>::iterator it = queue.begin(); it != queue.end(); it++)
    {
        delete *it;
        *it = NULL;
    }
    queue.clear();
}

/*
 * @internal This fuction will check if the queue is empty
 */
bool MessageQueue::IsEmpty()
{
    return queue.empty();
}

/*
 * @internal This fuction will check if the queue is full
 */
bool MessageQueue::IsFull()
{
    return (queue.size() >= MAX_MESSAGES);
}

/*
 * @internal This fuction will add an element to the queue
 */
void MessageQueue::Enqueue(Message* message)
{
    queue.push_back(message);
}

/*
 * @internal This fuction will remove an element from the queue
 */
Message* MessageQueue::Dequeue()
{
    Message* message = queue.front();
    queue.pop_front();

    return message;
}