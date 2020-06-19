#include <iostream>
#include <fstream>
#include <huffman.h>

using ncu_algorithm_homework::huffman;
using ncu_algorithm_homework::Node;
using std::cout;
using std::endl;

static const long long n = 100000L, count = 20;
static const int count_max_length = 11;

int main()
{
    int *values_p[n];
    float *ps_p[n];
    Node<int> *nodes_p[n];

    clock_t startTime, endTime;
    std::ofstream fout("log/huffman.log", std::ios_base::out | std::ios_base::app);
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

    for (size_t i = 2; i < count; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            values_p[j] = new int[i];
            ps_p[j] = new float[i];
            nodes_p[j] = new Node<int>[2 * i - 1];
            for (size_t k = 0; k < i; k++)
            {
                values_p[j][k] = rand();
                ps_p[j][k] = (float)rand();
            }
        }

        startTime = clock();
        for (size_t j = 0; j < n; j++)
        {
            huffman(values_p[j], ps_p[j], i, nodes_p[j]);
        }
        endTime = clock();
        fout.width(count_max_length);
        cout.width(count_max_length);
        fout << i << ":\t" << endTime - startTime << endl;
        cout << i << ":\t" << endTime - startTime << endl;

        for (size_t j = 0; j < n; j++)
        {
            delete values_p[j];
            delete ps_p[j];
            delete nodes_p[j];
        }
    }
    fout << "------------------------------------" << endl;

    fout << endl;
    fout.close();
}

namespace ncu_algorithm_homework
{
    template <typename T>
    class huffman_compare
    {
    public:
        bool operator()(const Node<T> *r, const Node<T> *l)
        {
            return r->p > l->p;
        }
    };

    template <typename T>
    void huffman(const T *const array, const float *const p, const int n, Node<T> *const nodes)
    {
        Node<T> *left, *right, *parent;
        std::priority_queue<Node<T> *, std::vector<Node<T> *>, huffman_compare<T>> heap;

        for (int i = 0; i < n; ++i)
        {
            nodes[i].c = array[i];
            nodes[i].p = p[i];
            nodes[i].parent = NULL;
            nodes[i].left = NULL;
            nodes[i].right = NULL;
            heap.push(nodes + i);
        }

        for (int i = 0; i < n - 1; ++i)
        {
            parent = nodes + n + i;
            left = heap.top();
            heap.pop();
            right = heap.top();
            heap.pop();
            parent->c = 0;
            parent->p = left->p + right->p;
            parent->left = left;
            parent->right = right;
            parent->parent = NULL;

            left->parent = right->parent = parent;

            heap.push(parent);
        }
    }
} // namespace ncu_algorithm_homework
