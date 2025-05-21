#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
#include "lista.h"
#include "alojamiento.h"

using namespace std; 

// Declaración adelantada 
class Alojamiento;

class Anfitrion {
private:
    string documento;                   // Documento de identidad del anfitrión
    int antiguedad;                     // Antigüedad en meses como anfitrión
    float puntuacion;                   // Puntuación del anfitrión (de 0 a 5)
    Lista<Alojamiento*> alojamientos;   // Lista de alojamientos que administra

public:
    // Constructor
    Anfitrion(const string& documento, int antiguedad = 0, float puntuacion = 5.0);
    
    // Destructor
    ~Anfitrion();
    
    // Getters y setters
    string getDocumento() const { return documento; }
    void setDocumento(const string& documento) { this->documento = documento; }
    
    int getAntiguedad() const { return antiguedad; }
    void setAntiguedad(int antiguedad) { this->antiguedad = antiguedad; }
    
    float getPuntuacion() const { return puntuacion; }
    void setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }
    
    // Métodos para gestionar alojamientos
    void agregarAlojamiento(Alojamiento* alojamiento);
    void eliminarAlojamiento(Alojamiento* alojamiento);
    Lista<Alojamiento*>& getAlojamientos() { return alojamientos; }
    int contarAlojamientos() const;
};

#endif // ANFITRION_H
