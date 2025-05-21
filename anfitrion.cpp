#include "anfitrion.h"
#include <iostream>

using namespace std;
// Constructor
Anfitrion::Anfitrion(const string& documento, int antiguedad, float puntuacion)
    : documento(documento), antiguedad(antiguedad), puntuacion(puntuacion) {
}

// Destructor
Anfitrion::~Anfitrion() {
    // Eliminar todas las referencias a alojamientos 
    Nodo<Alojamiento*>* actual = alojamientos.getCabeza();
    while (actual != nullptr) {
        Alojamiento* alojamiento = actual->getDato();
        // Solo se recorren las referencias
        actual = actual->getSiguiente();
    }
}

// Agregar un alojamiento
void Anfitrion::agregarAlojamiento(Alojamiento* alojamiento) {
    if (alojamiento && alojamiento->getAnfitrion() == this) {
        alojamientos.agregar(alojamiento);
    }
}

// Eliminar un alojamiento
void Anfitrion::eliminarAlojamiento(Alojamiento* alojamiento) {
    if (alojamiento) {
        alojamientos.eliminar(alojamiento);
    }
}

// Contar alojamientos
int Anfitrion::contarAlojamientos() const {
    return alojamientos.contar();
}
