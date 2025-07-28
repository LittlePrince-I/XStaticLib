#pragma once

#include <iostream>
#include <initializer_list>
#include <cassert>

#include "XLog.h"
#include "XAssert.h"

namespace XSL
{

    template <typename T>
    class ListNode
    {
    public:
        T data{};
        ListNode<T>* prev = nullptr;
        ListNode<T>* next = nullptr;
        size_t index = 0;

        ListNode() = default;
        ~ListNode() = default;

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
    class LinkedList
    {

    private: 

        ListNode<T>* head = nullptr;

        size_t size = 0;

    public:
        LinkedList()
        {
        };

        LinkedList(std::initializer_list<T>&& list)
        {
            for (int i = list.size() - 1; i >= 0; i--)
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

        LinkedList(LinkedList<T>&& list)
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
            if (head != nullptr)
                Empty();
            ListNode<T>* temp = list.GetHead();
            while (temp != nullptr)
            {
                AddOnTail(temp->data);
                temp = temp->next;
            }
            return *this;
        }

        LinkedList& operator=(LinkedList<T>&& list)
        {
            if (head != nullptr)
                Empty();
            ListNode<T>* temp = list.GetHead();
            while (temp != nullptr)
            {
                AddOnTail(temp->data);
                temp = temp->next;
            }
            return *this;
        }


        ~LinkedList()
        {
            Empty();
        }

        ListNode<T>* GetHead() const
        {
            return head;
        }
              

        void AddOnHead(const T& data)
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            newNode->next = head;
            head = newNode;
            size++;
            SetIndex();
        }

        void AddOnTail(const T& data)
        {
            ListNode<T>* newNode = new ListNode<T>;
            newNode->data = data;
            if (head == nullptr)
            {
                head = newNode;
                size++;
                return;
            }
            ListNode<T>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            size++;
            newNode->index = size - 1;
        }

        void SetIndex()
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

        void Empty()
        {
            ListNode<T>* temp;
            while (head != nullptr)
            {
                temp = head;                
                head = head->next;
                delete temp;
            }
            size = 0;
        }

        size_t Size() const
        {
            return size;
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

        ListNode<T>* operator[](size_t index)
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

        const ListNode<T>* operator[](size_t index) const
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

        void CoutList() const
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
        
    };

    template <typename T>
    class DLinkedList
    {
        private:
            ListNode<T>* head = nullptr;
            ListNode<T>* tail = nullptr;
            size_t size = 0;
        public:
            DLinkedList()
            {
            };

            DLinkedList(std::initializer_list<T> list) 
            {
                for (int i = 0; i < list.size(); i++)
                {
                    AddOnTail(list.begin()[i]);
                }
            };

            DLinkedList(const DLinkedList<T>& list)
            {
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
            }; 

            DLinkedList(DLinkedList<T>&& list)
            {
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
            };

            DLinkedList<T>& operator=(const DLinkedList<T>& list)
            {
                if(head != nullptr)
                    Empty();
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
                return *this;
            };

            DLinkedList<T>& operator=(DLinkedList<T>&& list)
            {
                if (head != nullptr)
                    Empty();
                ListNode<T>* temp = list.GetHead();
                while (temp != nullptr)
                {
                    AddOnTail(temp->data);
                    temp = temp->next;
                }
                return *this;
            };            

            ~DLinkedList()
            {
                Empty();
            };


            ListNode<T>* GetHead() const
            {
                return head;
            }

            ListNode<T>* GetTail() const
            {
                return tail;
            }          

            size_t Size() const
            {
                return size;
            }

            void AddOnHead(const T& data)
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (head == nullptr)
                {
                    head = newNode;
                    tail = newNode;
                    size++;
                    return;
                }
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
                size++;
                SetIndex();
            }

            void AddOnTail(const T& data)
            {
                ListNode<T>* newNode = new ListNode<T>;
                newNode->data = data;
                if (tail == nullptr)
                {
                    head = newNode;
                    tail = newNode;
                    size++;
                    return;
                }
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
                size++;
                newNode->index = size - 1;
            }

            void SetIndex()
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

            void Empty()
            {
                while (head != nullptr)
                {
                    ListNode<T>* temp = head;
                    head = head->next;
                    delete temp;
                }
                size = 0;
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
            };

            ListNode<T>* operator[](size_t index)
            {
                Assert(index < size, "Index out of range");
                ListNode<T>* temp = head;
                while (temp != nullptr)
                {
                    if (temp->index == index)
                        return temp;
                    temp = temp->next;
                }
                return nullptr;
            }

            void CoutList() const
            {
                XLog::Log(*this, LogLevel::LOG_INFO);
            };
            
    };
}