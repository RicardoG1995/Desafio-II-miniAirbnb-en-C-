#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
#include <iostream>
#include "Lista.h"
#include <ostream>
using namespace std;
class Alojamiento; // Declaración adelantada

class Anfitrion {
private:
    string documento;
    int antiguedad;
    float puntuacion;
    Lista<Alojamiento*> alojamientos;
    
public:
    // Constructor
    Anfitrion(string documento = "", int antiguedad = 0, float puntuacion = 0.0)
        : documento(documento), antiguedad(antiguedad), puntuacion(puntuacion) {}
    
    // Getters y setters
    string getDocumento() const { return documento; }
    void setDocumento(string doc) { documento = doc; }
    
    int getAntiguedad() const { return antiguedad; }
    void setAntiguedad(int ant) { antiguedad = ant; }
    
    float getPuntuacion() const { return puntuacion; }
    void setPuntuacion(float punt) { puntuacion = punt; }
    
    Lista<Alojamiento*>& getAlojamientos() { return alojamientos; }
    
    // Sobrecarga del operador de igualdad para comparar anfitriones
    bool operator==(const Anfitrion& otro) const {
        return this->documento == otro.documento;
    }

    // Sobrecarga del operador de salida para mostrar información
    friend ostream& operator<<(ostream& os, const Anfitrion& anfitrion) {
        os << "Documento: " << anfitrion.documento << "\n"
           << "Antigüedad: " << anfitrion.antiguedad << " años\n"
           << "Puntuación: " << anfitrion.puntuacion;
        return os;
    }
};

#endif // ANFITRION_H