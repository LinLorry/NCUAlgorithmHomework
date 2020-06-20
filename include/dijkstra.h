#ifndef NCU_ALGORITHM_HOMEWOKR_CONVOLUTION
#define NCU_ALGORITHM_HOMEWOKR_CONVOLUTION

namespace ncu_algorithm_homework
{
    typedef struct adj_list
    {
        int v_num;
        float len;
        struct adj_list *next;
    } Node;

    void dijkstra(Node *nodes, int n, int u, float *d, int *p);
} // namespace ncu_algorithm_homework

#endif // NCU_ALGORITHM_HOMEWOKR_CONVOLUTION
