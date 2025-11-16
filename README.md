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
gcc main.c curriculum.c tdas/*.c -o navegador

**## ▶️__textoClonar el repositori

En Linux / Mac:
./navegador

En Windows:
./navegador.exe


📂 Requisitos del archivo CSV
El archivo debe estar dentro de la carpeta:
data/


