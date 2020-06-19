#include <quit_sort.h>
#include <iostream>
#include <fstream>
#include <cmath>

using ncu_algorithm_homework::quick_sort;
using std::cout;
using std::endl;

static const long long n = 10000L, count = 5;
static const int count_max_length = 11;

int main()
{
    array_type arrays[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/quick_sort.log", std::ios_base::out | std::ios_base::app);
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
        const int number = pow(10, i + 1);
        for (size_t j = 0; j < n; j++)
        {
            for (size_t k = 0; k < number; k++)
            {
                arrays[j].push_back(rand());
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            quick_sort(arrays[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << number << ":\t" << endTime - startTime << endl;
        cout << number << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            arrays[j].clear();
        }
    }

    fout << "------------------------------------" << endl
         << endl;
    fout.close();

    return 0;
}

namespace ncu_algorithm_homework
{
    static size_t partition(array_type &array, const int p, const int r)
    {
        const int x = array[p];
        int i = p, j = r + 1;
        while (true)
        {
            while (x < array[--j])
                ;
            while (x > array[++i] && i < r)
                ;
            if (i < j)
            {
                array[i] ^= array[j];
                array[j] ^= array[i];
                array[i] ^= array[j];
            }
            else
            {
                return j;
            }
        }
    }

    static void quick_sort(array_type &array, int p, int r)
    {
        if (p < r)
        {
            const int q = partition(array, p, r);
            if (q != p)
            {
                array[q] ^= array[p];
                array[p] ^= array[q];
                array[q] ^= array[p];
            }

            quick_sort(array, p, q - 1);
            quick_sort(array, q + 1, r);
        }
    }

    void quick_sort(array_type &array)
    {
        quick_sort(array, 0, array.size());
    }

} // namespace ncu_algorithm_homework
