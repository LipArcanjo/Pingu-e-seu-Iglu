#ifndef IGLU
#define IGLU

#include "base.h"

OBJ cria_iglu(coordenadas*vertices, int vertice_inicial);

void desenha_iglu(OBJ sol, GLint loc_color, GLint loc_matriz, int cor);

#endif