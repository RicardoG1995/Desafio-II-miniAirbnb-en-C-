#ifndef SISTEMAUDEASTAY_H
#define SISTEMAUDEASTAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>
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

    void verMisAlojamientos(Anfitrion* anfitrion) {
        cout << "\n===== MIS ALOJAMIENTOS =====" << endl;
        Lista<Alojamiento*>& alojamientosAnfitrion = anfitrion->getAlojamientos();
        if (alojamientosAnfitrion.getCabeza() == nullptr) {
            cout << "No tiene alojamientos registrados." << endl;
            return;
        }

        Nodo<Alojamiento*>* actual = alojamientosAnfitrion.getCabeza();
        while (actual != nullptr) {
            Alojamiento* alojamiento = actual->getDato();
            alojamiento->mostrarInfo();
            cout << "-----------------------------------" << endl;
            actual = actual->getSiguiente();
        }
    }

    void registrarAlojamientoAnfitrion(Anfitrion* anfitrion) {
        string codigo, nombre, tipo, departamento, municipio, direccion;
        float precioNoche;
        
        cout << "\n===== REGISTRO DE NUEVO ALOJAMIENTO =====" << endl;
        cout << "Código: ";
        cin >> codigo;
        
        // Verificar si ya existe un alojamiento con ese código
        Alojamiento* alojamientoBusqueda = new Alojamiento();
        alojamientoBusqueda->setCodigo(codigo);
        if (alojamientos.buscar(alojamientoBusqueda) != nullptr) {
            delete alojamientoBusqueda;
            cout << "Ya existe un alojamiento con ese código." << endl;
            return;
        }
        delete alojamientoBusqueda;
        
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

        // Crear y configurar el nuevo alojamiento
        Alojamiento* nuevoAlojamiento = new Alojamiento(codigo, nombre, tipo, departamento, municipio, direccion, precioNoche, anfitrion);
        
        // Agregar amenidades
        cout << "\nIngrese las amenidades (escriba 'fin' para terminar):\n";
        string amenidad;
        cin.ignore();
        while (true) {
            cout << "Amenidad: ";
            getline(cin, amenidad);
            if (amenidad == "fin") break;
            nuevoAlojamiento->getAmenidades().agregar(amenidad);
        }
        
        // Agregar el alojamiento a las listas
        alojamientos.agregar(nuevoAlojamiento);
        anfitrion->getAlojamientos().agregar(nuevoAlojamiento);
        cout << "\nAlojamiento registrado exitosamente." << endl;
    }

    void verReservacionesAlojamientos(Anfitrion* anfitrion) {
        cout << "\n===== RESERVACIONES DE MIS ALOJAMIENTOS =====" << endl;
        bool tieneReservaciones = false;
        
        Lista<Alojamiento*>& alojamientosAnfitrion = anfitrion->getAlojamientos();
        Nodo<Alojamiento*>* actualAloj = alojamientosAnfitrion.getCabeza();
        
        while (actualAloj != nullptr) {
            Alojamiento* alojamiento = actualAloj->getDato();
            Lista<Reservacion*>& reservasAlojamiento = alojamiento->getFechasReservadas();
            
            if (reservasAlojamiento.getCabeza() != nullptr) {
                tieneReservaciones = true;
                cout << "\nAlojamiento: " << alojamiento->getNombre() << endl;
                cout << "Código: " << alojamiento->getCodigo() << endl;
                cout << "Reservaciones:" << endl;
                
                Nodo<Reservacion*>* actualRes = reservasAlojamiento.getCabeza();
                while (actualRes != nullptr) {
                    Reservacion* reserva = actualRes->getDato();
                    cout << "-----------------------------------" << endl;
                    cout << "Código de reserva: " << reserva->getCodigo() << endl;
                    cout << "Fecha de inicio: " << reserva->getFechaInicio() << endl;
                    cout << "Duración: " << reserva->getDuracion() << " días" << endl;
                    cout << "Huésped: " << reserva->getHuesped()->getNombre() << endl;
                    cout << "Monto: $" << reserva->getMonto() << endl;
                    actualRes = actualRes->getSiguiente();
                }
            }
            actualAloj = actualAloj->getSiguiente();
        }
        
        if (!tieneReservaciones) {
            cout << "No hay reservaciones para sus alojamientos." << endl;
        }
    }

    void modificarAlojamiento(Anfitrion* anfitrion) {
        string codigo;
        cout << "\n===== MODIFICAR ALOJAMIENTO =====" << endl;
        cout << "Ingrese el código del alojamiento a modificar: ";
        cin >> codigo;

        // Buscar el alojamiento
        Alojamiento* alojamientoBusqueda = new Alojamiento();
        alojamientoBusqueda->setCodigo(codigo);
        Alojamiento* alojamiento = alojamientos.buscar(alojamientoBusqueda);
        delete alojamientoBusqueda;

        if (alojamiento == nullptr || alojamiento->getAnfitrion() != anfitrion) {
            cout << "Alojamiento no encontrado o no le pertenece." << endl;
            return;
        }

        int opcion;
        do {
            cout << "\n1. Modificar nombre" << endl;
            cout << "2. Modificar tipo" << endl;
            cout << "3. Modificar ubicación" << endl;
            cout << "4. Modificar precio" << endl;
            cout << "5. Agregar amenidad" << endl;
            cout << "6. Volver al menú anterior" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore();

            string nuevoValor;
            switch(opcion) {
                case 1:
                    cout << "Nuevo nombre: ";
                    getline(cin, nuevoValor);
                    alojamiento->setNombre(nuevoValor);
                    break;
                case 2:
                    cout << "Nuevo tipo: ";
                    getline(cin, nuevoValor);
                    alojamiento->setTipo(nuevoValor);
                    break;
                case 3:
                    cout << "Nuevo departamento: ";
                    getline(cin, nuevoValor);
                    alojamiento->setDepartamento(nuevoValor);
                    cout << "Nuevo municipio: ";
                    getline(cin, nuevoValor);
                    alojamiento->setMunicipio(nuevoValor);
                    cout << "Nueva dirección: ";
                    getline(cin, nuevoValor);
                    alojamiento->setDireccion(nuevoValor);
                    break;
                case 4:
                    float nuevoPrecio;
                    cout << "Nuevo precio por noche: ";
                    cin >> nuevoPrecio;
                    alojamiento->setPrecioNoche(nuevoPrecio);
                    break;
                case 5:
                    cout << "Nueva amenidad: ";
                    getline(cin, nuevoValor);
                    alojamiento->getAmenidades().agregar(nuevoValor);
                    break;
                case 6:
                    cout << "Volviendo al menú anterior..." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
            }

            if (opcion >= 1 && opcion <= 5) {
                cout << "Modificación realizada exitosamente." << endl;
            }
        } while (opcion != 6);
    }
    
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

    void consultarAlojamientosDisponibles() {
        cout << "\n===== CONSULTA DE ALOJAMIENTOS DISPONIBLES =====" << endl;
        cout << "Seleccione el criterio de búsqueda:\n";
        cout << "1. Por ubicación\n";
        cout << "2. Por rango de precio\n";
        cout << "3. Ver todos\n";
        cout << "Opción: ";
        
        int opcion;
        cin >> opcion;
        cin.ignore();

        string departamento, municipio;
        float precioMin = 0, precioMax = 0;
        bool filtrarPorUbicacion = false;
        bool filtrarPorPrecio = false;

        switch(opcion) {
            case 1:
                cout << "Ingrese el departamento deseado: ";
                getline(cin, departamento);
                cout << "Ingrese el municipio deseado: ";
                getline(cin, municipio);
                filtrarPorUbicacion = true;
                break;
            case 2:
                cout << "Ingrese el precio mínimo por noche: $";
                cin >> precioMin;
                cout << "Ingrese el precio máximo por noche: $";
                cin >> precioMax;
                filtrarPorPrecio = true;
                break;
            case 3:
                break;
            default:
                cout << "Opción inválida. Mostrando todos los alojamientos." << endl;
        }

        cout << "\n===== ALOJAMIENTOS DISPONIBLES =====" << endl;
         if (filtrarPorUbicacion) {
             cout << "Ubicación: " << municipio << ", " << departamento << endl;
         }
         if (filtrarPorPrecio) {
             cout << "Rango de precio: $" << precioMin << " - $" << precioMax << " por noche" << endl;
         }
         cout << "====================================" << endl;
        bool encontrado = false;
        Nodo<Alojamiento*>* actual = alojamientos.getCabeza();
        
        while (actual != nullptr) {
            monitor.registrarIteracion();
            Alojamiento* alojamiento = actual->getDato();
            
            bool cumpleFiltros = true;

            if (filtrarPorUbicacion) {
                cumpleFiltros = alojamiento->getDepartamento() == departamento && 
                               alojamiento->getMunicipio() == municipio;
            }

            if (cumpleFiltros && filtrarPorPrecio) {
                float precio = alojamiento->getPrecioNoche();
                cumpleFiltros = precio >= precioMin && precio <= precioMax;
            }

            if (cumpleFiltros) {
                encontrado = true;
                cout << "\nCódigo: " << alojamiento->getCodigo() << endl;
                cout << "Nombre: " << alojamiento->getNombre() << endl;
                cout << "Tipo: " << alojamiento->getTipo() << endl;
                cout << "Dirección: " << alojamiento->getDireccion() << endl;
                cout << "Precio por noche: $" << alojamiento->getPrecioNoche() << endl;
                cout << "Amenidades: ";
                Nodo<string>* amenidad = alojamiento->getAmenidades().getCabeza();
                while (amenidad != nullptr) {
                    cout << amenidad->getDato();
                    if (amenidad->getSiguiente() != nullptr) cout << ", ";
                    amenidad = amenidad->getSiguiente();
                }
                cout << endl;
            }
            actual = actual->getSiguiente();
        }
        
        if (!encontrado) {
            cout << "No se encontraron alojamientos disponibles en la ubicación especificada." << endl;
        }
    }

    void cancelarReservacionHuesped(Huesped* huesped) {
        string codigoReserva;
        cout << "\n===== CANCELAR RESERVACIÓN =====" << endl;
        cout << "Ingrese el código de la reserva: ";
        cin >> codigoReserva;

        Nodo<Reservacion*>* actual = huesped->getReservacionesActivas().getCabeza();
        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            if (reserva->getCodigo() == codigoReserva) {
                // Verificar que no haya pasado la fecha de inicio
                time_t now = time(nullptr);
                struct tm fecha_inicio = {};
                std::istringstream ss(reserva->getFechaInicio());
                ss >> std::get_time(&fecha_inicio, "%d/%m/%Y");
                time_t fecha_reserva = mktime(&fecha_inicio);

                if (now < fecha_reserva) {
                    // Eliminar la reserva de la lista de reservas activas del huésped
                    huesped->getReservacionesActivas().eliminar(reserva);
                    // Eliminar la reserva de la lista de fechas reservadas del alojamiento
                    reserva->getAlojamiento()->getFechasReservadas().eliminar(reserva);
                    // Eliminar la reserva de la lista general de reservaciones
                    reservaciones.eliminar(reserva);
                    cout << "Reservación cancelada exitosamente." << endl;
                    return;
                } else {
                    cout << "No se puede cancelar la reserva porque la fecha de inicio ya pasó." << endl;
                    return;
                }
            }
            actual = actual->getSiguiente();
        }
        cout << "No se encontró una reserva con ese código." << endl;
    }

    void verReservasActivas(Huesped* huesped) {
        cout << "\n===== RESERVAS ACTIVAS =====" << endl;
        Nodo<Reservacion*>* actual = huesped->getReservacionesActivas().getCabeza();
        if (actual == nullptr) {
            cout << "No tiene reservas activas." << endl;
            return;
        }

        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            cout << "\nCódigo de reserva: " << reserva->getCodigo() << endl;
            cout << "Alojamiento: " << reserva->getAlojamiento()->getNombre() << endl;
            cout << "Fecha de inicio: " << reserva->getFechaInicio() << endl;
            cout << "Duración: " << reserva->getDuracion() << " días" << endl;
            cout << "Monto: $" << reserva->getMonto() << endl;
            actual = actual->getSiguiente();
        }
    }
    

    void agregarObservacionReservacion(Huesped* huesped) {
        cout << "\n===== AGREGAR OBSERVACIÓN A RESERVACIÓN =====" << endl;
        string codigoReserva;
        cout << "Ingrese el código de la reservación: ";
        cin >> codigoReserva;

        // Buscar la reservación
        Nodo<Reservacion*>* actual = huesped->getReservacionesActivas().getCabeza();
        bool encontrada = false;

        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            if (reserva->getCodigo() == codigoReserva) {
                encontrada = true;
                cin.ignore();
                cout << "Ingrese su observación (máximo 1000 caracteres): ";
                char observacion[1000];
                cin.getline(observacion, 1000);
                reserva->setObservaciones(observacion);
                cout << "Observación agregada exitosamente." << endl;
                break;
            }
            actual = actual->getSiguiente();
        }

        if (!encontrada) {
            cout << "No se encontró una reservación activa con ese código." << endl;
        }
    }

    void verHistorialReservas(Huesped* huesped) {
        cout << "\n===== HISTORIAL DE RESERVAS =====" << endl;
        bool tieneHistorial = false;

        // Mostrar reservas activas
        cout << "\nReservas Activas:" << endl;
        Nodo<Reservacion*>* actual = huesped->getReservacionesActivas().getCabeza();
        while (actual != nullptr) {
            tieneHistorial = true;
            Reservacion* reserva = actual->getDato();
            cout << "\nCódigo de reserva: " << reserva->getCodigo() << endl;
            cout << "Alojamiento: " << reserva->getAlojamiento()->getNombre() << endl;
            cout << "Fecha de inicio: " << reserva->getFechaInicio() << endl;
            cout << "Duración: " << reserva->getDuracion() << " días" << endl;
            cout << "Monto: $" << reserva->getMonto() << endl;
            cout << "Estado: Activa" << endl;
            actual = actual->getSiguiente();
        }

        // Mostrar reservas pasadas
        cout << "\nReservas Pasadas:" << endl;
        actual = reservaciones.getCabeza();
        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            if (reserva->getHuesped() == huesped) {
                // Verificar si la reserva ya pasó
                time_t now = time(nullptr);
                struct tm fecha_inicio = {};
                std::istringstream ss(reserva->getFechaInicio());
                ss >> std::get_time(&fecha_inicio, "%d/%m/%Y");
                time_t fecha_reserva = mktime(&fecha_inicio);
                fecha_reserva += (reserva->getDuracion() * 24 * 60 * 60); // Añadir la duración en segundos

                if (now > fecha_reserva) {
                    tieneHistorial = true;
                    cout << "\nCódigo de reserva: " << reserva->getCodigo() << endl;
                    cout << "Alojamiento: " << reserva->getAlojamiento()->getNombre() << endl;
                    cout << "Fecha de inicio: " << reserva->getFechaInicio() << endl;
                    cout << "Duración: " << reserva->getDuracion() << " días" << endl;
                    cout << "Monto: $" << reserva->getMonto() << endl;
                    cout << "Estado: Finalizada" << endl;
                }
            }
            actual = actual->getSiguiente();
        }

        if (!tieneHistorial) {
            cout << "No tiene historial de reservas." << endl;
        }
    }

    void realizarReservacionHuesped(Huesped* huesped) {
        string codigoAlojamiento;
        string fechaInicio;
        int duracion;
        
        cout << "\n===== REALIZAR RESERVACIÓN =====" << endl;
        cout << "Ingrese el código del alojamiento: ";
        cin >> codigoAlojamiento;

        Alojamiento* alojamientoBusqueda = new Alojamiento();
        alojamientoBusqueda->setCodigo(codigoAlojamiento);
        Alojamiento* alojamiento = alojamientos.buscar(alojamientoBusqueda);
        delete alojamientoBusqueda;

        if (alojamiento == nullptr) {
            cout << "No se encontró el alojamiento con ese código." << endl;
            return;
        }

        cout << "Ingrese la fecha de inicio (DD/MM/AAAA): ";
        cin >> fechaInicio;
        cout << "Ingrese la duración (días): ";
        cin >> duracion;

        // Verificar si el huésped ya tiene reservas en las mismas fechas
        Nodo<Reservacion*>* actual = huesped->getReservacionesActivas().getCabeza();
        while (actual != nullptr) {
            Reservacion* reserva = actual->getDato();
            if (reserva->getFechaInicio() == fechaInicio) {
                cout << "Ya tiene una reserva para la fecha seleccionada." << endl;
                return;
            }
            actual = actual->getSiguiente();
        }

        if (!alojamiento->verificarDisponibilidad(fechaInicio, "")) {
            cout << "El alojamiento no está disponible para las fechas seleccionadas." << endl;
            return;
        }

        string metodoPago;
        cout << "Método de pago: ";
        cin.ignore();
        getline(cin, metodoPago);

        float monto = alojamiento->getPrecioNoche() * duracion;
        string codigoReserva = "RES" + to_string(time(nullptr));

        Reservacion* nuevaReservacion = new Reservacion(
            codigoReserva,
            fechaInicio,
            duracion,
            huesped->getDocumento(),
            metodoPago,
            "Hoy",
            monto
        );
        monitor.sumarMemoria(sizeof(Reservacion));
        nuevaReservacion->setAlojamiento(alojamiento);
        nuevaReservacion->setHuesped(huesped);

        reservaciones.agregar(nuevaReservacion);
        alojamiento->agregarReservacion(nuevaReservacion);
        huesped->getReservacionesActivas().agregar(nuevaReservacion);

        cout << "Reservación realizada exitosamente." << endl;
        cout << "Código de reserva: " << codigoReserva << endl;
        cout << "Valor total: $" << monto << endl;
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
                    alojamiento->setAnfitrion(anfitrion);                    anfitrion->getAlojamientos().agregar(alojamiento);
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
    SistemaUdeAStay() {
        cargarHuespedes();
        cargarAnfitriones();
        cargarAlojamientos();
        cargarReservaciones();
    }
    
    // Métodos según el diagrama UML
    bool login() {
        string usuario, password;
        cout << "===== INICIO DE SESIÓN =====" << endl;
        cout << "1. Administrador\n2. Huésped\n3. Anfitrión\nSeleccione tipo de usuario: ";
        int tipoUsuario;
        cin >> tipoUsuario;

        if (tipoUsuario == 1) {
            cout << "Usuario: ";
            cin >> usuario;
            cout << "Contraseña: ";
            cin >> password;
            
            if (usuario == "admin" && password == "admin123") {
                cout << "Inicio de sesión exitoso como administrador." << endl;
                int opcion;
                do {
                    cout << "\n===== MENÚ ADMINISTRADOR =====" << endl;
                    cout << "1. Registrar nuevo alojamiento" << endl;
                    cout << "2. Registrar nuevo huésped" << endl;
                    cout << "3. Realizar reservacion" << endl;
                    cout << "4. Cancelar reservacion" << endl;
                    cout << "5. Consultar alojamientos" << endl;
                    cout << "6. Consultar huéspedes" << endl;
                    cout << "7. Consultar reservaciones" << endl;
                    cout << "8. Actualizar historial" << endl;
                    cout << "9. Guardar datos" << endl;
                    cout << "10. Salir" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case 1:
                            registrarAlojamiento();
                            break;
                        case 2:
                            registrarHuesped();
                            break;
                        case 3:
                            realizarReservacion();
                            break;
                        case 4:
                            cancelarReserva();
                            break;
                        case 5:
                            consultarAlojamientos();
                            break;
                        case 6:
                            consultarHuespedes();
                            break;
                        case 7:
                            consultarReservaciones();
                            break;
                        case 8:
                            actualizarHistorico();
                            break;
                        case 9:
                            guardarDatos();
                            break;
                        case 10:
                            cout << "Sesión de administrador cerrada." << endl;
                            break;
                        default:
                            cout << "Opción inválida." << endl;
                    }
                } while (opcion != 10);
                return true;
            } else {
                cout << "Credenciales incorrectas." << endl;
                return false;
            }
        } else if (tipoUsuario == 2) {
            string documento;
            cout << "Ingrese su número de documento: ";
            cin >> documento;

            // Crear un huésped temporal para la búsqueda
            Huesped* huespedBusqueda = new Huesped();
            huespedBusqueda->setDocumento(documento);
            Huesped* huesped = huespedes.buscar(huespedBusqueda);
            delete huespedBusqueda; // Liberar memoria del objeto temporal

            if (huesped != nullptr) {
                cout << "Bienvenido " << huesped->getNombre() << "!" << endl;
                int opcion;
                do {
                    cout << "\n===== MENÚ HUÉSPED =====" << endl;
                    cout << "1. Consultar alojamientos disponibles" << endl;
                    cout << "2. Realizar reservación" << endl;
                    cout << "3. Cancelar reservación" << endl;
                    cout << "4. Ver reservas activas" << endl;
                    cout << "5. Ver historial de reservas" << endl;
                    cout << "6. Agregar observación a reservación" << endl;
                    cout << "7. Salir" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcion;

                    switch(opcion) {
                        case 1:
                            consultarAlojamientosDisponibles();
                            break;
                        case 2:
                            realizarReservacionHuesped(huesped);
                            break;
                        case 3:
                            cancelarReservacionHuesped(huesped);
                            break;
                        case 4:
                            verReservasActivas(huesped);
                            break;
                        case 5:
                            verHistorialReservas(huesped);
                            break;
                        case 6:
                            agregarObservacionReservacion(huesped);
                            break;
                        case 7:
                            cout << "Gracias por usar nuestro sistema." << endl;
                            break;
                        default:
                            cout << "Opción inválida." << endl;
                    }
                } while (opcion != 7);
                return true;
            } else {
                cout << "Huésped no encontrado. ¿Desea registrarse? (1: Sí, 2: No): ";
                int opcion;
                cin >> opcion;

                if (opcion == 1) {
                    registrarHuesped();
                    return true;
                } else {
                    return false;
                }
            }
        } else if (tipoUsuario == 3) {
            string documento;
            cout << "Ingrese su número de documento: ";
            cin >> documento;

            // Buscar anfitrión
            Anfitrion* anfitrionBusqueda = new Anfitrion();
            anfitrionBusqueda->setDocumento(documento);
            Anfitrion* anfitrion = anfitriones.buscar(anfitrionBusqueda);
            delete anfitrionBusqueda;

            if (anfitrion != nullptr) {
                cout << "Bienvenido Anfitrión!" << endl;
                int opcion;
                do {
                    cout << "\n===== MENÚ ANFITRIÓN =====" << endl;
                    cout << "1. Ver mis alojamientos" << endl;
                    cout << "2. Registrar nuevo alojamiento" << endl;
                    cout << "3. Ver reservaciones de mis alojamientos" << endl;
                    cout << "4. Modificar alojamiento" << endl;
                    cout << "5. Ver mi puntuación" << endl;
                    cout << "6. Salir" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcion;

                    switch(opcion) {
                        case 1:
                            verMisAlojamientos(anfitrion);
                            break;
                        case 2:
                            registrarAlojamientoAnfitrion(anfitrion);
                            break;
                        case 3:
                            verReservacionesAlojamientos(anfitrion);
                            break;
                        case 4:
                            modificarAlojamiento(anfitrion);
                            break;
                        case 5:
                            cout << "Su puntuación actual es: " << anfitrion->getPuntuacion() << "/5.0" << endl;
                            break;
                        case 6:
                            cout << "Gracias por usar nuestro sistema." << endl;
                            break;
                        default:
                            cout << "Opción inválida." << endl;
                    }
                } while (opcion != 6);
                return true;
            } else {
                cout << "Anfitrión no encontrado." << endl;
                return false;
            }
        } else {
            cout << "Opción inválida." << endl;
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
