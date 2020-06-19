#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <loading.h>

using ncu_algorithm_homework::loading;
using std::cout;
using std::endl;

static const long long n = 10000L, count = 5;
static const int count_max_length = 11;

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
    std::ofstream fout("log/loading.log", std::ios_base::out | std::ios_base::app);
    time_t rawtime;
    struct tm *info;
    char time_str[80];

    srand((unsigned int)time(&rawtime));
    info = localtime(&rawtime);
    strftime(time_str, 80, "%Y-%m-%d %H:%M:%S", info);

    fout << "------------------------------------" << endl;
    fout << "Test time: " << time_str << endl;
    fout << "Test number: " << n << endl;
    fout << "------------------------------------" << endl;
    fout.width(count_max_length);
    fout << "Value number\tUse Time" << endl;

    for (size_t i = 0; i < count; i++)
    {
        const size_t number = pow(10, i + 1);
        for (size_t j = 0; j < n; j++)
        {
            array[j] = new int[number];
            result[j] = new bool[number];
            num[j] = number;
            max[j] = 0;
            for (size_t k = 0; k < number; k++)
            {
                array[j][k] = rand() % 100 + 1;
                max[j] += array[j][k];
                result[j][k] = false;
            }
            qsort(array[j], number, sizeof(int), comp);
            max[j] -= rand() % (max[j] - array[j][0]);
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            loading(max[j], array[j], result[j], num[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << number << ":\t" << endTime - startTime << endl;
        cout << number << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            delete array[j];
            delete result[j];
        }
    }
    fout << "------------------------------------" << endl
         << endl;
    fout.close();
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
