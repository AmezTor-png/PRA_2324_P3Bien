#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    // --- Atributos públicos ---
    std::string key;
    V value;

    // --- Constructores ---
    // Constructor completo: clave + valor
    TableEntry(std::string key, V value) : key(key), value(value) {}

    // Constructor solo con clave (sin valor)
    TableEntry(std::string key) : key(key) {}

    // Constructor por defecto: clave vacía
    TableEntry() : key("") {}

    // --- Operadores friend ---

    // Igualdad: solo compara la clave
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;
    }

    // Desigualdad: solo compara la clave
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key != te2.key;
    }

    // Operador de salida: imprime "key -> value"
    friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
        out << te.key << " -> " << te.value;
        return out;
    }
};

#endif

