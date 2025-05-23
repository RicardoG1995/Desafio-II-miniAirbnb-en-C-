#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <iostream>
using namespace std;
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    
public:
    // Constructor
    Lista() {
        cabeza = nullptr;
    }
    
    // Destructor
    ~Lista() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }
    
    // Métodos según el diagrama UML
    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente() != nullptr) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevo);
        }
    }
    
    void eliminar(T dato) {
        if (cabeza == nullptr) return;
        
        if (cabeza->getDato() == dato) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->getSiguiente();
            delete temp;
            return;
        }
        
        Nodo<T>* actual = cabeza;
        while (actual->getSiguiente() != nullptr && actual->getSiguiente()->getDato() != dato) {
            actual = actual->getSiguiente();
        }
        
        if (actual->getSiguiente() != nullptr) {
            Nodo<T>* temp = actual->getSiguiente();
            actual->setSiguiente(temp->getSiguiente());
            delete temp;
        }
    }
    
    void recorrer() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->getDato() << endl;
            actual = actual->getSiguiente();
        }
    }
    
    T buscar(T dato) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (*(actual->getDato()) == *dato) {
                return actual->getDato();  // ya es T (es decir, Anfitrion*)
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }
    
    int contar() {
        int contador = 0;
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            contador++;
            actual = actual->getSiguiente();
        }
        return contador;
    }
    
    Nodo<T>* getCabeza() const {
        return cabeza;
    }
};

#endif // LISTA_H
