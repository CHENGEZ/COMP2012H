//
// Queue.cpp
//

#include "Queue.h"
#include "EthernetFrame.h"

// TODO: task 3: queue operations

void queueResizeRing(Queue &queue, unsigned int newCapacity)
{
    EthernetFrame **newArr = new EthernetFrame *[newCapacity];
    int shortage = 0;
    if (newCapacity < queue.size)
    {
        shortage = queue.size - newCapacity;
        for (int i = newCapacity; i < shortage; i++)
        {
            delete queue.ring[i];
        }
    }
    else
    {
        for (int i = 0; i < queue.size; i++)
        {
            newArr[i] = queue.ring[i];
        }
    }

    queue.ring = newArr;
    queue.capacity = newCapacity;
    queue.size = newCapacity < queue.size ? newCapacity : queue.size;

    return;
}

void enqueue(Queue &queue, EthernetFrame *frame)
{
    if (queue.size == queue.capacity)
    {
        queueResizeRing(queue, (queue.size + 1) * 2);
    }

    queue.ring[queue.size] = frame;
    return;
}

void dequeue(Queue &queue)
{
    if (queue.size == 0)
        return;
    else
    {
        freeFrame(queue.ring[0]);
        queue.ring[0] = nullptr;
    }
    return;
}

const EthernetFrame *queueFront(const Queue &queue)
{
    if (queue.size == 0)
        return nullptr;
    else
        return queue.ring[0];
}

const EthernetFrame *queueBack(const Queue &queue)
{
    if (queue.size == 0)
        return nullptr;
    else
        return queue.ring[queue.size - 1];
}

bool queueIsEmpty(const Queue &queue)
{
    if (queue.size > 0)
        return true;
    else
        return false;
}

void freeQueue(Queue &queue)
{
    int curSize = queue.size;
    for (int i = 0; i < curSize; i++)
    {
        delete queue.ring[i];
        queue.ring[i] = nullptr;
        queue.size--;
    }

    return;
}
