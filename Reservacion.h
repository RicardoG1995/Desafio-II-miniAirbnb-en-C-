#ifndef RESERVACION_H
#define RESERVACION_H

#include <string>
#include <iostream>
#include <cstring> // Añadido para strcpy
#include "Alojamiento.h"
using namespace std;
class Alojamiento; // Declaración adelantada
class Huesped; // Declaración adelantada

class Reservacion {
private:
    string codigo;
    string fechaInicio;
    int duracion;
    string docHuesped;
    string metodoPago;
    string fechaPago;
    float monto;
    char observaciones[1000];
    Alojamiento* alojamiento;
    Huesped* huesped;
    
public:
    // Constructor
    Reservacion(string codigo = "", string fechaInicio = "", int duracion = 0,
               string docHuesped = "", string metodoPago = "", string fechaPago = "",
               float monto = 0.0, Alojamiento* alojamiento = nullptr, Huesped* huesped = nullptr)
        : codigo(codigo), fechaInicio(fechaInicio), duracion(duracion), docHuesped(docHuesped),
          metodoPago(metodoPago), fechaPago(fechaPago), monto(monto), alojamiento(alojamiento),
          huesped(huesped) {
        strcpy(observaciones, "");
    }
    
    // Getters y setters
    string getCodigo() const { return codigo; }
    void setCodigo(string cod) { codigo = cod; }
    
    string getFechaInicio() const { return fechaInicio; }
    void setFechaInicio(string fecha) { fechaInicio = fecha; }
    
    int getDuracion() const { return duracion; }
    void setDuracion(int dur) { duracion = dur; }
    
    string getDocHuesped() const { return docHuesped; }
    void setDocHuesped(string doc) { docHuesped = doc; }
    
    string getMetodoPago() const { return metodoPago; }
    void setMetodoPago(string metodo) { metodoPago = metodo; }
    
    string getFechaPago() const { return fechaPago; }
    void setFechaPago(string fecha) { fechaPago = fecha; }
    
    float getMonto() const { return monto; }
    void setMonto(float m) { monto = m; }
    
    const char* getObservaciones() const { return observaciones; }
    void setObservaciones(const char* obs) { strcpy(observaciones, obs); }
    
    Alojamiento* getAlojamiento() const { return alojamiento; }
    void setAlojamiento(Alojamiento* aloj) { alojamiento = aloj; }
    
    Huesped* getHuesped() const { return huesped; }
    void setHuesped(Huesped* hues) { huesped = hues; }
    
    // Métodos
    bool validarTraslapes() {
        // Implementación paraverificar si hay traslapes con otras reservaciones
        // Por simplicidad, asumimos que no hay traslapes
        return true;
    }
    
    string formatearFecha() {
        // Implementación básica: formatear la fecha para mostrarla
        return fechaInicio;
    }
    
    void imprimirComprobante() {
        cout << "===== COMPROBANTE DE RESERVACION ====="  << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Fecha de inicio: " << fechaInicio << endl;
        cout << "Duración: " << duracion << " días" << endl;
        cout << "Huésped: " << docHuesped << endl;
        cout << "Método de pago: " << metodoPago << endl;
        cout << "Fecha de pago: " << fechaPago << endl;
        cout << "Monto: $" << monto << endl;
        cout << "Observaciones: " << observaciones << endl;
        if (alojamiento != nullptr) {
            cout << "Alojamiento: " << alojamiento->getNombre() << endl;
        }
        cout << "===================================="  << endl;
    }
    
    // Sobrecarga del operador de igualdad para comparar reservaciones
    bool operator==(const Reservacion& otra) const {
        return codigo == otra.codigo;
    }
    
    // Sobrecarga del operador de salida para mostrar información
    friend ostream& operator<<(ostream& os, const Reservacion& reservacion) {
        os << "Código: " << reservacion.codigo << "\n"
           << "Fecha de inicio: " << reservacion.fechaInicio << "\n"
           << "Duración: " << reservacion.duracion << " días\n"
           << "Monto: $" << reservacion.monto;
        return os;
    }
};

#endif // RESERVACION_H
