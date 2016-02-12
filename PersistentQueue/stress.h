#include <vector>
#include <queue>
#include <cstdlib>
#include "PersistentQueue.h"

using namespace std;

void stress(int all, double pushProbability)
{
    PersistentQueue qToCheck;
    queue<int> qTrue;
    for (int i = 0; i < all; ++i) {
        if (rand() / (double)RAND_MAX <= pushProbability) {
            add(qToCheck, qTrue, rand());
        } else {
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
    int numTests = 1000;
    for (int i = 0; i < numTests; ++i) {
        stress((i + 1) * 10, rand() / (double)RAND_MAX);
    }
    return 0;
}
