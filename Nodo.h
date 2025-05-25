#ifndef NODO_H
#define NODO_H
using namespace std;
template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
    
public:
    // Constructor
    Nodo(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
    }
    
    // Getters y setters
    T getDato() const {
        return dato;
    }
    
    void setDato(T dato) {
        this->dato = dato;
    }
    
    Nodo<T>* getSiguiente() const {
        return siguiente;
    }
    
    void setSiguiente(Nodo<T>* siguiente) {
        this->siguiente = siguiente;
    }
};

#endif // NODO_H