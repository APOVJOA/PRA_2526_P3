#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
private:
    // ABB que almacena elementos TableEntry<V>
    BSTree<TableEntry<V>>* tree;

public:
    // ------------------ CONSTRUCTOR ------------------
    BSTreeDict() {
        this->tree = new BSTree<TableEntry<V>>();  // Crear ABB vacío
    }

    // ------------------ DESTRUCTOR ------------------
    ~BSTreeDict() {
        delete this->tree;  // Liberar memoria del ABB
    }

    // ------------------ SOBRECARGA DE << ------------------
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        // Imprime el ABB de TableEntry<V> usando print_inorder del BSTree
        out << *(bs.tree);
        return out;
    }

    // ------------------ OPERADOR [] ------------------
    V operator[](std::string key) {
        try {
            // Busca el TableEntry correspondiente a la clave
            TableEntry<V> entry = bs.tree->search(TableEntry<V>(key, V()));
            return entry.value;  // Devuelve el valor asociado
        }
        catch (std::runtime_error &e) {
            throw std::runtime_error("Clave no encontrada: " + key);
        }
    }

    // ------------------ MÉTODOS ADICIONALES (opcional) ------------------
    // Por ejemplo, insert o remove se pueden delegar al ABB
    void insert(std::string key, V value) {
        TableEntry<V> entry(key, value);
        this->tree->insert(entry);
    }

    void remove(std::string key) {
        TableEntry<V> entry(key, V());
        this->tree->remove(entry);
    }
};

#endif
