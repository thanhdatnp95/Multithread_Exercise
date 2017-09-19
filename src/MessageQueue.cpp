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
    if (this->IsFull())
    {
        cout << "ERROR: The message queue is full. No element can be inserted" << endl;
        return;
    }

    queue.push_back(message);
}

/*
 * @internal This fuction will remove an element from the queue
 */
Message* MessageQueue::Dequeue()
{
    if (this->IsEmpty())
    {
        cout << "ERROR: The message queue is empty. Cannot retrieve any element" << endl;
        return NULL;
    }

    Message* message = queue.front();
    queue.pop_front();

    return message;
}