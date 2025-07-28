#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "XArray.h"

namespace XSL
{
    template <typename T>
    int BinarySearch(std::vector<T>& arr, T& key)
    {
        int startIndex = 0;
        int midIndex;
        int endIndex = arr.size()-1;

        while (startIndex <= endIndex)
        {

            midIndex = (startIndex + endIndex) / 2;
            if (arr[midIndex] < key)
                startIndex = midIndex + 1;
            else if (arr[midIndex] > key)
                endIndex = midIndex - 1;
            else
                return midIndex;
            
        }    
        return -1;
    };

    template <typename T>
    int BinarySearch(std::vector<T>& arr, T& key, int& startIndex, int& endIndex)
    {

        int midIndex;

        while (startIndex <= endIndex)
        {

            midIndex = (startIndex + endIndex) / 2;
            if (arr[midIndex] < key)
                startIndex = midIndex + 1;
            else if (arr[midIndex] > key)
                endIndex = midIndex - 1;
            else
                return midIndex;

        }
        return -1;
    };

    template <typename T, size_t N>
    int BinarySearch(XSL::XArray<T, N>& arr, T& key)
    {
        int startIndex = 0;
        int midIndex;
        int endIndex = arr.Size() - 1;

        while (startIndex <= endIndex)
        {

            midIndex = (startIndex + endIndex) / 2;
            if (arr[midIndex] < key)
                startIndex = midIndex + 1;
            else if (arr[midIndex] > key)
                endIndex = midIndex - 1;
            else
                return midIndex;

        }
        return -1;
    };

    template <typename T, size_t N>
    int BinarySearch(XSL::XArray<T, N>& arr, T& key, int& startIndex, int& endIndex)
    {

        int midIndex;

        while (startIndex <= endIndex)
        {

            midIndex = (startIndex + endIndex) / 2;
            if (arr[midIndex] < key)
                startIndex = midIndex + 1;
            else if (arr[midIndex] > key)
                endIndex = midIndex - 1;
            else
                return midIndex;

        }
        return -1;
    };
}