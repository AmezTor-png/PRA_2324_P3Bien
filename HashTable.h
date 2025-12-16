#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

// Ajusta la ruta según tu estructura:
#include "ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;   // número de elementos almacenados
    int max; // tamaño de la tabla (número de cubetas)
    ListLinked<TableEntry<V>>* table; // array dinámico de listas enlazadas

    // Función hash: suma ASCII de la clave % tamaño tabla
    int h(std::string key) {
        int sum = 0;
        for (int i = 0; i < key.size(); i++)
            sum += int(key.at(i));
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) {
        max = size;
        n = 0;

        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Devuelve capacidad total
    int capacity() {
        return max;
    }

    // Inserta clave->valor
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        // verificar si existe en esa cubeta
        if (table[pos].search(entry) != -1)
            throw std::runtime_error("insert: clave ya existente");

        // insertar al principio
        table[pos].prepend(entry);
        n++;
    }

    // Buscar valor por clave
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> target(key);

        int idx = table[pos].search(target);
        if (idx == -1)
            throw std::runtime_error("search: clave no encontrada");

        return table[pos].get(idx).value;
    }

    // Eliminar clave->valor
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> target(key);

        int idx = table[pos].search(target);
        if (idx == -1)
            throw std::runtime_error("remove: clave no encontrada");

        TableEntry<V> removed = table[pos].remove(idx);
        n--;
        return removed.value;
    }

    // Número de elementos totales
    int entries() override {
        return n;
    }

    // Sobrecarga operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Imprimir contenido de la tabla hash
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        out << "HashTable (" << ht.n << " entries):\n";
        for (int i = 0; i < ht.max; i++) {
            out << "[" << i << "]: ";
            out << ht.table[i] << "\n";  // asume que ListLinked tiene <<
        }
        return out;
    }
};

#endif

