#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
    T key;
    Node<T>* prev;
    Node<T>* next;
public:
    Node() {
        prev = NULL;
        next = NULL;
    }
    
    Node(T key) {
        this->key = key;
        prev = NULL;
        next = NULL;
    }

    void setKey(T key) {
        this->key = key;
    }

    T getKey() {
        return key;
    }

    void setNext(Node<T>* next) {
        this->next = next;
    }

    void setPrev(Node<T>* prev) {
        this->prev = prev;
    }

    Node<T>* getPrev() {
        return prev;
    }

    Node<T>* getNext() {
        return next;
    }
};

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* init;

public: 
    DoubleLinkedList() {
        init = NULL;
    }

    void push(T key) {
        Node<T>* new_node = new Node(key);
        (*new_node).setNext(init);
        // Change prev of head to new node
        if (init != NULL)
            (*init).setPrev(new_node);
        (*new_node).setPrev(NULL);
        init = new_node;
    }

    void insert(Node<T>* ref, T key) {
        if (ref == NULL) {
            printf("The given previous pointer reference is NULL");
            return;
        }
        Node<T>* new_node = new Node(key);
        (*new_node).setNext((*ref).getNext());
        (*new_node).setPrev(ref);
        (*ref).setNext(new_node);
        if ((*ref).getNext() != NULL) 
            (*((*ref).getNext())).setPrev(new_node);
    }

    void insert(T key) {
        cout << "Insert init" << endl;
        if (init == NULL) {
            push(key);
            return;
        }
        int p = 0;
        int r = size() - 1;
        int m = (p + r) / 2;
        Node<T>* m_node = next(init, m);
        while (p < r) {
            if (key < (*m_node).getKey()) {
                r = m - 1;
                m = (p + r) / 2;
                m_node = prev(m_node, r - m + 1);
            }
            else if (key == (*m_node).getKey()) {
                break;
            }
            else {
                p = m + 1;
                m = (p + r) / 2;
                m_node = next(m_node, m - p + 1);
            }
            cout << "p: " << p << " | q: " << r << endl;
            cout << "m_node.key: " << (*m_node).getKey() << endl;
        }
        if (key < (*m_node).getKey()) {
            if ((*m_node).getPrev() == NULL) 
                push(key); 
            else  {
                m_node = prev(m_node, 1);
                cout << "m_node prev: " <<  (*m_node).getKey() << endl;
                insert(m_node, key);
            }
        }
        else insert(m_node, key);
    }

    int size() {
        Node<T>* last = init;
        int n = 0;
        while (last != NULL) {
            last = (*last).getNext();
            ++n;
        }
        return n;
    }

    Node<T>* next(Node<T>* ref, int n) {
        int i = 0;
        while (i < n && ref != NULL) {
            ref = (*ref).getNext();
            ++i;
        }
        return ref;
    }

    Node<T>* prev(Node<T>* ref, int n) {
        int i = n;
        while(i > 0 && ref != NULL) {
            ref = (*ref).getPrev();
            --i;
        }
        return ref;
    }

    void printList() {
        Node<T>* last = init;
        while (last != NULL) {
            cout << (*last).getKey() << endl;
            last = (*last).getNext();
        }
    }

    Node<T>* getInit() {
        return init;
    }
};

int main() {
    DoubleLinkedList<int> list;
    list.insert(4);
    list.insert(3);
    list.insert(7);
    list.insert(1);
    list.insert(3);
    list.insert(5);
    list.printList();
    return 0;
}