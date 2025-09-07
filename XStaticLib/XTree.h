#pragma once
#include <cstdint>
#include <cmath>
#include <functional>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

#include "XLog.h"

namespace xsl
{
    enum class BinaryNodeType :
    uint8_t
    {
        NONE,
        ROOT,
        RIGHT,
        LEFT
    };

    template<typename T>
    class TreeNode
    {
    public:
        T data {};
        size_t index = 0;
    };
    
    template<typename T>
    class BinaryTreeNode : public TreeNode<T>
    {
    private:
        bool leftTag = false;
        bool rightTag = false;
        
    public:
        BinaryTreeNode<T>* leftChild = nullptr;
        BinaryTreeNode<T>* rightChild = nullptr;
        BinaryNodeType nodeType = BinaryNodeType::NONE;
        
    public:
        BinaryTreeNode() = default;
        BinaryTreeNode(const T& data)
        {
            this->data = data;
        }
        
        BinaryTreeNode(BinaryTreeNode& node)
        {
            this->data = node.data;
            this->index = node.index;
            this->nodeType = node.nodeType;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        }
        BinaryTreeNode(BinaryTreeNode&& node) noexcept
        {
            this->data = node.data;
            this->index = node.index;
            this->nodeType = node.nodeType;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        }
        BinaryTreeNode& operator=(const BinaryTreeNode& node)
        {
            if (this == &node)
                return *this;
            this->data = node.data;
            this->index = node.index;
            this->nodeType = node.nodeType;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
            return *this;
        }
        BinaryTreeNode& operator=(BinaryTreeNode&& node)
        {
            if (this == &node)
                return *this;
            this->data = node.data;
            this->index = node.index;
            this->nodeType = node.nodeType;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
            return *this;
        }
        
        ~BinaryTreeNode() = default;
        
        friend std::ostream& operator<<(std::ostream& os, const BinaryTreeNode<T>& node)
        {
            os << node.data;
            return os;
        }

        void setLeftTag(const bool leftTag)
        {
            this->leftTag = leftTag;
        }

        void setRightTag(const bool rightTag)
        {
            this->rightTag = rightTag;
        }

        [[nodiscard]] bool getLeftTag() const
        {
            return leftTag;
        }

        [[nodiscard]] bool getRightTag() const
        {
            return rightTag;
        }
    };
    
    template<typename T>
    class Tree
    {
    private:
        TreeNode<T>* rootNode = nullptr;
        
    protected:
        size_t degree = 0;
        size_t treeDegree = 0;
        size_t level = 0;
        size_t depth = 0;
    };

    template<typename T>
    class BinaryTree :public Tree<T>
    {
    private:
        BinaryTreeNode<T>* rootNode = nullptr;
        bool isThreaded = false;
        
    protected:
        size_t maxDegree = 2;

    public:
        BinaryTree() = default;

        BinaryTree(BinaryTree& other)
        {
            this->treeCopy(other);
        }

        BinaryTree(BinaryTree&& other) noexcept
        {
            this->treeCopy(other);
        }

        BinaryTree& operator=(const BinaryTree& other)
        {
            if (this == &other)
                return *this;
            this->treeCopy(other);
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& other) noexcept
        {
            this->treeCopy(other);
            return *this;
        }

        ~BinaryTree()
        {
            empty();
        }

        BinaryTreeNode<T>* addNode(const T& data)
        {
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(data);
            if (rootNode == nullptr)
                setRootNode(newNode);
            return newNode;
        }

        void removeNode(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return;
            delete node;
        }

        void setRootNode(BinaryTreeNode<T>* node)
        {
            if (this->rootNode != nullptr)
                this->empty();
            this->rootNode = node;
            node->nodeType = BinaryNodeType::ROOT;
            node->index = 1;
        }

        [[nodiscard]] BinaryTreeNode<T>* getRootNode() const
        {
            return this->rootNode;
        }

        void setChildNode(BinaryTreeNode<T>* parentNode, BinaryTreeNode<T>* childNode, BinaryNodeType nodeType)
        {
            if (nodeType == BinaryNodeType::LEFT)
            {
                parentNode->leftChild = childNode;
                childNode->index = parentNode->index*2;
            }
            else if (nodeType == BinaryNodeType::RIGHT)
            {
                parentNode->rightChild = childNode;
                childNode->index = parentNode->index*2+1;
            }
            childNode->nodeType = nodeType;
        }

        void treeCopy(BinaryTree<T>& other)
        {
            if (this->rootNode != nullptr)
                this->empty();
            BinaryTreeNode<T>* previousNode = nullptr;
            other.preorderTraversal
            (
                [this, &previousNode](BinaryTreeNode<T>* node)
                {
                    BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>();
                    newNode->data = node->data;
                    newNode->index = node->index;
                    newNode->nodeType = node->nodeType;
                    newNode->setLeftTag(node->getLeftTag());
                    newNode->setRightTag(node->getRightTag());
                    if (newNode->nodeType == BinaryNodeType::ROOT)
                        this->setRootNode(newNode);
                    else if (newNode->nodeType == BinaryNodeType::LEFT)
                        previousNode->leftChild = newNode;
                    else if (newNode->nodeType == BinaryNodeType::RIGHT)
                        previousNode->rightChild = newNode;
                    previousNode = newNode;
                },
                other.getRootNode()
            );
            this->setIsThreaded(other.getIsThreaded());
        }

