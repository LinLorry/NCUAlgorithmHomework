#include <fstream>
#include <iostream>
#include <graph_color.h>

using ncu_algorithm_homework::graph_color;
using std::cout;
using std::endl;

static const long long n = 1000, count = 30;
static const int count_max_length = 11;

int main()
{
    int point_num;
    int color_num[n];
    int *points_color[n];
    bool *adjacency[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/graph_color.log", std::ios_base::out | std::ios_base::app);
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

    for (size_t i = 10; i < count; i++)
    {
        point_num = i + 2;
        for (size_t j = 0; j < n; j++)
        {
            color_num[j] = rand() % point_num;
            points_color[j] = new int[point_num];
            adjacency[j] = new bool[point_num * point_num];
            for (size_t k = 0; k < point_num; k++)
            {
                for (size_t l = 0; l < point_num; l++)
                {
                    *(adjacency[j] + k * point_num + l) = rand() % 2;
                }
                *(adjacency[j] + k * point_num + k) = true;
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            graph_color(color_num[j], points_color[j], point_num, adjacency[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << point_num << ":\t" << endTime - startTime << endl;
        cout << point_num << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            delete[] points_color[j];
            delete[] adjacency[j];
        }
    }
    fout << "------------------------------------" << endl
         << endl;
    fout.close();
}

namespace ncu_algorithm_homework
{
    static bool check(int c_p, const int point_color, int *points_color, const bool *adjacency) //检查第i个顶点的颜色是否满足条件
    {
        for (int i = 0; i < c_p; i++)
        {
            if (adjacency[i] && point_color == points_color[i]) //k与i之间相连并且i顶点的颜色与k顶点的颜色相同
                return false;
        }
        return true;
    }

    bool graph_color(const int color_num, int *const points_color, const int point_num, const bool *const adjacency)
    {
        int step = 0;
        size_t i;

        for (i = 0; i < point_num; i++)
        {
            points_color[i] = -1;
        }

        while (true)
        {
            for (i = points_color[step] + 1; i < color_num; i++)
            {
                if (check(step, i, points_color, adjacency + step * point_num))
                {
                    points_color[step] = i;
                    step++;
                    break;
                }
            }

            if (i == color_num)
            {
                points_color[step] = -1;
                if (step == 0)
                {
                    return false;
                }
                step--;
            }
            else if (step == point_num)
            {
                return true;
            }
        }
    }
} // namespace ncu_algorithm_homework
