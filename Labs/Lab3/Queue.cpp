//
// Queue.cpp
//

#include "Queue.h"
#include "EthernetFrame.h"
#include <iostream>

// TODO: task 3: queue operations

void queueResizeRing(Queue &queue, unsigned int newCapacity)
{

    EthernetFrame **newArr = new EthernetFrame *[newCapacity];

    int shortage = 0;
    int back = queue.capacity == 0 ? 0 : (queue.head + queue.size - 1) % queue.capacity;
    int deleteCnt = 0, deleteIndex = 0;

    if (newCapacity < queue.size)
    {
        shortage = queue.size - newCapacity;
        while (deleteCnt < shortage)
        {
            deleteIndex = back - deleteCnt >= 0 ? back - deleteCnt : queue.capacity + (back - deleteCnt);
            freeFrame(queue.ring[deleteIndex]);
            deleteCnt++;
        }
    }

    int newSize = newCapacity <= queue.size ? newCapacity : queue.size;
    for (int i = 0; i < newSize; i++)
    {
        newArr[i] = queue.ring[(queue.head + i) % queue.capacity];
    }

    queue.ring = newArr;
    queue.capacity = newCapacity;
    queue.size = newSize;
    queue.head = 0;

    return;
}

void enqueue(Queue &queue, EthernetFrame *frame)
{
    if (queue.size == queue.capacity)
    {
        queueResizeRing(queue, (queue.size + 1) * 2);
    }
    queue.ring[(queue.head + queue.size - 1) % queue.capacity] = frame;
    queue.size++;
    return;
}

void dequeue(Queue &queue)
{
    if (queue.size == 0)
        return;
    else
    {
        freeFrame(queue.ring[queue.head]);
    }
    queue.size--;
    return;
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