        void setIsThreaded(const bool value)
        {
            isThreaded = value;
        }

        [[nodiscard]] bool getIsThreaded() const
        {
            return isThreaded;
        }

        //前序遍历       
        template<typename Function>
        void preorderTraversal
            (
            Function callback,
            BinaryTreeNode<T>* node
            ) const
        {
            BinaryTreeNode<T>* currentNode = node;
            if (!isThreaded)
            {
                std::stack<BinaryTreeNode<T>*> nodeStack;
                while (!nodeStack.empty() || currentNode != nullptr)
                {
                    if (currentNode != nullptr)
                    {
                        callback(currentNode);
                        nodeStack.push(currentNode);
                        currentNode = currentNode->leftChild;
                    }
                    else
                    {
                        currentNode = nodeStack.top()->rightChild;
                        nodeStack.pop();
                    }
                }
            }
            else
            {
                while (currentNode != nullptr)
                {
                    callback(currentNode);
                    if (!currentNode->getLeftTag())
                    {
                        currentNode = currentNode->leftChild;
                    }
                    else
                    {
                        currentNode = currentNode->rightChild;
                    }
                }
            }
        }

        //中序遍历
        template<typename Function>
        void inorderTraversal
        (
            Function callback,
            BinaryTreeNode<T>* node
        ) const
        {
            std::stack<BinaryTreeNode<T>*> nodeStack;
            BinaryTreeNode<T>* currentNode = node;        
            while (!nodeStack.empty() || currentNode != nullptr)
            {
                if (currentNode != nullptr)
                {
                    nodeStack.push(currentNode);
                    currentNode = currentNode->leftChild;
                }
                else
                {
                    currentNode = nodeStack.top()->rightChild;
                    callback(nodeStack.top());
                    nodeStack.pop();
                }
            }
        }

        //后序遍历
        template<typename Function>
        void postorderTraversal
        (
            Function callback,
            BinaryTreeNode<T>* node
        ) const
        {
            BinaryTreeNode<T>* currentNode = node;
            BinaryTreeNode<T>* lastVisitedNode = nullptr;
            if (!this->getIsThreaded())
            {
                std::stack<BinaryTreeNode<T>*> nodeStack;
                while (!nodeStack.empty() || currentNode != nullptr)
                {
                    if (currentNode != nullptr)
                    {
                        nodeStack.push(currentNode);
                        currentNode = currentNode->leftChild;
                    }
                    else
                    {
                        currentNode = nodeStack.top()->rightChild;
                        if (currentNode == nullptr || lastVisitedNode == currentNode)
                        {
                            lastVisitedNode = nodeStack.top();
                            callback(lastVisitedNode);
                            nodeStack.pop();
                            currentNode = nullptr;
                        }
                    }
                }
            }
            else
            {
                while (currentNode != nullptr)
                {
                    if (!currentNode->getLeftTag())
                    {
                        currentNode = currentNode->leftChild;
                    }
                    else
                    {
                        lastVisitedNode = currentNode;
                        currentNode = currentNode->rightChild;
                        if (lastVisitedNode->getRightTag())
                        {
                            callback(lastVisitedNode);
                        }                     
                    }
                }
            }
        }

        //层序遍历
        template<typename Function>
        void levelOrderTraversal
        (
            Function callback,
            BinaryTreeNode<T>* node
        ) const
        {
            std::queue<BinaryTreeNode<T>*> nodeQueue;
            nodeQueue.push(node);
            while (!nodeQueue.empty())
            {
                if (nodeQueue.front() == nullptr)
                {
                    nodeQueue.pop();
                    continue;
                }
                BinaryTreeNode<T>* currentNode = nodeQueue.front();
                nodeQueue.pop();
                nodeQueue.push(currentNode->leftChild);
                nodeQueue.push(currentNode->rightChild);
                callback(currentNode);
            }
        }

        //线索化二叉树
        void threadedBinaryTree()
        {
            BinaryTreeNode<T>* previousNode = nullptr;
            BinaryTreeNode<T>* currentNode = this->getRootNode();
            std::stack<BinaryTreeNode<T>*> nodeStack;
            while (!nodeStack.empty() || currentNode != nullptr)
            {
                if (currentNode != nullptr)
                {
                    if (currentNode->leftChild == nullptr)
                    {
                        currentNode->leftChild = previousNode;
                        currentNode->setLeftTag(true);
                        if (previousNode->rightChild == nullptr && previousNode != nullptr)
                        {
                            previousNode->rightChild = currentNode;
                            currentNode->setRightTag(true);
                        }
                    }
                    previousNode = currentNode;
                    nodeStack.push(currentNode);
                    if(!currentNode->getLeftTag())
                        currentNode = currentNode->leftChild;
                    else
                        currentNode = currentNode->rightChild;
                }
                else
                {
                    currentNode = nodeStack.top()->rightChild;
                    nodeStack.pop();
                }
            }
            this->setIsThreaded(true);
 
        }

        void empty()
        {
            this->postorderTraversal
            (
                [](const BinaryTreeNode<T>* node)
                {
                    delete node;
                },
                rootNode
            );
        }

        friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& binaryTree)
        {
            os << "----------------------------------------\n";
            binaryTree.preorderTraversal(
                [&](const BinaryTreeNode<T>* node)
                {
                    os << *node << std::endl;
                    os << "----------------------------------------\n";
                },
                binaryTree.getRootNode()
                );
            return os;
        }

        void coutBinaryTree()
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };
}