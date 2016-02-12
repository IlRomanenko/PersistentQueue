#pragma once


class IQueue
{
public:
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual bool empty() = 0;
};