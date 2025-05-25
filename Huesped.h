#ifndef HUESPED_H
#define HUESPED_H

#include <string>
#include <iostream>
#include "Lista.h"
using namespace std;
class Reservacion; // Declaración adelantada

class Huesped {
private:
    string documento;
    string nombre;
    int antiguedadMeses;
    float puntuacion;
    Lista<Reservacion*> reservacionesActivas;
    
public:
    // Constructor
    Huesped(string documento = "", string nombre = "", int antiguedadMeses = 0, float puntuacion = 0.0)
        : documento(documento), nombre(nombre), antiguedadMeses(antiguedadMeses), puntuacion(puntuacion) {}
    
    // Getters y setters
    string getDocumento() const { return documento; }
    void setDocumento(string doc) { documento = doc; }
    
    string getNombre() const { return nombre; }
    void setNombre(string nom) { nombre = nom; }
    
    int getAntiguedadMeses() const { return antiguedadMeses; }
    void setAntiguedadMeses(int meses) { antiguedadMeses = meses; }
    
    float getPuntuacion() const { return puntuacion; }
    void setPuntuacion(float punt) { puntuacion = punt; }
    
    Lista<Reservacion*>& getReservacionesActivas() { return reservacionesActivas; }
    
    // Sobrecarga del operador de igualdad para comparar huéspedes
    bool operator==(const Huesped& otro) const {
        return documento == otro.documento;
    }
    
    // Método para mostrar información del huésped
    friend ostream& operator<<(ostream& os, const Huesped& huesped) {
        os << "Documento: " << huesped.documento << "\n"
           << "Nombre: " << huesped.nombre << "\n"
           << "Antigüedad (meses): " << huesped.antiguedadMeses << "\n"
           << "Puntuación: " << huesped.puntuacion;
        return os;
    }
};

#endif // HUESPED_H