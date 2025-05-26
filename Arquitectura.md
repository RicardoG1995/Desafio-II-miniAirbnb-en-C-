# Arquitectura del Sistema

## Visión General

El Sistema UdeASay es una aplicación de gestión de alojamientos implementada en C++ que sigue los principios de la programación orientada a objetos (POO). La arquitectura está diseñada para ser modular, mantenible y escalable, con un enfoque en la seguridad de datos y el rendimiento óptimo.

### Objetivos Arquitectónicos
- **Modularidad**: Componentes independientes y reutilizables
- **Escalabilidad**: Facilidad para añadir nuevas características
- **Mantenibilidad**: Código limpio y bien documentado
- **Seguridad**: Protección de datos y validación de entrada
- **Rendimiento**: Optimización de recursos y operaciones

## Estructura del Sistema

### Diagrama de Componentes
```
+-------------------+     +------------------+     +------------------+
|   SistemaUdeAStay |     |    Alojamiento   |     |    Reservacion   |
+-------------------+     +------------------+     +------------------+
| - alojamientos    |     | - codigo        |     | - codigo        |
| - huespedes       |     | - nombre        |     | - fechaInicio   |
| - anfitriones     |     | - tipo          |     | - duracion      |
| - reservaciones   |     | - ubicacion     |     | - huesped       |
| - monitor         |     | - precioNoche   |     | - metodoPago    |
+-------------------+     +------------------+     +------------------+
         |                        |                        |
         |                        |                        |
+-------------------+     +------------------+     +------------------+
|     Huesped       |     |    Anfitrion    |     |  MonitorSistema |
+-------------------+     +------------------+     +------------------+
| - documento       |     | - documento     |     | - memoriaTotal  |
| - nombre         |     | - antiguedad    |     | - iteraciones   |
| - antiguedad     |     | - puntuacion    |     | - reporte       |
| - puntuacion     |     | - alojamientos  |     +------------------+
+-------------------+     +------------------+
```

## Componentes Principales

### 1. SistemaUdeAStay
- **Responsabilidad**: Coordinar todas las operaciones del sistema
- **Dependencias**: Todas las demás clases

### 2. Estructuras de Datos

#### Lista Enlazada Genérica
```cpp
template<class T>
class Lista {
    Nodo<T>* primero;
public:
    void agregar(T dato);
    void eliminar(string id);
    T* buscar(string id);
};
```

#### Nodo Genérico
```cpp
template<class T>
class Nodo {
    T dato;
    Nodo<T>* siguiente;
public:
    Nodo(T dato);
};
```

## Flujos de Datos

### 1. Proceso de Reservación
```
[Usuario] -> [SistemaUdeASay]
    -> Verificar Huesped
    -> Verificar Alojamiento
    -> Crear Reservacion
    -> Actualizar Disponibilidad
    -> Guardar Datos
```

### 2. Gestión de Memoria
```
[Operación] -> [MonitorSistema]
    -> Registrar Memoria
    -> Contar Iteración
    -> Actualizar Reporte
```

## Persistencia de Datos

### Sistema de Almacenamiento
- **Tipo**: Almacenamiento basado en archivos de texto plano .txt
- **Ventajas**:
  * Simplicidad en la implementación
  * Fácil lectura y depuración
  * Portabilidad entre sistemas
- **Consideraciones**:
  * Validación de integridad de datos
  * Respaldo automático

### Estructura de Archivos
```
/UdeAStay-Terminal
├── alojamientos.txt    # Información de propiedades y amenidades
├── huespedes.txt      # Registro de usuarios y puntuaciones
├── anfitriones.txt    # Datos de propietarios
├── reservaciones.txt  # Historial de reservas
└── reporte_sistema.txt # Estadísticas y monitoreo
```

### Formato y Estructura de Datos

#### alojamientos.txt
```
codigo|nombre|tipo|departamento|municipio|direccion|precio|anfitrion
amenidad1,amenidad2,amenidad3
```
- **Separador principal**: | 
- **Separador de amenidades**: , 
- **Estructura**: Datos básicos en primera línea, amenidades en segunda

#### huespedes.txt
```
documento|nombre|antiguedad|puntuacion
```
- **Campos obligatorios**: documento, nombre
- **Campos calculados**: antiguedad, puntuacion

