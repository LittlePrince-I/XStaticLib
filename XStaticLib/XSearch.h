#pragma once

namespace xsl
{
    template <class Container, typename T>
    int linearSearch(const Container& container, const T& target, int startIndex, int endIndex)
    {
        for (int i = startIndex; i <= endIndex; ++i)
        {
            if (container[i] == target)
                return i;
        }
        return -1;
    }
    
    template<class Container, typename T>
    int binarySearch(const Container& container, const T target, int startIndex, int endIndex)
    {
        while (startIndex <= endIndex)
        {
            int midIndex = (startIndex + endIndex) / 2;
            if (container[midIndex] == target)
                return midIndex;
            if (container[midIndex] > target)
                endIndex = midIndex-1;
            else
                startIndex = midIndex + 1;
        }
        return -1;
    }
}