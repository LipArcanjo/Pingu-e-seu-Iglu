#include "iglu.h"

OBJ cria_iglu(coordenadas*vertices , int vertice_inicial)
{
    const int num_vert_circ = 32;
    int atual_vertc = vertice_inicial;

    OBJ iglu;
    iglu.vertice_inicial = vertice_inicial;

    //setando os valores iniciais para a matriz de transformacao do objeto
    iglu.s = 1;
    iglu.theta = 0;
    iglu.tx = 0;
    iglu.ty = 0;

    // Iglu corpo
    add_semi_circulo(vertices, atual_vertc, num_vert_circ, 0.0, 0.0, 0.5); 
    atual_vertc += num_vert_circ;
    
    // Iglu porta
    add_semi_circulo(vertices, atual_vertc, num_vert_circ, 0.0, 0.09, 0.25); 
    atual_vertc += num_vert_circ;

    // Iglu porta.2
    add_semi_circulo(vertices, atual_vertc, num_vert_circ, 0.0, 0.09, 0.18); 
    atual_vertc += num_vert_circ;

    // Iglu porta.3
    vertices[atual_vertc].x = 0.18;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = 0.18;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;

    vertices[atual_vertc].x = -0.18;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = -0.18;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;

    // Iglu porta.4
    vertices[atual_vertc].x = 0.25;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = 0.25;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;

    vertices[atual_vertc].x = 0.18;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = 0.18;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;

    // Iglu porta.5
    vertices[atual_vertc].x = -0.25;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = -0.25;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;

    vertices[atual_vertc].x = -0.18;
    vertices[atual_vertc].y = -0.03;
    atual_vertc++;

    vertices[atual_vertc].x = -0.18;
    vertices[atual_vertc].y = 0.09;
    atual_vertc++;


    iglu.num_vertices = atual_vertc - vertice_inicial;

    return iglu;

}

void desenha_iglu(OBJ iglu, GLint loc_color, GLint loc_matriz, int cor)
{
    //chamar a funcao para montar e enviar a matriz de transformacao para gpu
    matriz_transformacao_objeto(iglu, loc_matriz);

    int shift = iglu.vertice_inicial;

    // Corpo
    colorir(loc_color, 0.2, 0.8, 1.0, cor);
    desenha_circulo(0+shift, 32);
    
    //porta    
    colorir(loc_color, 0.2, 0.6, 1.0, cor);
    desenha_circulo(32+shift, 32);
    desenha_quadrado(100+shift);
    desenha_quadrado(104+shift);

    colorir(loc_color, 0.0, 0.15, 0.3, cor);
    desenha_circulo(64+shift, 32);
    desenha_quadrado(96+shift);
    
    return;
}