#ifndef CURRICULUM_H
#define CURRICULUM_H

#include "tdas/list.h"
#include "tdas/map.h"
#include <stdbool.h>

#define MAX_COURSES 200

typedef enum {
    SIN_CURSAR,
    CURSANDO,
    APROBADO,
    REPROBADO,
    RETIRADO
} Situacion;

typedef struct {
    char codigo[15];
    char nombre[100];
    int semestre;
    int creditos;
    List* prerequisitos;
    float nota;
    Situacion situacion;
} Asignatura;

typedef struct {
    int numero;
    List* asignaturas;
    float promedio;
} Semestre;

typedef struct {
    char nombre[100];
    Map* malla;
    List* semestres_cursados;
    int creditos_aprobados;
    float promedio_acumulado;
    int creditos_totales;
} Estudiante;

typedef struct {
    Estudiante* estudiante;
    char csv_path[256];
    bool datos_cargados;
} AppState;

Asignatura* createAsignatura(const char* codigo, const char* nombre, int semestre, int creditos, const char* prereqs);
void freeAsignatura(Asignatura* asig);

Semestre* createSemestre(int numero);
void freeSemestre(Semestre* sem);

Estudiante* createEstudiante(const char* nombre);
void freeEstudiante(Estudiante* est);

AppState* createAppState();
void freeAppState(AppState* state);

void cargarMalla(AppState* state, const char* csv_path);
void actualizarSemestre(AppState* state, int num_semestre);
void inscribirAsignaturas(AppState* state, int num_semestre);
void ingresarNotas(AppState* state);
void calcularPromedios(AppState* state);
void verAvance(AppState* state);
void exportarReporte(AppState* state);
bool validarPrerequisitos(Estudiante* est, Asignatura* asig);
List* obtenerAsignaturasDisponibles(AppState* state, int semestre);
Situacion stringToSituacion(const char* str);
const char* situacionToString(Situacion sit);

#endif
