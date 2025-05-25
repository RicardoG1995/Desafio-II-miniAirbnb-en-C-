#ifndef SISTEMAUDEASTAY_H
#define SISTEMAUDEASTAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include "Lista.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "Reservacion.h"
#include "Anfitrion.h"
#include "MonitorSistema.h"
using namespace std;
class SistemaUdeAStay {
private:
    Lista<Alojamiento*> alojamientos;
    Lista<Anfitrion*> anfitriones;
    Lista<Huesped*> huespedes;
    Lista<Reservacion*> reservaciones;
    MonitorSistema monitor;
    
    // Métodos privados para manejo de archivos
    void guardarAlojamientos() {
        ofstream archivo("alojamientos.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo de alojamientos." << endl;
            return;
        }
        
        Nodo<Alojamiento*>* actual = alojamientos.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            Alojamiento* alojamiento = actual->getDato();
            archivo << alojamiento->getCodigo() << "|"
                    << alojamiento->getNombre() << "|"
                    << alojamiento->getTipo() << "|"
                    << alojamiento->getDepartamento() << "|"
                    << alojamiento->getMunicipio() << "|"
                    << alojamiento->getDireccion() << "|"
                    << alojamiento->getPrecioNoche() << "|"
                    << (alojamiento->getAnfitrion() ? alojamiento->getAnfitrion()->getDocumento() : "") << endl;
            
            // Guardar amenidades
            Nodo<string>* amenidad = alojamiento->getAmenidades().getCabeza();
            if (amenidad != nullptr) {
                archivo << "AMENIDADES:";
                while (amenidad != nullptr) {
                    archivo << amenidad->getDato() << ",";
                    amenidad = amenidad->getSiguiente();
                }
                archivo << endl;
            }
            
            actual = actual->getSiguiente();
        }
        