#### anfitriones.txt
```
documento|antiguedad|puntuacion
```
- **Identificación única**: documento
- **Métricas de rendimiento**: antiguedad, puntuacion

#### reservaciones.txt
```
codigo|fechaInicio|duracion|huesped|metodoPago|fechaPago|monto|observaciones|alojamiento
```
- **Identificador**: codigo (único)
- **Datos temporales**: fechaInicio, duracion
- **Información financiera**: metodoPago, monto
- **Referencias**: huesped, alojamiento

### Estrategias de Manejo de Datos
1. **Carga Inicial**:
   - Lectura al inicio del programa
   - Validación de integridad
   - Creación de estructuras en memoria

2. **Actualización**:
   - Guardado automático tras modificaciones
   - Verificación antes de escribir
   - Manejo de errores de E/S

3. **Respaldo**:
   - Copias de seguridad periódicas
   - Recuperación ante fallos
   - Logs de transacciones

## Gestión de Memoria y Monitoreo

### Estrategias de Gestión de Memoria
1. **Asignación Dinámica**:
   - Uso de `new` y `delete` controlado
   - Gestión de memoria para estructuras de datos
   - Liberación automática en destructores

2. **Prevención de Fugas**:
   - Destructores bien implementados
   - Limpieza de recursos en casos de error
   - Verificación periódica de memoria

3. **Optimización de Recursos**:
   - Reutilización de objetos cuando es posible
   - Minimización de copias innecesarias
   - Uso eficiente de estructuras de datos

### Sistema de Monitoreo (MonitorSistema)

#### Métricas Principales
1. **Uso de Memoria**:
   - Seguimiento de memoria asignada

2. **Rendimiento**:
   - Conteo de operaciones
   - Tiempo de ejecución
   - Eficiencia de algoritmos

3. **Estadísticas del Sistema**:
   - Número total de objetos
   - Operaciones por segundo
   - Tasas de éxito/error

#### Implementación del Monitoreo
```cpp
class MonitorSistema {
private:
    size_t memoriaTotal;
    unsigned long iteraciones;
    vector<string> log;

public:
    void sumarMemoria(size_t bytes);
    void registrarIteracion();
    void generarReporte();
};
```

#### Generación de Reportes
- **Formato**: Archivo de texto estructurado
- **Frecuencia**: Actualización en tiempo real
- **Contenido**:
  * Estadísticas de uso de memoria
  * Contadores de operaciones
  * Registro de eventos importantes
  * Métricas de rendimiento

## Patrones de Diseño y Buenas Prácticas

### Patrones Implementados

1. **SistemaUdeAStay**
   ```cpp
   class SistemaUdeAStay {
   private:
       static SistemaUdeAStay* instancia;
       SistemaUdeAStay() {}
   public:
       static SistemaUdeAStay* obtenerInstancia();
   };
   ```
   - Garantiza una única instancia del sistema
   - Acceso global controlado
   - Inicialización 

2. **Template (Lista y Nodo)**
   ```cpp
   template<class T>
   class Lista {
       Nodo<T>* cabeza;
   public:
       void agregar(T elemento);
       T* buscar(const T& criterio);
   };
   ```
   - Reutilización de código
   - Tipado fuerte
   - Flexibilidad en tipos de datos

3. **Observer (MonitorSistema)**
   ```cpp
   class MonitorSistema {
   public:
       void notificarCambio(const string& evento);
       void registrarObservador(Observer* obs);
   };
   ```
   - Monitoreo en tiempo real
   - Notificaciones de eventos
   - Desacoplamiento de componentes

### Principios Aplicados

1. **Single Responsibility**
   - Cada clase tiene una única responsabilidad
   - Separación clara de funcionalidades

2. **Dependency Inversion**
   - Dependencias basadas en abstracciones
   - Inversión de control

## Sistema de Manejo de Errores

### Jerarquía de Excepciones
```cpp
class SistemaException : public exception {
public:
    enum TipoError {
        ERROR_ARCHIVO,
        ERROR_VALIDACION,
        ERROR_MEMORIA,
        ERROR_LOGICA
    };

private:
    string mensaje;
    TipoError tipo;

public:
    SistemaException(string msg, TipoError t)
        : mensaje(msg), tipo(t) {}
    
    const char* what() const throw() {
        return mensaje.c_str();
    }

    TipoError getTipo() const {
        return tipo;
    }
};
```

