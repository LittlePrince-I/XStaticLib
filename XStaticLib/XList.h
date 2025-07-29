#pragma once

#include <iostream>
#include <initializer_list>

#include "XLog.h"
#include "XAssert.h"

namespace xsl
{

    template <typename T>
    class ListNode
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
        ListNode<T>* head;
        size_t size;
        
        public:
        List() : head(nullptr), size(0) {}
        List(const List<T>& other) = default;
        List(const List<T>&& other) = default;
        List& operator=(const List<T>& other) = default;
        List& operator=(List<T>&& other) = default;
        virtual ~List() = default;

        virtual  ListNode<T>* GetHead() const { return head; }

        virtual size_t Size() const { return size; }

        virtual void AddOnHead() = 0;
        virtual void AddOnTail() = 0;
        virtual void CoutList() = 0;

        virtual void Empty()
        {
            while (head != nullptr)
            {
                ListNode<T>* temp = head;                
                head = head->next;
                delete temp;
            }
            size = 0;
        }

        virtual void SetIndex()
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
            Assert(size > index, "Index out of range");
            
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
        LinkedList()
        {
        }

        LinkedList(std::initializer_list<T> list)
        {
            for (int i = list.size() - 1; i >= 0; --i)
            {
                AddOnHead(list.begin()[i]);
            }
        }

        LinkedList(const LinkedList<T>& list)
        {            
            ListNode<T>* temp = list.GetHead();
            while (temp != nullptr)
            {
                AddOnTail(temp->data);
                temp = temp->next;
            }            
        }

        LinkedList(LinkedList<T>&& list) noexcept
        {
            ListNode<T>* temp = list.GetHead();
            while (temp != nullptr)
            {
                AddOnTail(temp->data);
                temp = temp->next;
            }
        }

        LinkedList& operator=(const LinkedList<T>& list)
        {
            if (this != &list)
            {
                if (List<T>::head != nullptr)
                    List<T>::Empty();
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
            }
            return *this;
        }

        LinkedList& operator=(LinkedList<T>&& list) noexcept
        {
            if (List<T>::head != nullptr)
                List<T>::Empty();
            ListNode<T>* temp = list.GetHead();
            while (temp != nullptr)
            {
                AddOnTail(temp->data);
                temp = temp->next;
            }
            return *this;
        }


        ~LinkedList() override
        {
            List<T>::Empty();
        }
        
        void AddOnHead(const T& data)
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            newNode->next = List<T>::head;
            List<T>::head = newNode;
            ++List<T>::size;
            List<T>::SetIndex();
        }

        void AddOnTail(const T& data)
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            if (List<T>::head == nullptr)
            {
                List<T>::head = newNode;
                ++List<T>::size;
                return;
            }
            ListNode<T>* temp = List<T>::head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            ++List<T>::size;
            newNode->index = List<T>::size - 1;
        }

        friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
        { 
            ListNode<T>* temp = list.GetHead();
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

        void CoutList() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
        
    };

    template <typename T>
    class DLinkedList : public List<T>
    {
        private:
            ListNode<T>* tail;
        public:
            DLinkedList():
            tail(nullptr)
            {
            }

            DLinkedList(std::initializer_list<T> list) 
            {
                for (int i = 0; i < list.size(); i++)
                {
                    AddOnTail(list.begin()[i]);
                }
            }

            DLinkedList(const DLinkedList<T>& list)
            {
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
            }

            DLinkedList(DLinkedList<T>&& list) noexcept
            {
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
            }

            DLinkedList<T>& operator=(const DLinkedList<T>& list)
            {
                if (this != &list)
                {
                    if(List<T>::head != nullptr)
                        List<T>::Empty();
                    ListNode<T>* temp = list.GetHead();
                    while (temp != nullptr)
                    {
                        AddOnTail(temp->data);
                        temp = temp->next;
                    }
                }
                return *this;
            }

            DLinkedList<T>& operator=(DLinkedList<T>&& list) noexcept
            {
                if (List<T>::head != nullptr)
                    List<T>::Empty();
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
                return *this;
            }            

            ~DLinkedList() override
            {
                List<T>::Empty();
            }

            ListNode<T>* GetTail() const
            {
                return tail;
            }          

            void AddOnHead(const T& data)
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (List<T>::head == nullptr)
                {
                    List<T>::head = newNode;
                    tail = newNode;
                    ++List<T>::size;
                    return;
                }
                newNode->next = List<T>::head;
                List<T>::head->prev = newNode;
                List<T>::head = newNode;
                ++List<T>::size;
                List<T>::SetIndex();
            }

            void AddOnTail(const T& data)
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (tail == nullptr)
                {
                    List<T>::head = newNode;
                    tail = newNode;
                    ++List<T>::size;
                    return;
                }
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
                ++List<T>::size;
                newNode->index = List<T>::size - 1;
            }

            friend std::ostream& operator<<(std::ostream& os, const DLinkedList<T>& list)
            {
                ListNode<T>* temp = list.GetHead();
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

            void CoutList() const
            {
                XLog::Log(*this, LogLevel::LOG_INFO);
            }
            
    };
}