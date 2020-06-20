#include <iostream>
#include <fstream>
#include <n_quenns.h>

using ncu_algorithm_homework::n_quenns;
using std::cout;
using std::endl;

static const long long n = 1000, count = 20;
static const int count_max_length = 11;

int main()
{
    int x[20];

    clock_t startTime, endTime;
    std::ofstream fout("log/n_quenns.log", std::ios_base::out | std::ios_base::app);
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

    for (size_t i = 10; i < count; i++)
    {
        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            n_quenns(i, x);
        }
        endTime = clock();

        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << i << ":\t" << endTime - startTime << endl;
        cout << i << ":\t" << endTime - startTime << endl;
    }

    fout << "------------------------------------" << endl
         << endl;
    fout.close();

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
