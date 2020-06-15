#include <iostream>
#include <n_quenns.h>

using ncu_algorithm_homework::n_quenns;
using std::cout;
using std::endl;

int main()
{
    const long long n = 1000, count = 20;
    int *x;
    clock_t startTime, endTime;

    srand((unsigned int)time(NULL));

    for (size_t i = 10; i < count; i++)
    {
        x = new int[i];

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            n_quenns(i, x);
        }
        endTime = clock();
        cout << i << ": " << endTime - startTime << endl;
        for (size_t j = 0; j < i; j++)
        {
            cout << x[j] << " ";
        }
        cout << endl;

        delete[] x;
    }

    return 0;
}

namespace ncu_algorithm_homework
{
    static bool place(const int value, const int k, const int *const x)
    {
        for (size_t i = 0; i < k; i++)
        {
            if ((value == x[i]) || (abs(x[i] - value) == abs(i - k)))
            {
                return false;
            }
        }
        return true;
    }

    bool n_quenns(const int num, int *const x)
    {
        int k = 0;
        size_t i;
        for (i = 0; i < num; i++)
        {
            x[i] = -1;
        }

        while (true)
        {
            for (i = x[k] + 1; i < num; i++)
            {
                if (place(i, k, x))
                {
                    x[k] = i;
                    k++;
                    break;
                }
            }
            if (i == num)
            {
                x[k] = -1;
                if (k == 0)
                {
                    return false;
                }
                k--;
            }
            else if (k == num)
            {
                return true;
            }
        }
    }
} // namespace ncu_algorithm_homework
