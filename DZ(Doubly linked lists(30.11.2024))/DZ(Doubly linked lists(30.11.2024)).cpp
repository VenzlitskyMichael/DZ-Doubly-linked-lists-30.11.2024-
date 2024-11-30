#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;

    void clear() {
        while (head) {
            pop_front();
        }
    }

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        clear();
    }

    List(const List& other) : head(nullptr), tail(nullptr) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this == &other) return *this;

        clear();

        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
        return *this;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop_back() {
        if (!tail) return;

        Node* toDelete = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            head = tail = nullptr;
        }
        delete toDelete;
    }

    void pop_front() {
        if (!head) return;

        Node* toDelete = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else {
            head = tail = nullptr;
        }
        delete toDelete;
    }

    void reverse() {
        Node* current = head;
        Node* temp = nullptr;

        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp) { 
            temp = temp->prev; 
            swap(head, tail);
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    List list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    cout << "Оригинальный список: ";
    list.print();

    list.reverse();
    cout << "Перевернутый список: ";
    list.print();

    list.pop_back();
    cout << "После pop_back: ";
    list.print();

    list.pop_front();
    cout << "После pop_front: ";
    list.print();

    List otherList;
    otherList = list;
    cout << "Копированный список: ";
    otherList.print();
}

