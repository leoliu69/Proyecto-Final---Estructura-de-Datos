#include "curriculum.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_equal_string(void* key1, void* key2) {
    return strcmp((char*)key1, (char*)key2) == 0;
}


void cargarMalla(AppState* state, const char* csv_path) {
    FILE* archivo = fopen(csv_path, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    
    strcpy(state->csv_path, csv_path);
    
    if (state->estudiante != NULL) {
        freeEstudiante(state->estudiante);
        state->estudiante = NULL;
    }
    
    state->estudiante = createEstudiante("Estudiante");
    if (state->estudiante == NULL) {
        fclose(archivo);
        return;
    }
    
    char** campos = leer_linea_csv(archivo, ',');
    if (campos == NULL) {
        fclose(archivo);
        return;
    }
    
    int total_creditos = 0;
    int count = 0;
    
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        if (campos[0] == NULL || campos[1] == NULL || campos[2] == NULL || campos[3] == NULL) {
            continue;
        }
        
        char* codigo = campos[0];
        char* nombre = campos[1];
        int semestre = atoi(campos[2]);
        int creditos = atoi(campos[3]);
        char* prereqs = (campos[4] != NULL) ? campos[4] : "";
        char* grades = (campos[5] != NULL) ? campos[5] : "";
        char* situacion_str = (campos[6] != NULL) ? campos[6] : "";
        
        Asignatura* asig = createAsignatura(codigo, nombre, semestre, creditos, prereqs);
        if (asig == NULL) continue;
        
        if (strlen(grades) > 0) {
            asig->nota = atof(grades);
        }
        
        asig->situacion = stringToSituacion(situacion_str);
        
        total_creditos += creditos;
        
        char* codigo_key = strdup(codigo);
        map_insert(state->estudiante->malla, codigo_key, asig);
        count++;
    }
    
    fclose(archivo);
    
    state->estudiante->creditos_totales = total_creditos;
    state->datos_cargados = true;
    
    printf("\nMalla curricular cargada exitosamente.\n");
    printf("Total de asignaturas: %d\n", count);
    printf("Total de creditos del programa: %d\n", total_creditos);
}

bool validarPrerequisitos(Estudiante* est, Asignatura* asig) {
    if (est == NULL || asig == NULL) return false;
    
    char* prereq = list_first(asig->prerequisitos);
    while (prereq) {
        MapPair* pair = map_search(est->malla, prereq);
        if (pair == NULL) {
            return false;
        }
        
        Asignatura* prereq_asig = (Asignatura*)pair->value;
        if (prereq_asig->situacion != APROBADO) {
            return false;
        }
        
        prereq = list_next(asig->prerequisitos);
    }
    
    return true;
}

void calcularPromedios (AppState* state){
    if (!state->datos_cargados) return;

    float sumaNotas = 0.0;
    int creditosConNota = 0;
    int creditosAprobados = 0;


    MapPair* pair = map_first(state->estudiante->malla);
    while (pair) {
        Asignatura* asig = (Asignatura*)pair->value;
        
        if (asig->situacion == APROBADO || asig->situacion == REPROBADO){
            if(asig->nota > 0){
                sumaNotas += asig->nota * asig->creditos;
                creditosConNota += asig->creditos;
            }
        }
        if (asig->situacion == APROBADO){
            creditosAprobados += asig->creditos;
        }

        pair = map_next(state->estudiante->malla);
    }

    state->estudiante->creditos_aprobados = creditosAprobados;
    state->estudiante->promedio_acumulado = (creditosConNota > 0) ? (sumaNotas / creditosConNota) : 0.0;
}

void verAvance(AppState* state) {
    if (!state->datos_cargados) {
        printf("\nPrimero debes cargar una malla curricular.\n");
        return;
    }

    calcularPromedios(state);

    limpiarPantalla();
    printf("========================================\n");
    printf("        AVANCE GENERAL\n");
    printf("========================================\n\n");

    printf("Estudiante: %s\n\n", state->estudiante->nombre);

    printf("Creditos Aprobados: %d / %d\n", state->estudiante->creditos_aprobados, state->estudiante->creditos_totales);
    
    float porcentaje = (state->estudiante->creditos_totales > 0) ? 
                       ((float)state->estudiante->creditos_aprobados / state->estudiante->creditos_totales) * 100 : 0.0;

    printf("Porcentaje de avance: %.1f%%\n", porcentaje);
    printf("Promedio acumulado: %.2f\n\n", state->estudiante->promedio_acumulado);
                       
    printf("Detalle por semestre:\n");
    printf("%-10s %-50s %-10s %-10s %-15s\n", "CODIGO", "NOMBRE", "CREDITOS", "NOTA", "SITUACION");
    printf("========================================================================================================\n");

    for (int sem = 1 ; sem <= 11 ; sem++) {
        bool tieneAsignaturas = false;

        MapPair* pair = map_first(state->estudiante->malla);
        while (pair) {
            Asignatura* asig = (Asignatura*)pair->value;
            if (asig->semestre == sem) {
                if (!tieneAsignaturas) {
                    printf("\n--- SEMESTRE %d ---\n", sem);
                    tieneAsignaturas = true;
                }

                printf("%-10s %-50s %-10d %-10.1f %-15s\n", asig->codigo, asig->nombre, asig->creditos, asig->nota, situacionToString(asig->situacion));
            }
            pair = map_next(state->estudiante->malla);
        }
    }

    printf("\n========================================\n");
}

Asignatura* createAsignatura(const char* codigo, const char* nombre, int semestre, int creditos, const char* prereqs) {
    Asignatura* asig = malloc(sizeof(Asignatura));
    if (!asig) return NULL;

    strcpy(asig->codigo, codigo);
    strcpy(asig->nombre, nombre);
    asig->semestre = semestre;
    asig->creditos = creditos;
    asig->nota = 0.0f;
    asig->situacion = SIN_CURSAR;

    asig->prerequisitos = list_create();
    
    if (prereqs && strlen(prereqs) > 0) {
        char* copia = strdup(prereqs);
        char* token = strtok(copia, " ");
        while (token) {
            pushBack(asig->prerequisitos, strdup(token));
            token = strtok(NULL, " ");
        }
        free(copia);
    }

    return asig;
}

void freeAsignatura(Asignatura* asig) {
    if (!asig) return;

    char* p = list_first(asig->prerequisitos);
    while (p) {
        free(p);
        p = list_next(asig->prerequisitos);
    }

    free(asig->prerequisitos);
    free(asig);
}

Semestre* createSemestre(int numero) {
    Semestre* s = malloc(sizeof(Semestre));
    s->numero = numero;
    s->asignaturas = list_create();
    s->promedio = 0.0;
    return s;
}

void freeSemestre(Semestre* sem) {
    if (!sem) return;

    free(sem->asignaturas);
    free(sem);
}

Estudiante* createEstudiante(const char* nombre) {
    Estudiante* e = malloc(sizeof(Estudiante));

    strcpy(e->nombre, nombre);
    e->malla = createMap(is_equal_string);
    e->semestres_cursados = list_create();

    e->creditos_aprobados = 0;
    e->promedio_acumulado = 0;
    e->creditos_totales = 0;

    return e;
}

void freeEstudiante(Estudiante* est) {
    if (!est) return;

    MapPair* p = map_first(est->malla);
    while (p) {
        freeAsignatura((Asignatura*)p->value);
        p = map_next(est->malla);
    }

    free(est->malla);
    free(est->semestres_cursados);
    free(est);
}
