#include <iostream>
#include <fstream>
#include <pow.h>

using ncu_algorithm_homework::pow;

using std::cout;
using std::endl;

static const long long n = 100000L, count = 10;
static const int count_max_length = 11;

int main()
{
    int p[n];
    double b[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/pow.log", std::ios_base::out | std::ios_base::app);
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
        const long number = (long)pow(10, i);
        for (size_t j = 0; j < n; j++)
        {
            b[j] = rand() % 100;
            if (i == 0)
            {
                p[j] = 1;
            }
            else
            {
                p[j] = number + rand() % ((long)pow(10, i + 1) - number);
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            pow(b[j], p[j]);
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