        archivo.close();
    }
    
    void guardarAnfitriones() {
        ofstream archivo("anfitriones.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo de anfitriones." << endl;
            return;
        }
        
        Nodo<Anfitrion*>* actual = anfitriones.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            Anfitrion* anfitrion = actual->getDato();
            archivo << anfitrion->getDocumento() << "|"
                    << anfitrion->getAntiguedad() << "|"
                    << anfitrion->getPuntuacion() << endl;
            
            actual = actual->getSiguiente();
        }
        
        archivo.close();
    }
    
    void guardarHuespedes() {
        ofstream archivo("huespedes.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo de huéspedes." << endl;
            return;
        }
        
        Nodo<Huesped*>* actual = huespedes.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            Huesped* huesped = actual->getDato();
            archivo << huesped->getDocumento() << "|"
                    << huesped->getNombre() << "|"
                    << huesped->getAntiguedadMeses() << "|"
                    << huesped->getPuntuacion() << endl;
            
            actual = actual->getSiguiente();
        }
        
        archivo.close();
    }
    
    void guardarReservaciones() {
        ofstream archivo("reservaciones.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo de reservaciones." << endl;
            return;
        }
        
        Nodo<Reservacion*>* actual = reservaciones.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            Reservacion* reservacion = actual->getDato();
            archivo << reservacion->getCodigo() << "|"
                    << reservacion->getFechaInicio() << "|"
                    << reservacion->getDuracion() << "|"
                    << reservacion->getDocHuesped() << "|"
                    << reservacion->getMetodoPago() << "|"
                    << reservacion->getFechaPago() << "|"
                    << reservacion->getMonto() << "|"
                    << reservacion->getObservaciones() << "|"
                    << (reservacion->getAlojamiento() ? reservacion->getAlojamiento()->getCodigo() : "") << "|"
                    << (reservacion->getHuesped() ? reservacion->getHuesped()->getDocumento() : "") << endl;
            
            actual = actual->getSiguiente();
        }
        
        archivo.close();
    }
    
    void cargarAlojamientos() {
        ifstream archivo("alojamientos.txt");
        if (!archivo.is_open()) {
            cout << "No se encontró el archivo de alojamientos. Se creará uno nuevo." << endl;
            return;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            monitor.registrarIteracion();
            if (linea.empty()) continue;
            
            if (linea.substr(0, 11) == "AMENIDADES:") {
                // Procesar amenidades para el último alojamiento agregado
                if (alojamientos.getCabeza() != nullptr) {
                    Alojamiento* ultimoAlojamiento = alojamientos.getCabeza()->getDato();
                    string amenidadesStr = linea.substr(11);
                    size_t pos = 0;
                    string token;
                    while ((pos = amenidadesStr.find(',')) != string::npos) {
                        token = amenidadesStr.substr(0, pos);
                        if (!token.empty()) {
                            ultimoAlojamiento->getAmenidades().agregar(token);
                        }
                        amenidadesStr.erase(0, pos + 1);
                    }
                }
                continue;
            }
            
            // Procesar datos del alojamiento
            size_t pos = 0;
            string token;
            string datos[8];
            int i = 0;
            
            while ((pos = linea.find('|')) != string::npos && i < 8) {
                token = linea.substr(0, pos);
                datos[i++] = token;
                linea.erase(0, pos + 1);
            }
            if (!linea.empty() && i < 8) {
                datos[i] = linea;
            }
            
            // Crear alojamiento
            Alojamiento* alojamiento = new Alojamiento(
                datos[0], // codigo
                datos[1], // nombre
                datos[2], // tipo
                datos[3], // departamento
                datos[4], // municipio
                datos[5], // direccion
                stof(datos[6]) // precioNoche
            );
            monitor.sumarMemoria(sizeof(Reservacion));
            monitor.sumarMemoria(sizeof(Huesped));
            monitor.sumarMemoria(sizeof(Anfitrion));
            monitor.sumarMemoria(sizeof(Alojamiento));
            
            // Asignar anfitrión si existe
            if (!datos[7].empty()) {
                Anfitrion* anfitrionBusqueda = new Anfitrion();
                monitor.sumarMemoria(sizeof(Anfitrion));
                anfitrionBusqueda->setDocumento(datos[7]);
                Anfitrion* anfitrion = anfitriones.buscar(anfitrionBusqueda);
                if (anfitrion != nullptr) {
                    alojamiento->setAnfitrion(anfitrion);   anfitrion->getAlojamientos().agregar(alojamiento);
                }
                delete anfitrionBusqueda; // Liberar memoria del objeto temporal
            }
            
            alojamientos.agregar(alojamiento);
        }
        
        archivo.close();
    }
    
    void cargarAnfitriones() {
        ifstream archivo("anfitriones.txt");
        if (!archivo.is_open()) {
            cout << "No se encontró el archivo de anfitriones. Se creará uno nuevo." << endl;
            return;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            monitor.registrarIteracion();
            if (linea.empty()) continue;
            
            size_t pos = 0;
            string token;
            string datos[3];
            int i = 0;
            
            while ((pos = linea.find('|')) != string::npos && i < 3) {
                token = linea.substr(0, pos);
                datos[i++] = token;
                linea.erase(0, pos + 1);
            }
            if (!linea.empty() && i < 3) {
                datos[i] = linea;
            }
            
            // Crear anfitrión
            Anfitrion* anfitrion = new Anfitrion(
                datos[0], // documento
                stoi(datos[1]), // antiguedad
                stof(datos[2]) // puntuacion
            );
            monitor.sumarMemoria(sizeof(Reservacion));
            monitor.sumarMemoria(sizeof(Huesped));
            monitor.sumarMemoria(sizeof(Anfitrion));
            
            anfitriones.agregar(anfitrion);
        }
        
        archivo.close();
    }
    
    void cargarHuespedes() {
        ifstream archivo("huespedes.txt");
        if (!archivo.is_open()) {
            cout << "No se encontró el archivo de huéspedes. Se creará uno nuevo." << endl;
            return;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            monitor.registrarIteracion();
            if (linea.empty()) continue;
            
            size_t pos = 0;
            string token;
            string datos[4];
            int i = 0;
            
            while ((pos = linea.find('|')) != string::npos && i < 4) {
                token = linea.substr(0, pos);
                datos[i++] = token;
                linea.erase(0, pos + 1);
            }
            if (!linea.empty() && i < 4) {
                datos[i] = linea;
            }
            
            // Crear huésped
            Huesped* huesped = new Huesped(
                datos[0], // documento
                datos[1], // nombre
                stoi(datos[2]), // antiguedadMeses
                stof(datos[3]) // puntuacion
            );
            monitor.sumarMemoria(sizeof(Reservacion));
            monitor.sumarMemoria(sizeof(Huesped));
            monitor.sumarMemoria(sizeof(Anfitrion));
            
            huespedes.agregar(huesped);
        }
        
        archivo.close();
    }
    
    void cargarReservaciones() {
        ifstream archivo("reservaciones.txt");
        if (!archivo.is_open()) {
            cout << "No se encontró el archivo de reservaciones. Se creará uno nuevo." << endl;
            return;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            monitor.registrarIteracion();
            if (linea.empty()) continue;
            
            size_t pos = 0;
            string token;
            string datos[10];
            int i = 0;
            
            while ((pos = linea.find('|')) != string::npos && i < 10) {
                token = linea.substr(0, pos);
                datos[i++] = token;
                linea.erase(0, pos + 1);
            }
            if (!linea.empty() && i < 10) {
                datos[i] = linea;
            }
            
            // Crear reservación
            Reservacion* reservacion = new Reservacion(
                datos[0], // codigo
                datos[1], // fechaInicio
                stoi(datos[2]), // duracion
                datos[3], // docHuesped
                datos[4], // metodoPago
                datos[5], // fechaPago
                stof(datos[6]) // monto
            );
            monitor.sumarMemoria(sizeof(Reservacion));
            monitor.sumarMemoria(sizeof(Huesped));
            monitor.sumarMemoria(sizeof(Anfitrion));
            
            // Asignar observaciones
            reservacion->setObservaciones(datos[7].c_str());
            
            // Asignar alojamiento si existe
            if (!datos[8].empty()) {
                Alojamiento* alojamientoBusqueda = new Alojamiento();
            monitor.sumarMemoria(sizeof(Alojamiento));
                alojamientoBusqueda->setCodigo(datos[8]);
                Alojamiento* alojamiento = alojamientos.buscar(alojamientoBusqueda);
                if (alojamiento != nullptr) {
                    reservacion->setAlojamiento(alojamiento);
                    alojamiento->getFechasReservadas().agregar(reservacion);
                }
                delete alojamientoBusqueda; // Liberar memoria del objeto temporal
            }
            
            // Asignar huésped si existe
            if (!datos[9].empty()) {
                Huesped* huespedBusqueda = new Huesped();
            monitor.sumarMemoria(sizeof(Huesped));
                huespedBusqueda->setDocumento(datos[9]);
                Huesped* huesped = huespedes.buscar(huespedBusqueda);
                if (huesped != nullptr) {
                    reservacion->setHuesped(huesped);
                    huesped->getReservacionesActivas().agregar(reservacion);
                }
                delete huespedBusqueda; // Liberar memoria del objeto temporal
            }
            
            reservaciones.agregar(reservacion);
        }
        
        archivo.close();
    }
    
