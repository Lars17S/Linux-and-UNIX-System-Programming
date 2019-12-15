#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
    T key;
    Node* next;
public:
    Node() {
        next = NULL;
    }
    Node(T key) {
        this->key = key;
        next = NULL;
    }

    void setKey(T key) {
        this->key = key;
    }

    T getKey() {
        return key;
    }

    void setNext(Node* next) {
        this->next = next;
    }

    Node* getNext() {
        return next;
    }
};

template<typename T>
class LinkedList {
private:
    Node<T>* init;
public: 
    LinkedList() {
        init = NULL;
    }

    void push(T key) {
        Node<T>* new_node = new Node(key);
        (*new_node).setNext(init);
        init = new_node;
    }

    void insertAfter(Node<T>* node, T key) {
        if (node == NULL) {
            printf("The given node cannot be null");
            return;
        }
        Node<T>* new_node = new Node(key);
        (*new_node).setNext((*node).getNext());
        (*node).setNext(new_node);
    }

    void append(T key) {
        Node<T>* new_node = new Node(key);
        Node<T>* last = init;
        while ((*last).getNext() != NULL) {
            last = (*last).getNext();
        }        
        (*last).setNext(new_node);
    }

    Node<T>* getInit() {
        return init;
    }

    void printList() {
        Node<T>* temp = init;
        while (temp != NULL) { // Null pointer is a constant with value of zero
            cout << (*temp).getKey() << endl;
            temp = (*temp).getNext();
        }
    }
};

int main() {
    LinkedList<int> list;
    list.push(4);
    list.push(8);
    list.printList();
    list.append(7);
    list.printList();
    return 0;
}