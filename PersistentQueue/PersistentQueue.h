#pragma once
#include "IQueue.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

class PersistentQueue : IQueue
{
    bool copied, recopy;
    int toCopy;

    stack<int> L, R, S, Rc_, L_, Rc;

    void checkRecopy()
    {
        bool recopy = L.size() > R.size();
        if (recopy)
        {
            toCopy = R.size();
            copied = false;
            checkNormal();
        }
    }

    void additionalOperations()
    {
        // ��� ���������� 3 �������� �� �����
        int toDo = 3;
        // �������� �������������� R � S
        while (!copied && toDo > 0 && R.size() > 0)
        {
            S.push(R.top());
            R.pop();
            toDo = toDo - 1;
        }
        // �������� �������������� L � R � Rc'
        while (toDo > 0 && L.size() > 0)
        {
            copied = true;
            int x = L.top();
            L.pop();
            R.push(x);
            Rc_.push(x);
            toDo = toDo - 1;
        }
        // �������� �������������� S � R � Rc' � ������ toCopy
        while (toDo > 0 && S.size() > 0)
        {
            int x = S.top();
            S.pop();
            if (toCopy > 0)
            {
                R.push(x);
                Rc_.push(x);
                toCopy = toCopy - 1;
            }
            toDo = toDo - 1;
        }
        // ���� ��� �����������, �� ������ ���� L, L' � Rc, Rc'
        if (S.size() == 0)
        {
            swap(L, L_);
            swap(Rc, Rc_);
        }
    }
    void checkNormal()
    {
        additionalOperations();
        // ���� �� �� ��� ��������������, �� � ��� �� ���� ���� S
        recopy = S.size() != 0;
    }

public:
    PersistentQueue()
    {
        copied = recopy = 0;
        toCopy = 0;
    }

    void push(int x)
    {
        if (!recopy)
        {
            L.push(x);
            if (Rc_.size() > 0)
            {
                Rc_.pop();
                checkRecopy();
            }
        }
        else
        {
            L_.push(x);
            checkNormal();
        }
    }


    int pop()
    {
        if (!recopy)
        {
            int tmp = R.top();
            R.pop();
            Rc.pop();
            if (Rc.size() > 0)
            {
                Rc.pop();
                checkRecopy();
                return tmp;
            }
            else
            {
                int tmp = Rc.top();
                Rc.pop();
                if (toCopy > 0)
                    toCopy = toCopy - 1;
                else
                {
                    R.pop();
                    Rc.pop();
                    checkNormal();
                    return tmp;
                }
            }
        }
    }

    bool empty()
    {
        return !recopy && R.size() == 0;
    }

};