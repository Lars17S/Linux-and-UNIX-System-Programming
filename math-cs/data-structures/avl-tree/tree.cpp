#include "tree.h"
#include <iostream>
using namespace std;
#define COUNT 10;

template <class T>
Tree<T>::Tree() {
    root = NULL;
}

template <class T>
Tree<T>::Tree(T key) {
    Node<T>* new_node = new Node(key);
    root = new_node;
    (*root)->x = 1000;
}

template <class T>
void Tree<T>::setRoot(T key) {
    Node<T>* new_node = new Node(key);
    root = new_node; 
    (*root)->x = 1000;
}

template <class T>
Node<T>* Tree<T>::getRoot() {
    return root;
}

// Utility function to right rotate subtree rooted with y
template <class T>
Node<T>* Tree<T>::rightRotate(Node<T>* node_y) {
    Node<T>* node_x = (*node_y).getLeft();
    Node<T>* sub_tree_x = (*node_x).getRight();

    // Perform rotation
    (*node_x).setRight(node_y);
    (*node_y).setLeft(sub_tree_x);

    // Update heights
    (*node_y).setHeight(max(height((*node_y).getLeft()), height((*node_y).getRight())) + 1);
    (*node_x).setHeight(max(height((*node_x).getLeft()), height((*node_x).getRight())) + 1);

    return node_x;
}

// Utility function to right rotate subtree rooted with x
template <class T>
Node<T>* Tree<T>::leftRotate(Node<T>* node_x) {
    //cout << "--1" << endl;
    Node<T>* node_y = (*node_x).getRight();
    Node<T>* sub_tree_y = (*node_y).getLeft();
    //cout << "--2" << endl;
    // Perform the rotation
    (*node_y).setLeft(node_x);
    (*node_x).setRight(sub_tree_y);
    //cout << "--3" << endl;
    //Update heights
    (*node_x).setHeight(max(height((*node_x).getLeft()), height((*node_x).getRight())) + 1);
    (*node_y).setHeight(max(height((*node_y).getLeft()), height((*node_y).getRight())) + 1);
    //cout << "--4" << endl;
    return node_y;
}

template <class T>
int Tree<T>::getBalance(Node<T>* node) {
    if (node == NULL)
        return 0;
    return height((*node).getLeft()) - height((*node).getRight());
}

template <class T>
int Tree<T>::height(Node<T>* node) {
    if (node == NULL) 
        return 0;
    return (*node).getHeight();
}

template <class T>
void Tree<T>::insert(T key) {
    root = insertUtil(root, key);
    calculatePos();
}    

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree
template <class T>
Node<T>* Tree<T>::insertUtil(Node<T>* node, T key) {
    // 1. Perform the normal BST insertion
    if (node == NULL) {
        Node<T>* new_node = new Node(key);
        return new_node;
    }

    if (key < (*node).getKey()) {
        (*node).setLeft(insertUtil((*node).getLeft(), key));
    }
    else if (key > (*node).getKey()) {
        (*node).setRight(insertUtil((*node).getRight(), key));
    }
    else // Equals keys are not allowed in BST
        return node;
    //cout << "--1" << endl;
    // 2. Update height of this ancestor node
    (*node).setHeight(1 + max(height((*node).getLeft()), height((*node).getRight())));
    // 3. Get the balance factor of this ancestor node to check
    // whether this node became unbalanced
    int balance = getBalance(node);

    cout << "Node (key): " << (*node).getKey() << " | height: " << height(node) 
        << " | balance: " << balance << endl;
    if ((*node).getLeft() != NULL)
        //cout << " left: " << (*(*node).getLeft()).getKey();
    if ((*node).getRight() != NULL) 
        //cout << " right: " << (*(*node).getRight()).getKey();
    //cout << " | KEY INSERTED: " << key << endl;

    // If this node becames unbalanced, then there are 4 cases
    //cout << "--2" << endl;
    // Left Left case
    if (balance > 1 && key < (*(*node).getLeft()).getKey()) {
        return rightRotate(node);
    }
    // Right Right case
    if (balance < -1 && key > (*(*node).getRight()).getKey()) {
        cout << "right right case" << endl;
        return leftRotate(node);
    }

    // Left Right case 
    if (balance > 1 && key > (*(*node).getLeft()).getKey()) {
        (*node).setLeft(leftRotate((*node).getLeft()));
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && key < (*(*node).getRight()).getKey()) {
        (*node).setRight(rightRotate((*node).getRight()));
        return leftRotate(node);
    }
    return node;
}

