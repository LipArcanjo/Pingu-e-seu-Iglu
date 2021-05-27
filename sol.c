#include "sol.h"

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
OBJ cria_sol(coordenadas*vertices, int vertice_inicial){
    OBJ sol;
    sol.vertice_inicial = vertice_inicial;

    //setando os valores iniciais para a matriz de transformacao do objeto
    sol.s = 1;
    sol.theta = 0;
    sol.tx = 0;
    sol.ty = 0;

    //armazena qual o proximo indice do vetor de vertices livre, inicialmente
    //sendo vertice_inicial
    int atual = vertice_inicial;

    //vamos montar o sol baseado em dois circulos de raios diferentes,
    //centrados no mesmo ponto
    int qtd_circulo = 30;
    
    double r1 = 0.2;
    double r2 = 0.25;

    //o raio do circulo principal do sol deve estar entre o circulo r1 e r2
    double raio_principal = r1 + (r2-r1)/10;
    //cria o circulo do sol
    add_circulo(vertices, atual, qtd_circulo, 0.0, 0.0, raio_principal);
    atual += qtd_circulo;
    //a logica abaixo monta os triangulo do sol

    //armazena os pontos do triangulo
    coordenadas pontos_triangulo[qtd_circulo*2 + 1];
    float pi = 3.14;
    float angle = 0.0;
    float x, y;
    for(int i=0; i <= qtd_circulo*2; i++){
        //alterna entre um ponto do circulo menor, um ponto do circulo maior
        double radius = r1;
        if(i%2 == 1){
            radius = r2;
        }
	    angle += (2.0*pi)/(qtd_circulo*2);
	    x = cos(angle)*radius;
	    y = sin(angle)*radius;
	    pontos_triangulo[i].x = x;
	    pontos_triangulo[i].y = y;
    }

    //criando os triangulos a partir dos pontos das coordenadas triangulos
    for(int i = 0; i < qtd_circulo; i++){
        for(int j = 0; j < 3; j++){
            vertices[atual].x = pontos_triangulo[2*i + j].x;
            vertices[atual].y = pontos_triangulo[2*i + j].y;
            atual++;
        }
    }

    sol.num_vertices = atual - vertice_inicial;
    
    return sol;
   
}

/*
Esta funcao envia a matriz referente ao objeto para a GPU alem de definir a cor
a ser utilizada. Apois isso invoca os metodos para desenhar este objeto. Esta funcao
pode desenhar um sol referenciado por OBJ sol. Vale dizer que pode ser desenhado
um objeto tanto como colorido, cinza e preto.
@PARAMETROS
    OBJ sol - variavel que guarda informacoes referente ao objeto, gerada quando o objeto eh criado
    GLint loc_color - variavel linkada a variavel de cor na GPU
    GLint loc_matriz - variavel linkada a variavel de matriz na GPU
    int cor - define se a deve ser colorido, cinza ou preto
              0 - colorido
              1 - cinza
              2 - preto
              Esta variavel esta linkada com base.h, utilizando um enum com os nomes das cores
*/
void desenha_sol(OBJ sol, GLint loc_color, GLint loc_matriz, int cor){

    //chamar a funcao para montar e enviar a matriz de transformacao para gpu
    matriz_transformacao_objeto(sol, loc_matriz);


    int atual = sol.vertice_inicial;

    //colocando a cor do sol
    colorir(loc_color, 1.0, 0.8, 0.0, cor);

    int qtd_circulo = 30;

    //desenhando o circulo principal do sol
    desenha_circulo(atual, qtd_circulo);
    atual += qtd_circulo;

    //desenhando os triangulos do sol
    desenha_triangulos(atual, qtd_circulo);

    
}