#ifndef NCU_ALGORITHM_HOMEWOKR_HUFFMAN
#define NCU_ALGORITHM_HOMEWOKR_HUFFMAN

#include <iostream>
#include <queue>

namespace ncu_algorithm_homework
{

    template <typename T>
    struct Node
    {
        T c;
        float p;
        Node *parent;
        Node *left;
        Node *right;
    };

    template <typename T>
    void huffman(const T *const array, const float *const p, const int n, Node<T> *const nodes);

} // namespace ncu_algorithm_homework

#endif // NCU_ALGORITHM_HOMEWOKR_HUFFMAN