public:
    // Constructor
    SistemaUdeAStay() {}
    
    // Métodos según el diagrama UML
    bool login() {
        string usuario, password;
        cout << "Usuario: ";
        cin >> usuario;
        cout << "Contraseña: ";
        cin >> password;
        
        // Verificar credenciales
        if (usuario == "admin" && password == "admin123") {
            cout << "Inicio de sesión exitoso." << endl;
            return true;
        } else {
            cout << "Credenciales incorrectas." << endl;
            return false;
        }
    }
    
    void registrarAlojamiento() {
        string codigo, nombre, tipo, departamento, municipio, direccion;
        float precioNoche;
        string docAnfitrion;
        
        cout << "===== REGISTRO DE ALOJAMIENTO ====="  << endl;
        cout << "Código: ";
        cin >> codigo;
        
        // Verificar si ya existe un alojamiento con ese código
        Alojamiento* alojamientoBusqueda = new Alojamiento();
        alojamientoBusqueda->setCodigo(codigo);
        if (alojamientos.buscar(alojamientoBusqueda) != nullptr) {
            delete alojamientoBusqueda; // Liberar memoria del objeto temporal
            cout << "Ya existe un alojamiento con ese código." << endl;
            return;
        }
        delete alojamientoBusqueda; // Liberar memoria del objeto temporal
        
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, nombre);
        
        cout << "Tipo (casa, apartamento, habitación): ";
        getline(cin, tipo);
        
        cout << "Departamento: ";
        getline(cin, departamento);
        
        cout << "Municipio: ";
        getline(cin, municipio);
        
        cout << "Dirección: ";
        getline(cin, direccion);
        
        cout << "Precio por noche: ";
        cin >> precioNoche;
        
        cout << "Documento del anfitrión: ";
        cin >> docAnfitrion;
        
        // Buscar anfitrión
        Anfitrion* anfitrionBusqueda = new Anfitrion();
        anfitrionBusqueda->setDocumento(docAnfitrion);
        Anfitrion* anfitrion = anfitriones.buscar(anfitrionBusqueda);
        delete anfitrionBusqueda; // Liberar memoria del objeto temporal
        
        if (anfitrion == nullptr) {
            cout << "No se encontró un anfitrión con ese documento. ¿Desea registrarlo? (s/n): ";
            char respuesta;
            cin >> respuesta;
            
            if (respuesta == 's' || respuesta == 'S') {
                int antiguedad;
                float puntuacion;
                
                cout << "Antigüedad (años): ";
                cin >> antiguedad;
                
                cout << "Puntuación inicial: ";
                cin >> puntuacion;
                
                anfitrion = new Anfitrion(docAnfitrion, antiguedad, puntuacion);
            monitor.sumarMemoria(sizeof(Anfitrion));
                anfitriones.agregar(anfitrion);
                cout << "Anfitrión registrado correctamente." << endl;
            } else {
                cout << "Registro de alojamiento cancelado." << endl;
                return;
            }
        }
        
        // Crear alojamiento
        Alojamiento* alojamiento = new Alojamiento(codigo, nombre, tipo, departamento, municipio, direccion, precioNoche, anfitrion);
        monitor.sumarMemoria(sizeof(Alojamiento));
        
        // Agregar amenidades
        cout << "¿Cuántas amenidades desea agregar?: ";
        int numAmenidades;
        cin >> numAmenidades;
        cin.ignore();
        
        for (int i = 0; i < numAmenidades; i++) {
            string amenidad;
            cout << "Amenidad " << (i + 1) << ": ";
            getline(cin, amenidad);
            alojamiento->getAmenidades().agregar(amenidad);
        }
        
        // Agregar alojamiento al sistema y al anfitrión
        alojamientos.agregar(alojamiento);
        anfitrion->getAlojamientos().agregar(alojamiento);
        
        cout << "Alojamiento registrado correctamente." << endl;
        monitor.registrarIteracion();
    }
    
    void registrarHuesped() {
        string documento, nombre;
        int antiguedadMeses;
        float puntuacion;
        
        cout << "===== REGISTRO DE HUÉSPED ====="  << endl;
        cout << "Documento: ";
        cin >> documento;
        
        // Verificar si ya existe un huésped con ese documento
        Huesped* huespedBusqueda = new Huesped();
        huespedBusqueda->setDocumento(documento);
        if (huespedes.buscar(huespedBusqueda) != nullptr) {
            delete huespedBusqueda; // Liberar memoria del objeto temporal
            cout << "Ya existe un huésped con ese documento." << endl;
            return;
        }
        delete huespedBusqueda; // Liberar memoria del objeto temporal
        
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, nombre);
        
        cout << "Antigüedad (meses): ";
        cin >> antiguedadMeses;
        
        cout << "Puntuación inicial: ";
        cin >> puntuacion;
        
        // Crear huésped
        Huesped* huesped = new Huesped(documento, nombre, antiguedadMeses, puntuacion);
        monitor.sumarMemoria(sizeof(Huesped));
        
        // Agregar huésped al sistema
        huespedes.agregar(huesped);
        
        cout << "Huésped registrado correctamente." << endl;
        monitor.registrarIteracion();
    }
    
    void realizarReservacion() {
        string codigoAlojamiento, docHuesped;
        string fechaInicio, metodoPago;
        int duracion;
        
        cout << "===== REALIZAR RESERVACIÓN ====="  << endl;
        
        // Mostrar alojamientos disponibles
        cout << "Alojamientos disponibles:" << endl;
        Nodo<Alojamiento*>* actualAloj = alojamientos.getCabeza();
        while (actualAloj != nullptr) {
            monitor.registrarIteracion();
            cout << actualAloj->getDato()->getCodigo() << " - " << actualAloj->getDato()->getNombre() << endl;
            actualAloj = actualAloj->getSiguiente();
        }
        
        cout << "Código del alojamiento: ";
        cin >> codigoAlojamiento;
        
        // Buscar alojamiento
        Alojamiento* alojamientoBusqueda = new Alojamiento();
        alojamientoBusqueda->setCodigo(codigoAlojamiento);
        Alojamiento* alojamiento = alojamientos.buscar(alojamientoBusqueda);
        delete alojamientoBusqueda; // Liberar memoria del objeto temporal
        
        if (alojamiento == nullptr) {
            cout << "No se encontró un alojamiento con ese código." << endl;
            return;
        }
        
        // Mostrar huéspedes registrados
        cout << "Huéspedes registrados:" << endl;
        Nodo<Huesped*>* actualHues = huespedes.getCabeza();
        while (actualHues != nullptr) {
            monitor.registrarIteracion();
            cout << actualHues->getDato()->getDocumento() << " - " << actualHues->getDato()->getNombre() << endl;
            actualHues = actualHues->getSiguiente();
        }
        
        cout << "Documento del huésped: ";
        cin >> docHuesped;
        
        // Buscar huésped
        Huesped* huespedBusqueda = new Huesped();
        huespedBusqueda->setDocumento(docHuesped);
        Huesped* huesped = huespedes.buscar(huespedBusqueda);
        delete huespedBusqueda; // Liberar memoria del objeto temporal
        
        if (huesped == nullptr) {
            cout << "No se encontró un huésped con ese documento." << endl;
            return;
        }
        
        cin.ignore();
        cout << "Fecha de inicio (DD/MM/AAAA): ";
        getline(cin, fechaInicio);
        
        cout << "Duración (días): ";
        cin >> duracion;
        
        // Verificar disponibilidad
        if (!alojamiento->verificarDisponibilidad(fechaInicio, "")) {
            cout << "El alojamiento no está disponible para esas fechas." << endl;
            return;
        }
        
        cin.ignore();
        cout << "Método de pago: ";
        getline(cin, metodoPago);
        
        // Calcular monto
        float monto = alojamiento->getPrecioNoche() * duracion;
        
        // Generar código único para la reservación
        string codigoReservacion = "RES" + to_string(time(nullptr));
        
        // Crear reservación
        Reservacion* reservacion = new Reservacion(
            codigoReservacion,
            fechaInicio,
            duracion,
            docHuesped,
            metodoPago,
            "Hoy", // Fecha de pago (simplificado)
            monto,
            alojamiento,
            huesped
        );
        
        // Agregar observaciones
        cout << "Observaciones: ";
        char observaciones[1000];
        cin.getline(observaciones, 1000);
        reservacion->setObservaciones(observaciones);
        
        // Agregar reservación al sistema, al alojamiento y al huésped
        reservaciones.agregar(reservacion);
        alojamiento->agregarReservacion(reservacion);
        huesped->getReservacionesActivas().agregar(reservacion);
        
        cout << "Reservación realizada correctamente." << endl;
        reservacion->imprimirComprobante();
        monitor.registrarIteracion();
    }
    
    void cancelarReserva() {
        string codigoReservacion;
        
        cout << "===== CANCELAR RESERVACIÓN ====="  << endl;
        cout << "Código de la reservación: ";
        cin >> codigoReservacion;
        
        // Buscar reservación
        Reservacion reservacionBusqueda;
        reservacionBusqueda.setCodigo(codigoReservacion);
        Reservacion* reservacion = reservaciones.buscar(&reservacionBusqueda);
        
        if (reservacion == nullptr) {
            cout << "No se encontró una reservación con ese código." << endl;
            return;
        }
        
        // Eliminar reservación del alojamiento y del huésped
        if (reservacion->getAlojamiento() != nullptr) {
            reservacion->getAlojamiento()->quitarReservacion(reservacion);
        }
        
        if (reservacion->getHuesped() != nullptr) {
            reservacion->getHuesped()->getReservacionesActivas().eliminar(reservacion);
        }
        
        // Eliminar reservación del sistema
        reservaciones.eliminar(reservacion);
        delete reservacion;
        
        cout << "Reservación cancelada correctamente." << endl;
        monitor.registrarIteracion();
    }
    
    void cargarDatos() {
        cargarAnfitriones();
        cargarHuespedes();
        cargarAlojamientos();
        cargarReservaciones();
        cout << "Datos cargados correctamente." << endl;
    }
    
    void guardarDatos() {
        guardarAnfitriones();
        guardarHuespedes();
        guardarAlojamientos();
        guardarReservaciones();
        cout << "Datos guardados correctamente." << endl;
    }
    
    void consultarAlojamientos() {
        cout << "===== CONSULTA DE ALOJAMIENTOS ====="  << endl;
        
        if (alojamientos.getCabeza() == nullptr) {
            cout << "No hay alojamientos registrados." << endl;
            return;
        }
        
        Nodo<Alojamiento*>* actual = alojamientos.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            actual->getDato()->mostrarInfo();
            cout << "-----------------------------------" << endl;
            actual = actual->getSiguiente();
        }
        
        monitor.registrarIteracion();
    }
    
    void consultarHuespedes() {
        cout << "===== CONSULTA DE HUÉSPEDES ====="  << endl;
        
        if (huespedes.getCabeza() == nullptr) {
            cout << "No hay huéspedes registrados." << endl;
            return;
        }
        
        Nodo<Huesped*>* actual = huespedes.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            cout << *actual->getDato() << endl;
            cout << "-----------------------------------" << endl;
            actual = actual->getSiguiente();
        }
        
        monitor.registrarIteracion();
    }
    
    void consultarReservaciones() {
        cout << "===== CONSULTA DE RESERVACIONES ====="  << endl;
        
        if (reservaciones.getCabeza() == nullptr) {
            cout << "No hay reservaciones registradas." << endl;
            return;
        }
        
        Nodo<Reservacion*>* actual = reservaciones.getCabeza();
        while (actual != nullptr) {
            monitor.registrarIteracion();
            actual->getDato()->imprimirComprobante();
            cout << "-----------------------------------" << endl;
            actual = actual->getSiguiente();
        }
        
        monitor.registrarIteracion();
    }
    
    void actualizarHistorico() {
        cout << "Actualizando historial del sistema..." << endl;
        monitor.reporte();
        cout << "Historial actualizado correctamente." << endl;
    }
};

#endif // SISTEMAUDEASAY_H
