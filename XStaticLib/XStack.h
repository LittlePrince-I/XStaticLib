#pragma once
#include <iostream>
#include <optional>

#include "XLog.h"

namespace xsl
{
    template<typename T, size_t N>
    class Stack
    {
    private:
        size_t stackSize {};
        T stack[N] {};
        int top = -1;
        size_t stackCapacity = N;

    private:
        T& operator[](size_t index) 
        {
            return stack[index];
        }

    public:
        Stack() = default;
        Stack(const Stack& other) = default;
        Stack(Stack&& other) = default;
        Stack& operator=(const Stack& other) = default;
        Stack& operator=(Stack&& other) = default;
        ~Stack() = default;

        size_t size() const { return stackSize; }

        size_t capacity() const { return stackCapacity; }

        void push(const T& value)
        {
            if (top >= static_cast<int>(stackCapacity))
            {
                XLog::Log("Stack Overflow", LogLevel::LOG_ERROR);
                return;
            }
            stack[++top] = value;
            stackSize++;
        }

        std::optional<T> pop()
        {
            if (top < 0)
            {
                XLog::Log("stack is empty", LogLevel::LOG_ERROR);
                return std::nullopt;
            }
            stackSize--;
            return stack[top--];
        }

        void empty()
        {
            if (top == -1)
                return;
            top = -1;
            stack[N] = {};
        }

        bool isEmpty() const { return top == -1; }

        friend std::ostream& operator<<(std::ostream& os, xsl::Stack<T, N> stack)
        {
            os<< "[";
            for (int i = 0; i < stack.top; i++)
            {
                os<<stack[i]<<",";
            }
            os<<stack[stack.top]<<"]\n";

            return os;
        }

        void coutStack() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };
}