template <class T>
Node<T>* Tree<T>::minValueNode(Node<T>* node) {
    Node<T>* current = node;
    
    // Loop down to find the leftmost leaf
    while ((*current).getLeft() != NULL) 
        current = (*current).getLeft();
    return current;
}

template <class T>
void Tree<T>::deleteNode(T key) {
    root = deleteUtil(root, key);
}

template <class T>
Node<T>* Tree<T>::deleteUtil(Node<T>* root, T key) {     
    // Perform standard BST delete
    if (root == NULL)
        return root;
    if (key < (*root).getKey())
        (*root).setLeft(deleteUtil((*root).getLeft(), key));
    else if (key > (*root).getKey())
        (*root).setRight(deleteUtil((*root).getRight(), key));
    
    // If the key is same as root's key, then
    // This is the node to be deleted
    else {
        // Node with only one child or no child
        if ((*root).getLeft() == NULL || (*root).getRight() == NULL) {
            Node<T>* temp = ((*root).getLeft()) ? (*root).getLeft() : (*root).getRight();
            // If no child case
            if (temp == NULL) {
                cout << "no child case" << endl;
                temp = root;
                root = NULL;
            }
            else {
                // Copy the contents of the non-empty child
                *root = *temp;
                cout << "one child case" << endl;
                cout << "new node: " << (*root).getKey() << endl;
            }
            free(temp);
        }
        // Node with two children: Get the inorder succesor
        else {
            Node<T>* temp = minValueNode((*root).getRight());
            // Copy the inorder successor's data to this node
            (*root).setKey((*temp).getKey());

            // Delete the inorder succesor
            (*root).setRight(deleteUtil((*root).getRight(), (*temp).getKey()));
        }
    }

    // If the tree had only one node, then return 
    if (root == NULL) 
        return root;



    // STEP 2: Update height of the current node
    (*root).setHeight(max(height((*root).getLeft()), height((*root).getRight())) + 1);

    // STEP 3: Get the balance factor of this node
    int balance  = getBalance(root);
    cout << "root: " << (*root).getKey() << " | balance: " << balance << endl;

    // Left Left case
    if (balance > 1 && key < (*(*root).getLeft()).getKey()) {
        return rightRotate(root);
    }

    // Right Right case
    if (balance < -1 && key > (*(*root).getRight()).getKey()) {
        return leftRotate(root);
    }

    // Left Right case 
    if (balance > 1 && key > (*(*root).getLeft()).getKey()) {
        (*root).setLeft(leftRotate((*root).getLeft()));
        return rightRotate(root);
    }

    // Right Left case
    if (balance < -1 && key < (*(*root).getRight()).getKey()) {
        (*root).setRight(rightRotate((*root).getRight()));
        return leftRotate(root);
    }
    cout << "node returned: " << (*root).getKey() << endl;
    return root;
}

template <class T>
void Tree<T>::printPreOrder() {
    preOrderRec(root);
}

template <class T>
void Tree<T>::preOrderRec(Node<T>* node) {
    if (node != NULL) {
        cout << (*node).getKey() << ", ";
        preOrderRec((*node).getLeft());
        preOrderRec((*node).getRight());
    }
}

template <class T>
void Tree<T>::printInOrder() {
    inOrderRec(root);
}

template <class T>
void Tree<T>::inOrderRec(Node<T>* node) {
    if (node != NULL) {
        inOrderRec((*node).getLeft());
        cout << (*node).getKey() << ", ";
        inOrderRec((*node).getRight());
    }
}

template <class T>
void Tree<T>::print2D() {
    print2DUtil(root, 0);
}

template <class T>
void Tree<T>::print2DUtil(Node<T>* node, int space) {
    if (node == NULL)
        return;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2DUtil((*node).getRight(), space); 
    // Print current node after space
    cout << endl;
    int i = COUNT;
    for (; i < space; ++i) 
        cout << " ";
    cout << (*node).getKey() << endl;

    // Process left child
    print2DUtil((*node).getLeft(), space);
}

template <class T>
void Tree<T>::calculatePos() {
    (*root).x = 1000 / 2;
    calculatePosUtil(root, 1);
}

template <class T>
void Tree<T>::calculatePosUtil(Node<T>* node, int height) {
    if (node != NULL) {
        (*node).refreshPosXChild(height);
        calculatePosUtil((*node).getLeft(), height + 1);
        calculatePosUtil((*node).getRight(), height + 1);
    }
}