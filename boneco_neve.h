#ifndef BONECO
#define BONECO

#include "base.h"

OBJ cria_boneco_neve(coordenadas*vertices,  int vertice_inicial);

void desenha_boneco(OBJ boneco_neve, GLint loc_color, GLint loc_matriz, int cor);

#endif