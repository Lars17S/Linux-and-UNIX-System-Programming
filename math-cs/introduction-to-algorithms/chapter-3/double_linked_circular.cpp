#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
    T key;
    Node<T>* prev;
    Node<T>* next;
public:
    void setKey(T key) {
        this->key = key;
    }

    T getKey() {
        return key;
    }

    void setPrev(Node<T>* prev) {
        this->prev = prev;
    }

    Node<T>* getPrev() {
        return prev;
    }

    void setNext(Node<T>* next) {
        this->next = next;
    }

    Node<T>* getNext() {
        return next;
    }
};

template<typename T>
class Circular_LinkedList {
private:
    Node<T> init;
public:

    Circular_LinkedList() {
        init.setNext(&init); 
        init.setPrev(&init);
    }

    Node<T>& getInit() {
        return init;
    }

    void insert(T key) {
        Node<T> temp;
        temp.setKey(key);
        temp.setNext(init.getNext());
        cout << (*temp.getNext()).getKey() << endl;
        (*(init.getNext())).setPrev(&temp);
        cout << (*((*init.getNext()).getPrev())).getKey() << endl;
        cout << (*(init.getPrev())).getKey() << endl;
        cout << (*(getInit().getPrev())).getKey() << endl;
        init.setNext(&temp);
        temp.setPrev(&init);
    }
    
    bool isEmpty() {
        return true;
    }
};

int main() {
    Circular_LinkedList<int> circular_LinkedList;
    circular_LinkedList.getInit().setKey(3);
    cout << (circular_LinkedList.getInit()).getKey() << endl;
    circular_LinkedList.insert(8);
    cout << (*((circular_LinkedList.getInit()).getNext())).getKey() << endl;
    cout << (*((circular_LinkedList.getInit()).getPrev())).getKey() << endl;
    return 0;
}
