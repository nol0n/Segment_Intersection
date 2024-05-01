#pragma once

#include "Node.hpp"

template <typename T>
class TwoThreeTree
{
private:
    Node<T> *root;

    Node<T> *internalInsert(Node<T> *root, T key);
    Node<T> *internalSearch(Node<T> *root, T key);
    Node<T> *internalRemove(Node<T> *root, T key);
    Node<T> *findMin(Node<T> *root);
    Node<T> *findMax(Node<T> *root);
    Node<T> *fix(Node<T> *leaf);
    Node<T> *merge(Node<T> *leaf);
    Node<T> *split(Node<T> *item);
    Node<T> *redistribute(Node<T> *leaf);

public:
    TwoThreeTree<T>();

    T findSuccessor(T key);
    T findPredecessor(T key);

    void insert(T key);
    void remove(T key);
    bool search(T key);
};

template <typename T>
TwoThreeTree<T>::TwoThreeTree()
{
    root = nullptr;
}

template <typename T>
T TwoThreeTree<T>::findSuccessor(T key)
{
    Node<T> *keyNode = internalSearch(root, key);
    T value = T();

    if (keyNode != nullptr)
    {
        if (keyNode->isLeaf())
        {
            if (keyNode->size == 2 && key == keyNode->key[0])
            {
                value = keyNode->key[1];
            }
            else if ((keyNode->size == 2 && key == keyNode->key[1]) || keyNode->size == 1)
            {
                while (keyNode->parent != nullptr &&
                       ((keyNode->parent->size == 2 && keyNode->parent->third == keyNode) ||
                        (keyNode->parent->size == 1 && keyNode->parent->second == keyNode)))
                {
                    keyNode = keyNode->parent;
                }
                if (keyNode->parent != nullptr)
                {
                    if (keyNode->parent->first == keyNode)
                    {
                        value = keyNode->parent->key[0];
                    }
                    else if (keyNode->parent->second == keyNode)
                    {
                        value = keyNode->parent->key[1];
                    }
                }
            }
        }
        else
        {
            if (key == keyNode->key[0])
            {
                value = findMin(keyNode->second)->key[0];
            }
            else if (key == keyNode->key[1])
            {
                value = findMin(keyNode->third)->key[0];
            }
        }
    }

    return value;
}

template <typename T>
T TwoThreeTree<T>::findPredecessor(T key)
{
    Node<T> *keyNode = internalSearch(root, key);
    T value = T();

    if (keyNode != nullptr)
    {
        if (keyNode->isLeaf())
        {
            if ((keyNode->size == 2) || keyNode->size == 1)
            {
                if (key == keyNode->key[1])
                {
                    value = keyNode->key[0];
                }
                else if (key == keyNode->key[0])
                {
                    while (keyNode->parent != nullptr && keyNode->parent->first == keyNode)
                    {
                        keyNode = keyNode->parent;
                    }
                    if (keyNode->parent != nullptr)
                    {
                        if (keyNode->parent->second == keyNode)
                        {
                            value = keyNode->parent->key[0];
                        }
                        else if (keyNode->parent->third == keyNode)
                        {
                            value = keyNode->parent->key[1];
                        }
                    }
                }
            }
        }
        else
        {
            if (key == keyNode->key[0])
            {
                value = findMax(keyNode->first)->key[0];
            }
            else if (key == keyNode->key[1])
            {
                value = findMax(keyNode->second)->key[0];
            }
        }
    }

    return value;
}

template <typename T>
void TwoThreeTree<T>::insert(T key)
{
    root = internalInsert(root, key);
}

template <typename T>
void TwoThreeTree<T>::remove(T key)
{
    root = internalRemove(root, key);
}

template <typename T>
bool TwoThreeTree<T>::search(T key)
{
    return (!internalSearch(root, key) ? false : true);
}

template <typename T>
Node<T> *TwoThreeTree<T>::internalInsert(Node<T> *root, T key)
{
    if (root == nullptr)
    {
        return new Node<T>(key);
    }

    if (root->isLeaf())
    {
        root->insertToNode(key);
    }
    else if (key <= root->key[0])
    {
        internalInsert(root->first, key);
    }
    else if ((root->size == 1) || ((root->size == 2) && key <= root->key[1]))
    {
        internalInsert(root->second, key);
    }
    else
    {
        internalInsert(root->third, key);
    }

    return split(root);
}

