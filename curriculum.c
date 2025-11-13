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
    
}
