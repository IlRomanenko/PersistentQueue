#pragma once
#include "IQueue.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <cassert>

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
            assert(R.size() == Rc.size());
            toCopy = R.size();
            copied = false;
            checkNormal();
        }
    }

    void additionalOperations()
    {
        // Нам достаточно 3 операций на вызов
        int toDo = 3;
        // Пытаемся перекопировать R в S
        while (!copied && toDo > 0 && R.size() > 0)
        {
            S.push(R.top());
            R.pop();
            toDo = toDo - 1;
        }
        // Пытаемся перекопировать L в R и Rc'
        while (toDo > 0 && L.size() > 0)
        {
            copied = true;
            int x = L.top();
            L.pop();
            R.push(x);
            Rc_.push(x);
            toDo = toDo - 1;
        }
        // Пытаемся перекопировать S в R и Rc' с учетом toCopy
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
        // Если все скопировано, то меняем роли L, L' и Rc, Rc'
        if (S.size() == 0)
        {
            swap(L, L_);
            swap(Rc, Rc_);
        }
    }
    void checkNormal()
    {
        additionalOperations();
        // Если мы не все перекопировали, то у нас не пуст стек S
        recopy = S.size() != 0;
    }

    void printStack(stack<int> &st)
    {
        vector<int> temp;
        while (st.size() != 0)
        {
            temp.push_back(st.top());
            st.pop();
        }
        for_each(temp.begin(), temp.end(), [](int x) { cout << x << ' '; });
        for_each(temp.rbegin(), temp.rend(), [&st](int x) { st.push(x); });
    }

public:
    PersistentQueue()
    {
        copied = recopy = false;
        toCopy = 0;
    }

    void push(int x)
    {
        if (!recopy)
        {
            L.push(x);
            if (Rc_.size() > 0)
                Rc_.pop();
            checkRecopy();
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
            if (Rc_.size() > 0)
                Rc_.pop();
            checkRecopy();
            return tmp;
        }
        else
        {
            int tmp;
            if (toCopy > 0)
            {
                tmp = Rc.top();
                Rc.pop();
                toCopy--;
            }
            else
            {
                tmp = R.top();
                R.pop();
                Rc_.pop();
            }
            checkNormal();
            return tmp;
        }
    }


    bool empty()
    {
        return !recopy && R.size() == 0;
    }


    void print()
    {
        cout << "toCopy = " << toCopy << "  copied = " << copied << "   recopy = " << recopy << endl;
        cout << "L = " << endl;
        printStack(L);
        cout << endl << endl;

        cout << "L' = " << endl;
        printStack(L_);
        cout << endl << endl;

        cout << "R = " << endl;
        printStack(R);
        cout << endl << endl;

        cout << "S = " << endl;
        printStack(S);
        cout << endl << endl;

        cout << "Rc = " << endl;
        printStack(Rc);
        cout << endl << endl;

        cout << "Rc' = " << endl;
        printStack(Rc_);
        cout << endl << endl;
        cout << endl << endl << endl << endl << endl << endl;
    }
};