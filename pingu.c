#include "pingu.h"

OBJ cria_pingu(coordenadas*vertices , int vertice_inicial)
{   
    const int num_vert_circ = 32;
    int atual_vertc = vertice_inicial;

    OBJ pingu;
    pingu.vertice_inicial = vertice_inicial;

    //setando os valores iniciais para a matriz de transformacao do objeto
    pingu.s = 1;
    pingu.theta = 0;
    pingu.tx = 0;
    pingu.ty = 0;

    // Corpo 1
    add_circulo(vertices, atual_vertc, num_vert_circ, 0.0, -0.1, 0.3); 
    atual_vertc += num_vert_circ;

    // Corpo 2
    add_circulo(vertices, atual_vertc, num_vert_circ, 0.0, -0.1, 0.17); 
    atual_vertc += num_vert_circ;

    // cabeca
    add_circulo(vertices, atual_vertc, num_vert_circ, 0.0, 0.26, 0.17); 
    atual_vertc += num_vert_circ;

    // Olho 1
    add_circulo(vertices, atual_vertc, num_vert_circ, 0.1, 0.3, 0.05); 
    atual_vertc += num_vert_circ;

    // Olho 1.2
    add_circulo(vertices, atual_vertc, num_vert_circ, 0.1, 0.3, 0.026); 
    atual_vertc += num_vert_circ;

    // Olho 2
    add_circulo(vertices, atual_vertc, num_vert_circ, -0.1, 0.3, 0.05); 
    atual_vertc += num_vert_circ;

    // Olho 2.2
    add_circulo(vertices, atual_vertc, num_vert_circ, -0.1, 0.3, 0.026); 
    atual_vertc += num_vert_circ;

    // Nariz
    vertices[atual_vertc].x = 0;
    vertices[atual_vertc].y = 0.18;
    atual_vertc++;

    vertices[atual_vertc].x = 0.05;
    vertices[atual_vertc].y = 0.25;
    atual_vertc++;

    vertices[atual_vertc].x = -0.05;
    vertices[atual_vertc].y = 0.25;
    atual_vertc++;

    // pegando o numero de vertices
    pingu.num_vertices = atual_vertc - vertice_inicial;

    return pingu;
}

void desenha_pingu(OBJ pingu, GLint loc_color, GLint loc_matriz, int cor)
{
    //chamar a funcao para montar e enviar a matriz de transformacao para gpu
    matriz_transformacao_objeto(pingu, loc_matriz);

    int shift = pingu.vertice_inicial;

    colorir(loc_color, 0.0, 0.0, 0.0, cor);
    //corpo, parte preta
    desenha_circulo(0+shift, 32);
    desenha_circulo(64+shift, 32);

    // corpo, parte branca
    colorir(loc_color, 1.0, 1.0, 1.0, cor);
    desenha_circulo(32+shift, 32);
    desenha_circulo(96+shift, 32);
    desenha_circulo(160+shift, 32);

    // pupila
    colorir(loc_color, 0.0, 0.0, 0.0, cor);
    desenha_circulo(128+shift, 32);
    desenha_circulo(192+shift, 32);

    // nariz
    colorir(loc_color, 0.93, 0.66, 0.18, cor);
    desenha_triangulo(224+shift);

    return;
}