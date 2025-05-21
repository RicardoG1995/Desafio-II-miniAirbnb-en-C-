#include "huesped.h"
#include <iostream>

// Constructor
Huesped::Huesped(const std::string& documento, const std::string& nombre, 
                 int antiguedadMeses, float puntuacion)
    : documento(documento), nombre(nombre), 
      antiguedadMeses(antiguedadMeses), puntuacion(puntuacion) {
}

// Destructor
Huesped::~Huesped() {
    // Eliminar todas las reservaciones asociadas
    Nodo<Reservacion*>* actual = reservacionesActivas.getCabeza();
    while (actual != nullptr) {
        Reservacion* reservacion = actual->getDato();
        // No eliminamos la reservación aquí, solo la referencia
        actual = actual->getSiguiente();
    }
}

// Agregar una reservación
void Huesped::agregarReservacion(Reservacion* reservacion) {
    if (reservacion && reservacion->getHuesped() == this) {
        reservacionesActivas.agregar(reservacion);
    }
}

// Eliminar una reservación
void Huesped::eliminarReservacion(Reservacion* reservacion) {
    if (reservacion) {
        reservacionesActivas.eliminar(reservacion);
    }
}

// Contar reservaciones activas
int Huesped::contarReservaciones() const {
    return reservacionesActivas.contar();
}