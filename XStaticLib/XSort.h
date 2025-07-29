#pragma once
#include <string>
#include <vector>

namespace xsl
{
    inline bool Compare(const char*& str1, const char*& str2)
    {
        return strcmp(str1, str2);
    }

    template <typename T>
    std::vector<T>& InsertSort(std::vector<T>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }

        return arr;
    }

    template <>
    std::vector<const char*>& InsertSort(std::vector<const char*>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            const char* key = arr[i];
            int j = i - 1;
            while (j >= 0 && strcmp(arr[j], key) > 0)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }

        return arr;
    }
}