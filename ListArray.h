#ifndef LISTARRAY_H
#define LISTARRAY_H
#include <iostream>
#include <stdexcept>  // Para std::out_of_range
#include "List.h"

using namespace std;

template <typename T>
class ListArray : public List<T> {

private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE)
            new_size = MINSIZE;

        T* new_arr = new T[new_size];
        for (int i = 0; i < n; ++i)
            new_arr[i] = arr[i];

        delete[] arr;
        arr = new_arr;
        max = new_size;
    }

public:
    // Constructor
    ListArray() {
        max = MINSIZE;
        n = 0;
        arr = new T[max];
    }

    // Destructor
    ~ListArray() {
        delete[] arr;
    }

    // Operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida");
        return arr[pos];
    }

    // Insertar un elemento en una posición
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida");

        if (n == max)
            resize(2 * max);

        for (int i = n; i > pos; --i)
            arr[i] = arr[i - 1];

        arr[pos] = e;
        n++;
    }

    // Agregar al final
    void append(T e) override {
        insert(n, e);
    }

    // Agregar al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Eliminar elemento por posición
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw out_of_range("Posición inválida");

        T elem = arr[pos];
        for (int i = pos; i < n - 1; ++i)
            arr[i] = arr[i + 1];

        n--;
        if (max >= 4 * n && max > MINSIZE)
            resize(max / 2);

        return elem;
    }

    // Obtener elemento
    T get(int pos) override {
        if (pos < 0 || pos >= n) throw out_of_range("Posición inválida");
        return arr[pos];
    }

    // Buscar elemento
    int search(T e) override {
        for (int i = 0; i < n; ++i)
            if (arr[i] == e) return i;
        return -1;
    }

    // Saber si está vacío
    bool empty() override {
        return n == 0;
    }

    // Saber tamaño actual
    int size() override {
        return n;
    }

    // Operador <<
    template <typename U>
    friend ostream& operator<<(ostream &out, const ListArray<U> &list) {
        out << "[";
        for (int i = 0; i < list.n; ++i) {
            out << list.arr[i];
            if (i < list.n - 1) out << ", ";
        }
        out << "]";
        return out;
    }

    friend ListArray <T> operator+(ListArray <T>& l1, int n2) {
        ListArray <T> nuevalista;
        for (int i = 0; i < l1.size(); i++){
            nuevalista.append(l1.get(i)+ n2);
        }
        return nuevalista;
    }
};

#endif

