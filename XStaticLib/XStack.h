#pragma once
#include "XLog.h"

namespace xsl
{
    template<typename T, size_t N>
    class Stack
    {
    private:
        size_t size {};
        T stack[N] {};
        int top;
        size_t capacity;

    public:
        Stack() : size(0), top(-1), capacity(N) {}
        Stack(const Stack& other) = default;
        Stack(Stack&& other) = default;
        Stack& operator=(const Stack& other) = default;
        Stack& operator=(Stack&& other) = default;
        ~Stack() = default;

        size_t Size() const { return size; }

        size_t Capacity() const { return capacity; }

        void Push(const T& value)
        {
            if (top >= capacity)
            {
                XLog::Log("Stack Overflow", LogLevel::LOG_ERROR);
                return;
            }
            stack[++top] = value;
        }

        T Pop()
        {
            if (top < 0)
            {
                XLog::Log("stack is empty", LogLevel::LOG_ERROR);
                return -1;
            }
            return stack[top--];
        }

        void Empty()
        {
            if (top == -1)
                return;
            top = -1;
            stack[N] = {};
        }

        bool IsEmpty() const { return top == -1; }

    
    
    };
}