#include <iostream>
#include <cstring>
#include <quit_sort.h>
#include <loading.h>
#include <cmath>

using ncu_algorithm_homework::loading;
using std::cin;
using std::cout;
using std::endl;

#define n 1000
#define count 5

int comp(const void *left, const void *right)
{
    return *(int *)left - *(int *)right;
}

int main()
{
    int num[n], max[n];
    int *array[n];
    bool *result[n];

    clock_t startTime, endTime;
    long long useTime[count];

    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            const size_t tmp = pow(10, i + 1);
            array[j] = new int[tmp];
            result[j] = new bool[tmp];
            num[j] = tmp;
            max[j] = 0;
            for (size_t k = 0; k < tmp; k++)
            {
                array[j][k] = rand() % 100 + 1;
                max[j] += array[j][k];
                result[j][k] = false;
            }
            qsort(array[j], tmp, sizeof(int), comp);
            max[j] -= rand() % (max[j] - array[j][0]);
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            loading(max[j], array[j], result[j], num[j]);
        }
        endTime = clock();
        useTime[i] = endTime - startTime;

        for (size_t j = 0; j < n; j++)
        {
            delete array[j];
            delete result[j];
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        cout << i << ": " << useTime[i] << endl;
    }
}

void ncu_algorithm_homework::loading(int max, int *w, bool *resutl, const unsigned int num)
{
    for (size_t i = 0; i < num; i++)
    {
        if (max - w[i] >= 0)
        {
            max -= w[i];
            resutl[i] = true;
        }
        else
            break;
    }
}
