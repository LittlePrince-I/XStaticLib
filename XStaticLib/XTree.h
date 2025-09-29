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

    template<typename T, class TreeType, class NodeType>
    class BinaryTreeNodeBase : public TreeNode<T>
    {
    public:
        TreeType leftChild = nullptr;
        TreeType rightChild = nullptr;
        NodeType nodeType = NodeType::NONE;
    protected:
        BinaryTreeNodeBase() = default;
    };
    
    template<typename T>
    class BinaryTreeNode : virtual public BinaryTreeNodeBase<T, BinaryTreeNode<T>*, BinaryNodeType>
    {
    private:
        bool leftTag = false;
        bool rightTag = false;
        
    public:
        BinaryTreeNode() = default;
        explicit BinaryTreeNode(const T& d) 
        {
            this->data = d;
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

        void setLeftTag(const bool lTag)
        {
            this->leftTag = lTag;
        }

        void setRightTag(const bool rTag)
        {
            this->rightTag = rTag;
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
    class AVLTreeNode : virtual public BinaryTreeNodeBase<T, AVLTreeNode<T>*, BinaryNodeType>
    {
    private:
        int height = 0;
        int balanceFactor = 0;
    public:
        AVLTreeNode<T>* parent = nullptr;
    public:
        AVLTreeNode() = default;
        AVLTreeNode(AVLTreeNode& node):BinaryTreeNode<T>(node)
        {
           this->height = node.getHeight();
           this->balanceFactor = node.getBalanceFactor();
        }

        explicit AVLTreeNode(const T& d)
        {
            this->data = d;
        }
        
        int getBalanceFactor() const
        {
            return balanceFactor;
        }
        
        void setBalanceFactor(const int bf)
        {
            this->balanceFactor = bf;
        }
        
        void setHeight(int h)
        {
            this->height = h;
        }

        int getHeight() const
        {
            return this->height;
        }
    };

    template<typename T, class Type>
    class TreeBase
    {
    protected:
        Type rootNode = nullptr;
        
    protected:
        TreeBase() = default;
    };
    
    template<typename T>
    class Tree : virtual  protected TreeBase<T, TreeNode<T>*>
    {
    
    };

    template<typename T>
    class BinaryTree :virtual protected TreeBase<T, BinaryTreeNode<T>*>
    {
    protected:
        bool isThreaded = false;
        
    protected:
        size_t maxDegree = 2;

    private:
        BinaryTreeNode<T>* TreeCopyCore(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return nullptr;
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>();
            newNode->data = node->data;
            newNode->index = node->index;
            newNode->nodeType = node->nodeType;
            newNode->setLeftTag(node->getLeftTag());
            newNode->setRightTag(node->getRightTag());
            BinaryTreeNode<T*> lChild = treeCopyCore(node->leftChild);
            if (lChild != nullptr)
                setChildNode(newNode, lChild, lChild->nodeType);
            BinaryTreeNode<T*> rChild = treeCopyCore(node->rightChild);
            if (rChild != nullptr)
                setChildNode(newNode, rChild, rChild->nodeType);
            return newNode;
        }

    public:
        BinaryTree() = default;

        BinaryTree(const BinaryTree& other)
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

        virtual ~BinaryTree()
        {
            empty();
        }

        virtual BinaryTreeNode<T>* addNode(const T& data)
        {
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(data);
            if (this->rootNode == nullptr)
                setRootNode(newNode);
            return newNode;
        }

        void setRootNode(BinaryTreeNode<T>* node)
        {
            this->rootNode = node;
            node->nodeType = BinaryNodeType::ROOT;
            node->index = 1;
        }

        BinaryTreeNode<T>* getRootNode() const
        {
            return this->rootNode;
        }

        static void setChildNode(BinaryTreeNode<T>* parentNode, BinaryTreeNode<T>* childNode, BinaryNodeType nodeType)
        {
            if (childNode == nullptr)
            {
                if (nodeType == BinaryNodeType::LEFT)
                    parentNode->leftChild = nullptr;
                else if (nodeType == BinaryNodeType::RIGHT)
                    parentNode->rightChild = nullptr;
                return;
            }
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

        void treeCopy(const BinaryTree<T>& other)
        {
            if (this->rootNode != nullptr)
                this->empty();
            treeCopyCore(other.getRootNode());
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
            BinaryTreeNode<T>* currentNode = node;        
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
                this->rootNode
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

        void setTreeIndex()
        {
            int index = 1;
            this->levelOrderTraversal
            (
                [&index](BinaryTreeNode<T>* node)
                {
                    node->index = index;
                    index++;
                },
                this->getRootNode()
            );
        }
    };

    template<typename T>
    class BinarySearchTree : virtual protected TreeBase<T, BinaryTreeNode<T>*>
    {
    private:
        static bool isLeafNode(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return false;
            if (node->leftChild == nullptr && node->rightChild == nullptr)
                return true;
            return false;
        }
    
    public:
        BinarySearchTree() = default;
        ~BinarySearchTree() override = default;
        
        void setChildNode(BinaryTreeNode<T>* parentNode, BinaryTreeNode<T>* childNode)
        {
            if (parentNode == nullptr || childNode == nullptr || parentNode->data == childNode->data)
                return;
            if (parentNode->data > childNode->data)
                BinaryTree<T>::setChildNode(parentNode, childNode, BinaryNodeType::LEFT);
            else if (parentNode->data < childNode->data)
                BinaryTree<T>::setChildNode(parentNode, childNode, BinaryNodeType::RIGHT);
        }

        BinaryTreeNode<T>* searchNode(const T& data)
        {
            BinaryTreeNode<T>* currentNode = this->getRootNode();
            while (currentNode != nullptr)
            {
                if (currentNode->data == data)
                    return currentNode;
                else if (currentNode->data > data)
                    currentNode = currentNode->leftChild;
                else if (currentNode->data < data)
                    currentNode = currentNode->rightChild;
            }
            return nullptr;
        }

        static BinaryTreeNode<T>* findMaxNode(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return nullptr;
            while (node->rightChild != nullptr)
            {
                node = node->rightChild;
            }
            return node;
        }

        static BinaryTreeNode<T>* findMinNode(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return nullptr;
            while (node->leftChild != nullptr)
            {
                node = node->leftChild;
            }
            return node;
        }

        void deleteNode(BinaryTreeNode<T>* node)
        {
            if (node == nullptr)
                return;
            BinaryTreeNode<T>* previousNode = getPreviousNode(node);
            if (isLeafNode(node))
            {
                BinaryTree<T>::setChildNode(previousNode, nullptr, node->nodeType);
                delete node;
            }
            else if (node->leftChild == nullptr)
            {
                BinaryTree<T>::setChildNode(previousNode, node->rightChild, node->nodeType);
                delete node;
            }
            else if (node->rightChild == nullptr)
            {
                BinaryTree<T>::setChildNode(previousNode, node->leftChild, node->nodeType);
                delete node;
            }
            else
            {
                BinaryTreeNode<T>* maxNode =  findMaxNode(node->leftChild);
                node->data = maxNode->data;
                if (isLeafNode(maxNode))
                {
                    BinaryTree<T>::setChildNode(getPreviousNode(maxNode), nullptr, node->nodeType);
                    delete maxNode;
                }
                else if (maxNode->leftChild != nullptr)
                {
                    BinaryTree<T>::setChildNode(getPreviousNode(maxNode), maxNode->leftChild, maxNode->nodeType);
                    delete maxNode;
                }
                else if (maxNode->rightChild != nullptr)
                {
                    BinaryTree<T>::setChildNode(maxNode, maxNode->rightChild, maxNode->nodeType);
                    delete maxNode;
                }
            }
            this->setTreeIndex();
        }

        BinaryTreeNode<T>* getPreviousNode(BinaryTreeNode<T>* node) const
        {
            BinaryTreeNode<T>* currentNode = this->getRootNode();
            BinaryTreeNode<T>* previousNode = nullptr;
            while (currentNode->data != node->data)
            {
                if (currentNode == nullptr)
                    return nullptr;
                previousNode = currentNode;
                if (currentNode->data > node->data)
                    currentNode = currentNode->leftChild;
                else if (currentNode->data < node->data)
                    currentNode = currentNode->rightChild;
            }
            return previousNode;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& binarySearchTree)
        {
            os << "----------------------------------------\n";
            binarySearchTree.levelOrderTraversal(
                [&](const BinaryTreeNode<T>* node)
                {
                    os << *node << std::endl;
                    os << "----------------------------------------\n";
                },
                binarySearchTree.getRootNode()
                );
            return os;
        }

        void coutBinarySearchTree()
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };

    template <typename T>
    class AVLTree : virtual protected TreeBase<T, AVLTreeNode<T>*>
    {
    private:
        void setTreeHeight(AVLTreeNode<T>* node)
        {
            int h = 1;
            AVLTreeNode<T>* currentNode = node;
            while (currentNode != nullptr)
            {
                if (currentNode->getHeight() > h)
                    return;
                currentNode->setHeight(h);
                h++;
                currentNode = currentNode->parent;
            }
        }

        void setBanlanceFactor(AVLTreeNode<T>* node)
        {
            int lHeight = 0;
            int rHeight = 0;
            if (node->leftChild != nullptr)
                lHeight = node->leftChild->getHeight();
            if (node->rightChild != nullptr)
                rHeight = node->rightChild->getHeight();
            node->setBalanceFactor(lHeight-rHeight);
        }

        void checkBalance(AVLTreeNode<T>* node)
        {
            AVLTreeNode<T>* currentNode = node;
            while (currentNode != nullptr)
            {
                setBanlanceFactor(currentNode);
                if (currentNode->getBalanceFactor() > 1 || currentNode->getBalanceFactor() < -1)
                    balance(currentNode);
                else
                {
                    currentNode = currentNode->parent;
                }
            }
        }

        void balance(AVLTreeNode<T>* node)
        {
            if (node->getBalanceFactor() == 2)
            {
                if (node->leftChild->getBalanceFactor() == 1)
                    LL(node);
                else if (node->leftChild->getBalanceFactor() == -1)
                    LR(node);
            }
            else if (node->getBalanceFactor() == -2)
            {
                if (node->rightChild->getBalanceFactor() == 1)
                    RL(node);
                else if (node->rightChild->getBalanceFactor() == -1)
                    RR(node);
            }
        }

        void LL(AVLTreeNode<T>* node)
        {
            AVLTreeNode<T>* nodeLeft = node->leftChild;
            nodeLeft->parent = node->parent;
            node->parent = nodeLeft;
            node->leftChild = nodeLeft->rightChild;
            nodeLeft->rightChild = node;
            if (node->leftChild != nullptr)
            {
                node->leftChild->parent = node;
                node->leftChild->nodeType = BinaryNodeType::LEFT;
            }
            if (node->nodeType == BinaryNodeType::LEFT)
                nodeLeft->parent->leftChild = nodeLeft;
            else if (node->nodeType == BinaryNodeType::RIGHT)
                nodeLeft->parent->rightChild = nodeLeft;
            nodeLeft->nodeType = node->nodeType;
            node->nodeType = BinaryNodeType::RIGHT;
            int lHeight = 0;
            int rHeight = 0;
            if (node->leftChild != nullptr)
                lHeight = node->leftChild->getHeight();
            if (node->rightChild != nullptr)
                rHeight = node->rightChild->getHeight();
            int nodeHeight = std::max(lHeight, rHeight)+1;
            node->setHeight(nodeHeight);
            node->setBalanceFactor(lHeight-rHeight);
            lHeight = 0;
            rHeight = 0;
            if (nodeLeft->leftChild != nullptr)
                lHeight = nodeLeft->leftChild->getHeight();
            if (nodeLeft->rightChild != nullptr)
                rHeight = nodeLeft->rightChild->getHeight();
            nodeHeight = std::max(lHeight, rHeight)+1;
            nodeLeft->setHeight(nodeHeight);
            nodeLeft->setBalanceFactor(lHeight-rHeight);
            if (nodeLeft->parent == nullptr)
                this->rootNode = nodeLeft;
        }

        void RR(AVLTreeNode<T>* node)
        {
            AVLTreeNode<T>* nodeRight = node->rightChild;
            nodeRight->parent = node->parent;
            node->parent = nodeRight;
            node->rightChild = nodeRight->leftChild;
            nodeRight->leftChild = node;
            if (node->rightChild!=nullptr)
            {
                node->rightChild->parent = node;
                node->rightChild->nodeType = BinaryNodeType::RIGHT;
            }
            if (node->nodeType == BinaryNodeType::LEFT)
                nodeRight->parent->leftChild = nodeRight;
            else if (node->nodeType == BinaryNodeType::RIGHT)
                nodeRight->parent->rightChild = nodeRight;
            nodeRight->nodeType = node->nodeType;
            node->nodeType = BinaryNodeType::LEFT;
            int lHeight = 0;
            int rHeight = 0;
            if (node->leftChild!=nullptr)
                lHeight = node->leftChild->getHeight();
            if (node->rightChild!=nullptr)
                rHeight = node->rightChild->getHeight();
            int nodeHeight = std::max(lHeight, rHeight)+1;
            node->setHeight(nodeHeight);
            node->setBalanceFactor(lHeight-rHeight);
            lHeight = 0;
            rHeight = 0;
            if (nodeRight->leftChild!=nullptr)
                lHeight = nodeRight->leftChild->getHeight();
            if (nodeRight->rightChild!=nullptr)
                rHeight = nodeRight->rightChild->getHeight();
            nodeHeight = std::max(lHeight, rHeight)+1;
            nodeRight->setHeight(nodeHeight);
            nodeRight->setBalanceFactor(lHeight-rHeight);
            if (nodeRight->parent==nullptr)
                this->rootNode = nodeRight;
        }

        void LR(AVLTreeNode<T>* node)
        {
            RR(node->leftChild);
            LL(node);
        }

        void RL(AVLTreeNode<T>* node)
        {
            LL(node->rightChild);
            RR(node);
        }

        static void coutNodeData(AVLTreeNode<T>* node, std::ostream& os)
        {
            if (node == nullptr)
                os << "N";
            else
                os << node->data;
        }

        static void coutSkip(std::ostream& os, const int height, const int level)
        {
            if (level <= 2)
                return;
            const int val = static_cast<int>(pow(2, height - level + 2)) - 1;
            for (int i = val; i > 0; i--)
            {
                os << " ";
            }
        }

         static void coutHorizontalLine(std::ostream& os, const int height, const int level)
        {
             if (level == 1)
             {
                 os << "\n";
                 return;
             }
            if (height == 1)
                return;
            const int val1 = static_cast<int>(pow(2, height - level + 2))-1;
            const int val2 = static_cast<int>(pow(2, level-2));
            for(int i=val2; i>0; i--)
            {
                for (int j = val1; j > 0; j--)
                {
                    os << "-";
                }
                coutSkip(os, height, level);
            }
            
            os << "\n";
        }

        static void coutVerticalLine(std::ostream& os, const int height, const int level)
        {
            if (height == 1)
            {
                return;
            }
            if (level == 1)
            {
                os << "|\n";
                return;
            }
            const int val = static_cast<int>(pow(2, level-2));
            for (int i=val; i>0; i--)
            {
                os<<"|";
                coutGaps(os, height, level);
                os << "|";
                coutSkip(os, height, level);
            }
            os << "\n";
        }

        static void coutSpace(std::ostream& os, const int height, const int level)
        {
            if (level == height)
                return;
            int val = 0;
            for (int j = height - level; j > 0; j--)
            {
                val+=static_cast<int>(pow(2, j)-1);
            }
            for (int i=val; i>0; i--)
            {
                os<<" ";
            }
        }

        static void coutGaps(std::ostream& os, const int height, const int level)
        {
            if (level == 1)
                return;
            const int val = static_cast<int>(pow(2, height - level+2))-3;
            for (int i=val; i>0; i--)
            {
                os<<" ";
            }
        }

        static void setChildNode(AVLTreeNode<T>* parentNode, AVLTreeNode<T>* childNode)
        {
            if (childNode == nullptr)
                return;
            if (parentNode->data > childNode->data)
            {
                parentNode->leftChild = childNode;
                childNode->parent = parentNode;
                childNode->nodeType = BinaryNodeType::LEFT;
            }
            else if (parentNode->data < childNode->data)
            {
                parentNode->rightChild = childNode;
                childNode->parent = parentNode;
                childNode->nodeType = BinaryNodeType::RIGHT;
            }
        }

        static void setIndex(AVLTreeNode<T>* node)
        {
            if (node->parent == nullptr)
            {
                node->index = 1;
                return;
            }
            if (node->nodeType == BinaryNodeType::LEFT)
                node->index = node->parent->index*2;
            else if (node->nodeType == BinaryNodeType::RIGHT)
                node->index = node->parent->index*2+1;
        }

        AVLTreeNode<T>* treeCopyCore(AVLTreeNode<T>* node)
        {
            if (node == nullptr)
                return nullptr;
            AVLTreeNode<T>* newNode = new AVLTreeNode<T>();
            newNode->data = node->data;
            newNode->nodeType = node->nodeType;
            newNode->setHeight(node->getHeight());
            newNode->setBalanceFactor(node->getBalanceFactor());
            newNode->index = node->index;
            AVLTreeNode<T>* lNode = treeCopyCore(node->leftChild);
            setChildNode(newNode, lNode);
            AVLTreeNode<T>* rNode = treeCopyCore(node->rightChild);
            setChildNode(newNode, rNode);
            return newNode;
        }
        
    public:
        AVLTree() = default;
        AVLTree(const AVLTree& other)
        {
            treeCopy(other);
        }
        ~AVLTree()
        {
           empty();
        }
        
        AVLTreeNode<T>* getRootNode() const
        {
            return this->rootNode;
        }
        
        AVLTreeNode<T>* insert(const T& data)
        {
            AVLTreeNode<T>* newNode = new AVLTreeNode<T>(data);
            if (this->rootNode == nullptr)
            {
                this->rootNode = newNode;
                return newNode;
            }
            AVLTreeNode<T>* currentNode = this->rootNode;
            AVLTreeNode<T>* previousNode = nullptr;
            while (currentNode != nullptr)
            {
                previousNode = currentNode;
                if (currentNode->data > data)
                {
                    currentNode = currentNode->leftChild;
                }
                else if (currentNode->data < data)
                {
                    currentNode = currentNode->rightChild;
                }
            }
            AVLTree<T>::setChildNode(previousNode, newNode);
            setTreeHeight(newNode);
            checkBalance(newNode);
            setIndex(newNode);
            return newNode;
        }

        template<typename Function>
        void preorderTraversal
        (
            Function callback,
            AVLTreeNode<T>* node
        )
        {
            std::stack<AVLTreeNode<T>*> nodeStack;
            AVLTreeNode<T>* currentNode = node;
            while (!nodeStack.empty() || currentNode != nullptr)
            {
                if (currentNode != nullptr)
                {
                    nodeStack.push(currentNode);
                    callback(currentNode);
                    currentNode = currentNode->leftChild;
                }
                else
                {
                    currentNode = nodeStack.top()->rightChild;
                    nodeStack.pop();
                }
            }
        }

        template<typename Function>
        void postorderTraversal
        (
            Function callback,
            AVLTreeNode<T>* node
        )
        {
            std::stack<AVLTreeNode<T>*> nodeStack;
            AVLTreeNode<T>* currentNode = node;
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

        void treeCopy(const AVLTree<T>& tree)
        {
            if (this->rootNode != nullptr)
                this->empty();
            this->rootNode = treeCopyCore(tree.getRootNode());
        }

        void empty()
        {
            postorderTraversal
            (
                [this](const AVLTreeNode<T>* node)
                {
                    delete node;
                },
                this->rootNode
            );
        }

        friend std::ostream& operator<<(std::ostream& os, const AVLTree<T>& avlTree)
        {
            std::queue<AVLTreeNode<T>*> nodeQueue;
            int height = avlTree.getRootNode()->getHeight();
            int level = 1;
            nodeQueue.push(avlTree.getRootNode());
            int counter = 0;
            while (level<=height)
            {
                coutSpace(os, height, level);
                coutHorizontalLine(os, height, level);
                if (level != 1)
                {
                    coutSpace(os, height, level);
                    coutVerticalLine(os, height, level);
                }
                
                coutSpace(os, height, level);
                for(int i=static_cast<int>(pow(2, level-1));i>0;--i)
                {
                    if (nodeQueue.front() != nullptr)
                    {
                        nodeQueue.push(nodeQueue.front()->leftChild);
                        nodeQueue.push(nodeQueue.front()->rightChild);

                    }
                    else
                    {
                        nodeQueue.push(nullptr);
                        nodeQueue.push(nullptr);
                    }
                    coutNodeData(nodeQueue.front(), os);
                    counter++;
                    
                    if (counter % 2 == 0)
                    {
                        coutSkip(os, height, level);
                    }
                    else
                    {
                        coutGaps(os, height, level);
                    }
                    nodeQueue.pop();
                }
                os<<"\n";
                coutSpace(os, height, level);
                if(!(level==height&&counter!=0))
                    coutVerticalLine(os, height, level);              
                level++;
                counter = 0;
            }
            return os;
        }

        void coutAVLTree()
        {
            XLog::Log(*this, LogLevel::LOG_INFO);
        }
    };
}