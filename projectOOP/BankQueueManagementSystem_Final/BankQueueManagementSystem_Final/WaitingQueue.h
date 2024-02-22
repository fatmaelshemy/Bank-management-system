#pragma once
#include <iostream>
#include "Node.h"
using namespace std;
template <typename T>
class WaitingQueue
{
private:
    Node<T>* front;
    Node<T>* rear;

public:
    WaitingQueue() : front(nullptr), rear(nullptr) {}

    ~WaitingQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty. Cannot dequeue.\n";
            return;
        }

        Node<T>* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }
    }

    T getFront() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. No front element.\n";
            exit(EXIT_FAILURE);
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

};



