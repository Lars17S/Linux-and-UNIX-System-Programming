#ifndef _NODE_H_
#define _NODE_H_

template<class T>
class Node {
private:
    T key;
    Node<T>* left;
    Node<T>* right;
    int height;
public:
    double x, y;
    Node();
    Node(T key);
    void setKey(T key);
    T getKey();
    void setLeft(Node<T>* left);
    Node<T>* getLeft();
    Node<T>* getRight();
    void setRight(Node<T>* right);
    void setHeight(int height);
    int getHeight();
    void refreshPosXChild(int height);
};

#include "node.cpp"
#endif