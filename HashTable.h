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
class HashTable : public Dict<V>
{

private:
    int n;   // número de elementos almacenados
    int max; // tamaño de la tabla (número de cubetas)
    ListLinked<TableEntry<V>>* table; // array dinámico de listas enlazadas

    // Función hash: suma ASCII de la clave % tamaño tabla
    int h(std::string key) {
        int sum = 0;
        for (int i = 0; i < key.size(); i++)
        {
            sum += int(key.at(i));
        }
        
        return sum % max;
    }

public:
    HashTable(int size)
    {
        max = size;
        n = 0;

        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable()
    {
        delete[] table;
    }

    int capacity()
    {
        return max;
    }

    void insert(std::string key, V value) override
    {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        if (table[pos].search(entry) != -1)
            throw std::runtime_error("insert: clave ya existente");

        table[pos].prepend(entry);
        n++;
    }

    V search(std::string key) override
    {
        int pos = h(key);
        TableEntry<V> target(key);

        int idx = table[pos].search(target);
        if (idx == -1)
            throw std::runtime_error("search: clave no encontrada");

        return table[pos].get(idx).value;
    }

    V remove(std::string key) override
    {
        int pos = h(key);
        TableEntry<V> target(key);

        int idx = table[pos].search(target);
        if (idx == -1)
            throw std::runtime_error("remove: clave no encontrada");

        TableEntry<V> removed = table[pos].remove(idx);
        n--;
        return removed.value;
    }

    int entries() override
    {
        return n;
    }

    V operator[](std::string key)
    {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht)
    {
        for (int i = 0; i < ht.max; i++)
        {
            out << ht.table[i] << "\n";
        }
        return out;
    }
};

#endif

