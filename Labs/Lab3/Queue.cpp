//
// Queue.cpp
//

#include "Queue.h"
#include "EthernetFrame.h"
#include <iostream>

// TODO: task 3: queue operations

void queueResizeRing(Queue &queue, unsigned int newCapacity)
{
    
}

void enqueue(Queue &queue, EthernetFrame *frame)
{
}

void dequeue(Queue &queue)
{
}

const EthernetFrame *queueFront(const Queue &queue)
{
    if (queue.size == 0)
        return nullptr;
    else
        return queue.ring[queue.head];
}

const EthernetFrame *queueBack(const Queue &queue)
{
    if (queue.size == 0)
        return nullptr;
    else
        return queue.ring[(queue.head + queue.size - 1) % queue.capacity];
}

bool queueIsEmpty(const Queue &queue)
{
    if (queue.size > 0)
        return false;
    else
        return true;
}

void freeQueue(Queue &queue)
{
    int curSize = queue.size;
    for (int i = 0; i < curSize; i++)
    {
        freeFrame(queue.ring[i]);
        queue.size--;
    }
    queue.head = 0;

    return;
}
