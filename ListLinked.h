#ifndef LISTLINKED_H
#define LISTLINKED_H
#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {

private:
    Node<T>* first;
    int n;

public:
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    ~ListLinked() {
        Node<T>* current = first;
        while (current != nullptr) {
            Node<T>* aux = current->next;
            delete current;            
            current = aux;   
        }
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw out_of_range("Posición inválida");

        Node<T>* current = first;
        for (int i = 0; i < pos; ++i)
            current = current->next;

        return current->data;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw out_of_range("Posición inválida");

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i)
                prev = prev->next;

            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw out_of_range("Posición inválida");

        Node<T>* removed;
        T data;

        if (pos == 0) {
            removed = first;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i)
                prev = prev->next;

            removed = prev->next;
            prev->next = removed->next;
        }

        data = removed->data;
        delete removed;
        n--;

        return data;
    }

    T get(int pos) override {
        return (*this)[pos];
    }

    int search(T e) override {
        Node<T>* current = first;
        int index = 0;

        while (current != nullptr) {
            if (current->data == e)
                return index;
            current = current->next;
            index++;
        }

        return -1; 
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }

    template <typename U>
    friend ostream& operator<<(std::ostream &out, const ListLinked<U> &list) {
        Node<U>* current = list.first;
        out << "[";
        while (current != nullptr) {
            out << current->data;
            if (current->next != nullptr)
                out << ", ";
            current = current->next;
        }
        out << "]";
        return out;
    }
    friend ListLinked <T> operator+(ListLinked <T>& l1, int n2) {
        ListLinked <T> nuevalista;
        for (int i = 0; i < l1.size(); i++){
            nuevalista.append(l1.get(i)+ n2);
        }
        return nuevalista;
    }
};

#endif

