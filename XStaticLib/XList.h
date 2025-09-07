#pragma once

#include <iostream>
#include <initializer_list>

#include "XLog.h"
#include "XAssert.h"

namespace xsl
{

    template <typename T>
    struct ListNode
    {
    public:
        T data{};
        ListNode<T>* prev = nullptr;
        ListNode<T>* next = nullptr;
        size_t index = 0;
        
        friend std::ostream& operator<<(std::ostream& os, const ListNode<T>* node)
        {
            os << "\n" << "----------------------------------------\n\n"
                << "node[" << node->index << "]" << std::endl
                << "Data:" << node->data << std::endl
                << "\n----------------------------------------\n" << std::endl;
            return os;

        }
    };

    template <typename T>
    class List
    {
    protected:
        ListNode<T>* head = nullptr;
        size_t listSize = 0;

    protected:
        List() = default;
        List(const List<T>& other) {}
        List(const List<T>&& other) noexcept {}
        List& operator=(const List<T>& other) = default;
        List& operator=(List<T>&& other) = default;
        virtual ~List() = default;
        
    public:
        virtual ListNode<T>* getHead() const { return head; }

        virtual size_t size() const { return listSize; }

        virtual void addOnHead(const T& data) = 0;
        virtual void addOnTail(const T& data) = 0;
        virtual void coutList() const = 0;

        virtual void empty()
        {
            while (head != nullptr)
            {
                ListNode<T>* temp = head;                
                head = head->next;
                delete temp;
            }
            listSize = 0;
        }

        virtual void setIndex()
        {
            ListNode<T>* temp = head;
            size_t counter = 0;
            while (temp != nullptr)
            {
                temp->index = counter;
                temp = temp->next;
                counter++;
            }
        }

        virtual const ListNode<T>* operator[](size_t index) const
        {
            ListNode<T>* temp = head;
            Assert(listSize > index, "Index out of range");
            
            while (temp != nullptr)
            {
                if (temp->index == index)
                    return temp;
                temp = temp->next;
            }
            return nullptr;
        }
    };
    
    template <typename T>
    class LinkedList : public List<T>
    {
        
    public:
        LinkedList() = default;
        

        LinkedList(std::initializer_list<T> list)
        {
            for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i)
            {
                LinkedList<T>::addOnHead(list.begin()[i]);
            }
        }

        LinkedList(const LinkedList<T>& list)
        {            
            ListNode<T>* temp = list.getHead();
            while (temp != nullptr)
            {
                LinkedList<T>::addOnTail(temp->data);
                temp = temp->next;
            }            
        }

        LinkedList(LinkedList<T>&& list) noexcept
        {
            ListNode<T>* temp = list.getHead();
            while (temp != nullptr)
            {
                LinkedList<T>::addOnTail(temp->data);
                temp = temp->next;
            }
        }

        LinkedList& operator=(const LinkedList<T>& list)
        {
            if (this != &list)
            {
                if (List<T>::head != nullptr)
                    List<T>::empty();
                ListNode<T>* temp = list.getHead();
                while (temp != nullptr)
                {
                    LinkedList<T>::addOnTail(temp->data);
                    temp = temp->next;
                }
            }
            return *this;
        }

        LinkedList& operator=(LinkedList<T>&& list) noexcept
        {
            if (List<T>::head != nullptr)
                List<T>::empty();
            ListNode<T>* temp = list.getHead();
            while (temp != nullptr)
            {
                LinkedList<T>::addOnTail(temp->data);
                temp = temp->next;
            }
            return *this;
        }


        ~LinkedList() override
        {
            List<T>::empty();
        }
        
        void addOnHead(const T& data) override
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            newNode->next = List<T>::head;
            List<T>::head = newNode;
            ++List<T>::listSize;
            List<T>::setIndex();
        }

        void addOnTail(const T& data) override
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            if (List<T>::head == nullptr)
            {
                List<T>::head = newNode;
                ++List<T>::listSize;
                return;
            }
            ListNode<T>* temp = List<T>::head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            ++List<T>::listSize;
            newNode->index = List<T>::listSize - 1;
        }

        friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
        { 
            ListNode<T>* temp = list.getHead();
            os << "\n----------------------------------------\n\n";
            while(temp != nullptr)
            {
                os << "node[" << temp->index << "]" << std::endl
                   <<"Data:" << temp->data << std::endl
                   << "\n----------------------------------------\n" << std::endl;
                temp = temp->next;
            }
            
            return os;
        }

        void coutList() const override
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
        
    };

    template <typename T>
    class DLinkedList : public List<T>
    {
        private:
            ListNode<T>* tail = nullptr;
        public:
            DLinkedList() = default;

            DLinkedList(std::initializer_list<T> list)
            {
                for (size_t i = 0; i < list.size(); i++)
                {
                    DLinkedList<T>::addOnTail(list.begin()[i]);
                }
            }

            DLinkedList(const DLinkedList<T>& list)
            {
                ListNode<T>* temp = list.getHead();
                while (temp != nullptr)
                {
                    DLinkedList<T>::addOnTail(temp->data);
                    temp = temp->next;
                }
            }

            DLinkedList(DLinkedList<T>&& list) noexcept
            {
                ListNode<T>* temp = list.getHead();
                while (temp != nullptr)
                {
                    DLinkedList<T>::addOnTail(temp->data);
                    temp = temp->next;
                }
            }

            DLinkedList<T>& operator=(const DLinkedList<T>& list)
            {
                if (this != &list)
                {
                    if(List<T>::head != nullptr)
                        List<T>::empty();
                    ListNode<T>* temp = list.getHead();
                    while (temp != nullptr)
                    {
                        DLinkedList<T>::addOnTail(temp->data);
                        temp = temp->next;
                    }
                }
                return *this;
            }

            DLinkedList<T>& operator=(DLinkedList<T>&& list) noexcept
            {
                if (List<T>::head != nullptr)
                    List<T>::empty();
                ListNode<T>* temp = list.getHead();
                while (temp != nullptr)
                {
                    DLinkedList<T>::addOnTail(temp->data);
                    temp = temp->next;
                }
                return *this;
            }            

            ~DLinkedList() override
            {
                List<T>::empty();
            }

            ListNode<T>* getTail() const
            {
                return tail;
            }          

            void addOnHead(const T& data) override
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (List<T>::head == nullptr)
                {
                    List<T>::head = newNode;
                    tail = newNode;
                    ++List<T>::listSize;
                    return;
                }
                newNode->next = List<T>::head;
                List<T>::head->prev = newNode;
                List<T>::head = newNode;
                ++List<T>::size;
                List<T>::setIndex();
            }

            void addOnTail(const T& data) override
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (tail == nullptr)
                {
                    List<T>::head = newNode;
                    tail = newNode;
                    ++List<T>::listSize;
                    return;
                }
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
                ++List<T>::listSize;
                newNode->index = List<T>::listSize - 1;
            }

            friend std::ostream& operator<<(std::ostream& os, const DLinkedList<T>& list)
            {
                ListNode<T>* temp = list.getHead();
                os << "\n----------------------------------------\n\n";
                while (temp != nullptr)
                {
                    os << "node[" << temp->index << "]" << std::endl
                       << "Data:" << temp->data << std::endl
                       << "\n----------------------------------------\n" << std::endl;
                    temp = temp->next;
                }

                return os;
            }

            void coutList() const override
            {
                XLog::Log(*this, LogLevel::LOG_INFO);
            }
            
    };
}