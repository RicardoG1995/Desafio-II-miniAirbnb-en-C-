#include "alojamiento.h"
#include <iostream>

using namespace std;

// Constructor
Alojamiento::Alojamiento(const string& codigo, const string& nombre, const string& tipo,
                         const string& departamento, const string& municipio, 
                         const string& direccion, float precioNoche, Anfitrion* anfitrion)
    : codigo(codigo), nombre(nombre), tipo(tipo), departamento(departamento),
      municipio(municipio), direccion(direccion), precioNoche(precioNoche),
      anfitrion(anfitrion) {
    // Si el anfitrión existe, agregar este alojamiento a su lista
    if (anfitrion) {
        anfitrion->agregarAlojamiento(this);
    }
}

// Destructor
Alojamiento::~Alojamiento() {
    // Eliminar todas las reservaciones asociadas
    Nodo<Reservacion*>* actual = fechasReservadas.getCabeza();
    while (actual != nullptr) {
        Reservacion* reservacion = actual->getDato();
        // No eliminamos la reservación aquí, solo la referencia
        actual = actual->getSiguiente();
    }
    
    // Si el anfitrión existe, eliminar este alojamiento de su lista
    if (anfitrion) {
        anfitrion->eliminarAlojamiento(this);
    }
}

// Agregar una amenidad
void Alojamiento::agregarAmenidad(const string& amenidad) {
    amenidades.agregar(amenidad);
}

// Eliminar una amenidad
void Alojamiento::eliminarAmenidad(const string& amenidad) {
    amenidades.eliminar(amenidad);
}

// Mostrar información del alojamiento
void Alojamiento::mostrarInfo() const {
    cout << "= INFORMACIÓN DEL ALOJAMIENTO =" << endl;
    cout << "Código: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Ubicación: " << municipio << ", " << departamento << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Precio por noche: $" << precioNoche << endl;
    cout << "Anfitrión: " << (anfitrion ? anfitrion->getDocumento() : "No especificado") << endl;
    
    // Mostrar amenidades
    cout << "Amenidades:" << endl;
    Nodo<string>* actual = amenidades.getCabeza();
    while (actual != nullptr) {
        cout << "- " << actual->getDato() << endl;
        actual = actual->getSiguiente();
    }
    
    cout << "Reservaciones: " << fechasReservadas.contar() << endl;
    cout << "========================================" << endl;
}

// Verificar disponibilidad en un rango de fechas
bool Alojamiento::verificarDisponibilidad(const string& inicio, const string& fin) const {
    // Implementación básica 
    return true; // Por ahora asumimos que siempre está disponible
}

// Agregar una reservación
void Alojamiento::agregarReservacion(Reservacion* reservacion) {
    if (reservacion && reservacion->getAlojamiento() == this) {
        fechasReservadas.agregar(reservacion);
    }
}

// Quitar una reservación
void Alojamiento::quitarReservacion(Reservacion* reservacion) {
    if (reservacion) {
        fechasReservadas.eliminar(reservacion);
    }
}