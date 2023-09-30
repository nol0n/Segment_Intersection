#pragma once

template <typename T>
class TwoThreeTree;

template <typename T>
class Node
{
private:
	int size;
	T key[3];
	Node<T>* first;
	Node<T>* second;
	Node<T>* third;
	Node<T>* fourth;
	Node<T>* parent;

    bool find(T item);
    void swap(T& x, T& y);
    void sort();
    void insertToNode(T item);
    void removeFromNode(T item);
    void makeTwoNode(T item, Node<T>* first, Node<T>* second);
    bool isLeaf();
public:
    Node<T>(T item);
    Node<T>(T item, Node<T>* first, Node<T>* second, Node<T>* third, Node<T>* fourth, Node<T>* parent);

    friend class TwoThreeTree<T>;
};

template <typename T>
Node<T>::Node(T item) : key{ item, T(), T() }
{
    size   = 1;
    first  = nullptr;
    second = nullptr;
    third  = nullptr;
    fourth = nullptr;
    parent = nullptr;
}

template <typename T>
Node<T>::Node(T item, Node<T>* first, Node<T>* second, Node<T>* third, Node<T>* fourth, Node<T>* parent) : key{ item, T(), T() }
{
    size         = 1;
    this->first  = first;
    this->second = second;
    this->third  = third;
    this->fourth = fourth;
    this->parent = parent;
}

template <typename T>
bool Node<T>::find(T item) 
{
    for (int i = 0; i < size; i++)
    {
        if (key[i] == item) return true;
    }
    return false;
}

template <typename T>
void Node<T>::swap(T& x, T& y) 
{
    T tmp = x;
    x   = y;
    y   = tmp;
}

template <typename T>
void Node<T>::sort()
{
    if (size <= 1) return;

    if (size == 2) {
        if (key[0] > key[1]) swap(key[0], key[1]);
    }
    else if (size == 3) {
        if (key[0] > key[1]) swap(key[0], key[1]);
        if (key[0] > key[2]) swap(key[0], key[2]);
        if (key[1] > key[2]) swap(key[1], key[2]);
    }
}

template <typename T>
void Node<T>::insertToNode(T item) 
{ 
    key[size] = item;
    size++;
    sort();
}

template <typename T>
void Node<T>::removeFromNode(T item) 
{
    if (size >= 1 && key[0] == item) 
    {
        key[0] = key[1];
        key[1] = key[2];
        size--;
    }
    else if (size == 2 && key[1] == item) 
    {
        key[1] = key[2];
        size--;
    }
}

template <typename T>
void Node<T>::makeTwoNode(T item, Node<T>* first, Node<T>* second) 
{
    size         = 1;
    key[0]       = item;
    this->first  = first;
    this->second = second;
    this->third  = nullptr;
    this->fourth = nullptr;
    this->parent = nullptr;

}

template <typename T>
bool Node<T>::isLeaf() 
{
    return (first == nullptr) && (second == nullptr) && (third == nullptr);
}