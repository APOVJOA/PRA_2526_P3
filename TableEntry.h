#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
public:
    std::string key; // Clave del par
    V value;         // Valor del par

    TableEntry(std::string key, V value) {
        this->key = key;
        this->value = value;
    }

    TableEntry(std::string key) {    
        this->key = key;
        this->value = V();
    }

    TableEntry() {
        this->key = "";
        this->value = V();
    }

    // ------------------ OPERADORES ------------------
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;
    }

    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key != te2.key;
    }

    // Comparación por clave para ABB
    friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key < te2.key;
    }

    friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key > te2.key;
    }

    // Impresión
    friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
        out << te.key << " -> " << te.value;
        return out;
    }
};

#endif



