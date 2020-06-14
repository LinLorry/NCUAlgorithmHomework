#include <iostream>
#include <graph_color.h>

using ncu_algorithm_homework::graph_color;
using std::cout;
using std::endl;

#define n 100
#define count 20

int main()
{
    int point_num;
    int color_num[n];
    int *points_color[n];
    bool *adjacency[n];

    clock_t startTime, endTime;

    srand((unsigned int)time(NULL));

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

        for (size_t j = 0; j < n; j++)
        {
            delete[] points_color[j];
            delete[] adjacency[j];
        }
        cout << i << ": " << endTime - startTime << endl;
    }
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
        size_t i, j;

        for (i = 0; i < point_num; i++)
        {
            points_color[i] = -1;
        }

        while (true)
        {
            if (step == point_num)
            {
                return true;
            }
            for (i = step; i < point_num; i++)
            {
                for (j = points_color[i] + 1; j < color_num; j++)
                {
                    if (check(i, j, points_color, adjacency + i * point_num))
                    {
                        points_color[i] = j;
                        step++;
                        break;
                    }
                }
                if (j == color_num)
                {
                    points_color[i] = -1;
                    step--;
                    break;
                }
            }
            if (step == -1 && points_color[0] == -1)
            {
                return false;
            }
        }
    }
} // namespace ncu_algorithm_homework
