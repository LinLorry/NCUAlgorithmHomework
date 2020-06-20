#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <integer_division.h>

using ncu_algorithm_homework::integer_division;

using std::cout;
using std::endl;

static const long long n = 10000L, count = 5;
static const int count_max_length = 11;

int main()
{
    unsigned array[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/integer_division.log", std::ios_base::out | std::ios_base::app);
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

    for (size_t i = 1; i < count; i++)
    {
        const long number = i * 10;
        for (size_t j = 0; j < n; j++)
        {
            array[j] = number + rand() % 10;
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            integer_division(array[j], array[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << number << ":\t" << endTime - startTime << endl;
        cout << number << ":\t" << endTime - startTime << endl;
    }

    fout << "------------------------------------" << endl
         << endl;
    fout.close();

    return 0;
}

unsigned int ncu_algorithm_homework::integer_division(unsigned int n, unsigned int m)
{
    unsigned int p;
    if (n < 1 || m < 1)
        p = 0;
    else if (n == 1 || m == 1)
    {
        p = 1;
    }
    else if (n <= m)
    {
        p = integer_division(n, n - 1) + 1;
    }
    else
    {
        p = integer_division(n, m - 1) + integer_division(n - m, m);
    }
    return p;
}
