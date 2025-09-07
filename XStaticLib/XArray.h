#pragma once
#include <iostream>
#include <initializer_list>
#include <optional>

#include "XLog.h"
#include "XAssert.h"
#include "XSearch.h"

namespace xsl
{
    template <typename T, size_t N>
    class Array
    {
    private:
        size_t arraySize = 0;
        T array[N] = {};
        T* arrayBegin = array;
        T* arrayEnd = array + N;

    public:
        Array() : 
            arraySize(N) 
        {
        }

        Array(std::initializer_list<T> array) :
            arraySize(N)
        {
            if(array.size() > N)
                std::copy(array.begin(), array.begin() + arraySize, this->array);
            else if(array.size() <= N)
                std::copy(array.begin(), array.end(), this->array);
        }

        Array(const Array<T, N>& arr) :
            arraySize(N)           
        {
            std::copy(arr.begin(), arr.end(), array);
        }

        Array(const Array<T, N>&& arr) noexcept :
            arraySize(N) 
        {
            std::copy(arr.begin(), arr.end(), array);
        }

        Array<T, N>& operator=(const Array<T, N>& arr)
        {
            if(this != &arr)
                std::copy(arr.begin(), arr.end(), array);
            return *this;
        }

        Array<T, N>& operator=(Array<T, N>&& arr) noexcept
        {
            std::copy(arr.begin(), arr.end(), array);
            return *this;
        }

        ~Array() = default;

        T& operator[](size_t index) 
        { 
            Assert(index < arraySize, "Index out of range");
            return array[index]; 
        }
        const T& operator[](size_t index) const 
        { 
            Assert(index < arraySize, "Index out of range");
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

        constexpr size_t size() const { return arraySize; }

        T* begin()  { return arrayBegin; }

        T* end()  { return arrayEnd; }

        const T* begin() const { return arrayBegin; }

        const T* end() const { return arrayEnd; }

        std::optional<int> search(const T& value) const
        {
            for (int i = 0, j = 1; j < arraySize; i++, j++)
            {
                if (!this[i]<this[j])
                {
                    XLog::Log("The array is not sorted in ascending order", xsl::LogLevel::LOG_ERROR);
                    return -1;
                }
            }
            int index = BinarySearch(*this, value, 0, static_cast<int>(arraySize-1));
            if (index == -1)
            {
                XLog::Log("Value not found", LogLevel::LOG_INFO);
                return std::nullopt;
            }
            return index;
        }
        
        void coutArray() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };

}