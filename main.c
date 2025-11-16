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
        limpiarPantalla();
        printf("========================================\n");
        printf(" SISTEMA DE AVANCE CURRICULAR\n");
        printf("========================================\n");

        if (state->datos_cargados) {
            printf("Estado: Malla cargada (%s)\n", state->csv_path);
            printf("Creditos aprobados: %d / %d\n",
                state->estudiante->creditos_aprobados,
                state->estudiante->creditos_totales);
        } else {
            printf("Estado: Sin datos cargados.\n");
        }

        printf("========================================\n");
        printf("1. Cargar malla curricular\n");
        printf("2. Actualizar semestre(s)\n");
        printf("3. Inscribir asignaturas\n");
        printf("4. Ingresar/Editar notas\n");
        printf("5. Ver avance general\n");
        printf("6. Exportar reporte (actualizar CSV)\n");
        printf("7. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");

        scanf(" %c", &opcion);
        while ((c = getchar()) != '\n' && c != EOF) ;

        switch (opcion) {
            case '1': {
                limpiarPantalla();
                printf("Cargando malla curricular por defecto...\n\n");
                cargarMalla(state, "data/curriculum_map.csv");
                presioneTeclaParaContinuar();
                break;
            }

            case '2': {
                if (!state->datos_cargados) {
                    limpiarPantalla();
                    printf("\nPrimero debes cargar una malla curricular.\n");
                    presioneTeclaParaContinuar();
                    break;
                }

                limpiarPantalla();
                printf("¿Que semestre desea actualizar? (1-11): ");
                int num_semestre ; 

                if (scanf("%d", &num_semestre) !=1 ) {
                    num_semestre = -1;
                }
                while ((c = getchar()) != '\n' && c != EOF) ;

                if (num_semestre < 1 || num_semestre > 11) {
                    printf("\nNumero de semestre invalido.\n");
                    presioneTeclaParaContinuar();
                    break;
                }

                actualizarSemestre(state, num_semestre);

                calcularPromedios(state);
                printf("¡Actualizacion completada!\n");
                presioneTeclaParaContinuar();
                break;
            }

            case '3': {
                if (!state->datos_cargados) {
                    limpiarPantalla();
                    printf("\nPrimero debes cargar una malla curricular.\n");
                    presioneTeclaParaContinuar();
                    break;
                }

                limpiarPantalla();
                printf("¿Para que semestre desea inscribir asignaturas? (1-11): ");
                int semestre ; 

                if (scanf("%d", &num_semestre) !=1 ) {
                    semestre = -1;
                }
                while ((c = getchar()) != '\n' && c != EOF) ;

                if (semestre < 1 || semestre > 11) {
                    printf("\nSemestre invalido.\n");
                    presioneTeclaParaContinuar();
                    break;
                }

                inscribirAsignaturas(state, semestre);

                presioneTeclaParaContinuar();
                break;
            }

            case '4': {
                ingresarNotas(state);
                calcularPromedios(state);
                presioneTeclaParaContinuar();
                break;
            } 

            case '5': {
                verAvance(state);
                presioneTeclaParaContinuar();
                break;
            }

            case '6': {
                exportarReporte(state); 
                presioneTeclaParaContinuar();
                break;     
            }
            case '7':
                printf("\n¡Gracias por usar el Sistema de Avance Curricular!\n");
                printf("\nDesarrollado por Team CZ, Estructura de Datos 2S 2025\n");
            }

            default: {
                printf("\nOpcion invalida.\n");
                presioneTeclaParaContinuar();
            }
        }

    } while (opcion != '7');
    freeAppState(state);
    return 0;  
}
