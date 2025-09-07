#pragma once

#include <optional>
#include <iostream>

#include "XLog.h"

namespace xsl
{
    template<typename T, size_t N>
    class Queue
    {
    private:
        size_t queueSize = 0;
        size_t queueCapacity = N;
        int head = 0;
        int tail = 0;
        T queue[N+1] {};

    private:
        T& operator[](size_t index)
        {
            return queue[index];
        }

        const T& operator[](size_t index) const
        {
            return queue[index];
        }
        
    public:
        Queue() = default;
        Queue(const Queue& other) = default;
        Queue& operator=(const Queue& other) = default;
        Queue(Queue&& other) = default;
        Queue& operator=(Queue&& other) = default;
        ~Queue() = default;

        size_t size() const { return queueSize; }

        size_t capacity() const { return queueCapacity; }

        int getHead() const
        {
            return head;
        }

        int getHead(int head) const
        {
            if (head >= queueCapacity)
                head %= queueCapacity;
            return head;
        }

        int getTail() const
        {
            return tail;
        }

        int getDetalTail(int dTail)
        {
            if (dTail >= static_cast<int>(queueCapacity))
                dTail %= queueCapacity;
            return dTail;
        }

        bool isFull()
        {
            if (getDetalTail(tail + 2) == head)
                return true;
            return false;
        }

        bool isEmpty() const
        {
            if (head == tail || tail == -1)
                return true;
            return false;
        }

        void empty()
        {
            head=0;
            tail=-1;
        }

        void enqueue(const T& item)
        {
            if (isFull())
            {
                XLog::Log("queue is overflow", LogLevel::LOG_ERROR);
                return;
            }
            queue[tail] = item;
            tail = (tail + 1) % queueCapacity;
        }

        std::optional<T>& dequeue()
        {
            if (isEmpty())
            {
                XLog::Log("queue is empty", LogLevel::LOG_ERROR);
                return std::nullopt;
            }
            T item = queue[head];
            head = (head + 1) % queueCapacity;
            return item;
        }

        friend std::ostream& operator<<(std::ostream& os,const xsl::Queue<T, N>& q)
        {
            os<<"[";
            int i = q.head;
            while (i != q.tail-1)
            {
                os<<q[i]<<",";
                ++i;
                if (i >= static_cast<int>(q.capacity()))
                    i %= q.capacity();
            }
            os<<q[q.tail-1]<<"]\n";
            return os;
        }

        void coutQueue() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };
}