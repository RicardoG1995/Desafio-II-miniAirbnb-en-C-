#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "SistemaUdeAStay.h"

using namespace std;


void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }    

int main() {
    SistemaUdeAStay sistema;
    int opcion = 0;
    bool loggedIn = false;
    
  //  limpiarPantalla();
    cout << "===== Bienvenido al Sistema UdeAStay ====="  << endl;
    
    while (true) {
        if (!loggedIn) {
            cout << "\n1. Iniciar sesion\n2. Salir\nSeleccione una opcion: ";
            cin >> opcion;
            
            switch (opcion) {
                case 1:
                    loggedIn = sistema.login();
                    if (loggedIn) {
                        sistema.cargarDatos();
                    }
                    break;
                case 2:
                    cout << "Gracias por usar el Sistema UdeAStay. ¡Hasta pronto!" << endl;
                    return 0;
                default:
                    cout << "Opcion inválida. Intente nuevamente." << endl;
            }
        } else {
           // limpiarPantalla();
            cout << "\n===== MENÚ PRINCIPAL =====";
            cout << "\n1. Registrar nuevo alojamiento";
            cout << "\n2. Registrar nuevo huésped";
            cout << "\n3. Realizar reservacion";
            cout << "\n4. Cancelar reservacion";
            cout << "\n5. Consultar alojamientos";
            cout << "\n6. Consultar huéspedes";
            cout << "\n7. Consultar reservaciones";
            cout << "\n8. Actualizar historial";
            cout << "\n9. Guardar datos";
            cout << "\n10. Cerrar sesion";
            cout << "\n11. Salir";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;
            
            switch (opcion) {
                case 1:
                    sistema.registrarAlojamiento();
                    break;
                case 2:
                    sistema.registrarHuesped();
                    break;
                case 3:
                    sistema.realizarReservacion();
                    break;
                case 4:
                    sistema.cancelarReserva();
                    break;
                case 5:
                    sistema.consultarAlojamientos();
                    break;
                case 6:
                    sistema.consultarHuespedes();
                    break;
                case 7:
                    sistema.consultarReservaciones();
                    break;
                case 8:
                    sistema.actualizarHistorico();
                    break;
                case 9:
                    sistema.guardarDatos();
                    break;
                case 10:
                    loggedIn = false;
                    cout << "Sesion cerrada correctamente." << endl;
                    break;
                case 11:
                    sistema.guardarDatos();
                    cout << "Gracias por usar el Sistema UdeASay. ¡Hasta pronto!" << endl;
                    return 0;
                default:
                    cout << "Opcion inválida. Intente nuevamente." << endl;
            }
        }
    }
    
    return 0;
}
