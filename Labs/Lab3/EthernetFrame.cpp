//
// EthernetFrame.cpp
//

#include "EthernetFrame.h"

// TODO: task 1: initialize & swap EthernetFrame

void initFrame(EthernetFrame &frame, const string &source, const string &destination,
               const string &payload, EtherType type)
{
    frame.source = source;
    frame.destination = destination;
    frame.payload = payload;
    frame.type = type;
    return;
}

void initFrame(EthernetFrame *frame, const string &source, const string &destination,
               const string &payload, EtherType type)
{
    if (frame == nullptr)
        return;
    (*frame).source = source;
    (*frame).destination = destination;
    (*frame).payload = payload;
    (*frame).type = type;
    return;
}

void swapFrames(EthernetFrame &frame1, EthernetFrame &frame2)
{
    EthernetFrame tempFrame = frame1;
    frame1 = frame2;
    frame2 = tempFrame;
    return;
}

void swapFrames(EthernetFrame *frame1, EthernetFrame *frame2)
{
    if (frame1 == nullptr || frame2 == nullptr)
        return;
    if (frame1 == frame2)
        return;
    EthernetFrame tempFrame = *frame1;
    *frame1 = *frame2;
    *frame2 = tempFrame;
    return;
}

// TODO: task 2: create & free EthernetFrame

EthernetFrame *createFrame(const string &source, const string &destination, const string &payload, EtherType type)
{
    EthernetFrame *frame = new EthernetFrame;
    *frame->destination = destination;
    *frame->source = source;
    *frame->payload = payload;
    *frame->type = type;
    return frame;
}

void freeFrame(EthernetFrame *frame)
{
    delete frame;
    frame = nullptr;
    return;
}
