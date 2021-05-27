#ifndef CENARIO
#define CENARIO

#include "base.h"

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
OBJ cria_cenario(coordenadas*vertices,int vertice_inicial);

/*
Esta funcao envia a matriz referente ao objeto para a GPU alem de definir a cor
a ser utilizada. Apois isso invoca os metodos para desenhar este objeto. Esta funcao
pode desenhar um cenario referenciado por OBJ cenario. Vale dizer que pode ser desenhado
um objeto tanto como colorido, cinza e preto.
@PARAMETROS
    OBJ cenario - variavel que guarda informacoes referente ao objeto, gerada quando o objeto eh criado
    GLint loc_color - variavel linkada a variavel de cor na GPU
    GLint loc_matriz - variavel linkada a variavel de matriz na GPU
    int cor - define se a deve ser colorido, cinza ou preto
              0 - colorido
              1 - cinza
              2 - preto
              Esta variavel esta linkada com base.h, utilizando um enum com os nomes das cores
*/
void desenha_cenario(OBJ cenario, GLint loc_color, GLint loc_matriz, int cor);

#endif