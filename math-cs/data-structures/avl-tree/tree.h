#ifndef _TREE_H_
#define _TREE_H_

template<class T>
class Tree {
private:
    Node<T>* root;
public: 
    Tree();
    Tree(T key);
    void setRoot(T key);
    Node<T>* getRoot();
    Node<T>* rightRotate(Node<T>* node_y);
    Node<T>* leftRotate(Node<T>* node_x);
    int getBalance(Node<T>* node);
    int height(Node<T>* node);
    void insert(T key);
    Node<T>* insertUtil(Node<T>* node, T key);
    Node<T>* minValueNode(Node<T>* node);
    void deleteNode(T key);
    Node<T>* deleteUtil(Node<T>* root, T key);
    void printPreOrder();
    void preOrderRec(Node<T>* node);
    void printInOrder();
    void inOrderRec(Node<T>* node);
    void print2D();
    void print2DUtil(Node<T>* node, int space);
    void calculatePos();
    void calculatePosUtil(Node<T>* node, int height);
};

#include "tree.cpp"
#endif