#ifndef BASE
#define BASE

#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
estrutura de coordenadas que sera passado para GPU.
*/
typedef struct{
    float x, y;
} coordenadas;

/*
ENUM para dar sentido as palavras COLORIDO, CINZA e PRETO, na hora de 
colorir os objetos.
*/
enum cores_{ COLORIDO, CINZA, PRETO } cores;

/*
estrutura que define os objetos em cena,
nela se guarda qual o  vertice do vetor de coordenadas
que se comeca o objeto, a quantidade de vertices, e seus
parametros da matriz de transformacao
*/
typedef struct _obg{
    int vertice_inicial;
    int num_vertices;


    double tx, ty;
    double s;
    double theta;
}OBJ;

/*
adiciona um circulo ao nosso vetor de vertices, as coordenadas do pontos do circulo começa na posicao
vertice_inicial do nosso vetor e possui num_vertices.
@PARAMETROS
    coordenadas *vertices - o nosso vetor de vertices
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
    float x_ini - coordenada x do centro do nosso circulo
    float y_ini - coordenada y do centro do nosso circulo
    float radius - raio do nosso circulo
*/
void add_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

/*
adiciona um semi-circulo ao nosso vetor de vertices, as coordenadas do pontos do circulo começa na posicao
vertice_inicial do nosso vetor e possui num_vertices.
o semi-circulo só tem a metade de cima do circulo, ou seja os pontos que respeitam a equacao y = sqrt(radius - x^2).
Utiliza-se a funcao desenha_circulo para desenhar o semi-circulo, por necessitar de usar a mesma primitiva para desenhar.
@PARAMETROS
    coordenadas *vertices - o nosso vetor de vertices
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
    float x_ini - coordenada x do centro do nosso circulo
    float y_ini - coordenada y do centro do nosso circulo
    float radius - raio do nosso circulo
*/
void add_semi_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

/*
chama a primitiva para se denhar um circulo, passando a posicao do vetor do primeiro
ponto do circulo, e sua quantidade de pontos.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
*/
void desenha_circulo(int vertice_inicial, int num_vertices);

/*
chama a primitiva para se desenhar um triangulo, passando a posicao do vetor do primeiro
ponto do triangulo.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso triangulo
*/
void desenha_triangulo(int vertice_inicial);

/*
chama a primitiva para se desenhar varios triangulos, passando a posicao do vetor do
primeiro ponto do primeiro triangulo, e a quantidade de triangulos que se deseja desenhar.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do primeiro triangulo.
    int qtd_triangulos - a quantidade de triangulos que deve ser desenhado.
*/
void desenha_triangulos(int vertice_inicial, int qtd_triangulos);

/*
chama a primitiva para se desenhar um quadrado, passando a posicao do vetor do primeiro
ponto do quadrado.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso quadrado
*/
void desenha_quadrado(int vertice_inicial);

/*
chama a primitiva para se desenhar uma linha, passando a posicao do vetor do primeiro
ponto da linha.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nossa linha
*/
void desenha_linha(int vertice_inicial);

/*
chama a primitiva para colorir, utilizando as cores RGB passadas no parametro, ou pintando de cinza,
ou de preto, baseado no pamametro COR.
GLint loc_color - variavel linkada a variavel de cor da GPU
double R - intensidade de vermelho a ser pintando caso cor seja COLORIDO
double G - intensidade de verde a ser pintando caso cor seja COLORIDO
double B - intensidade de azul a ser pintando caso cor seja COLORIDO
int cor - define se a deve ser colorido, cinza ou preto
              0 - colorido
              1 - cinza
              2 - preto
              Esta variavel esta linkada com base.h, utilizando um enum com os nomes das cores
*/
void colorir(GLint loc_color, double R, double G, double B, int cor);

/*
Compara se dois objetos estao posicionados da mesma forma,
ou seja, se têm os mesmo parametros da matriz de transformacao
retorna 1 se estao, retorna 0 caso contrario.
@PARAMETROS
    OBJ obj1 - objeto 1 a ser comparado.
    OBJ obj2 - objeto 2 a ser comparado.
*/
int compara_objetos(OBJ obj1, OBJ obj2);

/*
Faz a multiplicao de duas matrizes 4x4 e retorna o seu resultado
@PARAMETROS
    float* matrix1 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix2 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix_resultante - onde sera guardado a matriz resultando da multiplicacao matrix1*matrix2
*/
void mult_matrix(float* matrix1, float* matrix2, float* matrix_result);

/*
Esta funcao monta a matriz de transformacao de um objeto baseado em seus parametros
de transformacao ( s, tx, ty e theta), e chama a passa esta matriz para a loc_matriz da
GPU
@PARAMETROS
    OBJ objeto - objeto que queremos montar a matriz de transformacao
    GLint loc_matriz - variavel linkada a matriz de tranformacao da GPU
*/
void matriz_transformacao_objeto(OBJ objeto, GLint loc_matriz);

/*
Altera os parametros de transformacao de um objeto, baseado nos parametros passados
na funcao
@PARAMETROS
    OBJ* objeto - endereco do objeto que queremos mudar os parametros
    double tx - qual o valor de tx que queremos que nosso objeto tenha
    double ty - qual o valor de ty que queremos que nosso objeto tenha
    double ts - qual o valor de s que queremos que nosso objeto tenha
    double theta - qual o valor de theta que queremos que nosso objeto tenha
*/
void posiciona_objeto(OBJ*objeto, double tx, double ty, double s, double theta);

#endif