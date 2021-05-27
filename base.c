#include "base.h"

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
void add_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius){
    float pi = 3.14;
    float counter = 0;
    float angle = 0.0;
    float x, y;
    for(int i=0; i < num_vertices; i++){
	    angle += (2.0*pi)/num_vertices;
	    x = cos(angle)*radius + x_ini;
	    y = sin(angle)*radius + y_ini;
	    vertices[i + vertice_inicial].x = x;
	    vertices[i + vertice_inicial].y = y;
    }
}

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
void add_semi_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius){
    
    vertices[vertice_inicial].x = x_ini + radius;
    vertices[vertice_inicial].y = y_ini;

    vertice_inicial++;
    num_vertices--;

    float pi = M_PI;
    float angle = 0.0;
    float x, y;
    
    for(int i=0; i < num_vertices; i++){
	    angle += (1.0*pi)/num_vertices;
        x = cos(angle)*radius + x_ini;
        y = sin(angle)*radius + y_ini;
        vertices[i + vertice_inicial].x = x;
        vertices[i + vertice_inicial].y = y;
    }
}

/*
chama a primitiva para se denhar um circulo, passando a posicao do vetor do primeiro
ponto do circulo, e sua quantidade de pontos.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
*/
void desenha_circulo(int vertice_inicial, int num_vertices){
    glDrawArrays(GL_TRIANGLE_FAN, vertice_inicial, num_vertices);
}

/*
chama a primitiva para se desenhar um triangulo, passando a posicao do vetor do primeiro
ponto do triangulo.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso triangulo
*/
void desenha_triangulo(int vertice_inicial){
    glDrawArrays(GL_TRIANGLES, vertice_inicial, 3);
}

/*
chama a primitiva para se desenhar varios triangulos, passando a posicao do vetor do
primeiro ponto do primeiro triangulo, e a quantidade de triangulos que se deseja desenhar.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do primeiro triangulo.
    int qtd_triangulos - a quantidade de triangulos que deve ser desenhado.
*/
void desenha_triangulos(int vertice_inicial, int qtd_triangulos){
    glDrawArrays(GL_TRIANGLES, vertice_inicial, qtd_triangulos*3);
}

/*
chama a primitiva para se desenhar um quadrado, passando a posicao do vetor do primeiro
ponto do quadrado.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso quadrado
*/
void desenha_quadrado(int vertice_inicial){
    glDrawArrays(GL_TRIANGLE_STRIP, vertice_inicial, 4);
}

/*
chama a primitiva para se desenhar uma linha, passando a posicao do vetor do primeiro
ponto da linha.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nossa linha
*/
void desenha_linha(int vertice_inicial){
    glDrawArrays(GL_LINES, vertice_inicial, 2);
}

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
void colorir(GLint loc_color, double R, double G, double B, int cor){
    if(cor == PRETO){
        R = 0.2;
        G = 0.2;
        B = 0.2;
    }else if(cor == CINZA){
        R = 0.5;
        G = 0.5;
        B = 0.5;
    }
    glUniform4f(loc_color, R, G, B, 1.0);

}

/*
Compara se dois objetos estao posicionados da mesma forma,
ou seja, se têm os mesmo parametros da matriz de transformacao
retorna 1 se estao, retorna 0 caso contrario.
@PARAMETROS
    OBJ obj1 - objeto 1 a ser comparado.
    OBJ obj2 - objeto 2 a ser comparado.
*/
int compara_objetos(OBJ obj1, OBJ obj2){
    double eps = 0.0001;
    //compara os parametros da matriz de transformacao
    //do objeto, vendo se a diferenca absoluta
    //eh maior que um epsilon ( para evitar impressicao de ponto flutuante)
    if( fabs(obj1.tx - obj2.tx)  > eps) return 0;
    if( fabs(obj1.ty - obj2.ty) > eps) return 0;
    if( fabs(obj1.theta - obj2.theta) > eps) return 0;
    if( fabs(obj1.s - obj2.s) > eps) return 0;

    return 1;
}

/*
Faz a multiplicao de duas matrizes 4x4 e retorna o seu resultado
@PARAMETROS
    float* matrix1 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix2 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix_resultante - onde sera guardado a matriz resultando da multiplicacao matrix1*matrix2
*/
void mult_matrix(float* matrix1, float* matrix2, float* matrix_result)
{
    float matrix_temp[16];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
            {
                sum += matrix1[4*i+k] * matrix2[4*k+j];
            }
            matrix_temp[4*i+j] = sum;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix_result[4*i+j] = matrix_temp[4*i+j];
        }
    }

    return;
}

/*
Esta funcao monta a matriz de transformacao de um objeto baseado em seus parametros
de transformacao ( s, tx, ty e theta), e chama a passa esta matriz para a loc_matriz da
GPU
@PARAMETROS
    OBJ objeto - objeto que queremos montar a matriz de transformacao
    GLint loc_matriz - variavel linkada a matriz de tranformacao da GPU
*/
void matriz_transformacao_objeto(OBJ objeto, GLint loc_matriz){

    //matriz de rotacao objeto baseado no seu angulo theta
    double cose = cos(objeto.theta);
    double seno = sin(objeto.theta);

    //matriz de rotacao
    float matriz_rotacao[16] = {
            cose, -seno, 0.0f, 0.0f,
            seno,  cose, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    //matriz de escala objeto baseado no seu parametro s
    double s = objeto.s;
    float matriz_escala[16] = {
            s   , 0.0f, 0.0f, 0.0f,
            0.0f, s   , 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    //matriz de transladacao do objeto baseado nos seus parametros tx e ty 
    double tx = objeto.tx;
    double ty = objeto.ty;
    float matriz_transladacao[16] = {
            1.0f, 0.0f, 0.0f, tx  ,
            0.0f, 1.0f, 0.0f, ty  ,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    float matriz_final[16];
    //fazendo as multiplicacoes das matrizes
    mult_matrix(matriz_escala, matriz_rotacao, matriz_final);
    mult_matrix(matriz_transladacao, matriz_final , matriz_final);

    //setando o valor de gpu para ser a matriz final
    glUniformMatrix4fv(loc_matriz, 1, GL_TRUE, matriz_final);

}

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
void posiciona_objeto(OBJ*objeto, double tx, double ty, double s, double theta){
    objeto->tx = tx;
    objeto->ty = ty;
    objeto->s = s;
    objeto->theta = theta;
}