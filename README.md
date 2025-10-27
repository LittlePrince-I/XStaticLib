# 算法

## 排序算法

### 1.插入排序

时间复杂度：$ \log n $



```c++
template <typename T>
void InsertSort(std::vector<T>& arr)
{
	for (size_t i = 1; i < arr.size(); i++)
	{
		T key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
```
### 2.冒泡排序
时间复杂度：$ n^{2} $
```c++
template <typename T>
void BubbleSort(std::vector<T>& arr)
{
    if (arr.empty()) return;
    for (size_t i = 0; i < arr.size() - 1; ++i)
    {
        bool swapped = false;
        for (size_t j = 0; j < arr.size() - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```





# 数据结构

## 一、树

### (一）二叉树

#### 1.完全二叉树

只有最后一层空缺（可满可不满），并且最后一层结点从左到右排列。

#### 2.性质

（1）当前层(n)最大子结点数 ：$2^{n-1}$

（2）总结点数：

​		 $E = 2^n-1 = n_0+n_1+n_2$

​	    $n_x,x$为该结点子结点数。

（3）总边数：

​        $B=E-1=n_1+2n_2$

​        每个子结点有一边，根结点没有。

（4）任意二叉树满足：

​		 $n_0=n_2+1$

（5）完全二叉树得：

​		 总结点数n

​		 $2^{k-1}-1<n<=2^k-1$

​       因为n为整数

​		 $2^{k-1}<=n<=2^k-1$

​		 只看左边

​		 同时取对数：

​		 $k-1<=log_2n$

​		 综上一棵具有n个结点的完全二叉树深度为$k=\lfloor log_2n\rfloor+1$

（6）n个结点的完全二叉树编号i，从上往下，从左往右

![image-20250801213156872](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20250801213156872.png)

- 一个有左右孩子的结点左孩子为$2i$，右孩子为$2i+1$。

- 如果$2i$大于n，结点i没有左孩子。

- 如果$2i+1$大于n，结点i没有右孩子。

#### 3.二叉树的遍历

##### 3.1前序遍历

###### （1）定义

**前序遍历（Pre-order Traversal）** 是一种深度优先遍历方式，遍历顺序为：

* 访问根节点。

* 遍历左子树。

* 遍历右子树。

###### （2）算法逻辑

前序遍历的核心思想是先访问根节点，然后递归地遍历左子树和右子树。递归终止条件是当前节点为空。

###### （3）递归实现

递归实现是最直观的前序遍历方法。

```c++
template<typename T, typename Function>
void preorderTraversal
	(
	BinaryTreeNode<T>* node, 
	Function function
	) 
	{
    if (node == nullptr) 
        return;
    function(node);
    preorderTraversal(node->leftChild, function);
    preorderTraversal(node->rightChild, function);
}
```



###### （4）非递归实现

非递归实现需要借助栈来模拟递归过程。

```c++
template<typename T, typename Function>
void preorderTraversal
	(
	BinaryTreeNode<T>* node, 
	Function function
	) 
	{
		std::stack<BinaryTreeNode<T>*> nodeStack;
		BinaryTreeNode<T>* currentNode = node;
		while (currentNode != nullptr || !nodeStack.empty())
    	{
        	if(currentNode != nullptr)
        	{
            	function(currentNode);
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
```



###### （5）示例

假设我们有以下二叉树：

        1
       / \
      2   3
     / \
    4   5

**输出结果**：

```
1 2 4 5 3
```

###### （6）时间复杂度与空间复杂度

- **时间复杂度**：*O*(*n*)，其中 *n* 是二叉树的节点数。每个节点恰好被访问一次。
- **空间复杂度**：
  - 递归实现：*O*(*h*)，其中 *h* 是二叉树的高度。递归调用栈的深度等于树的高度。
  - 非递归实现：*O*(*n*)，最坏情况下栈中可能存储所有节点。

###### （7）应用场景

前序遍历常用于以下场景：

+ **复制二叉树**：通过前序遍历可以方便地复制整个二叉树。

+ **序列化二叉树**：前序遍历可以用于将二叉树序列化为字符串。

+ **表达式树**：在表达式树中，前序遍历可以用于生成前缀表达式。

##### 3.2中序遍历

###### （1）定义

**中序遍历（In-order Traversal）** 是一种深度优先遍历方式，遍历顺序为：

* 遍历左子树。

* 访问根节点。

* 遍历右子树。

中序遍历的特点是，对于二叉搜索树（BST），中序遍历的结果是一个递增的有序序列。

###### （2）算法逻辑

中序遍历的核心思想是先递归地遍历左子树，然后访问根节点，最后递归地遍历右子树。递归终止条件是当前节点为空。

###### （3）递归实现

递归实现是最直观的中序遍历方法。

```c++
template<typename T, typename Function>
void inorderTraversal(BinaryTreeNode<T>* node, Function function) 
	{
    if (node == nullptr) 
    {
        return;
    }
    inorderTraversal(node->leftChild, function);
    function(node);
    inorderTraversal(node->rightChild, function);
}
```

