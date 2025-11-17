# Proyecto-Final---Estructura-de-Datos






# 📘 Navegador Académico – Proyecto Final (Estructura de Datos)

## 📝 Descripción
El **Navegador Académico** es una aplicación desarrollada en **lenguaje C** que permite a los estudiantes registrar, visualizar y analizar su avance curricular de manera clara y automatizada.  

El sistema carga una malla curricular desde un archivo, permite registrar semestres, ingresar notas por asignatura, verificar prerrequisitos, calcular promedios y mostrar el progreso total del estudiante.

---

## 🎯 Características principales
- 📂 Carga de malla curricular desde archivo CSV.
- 🧮 Ingreso de notas y ponderaciones por asignatura.
- 📊 Cálculo de promedios por asignatura, por semestre y promedio general acumulado (PGA).
- ✔️ Validación de prerrequisitos.
- 📎 Registro histórico de semestres cursados.
- 📈 Reporte de avance: créditos aprobados, pendientes y porcentaje completado.
- 💾 Exportación del historial académico a archivo externo.
  
---

## 📁 Estructura del proyectos


---

## 🧩 Tecnologías y TDAs utilizados

### 🔹 **Lenguaje**

- C

### 🔹 **TDA Map**

- Implementado como **tabla hash**
- Se usa para almacenar las asignaturas por código
- Operaciones comunes: búsqueda, inserción, actualización  
- Complejidad promedio: **O(1)**

### 🔹 **TDA List**

- Lista doblemente enlazada
- Usada para:
  - prerrequisitos
  - asignaturas inscritas
  - historial de semestres
- Complejidad de recorrido: **O(n)**

### 🔹 **(Opcional) TDA Graph**

- Representación de prerrequisitos como grafo dirigido
- Sirve para obtener ramos disponibles (topological sort)

---

## ▶️ Compilación

En Linux / Mac:

```bash
gcc main.c curriculum.c tdas/list.c tdas/map.c tdas/extra.c -o curriculum -Itdas -lm
./curriculum

En Windows:
gcc main.c curriculum.c tdas/list.c tdas/map.c tdas/extra.c -o curriculum -Itdas -lm
./curriculum


📂 Requisitos del archivo CSV
El archivo debe estar dentro de la carpeta:
data/

---

# 🧭 Flujo de ejecución del programa

Al iniciar el programa, se muestra una pantalla introductoria y se pregunta al usuario:

¿Desea cargar una malla curricular? (S/N):
```

Opciones iniciales:

S / s → el usuario escribe el nombre del archivo CSV a cargar desde la carpeta "data/"
N / n → el programa carga la malla por defecto desde:
```data/curriculum_map.csv```

Después de cargar la malla, el sistema entra al menú principal.

---

# 📋 Menú principal (basado en el código real)

```
========================================
 SISTEMA DE AVANCE CURRICULAR
========================================
1. Cargar malla curricular
2. Actualizar semestre(s)
3. Inscribir asignaturas
4. Ingresar/Editar notas
5. Ver avance general
6. Exportar reporte (actualizar CSV)
7. Salir
========================================
Seleccione una opcion:
```
🧾 Descripción de las opciones:

1) Cargar malla curricular

Carga nuevamente la malla por defecto desde:

```data/curriculum_map.csv```

2) Actualizar semestre(s):
-Solicita un número entre 1 y 11
-Ejecuta:
          actualizarSemestre(state, num_semestre)
          calcularPromedios(state)
          
3) Inscribir asignaturasSolicita el número de un semestre entre 1 y 11

Ejecuta:
inscribirAsignaturas(state, semestre)

4) Ingresar/Editar notas

Llama a ingresarNotas(state)
Luego actualiza los cálculos con calcularPromedios(state)

5) Ver avance general

Muestra:
Créditos aprobados
Créditos totales
% de avance curricular
Promedios actualizados

6) Exportar reporte (actualizar CSV)

Guarda la información actual del estudiante:
```exportarReporte(state);```

7) Salir

Muestra mensaje de despedida
Ejecuta freeAppState(state)

Termina el programa

🧱 Estructuras principales del sistema

Asignatura:
```
typedef struct {
    char codigo[10];
    char nombre[60];
    float creditos;
    float notaFinal;
    bool aprobada;
    List* prerequisitos;
} Asignatura;
```
Semestre:
```
typedef struct {
    int numero;
    List* asignaturas;
} Semestre;
```
Estudiante:
```
typedef struct {
    char nombre[50];
    Map* malla;
    List* semestres;
    int creditos_aprobados;
    int creditos_totales;
} Estudiante; 
```
```
AppState
```
Contiene:

Bandera datos_cargados
Ruta del CSV cargado
Puntero al estudiante
Estados internos de la ejecución


🧠 Funciones principales

| Función                | Acción                         |
| ---------------------- | ------------------------------ |
| createAppState()       | Inicializa la aplicación       |
| cargarMalla()          | Carga CSV y crea la malla      |
| actualizarSemestre()   | Actualiza datos del semestre   |
| inscribirAsignaturas() | Inscribe ramos del semestre    |
| ingresarNotas()        | Permite ingresar/editar notas  |
| calcularPromedios()    | Calcula promedios actualizados |
| verAvance()            | Muestra el avance general      |
| exportarReporte()      | Guarda datos en archivo        |
| freeAppState()         | Libera memoria al salir        |

---

# 🔥 Desafíos del proyecto

Durante el desarrollo del sistema se presentaron varios desafíos técnicos, entre ellos:

- Manejo de memoria dinámica en C utilizando **listas enlazadas**, **tablas hash** y estructuras anidadas.  
- Mantener la consistencia entre:
  - malla curricular cargada,
  - semestres actualizados,
  - notas registradas,
  - reporte exportado.
- Validación correcta de entradas del usuario (semestres válidos, archivos válidos, opciones del menú, etc.).  
- Integración de múltiples módulos (`curriculum.c`, TDAs, utilidades de consola).  
- Lectura y manipulación de archivos CSV con diferentes longitudes y estructura variable.

---

# 🔮 Mejoras futuras

Algunas mejoras que podrían implementarse en futuras versiones del sistema:

- Agregar opción para cargar diferentes archivos de malla desde el menú principal.  
- Guardar y cargar el progreso del estudiante en formatos modernos como **JSON**.  
- Implementar interfaz gráfica (GUI) para mejorar la usabilidad.  
- Permitir manejo de múltiples estudiantes en un solo programa.  
- Integración de un grafo de prerrequisitos real para sugerencias automáticas de inscripción.  
- Mejorar validación del archivo CSV (detección de errores de formato o datos faltantes).  

---

# 👥 Integrantes del equipo

- **Patricio Quispe Aquino**  
- **Cristóbal Ogaz Cedano**  
- **Fernando Guerrero Díaz**  
- **Miguel Carvajal Camus**  
- **Manuel Campillay Miranda**

*(La contribución detallada de cada integrante se encuentra en el informe del proyecto.)*

