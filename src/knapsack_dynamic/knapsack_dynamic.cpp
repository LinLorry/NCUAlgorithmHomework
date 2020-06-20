#include <cmath>
#include <iostream>
#include <fstream>
#include <knapsack_dynamic.h>

using ncu_algorithm_homework::knapsack_dynamic;
using std::cout;
using std::endl;

template <>
int ncu_algorithm_homework::knapsack_dynamic<int>(int *w, int *p, int n, int m, bool *x);

static const long long n = 1000L, count = 60;
static const int count_max_length = 11;

int main()
{
    int max[n];
    int *w[n], *p[n];
    bool *x[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/knapsack_dynamic.log", std::ios_base::out | std::ios_base::app);
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
    fout << "Point number\tUse Time" << endl;

    for (size_t i = 1; i < count; i++)
    {
        const int number = i * 10;
        for (size_t j = 0; j < n; j++)
        {
            w[j] = new int[number];
            p[j] = new int[number];
            x[j] = new bool[number + 1];
            max[j] = 0;
            for (size_t k = 0; k < number; k++)
            {
                w[j][k] = rand() % 10 + 1;
                p[j][k] = rand() % 10 + 1;
                max[j] += w[j][k];
                x[j][k] = false;
            }
            max[j] -= rand() % (max[j] - w[j][0]);
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            knapsack_dynamic<int>(w[j], p[j], number, max[j], x[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << number << ":\t" << endTime - startTime << endl;
        cout << number << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            delete w[j];
            delete p[j];
            delete x[j];
        }
    }
    fout << "------------------------------------" << endl
         << endl;
    fout.close();
    return 0;
}

template <>
int ncu_algorithm_homework::knapsack_dynamic<int>(int *w, int *p, int n, int m, bool *x)
{
    int i, j, k;
    int v, optp[n + 1][m + 1];

    for (i = 0; i <= n; i++)
    {
        optp[i][0] = 0;
        x[i] = false;
    }

    for (i = 0; i <= m; i++)
    {
        optp[0][i] = 0;
    }

    for (i = 1; i <= n; i++)
    {
        const int tmp_w = w[i - 1];
        for (j = 1; j <= m; j++)
        {
            optp[i][j] = optp[i - 1][j];
            if ((j >= tmp_w) && (optp[i - 1][j - tmp_w] + p[i - 1] > optp[i - 1][j]))
            {
                optp[i][j] = optp[i - 1][j - tmp_w] + p[i - 1];
            }
        }
    }
    j = m;
    for (i = n; i > 0; i--)
    {
        if (optp[i][j] > optp[i - 1][j])
        {
            x[i] = true;
            j = j - w[i - 1];
        }
    }

    v = optp[n][m];
    return v;
}