template <typename T>
Node<T> *TwoThreeTree<T>::internalSearch(Node<T> *root, T key)
{
    Node<T> *pNode = nullptr;

    if (root == nullptr)
    {
        pNode = nullptr;
    }

    if (root->find(key))
    {
        pNode = root;
    }
    else if (key < root->key[0])
    {
        pNode = internalSearch(root->first, key);
    }
    else if ((root->size == 2) && (key < root->key[1]) || (root->size == 1))
    {
        pNode = internalSearch(root->second, key);
    }
    else if (root->size == 2)
    {
        pNode = internalSearch(root->third, key);
    }

    return pNode;
}

template <typename T>
Node<T> *TwoThreeTree<T>::internalRemove(Node<T> *root, T key)
{
    Node<T> *item = internalSearch(root, key);

    if (!item)
    {
        return root;
    }

    Node<T> *min = nullptr;
    if (item->key[0] == key)
    {
        min = findMin(item->second);
    }
    else
    {
        min = findMin(item->third);
    }

    if (min)
    {
        T &z = (key == item->key[0] ? item->key[0] : item->key[1]);
        item->swap(z, min->key[0]);
        item = min;
    }

    item->removeFromNode(key);
    return fix(item);
}

template <typename T>
Node<T> *TwoThreeTree<T>::findMin(Node<T> *root)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->first == nullptr)
    {
        return root;
    }
    else
    {
        return findMin(root->first);
    }
}

template <typename T>
Node<T> *TwoThreeTree<T>::findMax(Node<T> *root)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->third == nullptr)
    {
        if (root->second == nullptr)
        {
            return root;
        }
        return findMax(root->second);
    }
    else
    {
        return findMax(root->third);
    }
}

template <typename T>
Node<T> *TwoThreeTree<T>::fix(Node<T> *leaf)
{
    if (leaf->size == 0 && leaf->parent == nullptr)
    {
        delete leaf;
        return nullptr;
    }
    if (leaf->size != 0)
    {
        if (leaf->parent)
        {
            return fix(leaf->parent);
        }
        else
        {
            return leaf;
        }
    }

    Node<T> *parent = leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
    {
        leaf = redistribute(leaf);
    }
    else if (parent->size == 2 && parent->third->size == 2)
    {
        leaf = redistribute(leaf);
    }
    else
    {
        leaf = merge(leaf);
    }

    return fix(leaf);
}

