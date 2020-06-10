#include <quit_sort.h>

using ncu_algorithm_homework::quick_sort;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    size_t number;
    array_type array;

    cout << "Please input the number of array: ";
    cin >> number;

    cout << "Please input the array element: ";
    array = array_type(number);
    for (size_t i = 0; i < number; i++)
    {
        cin >> array[i];
    }

    quick_sort(array, 0, number - 1);

    cout << "Quick sort result: ";
    for (size_t i = 0; i < number; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}

namespace ncu_algorithm_homework
{
    size_t partition(array_type &array, const int p, const int r)
    {
        const int x = array[p];
        int i = p, j = r + 1;
        while (true)
        {
            while (x < array[--j])
                ;
            while (x > array[++i] && i < r)
                ;
            if (i < j)
            {
                array[i] ^= array[j];
                array[j] ^= array[i];
                array[i] ^= array[j];
            }
            else
            {
                return j;
            }
        }
    }

    void quick_sort(array_type &array, int p, int r)
    {
        if (p < r)
        {
            const int q = partition(array, p, r);
            if (q != p)
            {
                array[q] ^= array[p];
                array[p] ^= array[q];
                array[q] ^= array[p];
            }

            quick_sort(array, p, q - 1);
            quick_sort(array, q + 1, r);
        }
    }

} // namespace ncu_algorithm_homework
