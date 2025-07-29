#pragma once

namespace xsl
{
    template<class Container, typename T>
    int BinarySearch(const Container& container, const T value, int startIndex, int endIndex)
    {
        while (startIndex <= endIndex)
        {
            int midIndex = (startIndex + endIndex) / 2;
            if (container[midIndex] == value)
                return midIndex;
            if (container[midIndex] > value)
                endIndex = midIndex-1;
            else
                startIndex = midIndex + 1;
        }
        return -1;
    }
}