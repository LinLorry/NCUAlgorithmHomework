#include <iostream>
#include <pow.h>
#include <time.h>

using ncu_algorithm_homework::pow;

using std::cin;
using std::cout;
using std::endl;

int main()
{
    const long long n = 10000L, count = 10;
    int p[n];
    double b[n], reuslt[n];
    clock_t startTime, endTime;
    long long useTime[count] = {0};

    for (size_t i = 0; i < count; i++)
    {
        useTime[i] = 0;

        for (size_t j = 0; j < n; j++)
        {
            b[j] = rand() % 100;
            if (i == 0)
            {
                p[j] = 1;
            }
            else
            {
                p[j] = (long)pow(10, i - 1) + rand() % ((long)pow(10, i) - (long)pow(10, i - 1));
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            reuslt[j] = pow(b[j], p[j]);
        }
        endTime = clock();
        useTime[i] = endTime - startTime;
    }

    for (size_t i = 0; i < count; i++)
    {
        cout << i << ": " << (double)useTime[i] / CLOCKS_PER_SEC << endl;
    }
}

double ncu_algorithm_homework::pow(const double b, const int p)
{
    if (p == 0)
        return 1;
    else if (p == 1)
        return b;
    else if (p % 2)
    {
        const double tmp = pow(b, p / 2);
        return tmp * tmp * b;
    }
    else
    {
        const double tmp = pow(b, p / 2);
        return tmp * tmp;
    }
}
