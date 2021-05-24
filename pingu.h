#ifndef PINGU
#define PINGU

#include "base.h"

OBJ cria_pingu(coordenadas*vertices, int vertice_inicial);

void desenha_pingu(OBJ sol, GLint loc_color, GLint loc_matriz, int cor);

#endif