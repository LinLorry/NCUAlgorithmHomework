#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dijkstra.h>

using ncu_algorithm_homework::dijkstra;
using ncu_algorithm_homework::Node;
using std::cout;
using std::endl;

static const long long n = 100000L, count = 10;
static const int count_max_length = 11;

static void free_node(const Node *p)
{
    if (NULL != p->next)
    {
        free_node(p->next);
    }
    delete p;
}

int main()
{
    Node *nodes[n];
    float d[count];
    int p[count];

    clock_t startTime, endTime;
    std::ofstream fout("log/dijkstra.log", std::ios_base::out | std::ios_base::app);
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
        const long number = i;
        for (size_t j = 0; j < n; j++)
        {
            nodes[j] = new Node[number];
            for (size_t k = 0; k < number; k++)
            {
                nodes[j][k].v_num = k;
                nodes[j][k].len = rand() % 10;
                Node *node_p = &(nodes[j][k]);
                int tmp = 0;
                for (size_t l = 0; l < 5; l++)
                {
                    node_p->next = new Node();
                    node_p = node_p->next;
                    node_p->v_num = tmp + rand() % (number - tmp);
                    tmp = node_p->v_num;
                }
                node_p->next = NULL;
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            dijkstra(nodes[j], number, 0, d, p);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << number << ":\t" << endTime - startTime << endl;
        cout << number << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            for (size_t k = 0; k < number; k++)
            {
                free_node(nodes[j][k].next);
            }

            delete nodes[j];
        }
    }

    fout << "------------------------------------" << endl
         << endl;
    fout.close();

    return 0;
}

void ncu_algorithm_homework::dijkstra(Node *nodes, int n, int u, float *d, int *p)
{
    float temp;
    int i, j, t;
    bool s[n];
    Node *pnode;
    for (i = 0; i < n; i++)
    {
        d[i] = MAXFLOAT;
        s[i] = false;
        p[i] = -1;
    }
    if (!(pnode = nodes[u].next))
    {
        return;
    }
    while (pnode)
    {
        d[pnode->v_num] = pnode->len;
        p[pnode->v_num] = u;
        pnode = pnode->next;
    }
    d[u] = 0;
    s[u] = true;

    for (i = 1; i < n; i++)
    {
        temp = MAXFLOAT;
        t = u;
        for (j = 0; j < n; j++)
        {
            if (!s[i] && d[j] < temp)
            {
                t = j;
                temp = d[j];
            }
        }
        if (t == u)
        {
            break;
        }
        s[t] = true;
        pnode = nodes[t].next;
        while (pnode)
        {
            if (!s[pnode->v_num] && d[pnode->v_num] > (d[t] + pnode->len))
            {
                d[pnode->v_num] = d[t] + pnode->len;
                p[pnode->v_num] = t;
            }
            pnode = pnode->next;
        }
    }
}
