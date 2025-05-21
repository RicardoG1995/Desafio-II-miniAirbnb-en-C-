#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "lista.h"
#include "reservacion.h"
#include "anfitrion.h"

using namespace std; 
// Declaraciones adelantadas 
class Reservacion;
class Anfitrion;

class Alojamiento {
private:
    string codigo;              // Código único del alojamiento
    string nombre;              // Nombre del alojamiento
    string tipo;                // Tipo de alojamiento (casa, apartamento, etc.)
    string departamento;        // Departamento donde se ubica
    string municipio;           // Municipio donde se ubica
    string direccion;           // Dirección exacta
    float precioNoche;          // Precio por noche
    Lista<string> amenidades;   // Lista de amenidades disponibles
    Anfitrion* anfitrion;       // Puntero al anfitrión que administra el alojamiento
    Lista<Reservacion*> fechasReservadas; // Lista de reservaciones para este alojamiento

public:
    // Constructor
    Alojamiento(const string& codigo, const string& nombre, const string& tipo,
                const string& departamento, const string& municipio, 
                const string& direccion, float precioNoche, Anfitrion* anfitrion);
    
    // Destructor
    ~Alojamiento();
    
    // Getters y setters
    string getCodigo() const { return codigo; }
    void setCodigo(const string& codigo) { this->codigo = codigo; }
    
    string getNombre() const { return nombre; }
    void setNombre(const string& nombre) { this->nombre = nombre; }
    
    string getTipo() const { return tipo; }
    void setTipo(const string& tipo) { this->tipo = tipo; }
    
    string getDepartamento() const { return departamento; }
    void setDepartamento(const string& departamento) { this->departamento = departamento; }
    
    string getMunicipio() const { return municipio; }
    void setMunicipio(const string& municipio) { this->municipio = municipio; }
    
    string getDireccion() const { return direccion; }
    void setDireccion(const string& direccion) { this->direccion = direccion; }
    
    float getPrecioNoche() const { return precioNoche; }
    void setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche; }
    
    Anfitrion* getAnfitrion() const { return anfitrion; }
    void setAnfitrion(Anfitrion* anfitrion) { this->anfitrion = anfitrion; }
    
    // Métodos para gestionar amenidades
    void agregarAmenidad(const string& amenidad);
    void eliminarAmenidad(const string& amenidad);
    Lista<string>& getAmenidades() { return amenidades; }
    
    // Métodos específicos
    void mostrarInfo() const;                                      // Muestra información del alojamiento
    bool verificarDisponibilidad(const string& inicio, const string& fin) const; // Verifica disponibilidad
    void agregarReservacion(Reservacion* reservacion);            // Agrega una reservación
    void quitarReservacion(Reservacion* reservacion);             // Elimina una reservación
};

#endif // ALOJAMIENTO_H
