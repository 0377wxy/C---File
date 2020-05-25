#include <iostream>
using namespace std;

template <class TT>
class TreeNode
{
private:
    int key;
    TT payload;
    int balanceFactor = 0;
    TreeNode<TT> *leftChild;
    TreeNode<TT> *rightChild;
    TreeNode<TT> *parent;

public:
    TreeNode(int key, TT val, TreeNode<TT> *left = NULL,
             TreeNode<TT> *right = NULL, TreeNode<TT> *parent = NULL);
    bool hasLeftChild();
    bool hasRightChild();
    bool isLeftChild();
    bool isRightChild();
    bool isRoot();
    bool isLeaf();
    bool hasAnyChildren();
    bool hasBothChildren();
    void replaceNodeData(int key, TT val, TreeNode<TT> *left,
                         TreeNode<TT> *right, TreeNode<TT> *parent);
    TreeNode<TT> *findSuccessor();
    TreeNode<TT> *finMin();
    void splicOut();
};

template <class TT>
TreeNode<TT>::TreeNode(int key, TT val, TreeNode<TT> *left,
                       TreeNode<TT> *right, TreeNode<TT> *parent) : key(key), payload(val), leftChild(left),
                                                                    rightChild(right) {}
template <class TT>
bool TreeNode<TT>::hasLeftChild()
{
    if (leftChild == NULL)
        return false;
    else
        return true;
}

template <class TT>
bool TreeNode<TT>::hasRightChild()
{
    if (rightChild == NULL)
        return false;
    else
        return true;
}
template <class TT>
bool TreeNode<TT>::isLeftChild()
{
    if (parent->leftChild == this)
        return true;
    else
        return false;
}
template <class TT>
bool TreeNode<TT>::isRightChild()
{
    if (parent->rightChild == this)
        return true;
    else
        return false;
}

template <class TT>
bool TreeNode<TT>::isRoot()
{
    if (parent == NULL)
        return true;
    else
        return false;
}
template <class TT>
bool TreeNode<TT>::isLeaf()
{
    if (leftChild == NULL || rightChild == NULL)
        return true;
    else
        return false;
}

template <class TT>
bool TreeNode<TT>::hasAnyChildren()
{
    return !(this->isLeft());
}

template <class TT>
bool TreeNode<TT>::hasBothChildren()
{
    if (leftChild == NULL && rightChild == NULL)
        return true;
    else
        return false;
}

template <class TT>
void TreeNode<TT>::replaceNodeData(int key, TT val, TreeNode<TT> *left,
                                   TreeNode<TT> *right, TreeNode<TT> *parent)
{
    key = key;
    payload = val;
    rightChild = right;
    leftChild = left;
    if (this->isLeftChild())
        leftChild->parent = this;
    if (this->hasRightChild())
        rightChild->parent = this;
}
template <class TT>
TreeNode<TT> *TreeNode<TT>::findSuccessor()
{
    TreeNode<TT> *succ = NULL;
    if (this->hasRightChild())
        succ = this->finMin();
    else
    {
        if (this->parent != NULL)
        {
            if (this->isLeftChild())
                succ = parent;
            else
            {
                parent->rightChild = NULL;
                succ = parent->findSuccessor();
                parent->rightChild = this;
            }
        }
    }
    return succ;
}

template <class TT>
TreeNode<TT> *TreeNode<TT>::finMin()
{
    TreeNode<TT> *current = this;
    while (current->hasLeftChild())
        current = current->leftChild;
    return current;
}

template <class TT>
void TreeNode<TT>::splicOut()
{
    if (this->isLeaf())
    {
        if (this->isLeftChild())
            parent->leftChild = NULL;
        else
            parent->rightChild = NULL;
        delete this;
    }
    else if (this->hasAnyChildren)
    {
        if (this->hasLeftChild())
        {
            if (this->isLeftChild())
                parent->leftChild = leftChild;
            else
                parent->rightChild = leftChild;
            leftChild->parent = parent;
        }
        else
        {
            if (this->isLeftChild())
                parent->leftChild = rightChild;
            else
                parent->rightChild = rightChild;
            rightChild->parent = parent;
        }
        delete this;
    }
}

template <class TT>
class BinarySearchTree
{
private:
    int size = 0;
    TreeNode<TT> *root = NULL;

public:
    friend class TreeNode;
    int lenght();
    void put(int key, TT val);
    void _put(int key, TT val, TreeNode<TT> *currentNode);
    void updateBalance(TreeNode<TT> *node);
    TT *get(int key);
    TreeNode<TT> *_get(int key, TreeNode<TT> *currentNode);
    void delete (int key);
    void remove(TreeNode<TT> *currentNode);
    TT &operator[](int key);
    void rotateLeft(TreeNode<TT> *rotRoot);
    void rotateRight(TreeNode<TT> *rotRoot);
    void rebalance(TreeNode<TT> *node);
};

template <class TT>
int BinarySearchTree<TT>::lenght()
{
    return size;
}

template <class TT>
void BinarySearchTree<TT>::put(int key, TT val)
{
    if (root == NULL)
        this->_put(key, val, root);
    else
        root = new TreeNode<TT>(key, val);
    size++;
}

template <class TT>
void BinarySearchTree<TT>::_put(int key, TT val, TreeNode<TT> *currentNode)
{
    if (key < currentNode->key)
    {
        if (currentNode->hasLeftChild())
            this->_put(key, val, currentNode->leftChild);
        else
        {
            currentNode->leftChild = new TreeNode<TT>(key, val);
            currentNode->leftChild->parent = currentNode;
            this->updateBalance(currentNode->leftChild);
        }
    }
    else
    {

        if (currentNode->hasRightChild())
            this->_put(key, val, currentNode->rightChild);
        else
        {
            currentNode->rightChild = new TreeNode<TT>(key, val);
            currentNode->rightChild->parent = currentNode;
            this->updateBalance(currentNode->rightChild);
        }
    }
}

template <class TT>
void BinarySearchTree<TT>::updateBalance(TreeNode<TT> *node)
{
    if (node->balanceFactor > 1 || node->balanceFactor < -1)
    {
        this->rebalance(node);
        return;
    }
    if (node->parent != NULL)
    {
        if (node->isLeftChild())
            node->parent->balanceFactor++;
        else
        {
            if (node->isRightChild())
            {
                node->parent->balanceFactor--;
            }
        }
        if (node->parent->balanceFactor != 0)
            this->updateBalance(node->parent)
    }
}

template <class TT>
TT *BinarySearchTree<TT>::get(int key)
{
    if (root != NULL)
    {
        TreeNode<TT> *res = this->_get(key, root);
        if (res != NULL)
            return &(res->payload);
        else
            return NULL;
    }
    else
        return NULL;
}

template <class TT>
TreeNode<TT> *BinarySearchTree<TT>::_get(int key, TreeNode<TT> *currentNode)
{
    if (currentNode == NULL)
        return NULL;
    else if (currentNode->key == key)
    {
        return currentNode;
    }
    else if (key < currentNode.key)
    {
        return this->_get(key, currentNode->leftChild)
    }
    else
        return this->_get(key, currentNode->rightChild)
}