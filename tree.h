#ifndef TREE
#define TREE

#include "base.h"

OBJ cria_tree(coordenadas*vertices, int vertice_inicial);

void desenha_tree(OBJ tree, GLint loc_color, GLint loc_matriz, int cor);

#endif