### Estrategias de Manejo de Errores

1. **Validación Preventiva**
   - Verificación de datos de entrada
   - Validación de estados del sistema
   - Comprobación de precondiciones

2. **Manejo de Excepciones**
   ```cpp
   try {
       // Operación que puede fallar
   } catch (const SistemaException& e) {
       switch(e.getTipo()) {
           case SistemaException::ERROR_ARCHIVO:
               // Manejo específico
               break;
           // Otros casos
       }
   }
   ```

3. **Logging y Recuperación**
   - Registro detallado de errores
   - Estrategias de recuperación
   - Notificación al usuario

4. **Niveles de Severidad**
   - Errores críticos (requieren terminación)
   - Advertencias (pueden continuar)
   - Información (registro para debugging)

## Seguridad y Protección de Datos

### Medidas de Seguridad Implementadas

1. **Control de Acceso**
   ```cpp
   class SistemaUdeAStay {
   private:
       bool autenticarUsuario(string documento, string tipo);
       bool validarPermisos(string documento, string operacion);
   public:
       bool login();
   };
   ```
   - Autenticación de usuarios
   - Control de roles (huésped/anfitrión)
   - Registro de accesos

2. **Protección de Datos**
   - Validación de entrada
   - Sanitización de datos
   - Encapsulamiento de información sensible

3. **Integridad de Datos**
   - Verificación de consistencia
   - Validación de restricciones
   - Respaldo periódico

### Buenas Prácticas de Seguridad

1. **Manejo de Datos Sensibles**
   - No almacenar contraseñas en texto plano
   - Protección de información personal
   - Acceso controlado a datos críticos

2. **Validación de Entrada**
   ```cpp
   class ValidadorDatos {
   public:
       static bool validarDocumento(const string& doc);
       static bool validarFecha(const string& fecha);
       static bool validarMonto(float monto);
   };
   ```

## Escalabilidad y Mantenimiento

### Arquitectura Escalable

1. **Diseño Modular**
   - Componentes independientes
   - Interfaces bien definidas
   - Bajo acoplamiento

2. **Extensibilidad**
   ```cpp
   // Interfaz base para futuros tipos de alojamiento
   class IAlojamiento {
   public:
       virtual float calcularPrecio() = 0;
       virtual bool verificarDisponibilidad() = 0;
   };
   ```

## Optimización y Rendimiento

### Estrategias de Optimización

1. **Estructuras de Datos Eficientes**
   ```cpp
   template<class T>
   class CacheOptimizada {
   private:
       unordered_map<string, T> cache;
       size_t maxSize;
   public:
       T* obtener(const string& key);
       void almacenar(const string& key, const T& valor);
   };
   ```

2. **Algoritmos Optimizados**
   - Búsqueda eficiente
   - Ordenamiento optimizado
   - Procesamiento por lotes

### Métricas de Rendimiento

1. **Monitoreo en Tiempo Real**
   - Tiempo de respuesta promedio
   - Uso de memoria
   - Operaciones por segundo

2. **Análisis de Rendimiento**
   ```cpp
   class AnalizadorRendimiento {
   public:
       void iniciarMedicion();
       void finalizarMedicion();
       void generarReporte();
   private:
       chrono::high_resolution_clock::time_point inicio;
       vector<MetricaRendimiento> metricas;
   };
   ```

### Optimizaciones Implementadas

1. **Gestión de Memoria**
   - Pool de objetos
   - Liberación controlada
   - Prevención de fragmentación

2. **Caché y Almacenamiento**
   - Caché en memoria
   - Búfer de escritura
   - Compresión de datos

## Pruebas

### Estrategias
1. Pruebas unitarias
2. Pruebas de integración
3. Pruebas de sistema
4. Pruebas de rendimiento

## Mantenimiento

### Prácticas
1. Código limpio
2. Documentación actualizada
3. Control de versiones
4. Revisión de código

## Futuras Mejoras

### Planificadas
1. Sistema de notificaciones
2. Múltiples idiomas
3. Respaldo automático
4. Análisis de datos
5. Agregar mas funcionalidades

