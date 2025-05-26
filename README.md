# Desafio-II-miniAirbnb-en-C++
Sistema busca ofrecer una plataforma para la gestión de alojamientos temporales entre anfitriones y huéspedes, permitiendo realizar operaciones como reservas, consultas, administración de datos y almacenamiento en archivos de forma permanente.
# Sistema UdeAStay

## Descripción
Sistema busca ofrecer una plataforma para la gestión de alojamientos temporales entre anfitriones y huéspedes, permitiendo realizar operaciones como reservas, consultas, administración de datos y almacenamiento en archivos de forma permanente.

## Características Principales
- Gestión de alojamientos
- Sistema de reservaciones
- Autenticación de usuarios
- Perfiles de huéspedes y administradores
- Gestión de disponibilidad
- Historial de reservaciones

## Uso

### Como Huésped
1. Registrarse en el sistema
2. Iniciar sesión
3. Buscar alojamientos disponibles segun la necesidad
4. Realizar reservaciones
5. Ver historial de reservas
6. Cancelar reservaciones activas

### Como Administrador
1. Iniciar sesión como administrador
2. Gestionar alojamientos
3. Administrar usuarios
4. Ver reportes del sistema

## Estructura del Proyecto
```
UdeAStay/
├── src/
│   ├── main.cpp
│   ├── SistemaUdeAStay.h
│   ├── Alojamiento.h
│   ├── Huesped.h
│   └── Reservacion.h
├── data/
│   ├── alojamientos.txt
│   ├── huespedes.txt
│   └── reservaciones.txt
├── docs/
└── README.md
```

## Persistencia de Datos
El sistema utiliza archivos de texto para almacenar la información:
- `alojamientos.txt`: Información de alojamientos disponibles
- `huespedes.txt`: Datos de usuarios registrados
- `reservaciones.txt`: Registro de reservaciones

