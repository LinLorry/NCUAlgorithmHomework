#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <lcs.h>

using ncu_algorithm_homework::lcs;
using std::cout;
using std::endl;
using std::string;

static const long long n = 10000L, count = 4;
static const int count_max_length = 11;

int main()
{
    string f_strs[n], s_strs[n];
    char buffer[100000];

    clock_t startTime, endTime;
    std::ofstream fout("log/lcs.log", std::ios_base::out | std::ios_base::app);
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

    for (size_t i = 0; i < count; i++)
    {
        const int number = pow(5, i + 1);
        const int tmp = number / 10;
        const int f_len = tmp + rand() % (number - tmp);
        const int s_len = tmp + rand() % (number - tmp);
        for (size_t j = 0; j < n; j++)
        {
            f_strs[j].reserve(number + 1);
            s_strs[j].reserve(number + 1);
            for (size_t k = 0; k < f_len; k++)
            {
                f_strs[j] = f_strs[j] + (char)(rand());
            }
            for (size_t k = 0; k < s_len; k++)
            {
                s_strs[j] = s_strs[j] + (char)(rand());
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            lcs(f_strs[j].c_str(), s_strs[j].c_str(), buffer, f_len, s_len);
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

int ncu_algorithm_homework::lcs(const char *A, const char *B, char *C, const int n, const int m)
{
    const int base = m + 1;
    int i, j, k, len;
    int L[n + 1][m + 1];
    int s[n + 1][m + 1];

    for (i = 0; i <= n; i++)
    {
        L[i][0] = 0;
    }
    for (i = 0; i <= m; i++)
    {
        L[0][i] = 0;
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (A[i] == B[j])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
                s[i][j] = 1;
            }
            else if (L[i - 1][j] >= L[i][j - 1])
            {
                L[i][j] = L[i - 1][j];
                s[i][j] = 2;
            }
            else
            {
                L[i][j] = L[i][j - 1];
                s[i][j] = 3;
            }
        }
    }

    i = n;
    j = m;
    k = len = L[i][j];

    while ((i != 0) && (j != 0))
    {
        switch (s[i][j])
        {
        case 1:
            C[k] = A[i];
            k--;
            j--;
        case 2:
            i--;
            break;
        case 3:
            j--;
            break;
        }
    }

    return len;
}
