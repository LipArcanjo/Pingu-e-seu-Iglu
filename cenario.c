#include "cenario.h"

OBJ cria_cenario(coordenadas*vertices,int vertice_inicial){

    
    OBJ cenario;
    cenario.vertice_inicial = vertice_inicial;

    //setando os valores iniciais para a matriz de transformacao do objeto
    cenario.s = 1;
    cenario.theta = 0;
    cenario.tx = 0;
    cenario.ty = 0;


    int atual = vertice_inicial;

    //adiciona o fundo azul
    vertices[atual].x = -1;
    vertices[atual].y = -1;
    atual++;
    
    vertices[atual].x = -1;
    vertices[atual].y = 1;
    atual++;

    vertices[atual].x = 1;
    vertices[atual].y = -1;
    atual++;

    vertices[atual].x = 1;
    vertices[atual].y = 1;
    atual++;

    //adicionando o chao de gelo
    vertices[atual].x = -1;
    vertices[atual].y = -1;
    atual++;
    
    vertices[atual].x = -1;
    vertices[atual].y = 0.3;
    atual++;

    vertices[atual].x = 1;
    vertices[atual].y = -1;
    atual++;

    vertices[atual].x = 1;
    vertices[atual].y = 0.3;
    atual++;

    cenario.num_vertices = atual - vertice_inicial;
    return cenario;

}

void desenha_cenario(OBJ cenario, GLint loc_color, GLint loc_matriz, int cor){

    //chamar a funcao para montar e enviar a matriz de transformacao para gpu
    matriz_transformacao_objeto(cenario, loc_matriz);


    int atual = cenario.vertice_inicial;

    //desenhando o fundo azul
    colorir(loc_color, 0.0, 0.6, 1, cor);
    desenha_quadrado(atual);
    atual += 4;

    //desenhando chao de gelo
    colorir(loc_color, 1.0, 1.0, 1.0, cor);
    desenha_quadrado(atual);

}