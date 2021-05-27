#include "tree.h"

/*
Gera os pontos referente ao objeto e adiciona os valores no vetor passado.
Ao adicionar os pontos no vetor vertices, ele utiliza o parametro vertice
inicial para saber o local onde esses pontos devem ser salvos. No fim retorna
uma variavel do tipo OBJ com informacoes referentes a este objeto criado
@PARAMETROS
    coordenadas *vertices - endereco do vetor para armazenar os vertices gerados
    int vertice_inicial - posisao no vetor vertices para o primeiro vertice gerado
@RETORNO
    OBJ - retorna o tipo OBJ com informacoes sobre o objeto criado
*/
OBJ cria_tree(coordenadas* vertices, int vertice_inicial){
    OBJ tree;
    tree.vertice_inicial = vertice_inicial;

    tree.s = 1;
    tree.theta = 0;
    tree.tx = 0;
    tree.ty = 0;

    int atual = vertice_inicial;

    //Triângulo 1 Sombra - Superior
    vertices[atual].x = -0.25f;
    vertices[atual].y = 0.35f;
    atual++;

    vertices[atual].x = 0.25f;
    vertices[atual].y = 0.35f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.80f;
    atual++;

    //Triângulo 2 Sombra - Meio
    vertices[atual].x = -0.35f;
    vertices[atual].y = 0.15f; 
    atual++;

    vertices[atual].x = 0.35f;
    vertices[atual].y = 0.15f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.60f;
    atual++;

    //Triângulo 3 Sombra - Inferior
    vertices[atual].x = -0.45f;
    vertices[atual].y = -0.05f;
    atual++;

    vertices[atual].x = 0.45f;
    vertices[atual].y = -0.05f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.40f;
    atual++;
    
    //Quadrado Sombra
    vertices[atual].x = -0.10f;
    vertices[atual].y = -0.05f;
    atual++;

    vertices[atual].x = 0.10f;
    vertices[atual].y = -0.05f;
    atual++;

    vertices[atual].x = -0.10f;
    vertices[atual].y = -0.30f;
    atual++;

    vertices[atual].x = 0.10f;
    vertices[atual].y = -0.30f;
    atual++;

    //Quadrado Luz
    vertices[atual].x = -0.08f;
    vertices[atual].y = -0.07f;
    atual++;

    vertices[atual].x = 0.08f;
    vertices[atual].y = -0.07f;
    atual++;

    vertices[atual].x = -0.08f;
    vertices[atual].y = -0.28f;
    atual++;

    vertices[atual].x = 0.08f;
    vertices[atual].y = -0.28f;
    atual++;

    //Triângulo 1 Luz - Superior
    vertices[atual].x = -0.23f;
    vertices[atual].y = 0.37f;
    atual++;

    vertices[atual].x = 0.23f;
    vertices[atual].y = 0.37f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.78f;
    atual++;

    //Triângulo 2 Luz - Meio
    vertices[atual].x = -0.33f;
    vertices[atual].y = 0.17f;
    atual++;

    vertices[atual].x = 0.33f;
    vertices[atual].y = 0.17f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.58f;
    atual++;

    //Triângulo 3 Luz - Inferior
    vertices[atual].x = -0.43f;
    vertices[atual].y = -0.03f;
    atual++;

    vertices[atual].x = 0.43f;
    vertices[atual].y = -0.03f;
    atual++;

    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.38f;
    atual++;

    tree.num_vertices = atual - vertice_inicial;

    return tree;
}

/*
Esta funcao envia a matriz referente ao objeto para a GPU alem de definir a cor
a ser utilizada. Apois isso invoca os metodos para desenhar este objeto. Esta funcao
pode desenhar um tree referenciado por OBJ tree. Vale dizer que pode ser desenhado
um objeto tanto como colorido, cinza e preto.
@PARAMETROS
    OBJ tree - variavel que guarda informacoes referente ao objeto, gerada quando o objeto eh criado
    GLint loc_color - variavel linkada a variavel de cor na GPU
    GLint loc_matriz - variavel linkada a variavel de matriz na GPU
    int cor - define se a deve ser colorido, cinza ou preto
              0 - colorido
              1 - cinza
              2 - preto
              Esta variavel esta linkada com base.h, utilizando um enum com os nomes das cores
*/
void desenha_tree(OBJ tree, GLint loc_color, GLint loc_matriz, int cor){
    
    matriz_transformacao_objeto(tree, loc_matriz);

    int atual = tree.vertice_inicial;

    colorir(loc_color, 0.113, 0.33, 0.117, cor);
    desenha_triangulo(atual);
    atual += 3;

    colorir(loc_color, 0.113, 0.33, 0.117, cor);
    desenha_triangulo(atual);
    atual += 3;

    colorir(loc_color, 0.113, 0.33, 0.117, cor);
    desenha_triangulo(atual);
    atual += 3;

    colorir(loc_color, 0.36, 0.223, 0.086, cor);
    desenha_quadrado(atual);
    atual += 4;

    colorir(loc_color, 0.568, 0.35, 0.13, cor);
    desenha_quadrado(atual);
    atual += 4;

    colorir(loc_color, 0.137, 0.411, 0.141, cor);
    desenha_triangulo(atual);
    atual += 3;

    colorir(loc_color, 0.137, 0.411, 0.141, cor);
    desenha_triangulo(atual);
    atual += 3;

    colorir(loc_color, 0.137, 0.411, 0.141, cor);
    desenha_triangulo(atual);

}