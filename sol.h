#ifndef SOL
#define SOL

#include "base.h"

OBJ cria_sol(coordenadas*vertices, int vertice_inicial);

void desenha_sol(OBJ sol, GLint loc_color, GLint loc_matriz, int cor);

#endif