template <typename T>
Node<T> *TwoThreeTree<T>::merge(Node<T> *leaf)
{
    Node<T> *parent = leaf->parent;

    if (parent->first == leaf)
    {
        parent->second->insertToNode(parent->key[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != nullptr)
        {
            parent->second->first = leaf->first;
        }
        else if (leaf->second != nullptr)
        {
            parent->second->first = leaf->second;
        }

        if (parent->second->first != nullptr)
        {
            parent->second->first->parent = parent->second;
        }

        parent->removeFromNode(parent->key[0]);
        delete parent->first;
        parent->first = nullptr;
    }
    else if (parent->second == leaf)
    {
        parent->first->insertToNode(parent->key[0]);

        if (leaf->first != nullptr)
        {
            parent->first->third = leaf->first;
        }
        else if (leaf->second != nullptr)
        {
            parent->first->third = leaf->second;
        }

        if (parent->first->third != nullptr)
        {
            parent->first->third->parent = parent->first;
        }

        parent->removeFromNode(parent->key[0]);
        delete parent->second;
        parent->second = nullptr;
    }

    if (parent->parent == nullptr)
    {
        Node<T> *tmp = nullptr;
        if (parent->first != nullptr)
        {
            tmp = parent->first;
        }
        else
        {
            tmp = parent->second;
        }
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}

template <typename T>
Node<T> *TwoThreeTree<T>::split(Node<T> *item)
{
    if (item->size < 3)
    {
        return item;
    }

    Node<T> *x = new Node<T>(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
    Node<T> *y = new Node<T>(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);
    if (x->first)
    {
        x->first->parent = x;
    }
    if (x->second)
    {
        x->second->parent = x;
    }
    if (y->first)
    {
        y->first->parent = y;
    }
    if (y->second)
    {
        y->second->parent = y;
    }

    if (item->parent)
    {
        item->parent->insertToNode(item->key[1]);

        if (item->parent->first == item)
        {
            item->parent->first = nullptr;
        }
        else if (item->parent->second == item)
        {
            item->parent->second = nullptr;
        }
        else if (item->parent->third == item)
        {
            item->parent->third = nullptr;
        }

        if (item->parent->first == nullptr)
        {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (item->parent->second == nullptr)
        {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else
        {
            item->parent->fourth = y;
            item->parent->third = x;
        }

        Node<T> *tmp = item->parent;
        delete item;
        return tmp;
    }
    else
    {
        x->parent = item;
        y->parent = item;
        item->makeTwoNode(item->key[1], x, y);
        return item;
    }
}

template <typename T>
Node<T> *TwoThreeTree<T>::redistribute(Node<T> *leaf)
{
    Node<T> *parent = leaf->parent;
    Node<T> *first = parent->first;
    Node<T> *second = parent->second;
    Node<T> *third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2))
    {
        if (first == leaf)
        {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = nullptr;
            parent->first->insertToNode(parent->key[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != nullptr)
            {
                parent->first->first = leaf->first;
            }
            else if (leaf->second != nullptr)
            {
                parent->first->first = leaf->second;
            }

            if (parent->first->first != nullptr)
            {
                parent->first->first->parent = parent->first;
            }

            parent->removeFromNode(parent->key[0]);
            delete first;
        }
        else if (second == leaf)
        {
            first->insertToNode(parent->key[0]);
            parent->removeFromNode(parent->key[0]);
            if (leaf->first != nullptr)
            {
                first->third = leaf->first;
            }
            else if (leaf->second != nullptr)
            {
                first->third = leaf->second;
            }

            if (first->third != nullptr)
            {
                first->third->parent = first;
            }

            parent->second = parent->third;
            parent->third = nullptr;

            delete second;
        }
        else if (third == leaf)
        {
            second->insertToNode(parent->key[1]);
            parent->third = nullptr;
            parent->removeFromNode(parent->key[1]);
            if (leaf->first != nullptr)
            {
                second->third = leaf->first;
            }
            else if (leaf->second != nullptr)
            {
                second->third = leaf->second;
            }

            if (second->third != nullptr)
            {
                second->third->parent = second;
            }
            delete third;
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2)))
    {
        if (third == leaf)
        {
            if (leaf->first != nullptr)
            {
                leaf->second = leaf->first;
                leaf->first = nullptr;
            }

            leaf->insertToNode(parent->key[1]);
            if (second->size == 2)
            {
                parent->key[1] = second->key[1];
                second->removeFromNode(second->key[1]);
                leaf->first = second->third;
                second->third = nullptr;
                if (leaf->first != nullptr)
                {
                    leaf->first->parent = leaf;
                }
            }
            else if (first->size == 2)
            {
                parent->key[1] = second->key[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != nullptr)
                {
                    leaf->first->parent = leaf;
                }

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                first->removeFromNode(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr)
                {
                    second->first->parent = second;
                }
                first->third = nullptr;
            }
        }
        else if (second == leaf)
        {
            if (third->size == 2)
            {
                if (leaf->first == nullptr)
                {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                second->insertToNode(parent->key[1]);
                parent->key[1] = third->key[0];
                third->removeFromNode(third->key[0]);
                second->second = third->first;
                if (second->second != nullptr)
                {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
            else if (first->size == 2)
            {
                if (leaf->second == nullptr)
                {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }
                second->insertToNode(parent->key[0]);
                parent->key[0] = first->key[1];
                first->removeFromNode(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr)
                {
                    second->first->parent = second;
                }
                first->third = nullptr;
            }
        }
        else if (first == leaf)
        {
            if (leaf->first == nullptr)
            {
                leaf->first = leaf->second;
                leaf->second = nullptr;
            }
            first->insertToNode(parent->key[0]);
            if (second->size == 2)
            {
                parent->key[0] = second->key[0];
                second->removeFromNode(second->key[0]);
                first->second = second->first;
                if (first->second != nullptr)
                {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
            }
            else if (third->size == 2)
            {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                third->removeFromNode(third->key[0]);
                first->second = second->first;
                if (first->second != nullptr)
                {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = third->first;
                if (second->second != nullptr)
                {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
        }
    }
    else if (parent->size == 1)
    {
        leaf->insertToNode(parent->key[0]);

        if (first == leaf && second->size == 2)
        {
            parent->key[0] = second->key[0];
            second->removeFromNode(second->key[0]);

            if (leaf->first == nullptr)
            {
                leaf->first = leaf->second;
            }

            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = nullptr;
            if (leaf->second != nullptr)
            {
                leaf->second->parent = leaf;
            }
        }
        else if (second == leaf && first->size == 2)
        {
            parent->key[0] = first->key[1];
            first->removeFromNode(first->key[1]);

            if (leaf->second == nullptr)
            {
                leaf->second = leaf->first;
            }

            leaf->first = first->third;
            first->third = nullptr;
            if (leaf->first != nullptr)
            {
                leaf->first->parent = leaf;
            }
        }
    }
    return parent;
}
