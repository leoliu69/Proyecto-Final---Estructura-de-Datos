#include "curriculum.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>


void cargarMalla(AppState* state, const char* csv_path);
void actualizarSemestre(AppState* state, int num_semestre);
void inscribirAsignaturas(AppState* state, int num_semestre)
