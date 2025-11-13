#include "curriculum.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    AppState* state createAppState() ;
    char opcion;
    printf("========================================\n");
    printf(" SISTEMA DE AVANCE CURRICULAR\n");
    printf("  Ingeniería Civil Informática\n - PUCV\n");
    printf("  (Actualizado 2025)\n");
    printf("========================================\n\n");

    printf("¿Desea cargar una malla curricular? (S/N): ");
    char cargar;
    scanf(" %c", &cargar);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 

    if (cargar == 'S' || cargar == 's') {
        limpiarPantalla();
        printf("Ingrese el nombre del archivo (debe estar en la carpeta 'data'):\n");
        printf("Ejemplo: mi_malla.csv\n");
        printf(">");
        
        char nombreArchivo[256];
        scanf("%255s", nombreArchivo);
        char rutaCompleta[300];
        sprintf(rutaCompleta, "data/%s", nombreArchivo);

        printf("\nCargando malla curricular desde:  %s...\n\n", rutaCompleta);
        cargarMalla(state, rutaCompleta);
        presioneTeclaParaContinuar();
    } else {
        limpiarPantalla();
        printf("Cargando malla curricular por defecto...\n\n");
        cargarMalla(state, "data/curriculum_map.csv");
        presioneTeclaParaContinuar();
    }
    do {
        
    }
}
