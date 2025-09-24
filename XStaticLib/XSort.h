#pragma once
#include <vector>
#include <cmath>

namespace xsl
{
    template <class Container, typename T>
    Container& insertSort(Container& container, const int size)
    {
        for (int i = 1; i < size; i++)
        {
            T key = container[i];
            int j = i - 1;
            while (j >= 0 && container[j] > key)
            {
                container[j + 1] = container[j];
                j--;
            }
            container[j + 1] = key;
        }

        return container;
    }

    template <class Container, typename T>
    Container& shellSort(Container& container, const int size)
    {
        for (int gap = size / 2;gap > 0; gap /= 2)
        {
            for (int i = gap; i < size; i+=gap)
            {
                T key = container[i];
                int j = i - gap;
                while (j >= 0 && container[j] > key)
                {
                    container[j + gap] = container[j];
                    j -= gap;
                }
                container[j + gap] = key;
            }
        }
        return container;
    }

    template<class Container, typename T>
    Container& quickSort(Container& container, const int size)
    {
        T pivot = container[0];
        T* left = &container[0];
        T* right = &container[size - 1];
        
    }
}