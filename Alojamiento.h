#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include <iostream>
#include "Lista.h"
using namespace std;
class Reservacion; // Declaración adelantada
class Anfitrion; // Declaración adelantada

class Alojamiento {
private:
    string codigo;
    string nombre;
    string tipo;
    string departamento;
    string municipio;
    string direccion;
    float precioNoche;
    Lista<string> amenidades;
    Anfitrion* anfitrion;
    Lista<Reservacion*> fechasReservadas;
    
public:
    // Constructor
    Alojamiento(string codigo = "", string nombre = "", string tipo = "", 
               string departamento = "", string municipio = "", string direccion = "", 
               float precioNoche = 0.0, Anfitrion* anfitrion = nullptr)
        : codigo(codigo), nombre(nombre), tipo(tipo), departamento(departamento),
          municipio(municipio), direccion(direccion), precioNoche(precioNoche), anfitrion(anfitrion) {}
    
    // Getters y setters
    string getCodigo() const { return codigo; }
    void setCodigo(string cod) { codigo = cod; }
    
    string getNombre() const { return nombre; }
    void setNombre(string nom) { nombre = nom; }
    
    string getTipo() const { return tipo; }
    void setTipo(string t) { tipo = t; }
    
    string getDepartamento() const { return departamento; }
    void setDepartamento(string dep) { departamento = dep; }
    
    string getMunicipio() const { return municipio; }
    void setMunicipio(string mun) { municipio = mun; }
    
    string getDireccion() const { return direccion; }
    void setDireccion(string dir) { direccion = dir; }
    
    float getPrecioNoche() const { return precioNoche; }
    void setPrecioNoche(float precio) { precioNoche = precio; }
    
    Lista<string>& getAmenidades() { return amenidades; }
    
    Anfitrion* getAnfitrion() const { return anfitrion; }
    void setAnfitrion(Anfitrion* anf) { anfitrion = anf; }
    
    Lista<Reservacion*>& getFechasReservadas() { return fechasReservadas; }
    
    // Métodos según el diagrama UML
    void mostrarInfo() {
        cout << "Código: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Ubicación: " << municipio << ", " << departamento << endl;
        cout << "Dirección: " << direccion << endl;
        cout << "Precio por noche: $" << precioNoche << endl;
        
        cout << "Amenidades: ";
        Nodo<string>* actual = amenidades.getCabeza();
        while (actual != nullptr) {
            cout << actual->getDato() << ", ";
            actual = actual->getSiguiente();
        }
        cout << endl;
    }
    
    bool verificarDisponibilidad(string inicio, string fin) {
        // Implementación básica: verificar si hay alguna reserva que se solape
        Nodo<Reservacion*>* actual = fechasReservadas.getCabeza();
        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            // Aquí se debería implementar la lógica para verificar si las fechas se solapan
            // Por simplicidad, asumimos que no hay solapamiento
            actual = actual->getSiguiente();
        }
        return true; // Por defecto, asumimos disponibilidad
    }
    
    void agregarReservacion(Reservacion* reservacion) {
        fechasReservadas.agregar(reservacion);
    }
    
    void quitarReservacion(Reservacion* reservacion) {
        fechasReservadas.eliminar(reservacion);
    }
    
    // Sobrecarga del operador de igualdad para comparar alojamientos
    bool operator==(const Alojamiento& otro) const {
        return codigo == otro.codigo;
    }
    
    // Sobrecarga del operador de salida para mostrar información
    friend ostream& operator<<(ostream& os, const Alojamiento& alojamiento) {
        os << "Código: " << alojamiento.codigo << "\n"
           << "Nombre: " << alojamiento.nombre << "\n"
           << "Tipo: " << alojamiento.tipo << "\n"
           << "Ubicación: " << alojamiento.municipio << ", " << alojamiento.departamento << "\n"
           << "Precio por noche: $" << alojamiento.precioNoche;
        return os;
    }
};

#endif // ALOJAMIENTO_H