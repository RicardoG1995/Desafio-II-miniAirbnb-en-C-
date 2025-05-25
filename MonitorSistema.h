#ifndef MONITORSISTEMA_H
#define MONITORSISTEMA_H

#include <iostream>
#include <fstream>
using namespace std;
class MonitorSistema {
private:
    size_t memoriaTotal;
    int iteracionesTotales;
    
public:
    // Constructor
    MonitorSistema() : memoriaTotal(0), iteracionesTotales(0) {}
    
    // Métodos según el diagrama UML
    void sumarMemoria(size_t bytes) {
        memoriaTotal += bytes;
    }
    
    void registrarIteracion() {
        iteracionesTotales++;
    }
    
    size_t obtenerMemoria() const {
        return memoriaTotal;
    }
    
    int obtenerIteraciones() const {
        return iteracionesTotales;
    }
    
    void reporte() {
        cout << "===== REPORTE DEL SISTEMA ====="  << endl;
        cout << "Memoria total utilizada: " << memoriaTotal << " bytes" << endl;
        cout << "Iteraciones totales: " << iteracionesTotales << endl;
        cout << "====================================" << endl;
        
        // Guardar reporte en archivo
        ofstream archivo("reporte_sistema.txt");
        if (archivo.is_open()) {
            archivo << "===== REPORTE DEL SISTEMA =====" << endl;
            archivo << "Memoria total utilizada: " << memoriaTotal << " bytes" << endl;
            archivo << "Iteraciones totales: " << iteracionesTotales << endl;
            archivo << "====================================" << endl;
            archivo.close();
        }
    }
};

#endif // MONITORSISTEMA_H