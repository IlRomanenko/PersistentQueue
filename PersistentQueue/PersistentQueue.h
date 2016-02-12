#pragma once
#include "IQueue.h"

class PersistentQueue : IQueue
{
    bool copied, recopy;
    int to_copy;
public:
    PersistentQueue()
    {
        copied = recopy = 0;
        to_copy = 0;
    }

    int pop()
    {
        if !recopy
        {
            T tmp = R.pop()
            Rc.pop()
            if Rc'.size > 0
                Rc'.pop()
                checkRecopy()
                return tmp
            else
                T tmp = Rc.pop()
                if toCopy > 0
                    toCopy = toCopy - 1
                else
                    R.pop()
                    Rc'.pop()
                    checkNormal()
                    return tmp
        }
    }
};