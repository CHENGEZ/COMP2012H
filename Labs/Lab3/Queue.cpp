//
// Queue.cpp
//

#include "Queue.h"
#include "EthernetFrame.h"
#include <iostream>
#define debug 0
// TODO: task 3: queue operations

int myMin(const int &a, const int &b)
{
    return a < b ? a : b;
}

void queueResizeRing(Queue &queue, unsigned int newCapacity)
{
    EthernetFrame **newRing = new EthernetFrame *[newCapacity];
    for (int i = 0; i < newCapacity; i++) // make sure before doing anything, all elemments in new ring is just nullptr
    {
        newRing[i] = nullptr;
    }

    int backIndexOfOldArr = queue.capacity == 0 ? 0 : (queue.head + queue.size - 1) % queue.capacity;
    int shortage = 0, deleteIndex = 0;
    if (newCapacity < queue.size) // delete the last few frames according to the shortage
    {
        shortage = queue.size - newCapacity;
        for (int i = 0; i < shortage; i++)
        {
            deleteIndex = backIndexOfOldArr - i;
            while (deleteIndex < 0)
            {
                deleteIndex += queue.capacity;
            }
            freeFrame(queue.ring[deleteIndex]);
        }
    }

    int newSize = myMin(newCapacity, queue.size);
    int indexInOldRing = 0;

    for (int i = 0; i < newSize; i++) // fill the new array, and set index 0 to be the head
    {
        indexInOldRing = queue.head + i;
        while (indexInOldRing > queue.capacity - 1)
        {
            indexInOldRing -= queue.capacity;
        }
        newRing[i] = queue.ring[indexInOldRing];
    }

    queue.ring = newRing;
    queue.capacity = newCapacity;
    queue.head = 0;
    queue.size = newSize;
    return;
}

void enqueue(Queue &queue, EthernetFrame *frame)
{
    int curSize = queue.size;
    int curCapacity = queue.capacity;
    if (curSize == curCapacity)
    {
        queueResizeRing(queue, 2 * (curSize + 1));
    }
#if debug
    cout << "the capacity now is " << queue.capacity << endl;
    cout << "the size now is " << queue.size << endl;
#endif
    int backIndex = (queue.head + queue.size - 1) % queue.capacity;
    queue.ring[(backIndex + 1) % queue.capacity] = frame;
    queue.size++;
    return;
}

void dequeue(Queue &queue)
{
    if (queueIsEmpty(queue))
    {
        return;
    }

    int headIndex = queue.head;
    freeFrame(queue.ring[headIndex]);
    queue.ring[headIndex] = nullptr;
    int newHeadIndex = headIndex + 1;
    while (newHeadIndex > queue.capacity - 1)
    {
        newHeadIndex -= queue.capacity;
    }
    queue.head = newHeadIndex;
    queue.size--;
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
    delete[] queue.ring;
    queue.head = 0;
    queue.ring = nullptr;
    queue.capacity = 0;

    return;
}
