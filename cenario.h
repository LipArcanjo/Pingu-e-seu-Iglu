#ifndef CENARIO
#define CENARIO

#include "base.h"

OBJ cria_cenario(coordenadas*vertices,int vertice_inicial);

void desenha_cenario(OBJ cenario, GLint loc_color, GLint loc_matriz, int cor);

#endif