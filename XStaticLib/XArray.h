#pragma once
#include <iostream>
#include <initializer_list>

#include "XLog.h"
#include "XAssert.h"
#include "XSearch.h"

namespace xsl
{
    template <typename T, size_t N>
    class Array
    {
    private:
        size_t size = 0;
        T array[N] = {};
        T* begin = array;
        T* end = array + N;

    public:
        Array() : 
            size(N) 
        {
        }

        Array(std::initializer_list<T> array) :
            size(N)
        {
            if(array.size() > N)
                std::copy(array.begin(), array.begin() + size, this->array);
            else if(array.size() <= N)
                std::copy(array.begin(), array.end(), this->array);
        }

        Array(const Array<T, N>& arr) :
            size(N)           
        {
            std::copy(arr.Begin(), arr.End(), array);
        }

        Array(const Array<T, N>&& arr) noexcept :
            size(N) 
        {
            std::copy(arr.Begin(), arr.End(), array);
        }

        Array<T, N>& operator=(const Array<T, N>& arr)
        {
            if(this != &arr)
                std::copy(arr.Begin(), arr.End(), array);
            return *this;
        }

        Array<T, N>& operator=(Array<T, N>&& arr) noexcept
        {
            std::copy(arr.Begin(), arr.End(), array);
            return *this;
        }

        ~Array() = default;

        T& operator[](size_t index) 
        { 
            Assert(index < size, "Index out of range");
            return array[index]; 
        }
        const T& operator[](size_t index) const 
        { 
            Assert(index < size, "Index out of range");
            return array[index]; 
        }

        friend std::ostream& operator<<(std::ostream& os, const Array<T, N>& arr)
        {
            os << "[";
            int i;
            for (i = 0; i < arr.size - 1; i++)
            {
                os << arr[i] << ",";
            }
            os << arr[i] << "]" << std::endl;
            return os;
        }

        constexpr size_t Size() const { return size; }

        T* Begin()  { return begin; }

        T* End()  { return end; }

        const T* Begin() const { return begin; }

        const T* End() const { return end; }

        int BSearch(const T& value) const
        {
            for (int i = 0, j = 1; j < size; i++, j++)
            {
                if (!this[i]<this[j])
                {
                    XLog::Log("The array is not sorted in ascending order", xsl::LogLevel::LOG_ERROR);
                    return -1;
                }
            }
            int index = BinarySearch(*this, value, 0, static_cast<int>(size-1));
            if (index == -1)
            {
                XLog::Log("Value not found", LogLevel::LOG_INFO);
                return -1;
            }
            return index;
        }
        
        void CoutArray() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };

}