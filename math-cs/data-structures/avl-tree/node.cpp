#include <cstddef>
#include <iostream>
#include <math.h>

#include "node.h"

using namespace std;
 
template <class T>
Node<T>::Node() {
    height = 1;
    left = NULL;
    right = NULL;
    y = -1;
    x = -1;
}

template <class T>
Node<T>::Node(T key) {
    this->key = key;
    height = 1;
    left = NULL;
    right = NULL;
    y = -1;
    x = -1;
}

template <class T>
void Node<T>::setKey(T key) {
        this->key = key;
}

template <class T>
T Node<T>::getKey() {
    return key;
}

template <class T>
void Node<T>::setLeft(Node<T>* left) {
    this->left = left;
}

template <class T>
Node<T>* Node<T>::getLeft() {
    return left;
}

template <class T>
void Node<T>::setRight(Node<T>* right) {
    this->right = right;
}

template <class T>
Node<T>* Node<T>::getRight() {
    return right;
}

template <class T>
void Node<T>::setHeight(int height) {
    this->height = height;
}

template <class T>
int Node<T>::getHeight() {
    return height;
}

template <class T>
void Node<T>::refreshPosXChild(int height) {
    cout << "NODE: " << key << " pos x root: " << x << " height: " << height << " -> ";
    if (left != NULL) {
        (*left).x = x - ((double)1 / (double)2) * ((double)1000 / pow(2, height));
        cout << " left child: " << (*left).getKey() << " posX: " << (*left).x;
    }
        
    if (right != NULL) {
        (*right).x = x + ((double)1 / (double)2) * ((double)1000 / pow(2, height));
        cout << " | right child: " << (*right).getKey() << " posX: " << (*right).x;
    }
    cout << endl << endl;
        
}