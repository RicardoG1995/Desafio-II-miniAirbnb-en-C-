#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

// Clase Lista
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;  // Puntero al primer nodo de la lista

public:
    // Constructor y destructor
    Lista() : cabeza(nullptr) {}
    ~Lista();
    
    // Métodos básicos de la lista
    void agregar(const T& dato);
    void eliminar(const T& dato);
    bool buscar(const T& dato) const;
    void recorrer() const;
    int contar() const;
    
    // Getter para acceder al primer nodo
    Nodo<T>* getCabeza() const { return cabeza; }
};

// Implementación de los métodos de la clase Lista

// Destructor: libera la memoria de todos los nodos
template <typename T>
Lista<T>::~Lista() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
}

// Agrega un nuevo nodo al final de la lista
template <typename T>
void Lista<T>::agregar(const T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    
    if (cabeza == nullptr) {
        // Si la lista está vacía, el nuevo nodo es la cabeza
        cabeza = nuevo;
    } else {
        // Recorrer hasta el último nodo
        Nodo<T>* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        // Enlazar el último nodo con el nuevo
        actual->setSiguiente(nuevo);
    }
}

// Elimina el primer nodo que contiene el dato especificado
template <typename T>
void Lista<T>::eliminar(const T& dato) {
    if (cabeza == nullptr) {
        return; // Lista vacía
    }
    
    // Si el nodo a eliminar es la cabeza
    if (cabeza->getDato() == dato) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
        return;
    }
    
    // Buscar el nodo a eliminar
    Nodo<T>* actual = cabeza;
    while (actual->getSiguiente() != nullptr && actual->getSiguiente()->getDato() != dato) {
        actual = actual->getSiguiente();
    }
    
    // Si se encontró el nodo a eliminar
    if (actual->getSiguiente() != nullptr) {
        Nodo<T>* temp = actual->getSiguiente();
        actual->setSiguiente(temp->getSiguiente());
        delete temp;
    }
}

// Busca un dato en la lista
template <typename T>
bool Lista<T>::buscar(const T& dato) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getDato() == dato) {
            return true; // Dato encontrado
        }
        actual = actual->getSiguiente();
    }
    return false; // Dato no encontrado
}

// Recorre la lista
template <typename T>
void Lista<T>::recorrer() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        // Aquí se puede agregar código para mostrar o procesar cada dato
        actual = actual->getSiguiente();
    }
}

// Cuenta el número de nodos en la lista
template <typename T>
int Lista<T>::contar() const {
    int contador = 0;
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        contador++;
        actual = actual->getSiguiente();
    }
    return contador;
}

#endif // LISTA_H
