#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;          // Número de elementos en el ABB
    BSNode<T>* root;    // Nodo raíz del ABB

    // ------------------ MÉTODOS PRIVADOS ------------------

    // Método recursivo para buscar un elemento en el subárbol
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (n->elem < e) {
            return search(n->right, e);   // Buscar en subárbol derecho
        }
        else if (n->elem > e) {
            return search(n->left, e);    // Buscar en subárbol izquierdo
        }
        else {
            return n;                     // Elemento encontrado
        }
    }

    // Método recursivo para insertar un elemento en el subárbol
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            return new BSNode<T>(e);     // Crear nuevo nodo
        }
        if (e < n->elem) {
            n->left = insert(n->left, e);   // Insertar en subárbol izquierdo
        }
        else if (e > n->elem) {
            n->right = insert(n->right, e); // Insertar en subárbol derecho
        }
        else {
            throw std::runtime_error("Elemento ya existe"); // Elemento duplicado
        }
        return n;    // Devolver nodo actualizado
    }

    // Recorrido inorden para imprimir elementos ordenados
    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n == nullptr) return;

        print_inorder(out, n->left);      // Recorrer subárbol izquierdo
        out << n->elem << " ";            // Imprimir nodo actual
        print_inorder(out, n->right);     // Recorrer subárbol derecho
    }

    // Método recursivo para eliminar un elemento del subárbol
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
        }

        if (e < n->elem) {
            n->left = remove(n->left, e);     // Buscar y eliminar en izquierdo
        }
        else if (e > n->elem) {
            n->right = remove(n->right, e);   // Buscar y eliminar en derecho
        }
        else {
            // Nodo encontrado
            if (n->left == nullptr) {
                BSNode<T>* tmp = n->right;
                delete n;
                return tmp;                     // Reemplazo por hijo derecho
            }
            else if (n->right == nullptr) {
                BSNode<T>* tmp = n->left;
                delete n;
                return tmp;                     // Reemplazo por hijo izquierdo
            }
            else {
                // Nodo con dos hijos: reemplazo por máximo del subárbol izquierdo
                T maxLeft = max(n->left);       
                n->elem = maxLeft;              
                n->left = remove_max(n->left);  
            }
        }
        return n;    // Devolver nodo actualizado
    }

    // Devuelve el elemento máximo en el subárbol
    T max(BSNode<T>* n) const {
        if (n->right == nullptr) return n->elem; // Máximo encontrado
        return max(n->right);                     // Buscar en derecho
    }

    // Elimina el elemento máximo en el subárbol
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* tmp = n->left;
            delete n;
            return tmp;                            // Reemplazo por hijo izquierdo
        }
        n->right = remove_max(n->right);           // Seguir hacia derecha
        return n;
    }

    // Elimina todos los nodos del subárbol (destructor recursivo)
    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    // ------------------ CONSTRUCTOR ------------------
    BSTree() {
        this->nelem = 0;
        this->root = nullptr;
    }

    // ------------------ DESTRUCTOR ------------------
    ~BSTree() {
        delete_cascade(this->root);
    }

    // ------------------ MÉTODOS PÚBLICOS ------------------

    int size() const {
        return this->nelem;  // Devuelve número de elementos
    }

    // Método lanzadera para buscar un elemento
    T search(T e) const {
        BSNode<T>* result = search(this->root, e);
        return result->elem;
    }

    // Método lanzadera para insertar un elemento
    void insert(T e) {
        this->root = insert(this->root, e);
        this->nelem = this->nelem + 1;
    }

    // Método lanzadera para eliminar un elemento
    void remove(T e) {
        this->root = remove(this->root, e);
        this->nelem = this->nelem - 1;
    }

    // Sobrecarga de operador << para imprimir ABB inorden
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
    T operator[](T e) const {
    return search(e);  // Simplemente delega en search()
}
};

#endif

