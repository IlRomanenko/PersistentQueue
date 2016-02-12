#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <queue>
#include <cstdlib>
#include "PersistentQueue.h"

using namespace std;

void add(PersistentQueue &q1, queue<int> &q2, int elem)
{
    q1.push(elem);
    q2.push(elem);
}

void stress(int all, double pushProbability)
{
    PersistentQueue qToCheck;
    queue<int> qTrue;
    for (int i = 0; i < all; ++i) {
        if (rand() / (double)RAND_MAX <= pushProbability) {
            add(qToCheck, qTrue, rand());
        } else if (!qTrue.empty()) {
            if (qTrue.empty() ^ qToCheck.empty())
            {
                cout << "ALARM!!!";
                exit(0);
            }
            qToCheck.print();
            int p1 = qTrue.front();
            qTrue.pop();
            int p2 = qToCheck.pop();
            if (p1 != p2) {
                cout << "err" << endl;
            }
        }
    }
}

int main()
{
    freopen("output.txt", "w", stdout);
    int numTests = 1000;
    for (int i = 0; i < numTests; ++i) {
        cout << i << endl;
        for (int j = 0; j <= 100; ++j) {
            stress((i + 1) * 10, j / 100.0);
        }
    }
    return 0;
}
