#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "SistemaUdeAStay.h"

using namespace std;

int main() {
    SistemaUdeAStay sistema;
    int opcion = 0;
    bool loggedIn = false;
    
    cout << "===== Bienvenido al Sistema UdeAStay ====="  << endl;
    
    while (true) {
        if (!loggedIn) {
            do {
                cout << "\n1. Iniciar sesion\n2. Salir\nSeleccione una opcion: ";
                if (!(cin >> opcion)) {
                    cout << "Error: Debe ingresar un numero." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    opcion = 0;
                    continue;
                }
                cin.ignore(10000, '\n');
                if (opcion != 1 && opcion != 2) {
                    cout << "Error: Opcion invalida. Debe ser 1 o 2." << endl;
                }
            } while (opcion != 1 && opcion != 2);
            
            switch (opcion) {
                case 1:
                    loggedIn = sistema.login();
                    if (loggedIn) {
                        sistema.cargarDatos();
                    }
                    break;
                case 2:
                    cout << "Gracias por usar el Sistema UdeAStay. ¡ Hasta pronto !" << endl;
                    return 0;
                default:
                    cout << "Opcion invalida. Intente nuevamente." << endl;
            }
        } else {
            // El menú se maneja dentro del método login() para cada tipo de usuario
            loggedIn = false;
            sistema.guardarDatos();
            cout << "Sesion finalizada." << endl;
        }
    }
    
    return 0;
}
