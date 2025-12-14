#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(const std::string& key) const {
        int sum = 0;
        for (size_t i = 0; i < key.size(); ++i)
            sum += static_cast<int>(key.at(i));
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() const {
        return max;
    }

    // Inserta clave->valor, lanza excepción si ya existe
    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entry(key, value);
        int pos = table[idx].search(entry);
        if (pos != -1)
            throw std::runtime_error("Clave ya existe");
        table[idx].append(entry);
        n++;
    }

    // Devuelve el valor asociado, lanza excepción si no existe
    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1)
            throw std::runtime_error("Clave no encontrada");
        return table[idx].get(pos).value;
    }

    // Elimina y devuelve valor asociado, lanza excepción si no existe
    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1)
            throw std::runtime_error("Clave no encontrada");
        V val = table[idx].get(pos).value;
        table[idx].remove(pos);
        n--;
        return val;
    }

    // Número de elementos
    int entries() override {
        return n;
    }

    // Sobrecarga <<
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << "Cubeta " << i << ": " << ht.table[i] << "\n";
        }
        return out;
    }

    // Sobrecarga operator[] para lectura
    V operator[](std::string key) {
        return search(key);
    }
};

#endif