###### （4）非递归实现

非递归实现需要借助栈来模拟递归过程。

```c++
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
```

###### （5）示例

假设我们有以下二叉树：

        1
       / \
      2   3
     / \
    4   5

**输出结果：**

```(空)
4 2 5 1 3
```

###### （6）时间复杂度与空间复杂度

- **时间复杂度**：*O*(*n*)，其中 *n* 是二叉树的节点数。每个节点恰好被访问一次。
- **空间复杂度**：
  - 递归实现：*O*(*h*)，其中 *h* 是二叉树的高度。递归调用栈的深度等于树的高度。
  - 非递归实现：*O*(*n*)，最坏情况下栈中可能存储所有节点。

###### （7）应用场景

中序遍历常用于以下场景：

- **二叉搜索树（BST）**：中序遍历可以生成一个递增的有序序列。
- **表达式树**：中序遍历可以用于生成中缀表达式。
- **树的遍历和操作**：中序遍历是树遍历的基础，可以用于各种树的操作和算法。

##### 3.3后序遍历

###### （1）定义

**后序遍历（Post-order Traversal）** 是一种深度优先遍历方式，遍历顺序为：

* 遍历左子树。

* 遍历右子树。

* 访问根节点。

后序遍历的特点是，根节点是最后被访问的。这种遍历方式常用于删除二叉树中的节点，因为需要先删除子节点，再删除根节点。

###### （2）算法逻辑

后序遍历的核心思想是先递归地遍历左子树，然后递归地遍历右子树，最后访问根节点。递归终止条件是当前节点为空。

###### （3）递归实现

递归实现是最直观的后序遍历方法。

```c++
template<typename T, typename Function>
void postorderTraversal
	(
    BinaryTreeNode<T>* node,
    Function function
	) 
	{
    if (node == nullptr) 
    {
        return;
    }
    postorderTraversal(node->leftChild, function);
    postorderTraversal(node->rightChild, function);
    function(node);
}
```

###### （4）非递归实现

非递归实现需要借助栈来模拟递归过程。后序遍历的非递归实现相对复杂，因为需要确保右子树在根节点之前被访问。

```c++
template<typename Function>
        void postorderTraversal
        (
            Function callback,
            BinaryTreeNode<T>* node
        ) const
        {
            std::stack<BinaryTreeNode<T>*> nodeStack;
            BinaryTreeNode<T>* currentNode = node;
            BinaryTreeNode<T>* lastVisitedNode = nullptr;
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
```

###### （5）示例

假设我们有以下二叉树：

        1
       / \
      2   3
     / \
    4   5

**输出结果**：

```
4 5 2 3 1
```

###### （6）时间复杂度与空间复杂度

- **时间复杂度**：*O*(*n*)，其中 *n* 是二叉树的节点数。每个节点恰好被访问一次。
- **空间复杂度**：
  - 递归实现：*O*(*h*)，其中 *h* 是二叉树的高度。递归调用栈的深度等于树的高度。
  - 非递归实现：*O*(*n*)，最坏情况下栈中可能存储所有节点。

###### （7）应用场景

后序遍历常用于以下场景：

- **删除二叉树节点**：后序遍历可以确保先删除子节点，再删除根节点。
- **表达式树**：后序遍历可以用于生成后缀表达式。
- **树的遍历和操作**：后序遍历是树遍历的基础，可以用于各种树的操作和算法。

##### 3.4层序遍历

###### （1）定义

**层序遍历（Level-order Traversal）** 是一种广度优先遍历方式，遍历顺序为：

* 从根节点开始，逐层遍历。

* 每一层从左到右依次访问节点。

层序遍历的特点是，它按照从上到下、从左到右的顺序访问所有节点。

###### （2）算法逻辑

层序遍历的核心思想是使用队列来逐层访问节点。具体步骤如下：

* 将根节点加入队列。

* 当队列不为空时，执行以下操作：

  - 从队列中取出一个节点，访问该节点。

  - 将该节点的左子节点（如果存在）加入队列。

  * 将该节点的右子节点（如果存在）加入队列。

* 重复上述过程，直到队列为空。

###### （3）代码实现

以下是层序遍历的代码实现：

```c++
template<typename T, typename Function>
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
```

###### （4）示例

假设我们有以下二叉树：

        1
       / \
      2   3
     / \
    4   5

**输出结果**：

```
1 2 3 4 5
```

###### （5）时间复杂度与空间复杂度

- **时间复杂度**：*O*(*n*)，其中 *n* 是二叉树的节点数。每个节点恰好被访问一次。
- **空间复杂度**：*O*(*n*)，最坏情况下队列中可能存储所有节点。

###### （6）应用场景

层序遍历常用于以下场景：

- **按层打印二叉树**：逐层打印二叉树的节点。
- **计算二叉树的深度**：通过层序遍历可以方便地计算二叉树的深度。
- **查找特定层的节点**：可以方便地找到特定层的所有节点。

### （二）高级树结构

