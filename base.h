#ifndef BASE
#define BASE

#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// variaveis globais
typedef struct{
    float x, y;
} coordenadas;

enum cores_{ COLORIDO, CINZA, PRETO } cores;

typedef struct _obg{
    int vertice_inicial;
    int num_vertices;


    double tx, ty;
    double s;
    double theta;
}OBJ;

void add_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

void add_semi_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

void desenha_circulo(int vertice_inicial, int num_vertices);

void desenha_triangulo(int vertice_inicial);

void desenha_triangulos(int vertice_inicial, int qtd_triangulos);

void desenha_quadrado(int vertice_inicial);

void desenha_linha(int vertice_inicial);

void colorir(GLint loc_color, double R, double G, double B, int cor);

int compara_objetos(OBJ obj1, OBJ obj2);

void mult_matrix(float* matrix1, float* matrix2, float* matrix_result);

void matriz_transformacao_objeto(OBJ objeto, GLint loc_matriz);

void posiciona_objeto(OBJ*objeto, double tx, double ty, double s, double theta);

#endif