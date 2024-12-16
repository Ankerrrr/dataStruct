#include <iostream>

using namespace std;

template <typename T>
class linkList;

template <typename T>
class chainNode {
    friend class linkList<T>;

private:
    T data;
    chainNode* link;

public:
    chainNode(T& d, chainNode* l = 0) : data(d), link(l) {};
};

template <typename T>
class linkList {
private:
    chainNode<T>* head;

public:
    linkList() : head(nullptr) {};
    void insertBack(T);
    void concatenate(linkList<T>&);
    void reverse();
    void print();
};

template <typename T>
void linkList<T>::insertBack(T d) {
    if (head != nullptr) {
        chainNode<T>* findTail = head;
        while (findTail->link != nullptr) {
            findTail = findTail->link;
        }
        findTail->link = new chainNode<T>(d);
    }
    else {
        head = new chainNode<T>(d);
    }
}

template <typename T>
void linkList<T>::concatenate(linkList& other) {
    if (other.head == nullptr) {
        throw "second List is null, cant concatenate()";
        return;
    }
    if (head == nullptr) {
        head = other.head;
        return;
    }

    chainNode<T>* current = head;
    while (current->link != nullptr) {
        current = current->link;
    }

    current->link = other.head;
}

template <typename T>
void linkList<T>::reverse() {
    chainNode<T>* prev = NULL;
    chainNode<T>* next = NULL;
    chainNode<T>* now = head;

    while (now) {
        next = now->link;
        now->link = prev;
        prev = now;
        now = next;
    }
    head = prev;
}

template <typename T>
void linkList<T>::print() {
    chainNode<T>* current;
    current = head;
    while (current) {
        cout << current->data << ", ";
        current = current->link;
    }
    cout << endl;
}

int main() {
    linkList<float> myList;
    myList.insertBack(13);
    myList.insertBack(14);
    myList.insertBack(3.14);
    myList.print();


    myList.reverse();
    myList.print();

    linkList<float> secondList;
    secondList.insertBack(15);
    secondList.insertBack(18.3);
    myList.concatenate(secondList);
    myList.print();
}
