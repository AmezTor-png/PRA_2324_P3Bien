#ifndef LISTLINKED_H
#define LISTLINKED_H
#include <ostream>
#include <stdexcept>  // para std::out_of_range
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {

private:
    Node<T>* first;  // puntero al primer nodo
    int n;           // número de elementos

public:
    // 🔹 Constructor: lista vacía
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    // 🔹 Destructor: libera toda la memoria de los nodos
    ~ListLinked() {
        Node<T>* current = first;
        while (current != nullptr) {
            Node<T>* aux = current->next; // guarda el siguiente nodo
            delete current;               // libera el actual
            current = aux;                // avanza
        }
    }

    // 🔹 Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw out_of_range("Posición inválida");

        Node<T>* current = first;
        for (int i = 0; i < pos; ++i)
            current = current->next;

        return current->data;
    }

    // 🔹 Insertar elemento en posición dada
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

    // 🔹 Añadir al final
    void append(T e) override {
        insert(n, e);
    }

    // 🔹 Añadir al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // 🔹 Eliminar elemento por posición
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

    // 🔹 Obtener elemento en posición
    T get(int pos) override {
        return (*this)[pos];
    }

    // 🔹 Buscar elemento
    int search(T e) override {
        Node<T>* current = first;
        int index = 0;

        while (current != nullptr) {
            if (current->data == e)
                return index;
            current = current->next;
            index++;
        }

        return -1; // no encontrado
    }

    // 🔹 Comprobar si está vacía
    bool empty() override {
        return n == 0;
    }

    // 🔹 Devolver tamaño
    int size() override {
        return n;
    }

    // 🔹 Sobrecarga del operador <<
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

