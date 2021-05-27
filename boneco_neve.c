#include "boneco_neve.h"

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
OBJ cria_boneco_neve(coordenadas*vertices,  int vertice_inicial){
    OBJ boneco_neve;
    boneco_neve.vertice_inicial = vertice_inicial;
    //setando os valores iniciais para a matriz de transformacao do objeto
    boneco_neve.s = 0.5;
    boneco_neve.theta = 0;
    boneco_neve.tx = 0;
    boneco_neve.ty = 0;

    //raios dos circulos pretos, da borda do corpo do boneco
    double r1 = 0.12;
    double r2 = 0.09;
    double r3 = 0.06;

    //alturas do centro de cada circulo do corpo, baseado nos raios
    double altura1 = r1;
    double altura2 = altura1 + r1*0.5 + r2;
    double altura3 = altura2 + r2*0.7 + r3;
    
    //armazena qual o proximo indice do vetor de vertices livre, inicialmente
    //sendo vertice_inicial
    int atual = vertice_inicial;

    //qtd de pontos em cada circulo do ponto
    int qtd_circulo = 30;

    //criando os circulos com a funcao auxiliar
    add_circulo(vertices, atual, qtd_circulo, 0, altura1, r1);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, 0, altura2, r2);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, 0, altura3, r3);
    atual += qtd_circulo;

    
    //tamanho da borda preta do bonecod de neve
    double tam_borda = 0.01;
    
    //adicionando os circulos brancos, do corpo do boneco
    add_circulo(vertices, atual, qtd_circulo, 0, altura1, r1 - tam_borda);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, 0, altura2, r2 - tam_borda);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, 0, altura3, r3 - tam_borda);
    atual += qtd_circulo;


    //criando botoes vermelhos da camisa
    //a distancia entre o botao da camisa e o centro do segundo circulo;
    double distancia_botao = r2/3;
    //raio dos botoes da camida
    double  botao_raio = r2/10; 

    add_circulo(vertices, atual, qtd_circulo, 0, altura2 + distancia_botao, botao_raio);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, 0, altura2 - distancia_botao, botao_raio);
    atual += qtd_circulo;
    //criando os circulos dos olhos do boneco
    
    //distancia entre o olho e o centro do terceiro circulo, para cada coordenada
    double distancia_olho = r3/3;
    //raio do circulo do olho
    double olho_raio = r3/10;

    add_circulo(vertices, atual, qtd_circulo, -distancia_olho, altura3 + distancia_olho, olho_raio);
    atual += qtd_circulo;

    add_circulo(vertices, atual, qtd_circulo, distancia_olho, altura3 + distancia_olho, olho_raio);
    atual += qtd_circulo;
    //adicionando o triangulo do nariz do boneco

    //distancia do centro do terceiro circulo para os pontos do triangulo em x=0
    double dist_nariz_y = r3/5;
    //distancia do centro do terceiro ciurlo para o ponto do trinauglo em y3 = altura3;
    double dist_nariz_x = -r3*1.8;
    vertices[atual].x = 0;
    vertices[atual].y = altura3 + dist_nariz_y;
    atual++;

    vertices[atual].x = 0;
    vertices[atual].y = altura3 - dist_nariz_y;
    atual++;

    vertices[atual].x = dist_nariz_x; 
    vertices[atual].y = altura3;
    atual++;

    //adicionando o chapeu do boneco
    //altura e largura dos dois quadrados que copoem o chapeu
    double largura_chapeu[2];
    double altura_chapeu[2];

    largura_chapeu[0] = 0.12;
    largura_chapeu[1] = 0.06;

    altura_chapeu[0] = 0.02;
    altura_chapeu[1] = 0.1;
    //coordena x e y do canto inferior esquerdo de cada triangulo
    double inferior_esquerdo_x[2];
    double inferior_esquerdo_y[2];

    inferior_esquerdo_x[0] = -largura_chapeu[0]/2;
    inferior_esquerdo_x[1] = -largura_chapeu[1]/2;

    inferior_esquerdo_y[0] = altura3 + r3*0.8;
    inferior_esquerdo_y[1] = inferior_esquerdo_y[0];

    for(int i = 0; i < 2; i++){
        //adicioando os quatro pontos do quadrado, baseado nos valores acima

        vertices[atual].x = inferior_esquerdo_x[i];
        vertices[atual].y = inferior_esquerdo_y[i];
        atual++;

        vertices[atual].x = inferior_esquerdo_x[i] + largura_chapeu[i];
        vertices[atual].y = inferior_esquerdo_y[i];
        atual++;

        vertices[atual].x = inferior_esquerdo_x[i];
        vertices[atual].y = inferior_esquerdo_y[i] + altura_chapeu[i];
        atual++;

        vertices[atual].x = inferior_esquerdo_x[i] + largura_chapeu[i];
        vertices[atual].y = inferior_esquerdo_y[i] + altura_chapeu[i];
        atual++;
    }

    boneco_neve.num_vertices = atual - vertice_inicial;

    return boneco_neve;
}

/*
Esta funcao envia a matriz referente ao objeto para a GPU alem de definir a cor
a ser utilizada. Apois isso invoca os metodos para desenhar este objeto. Esta funcao
pode desenhar um boneco_neve referenciado por OBJ boneco_neve. Vale dizer que pode ser desenhado
um objeto tanto como colorido, cinza e preto.
@PARAMETROS
    OBJ boneco_neve - variavel que guarda informacoes referente ao objeto, gerada quando o objeto eh criado
    GLint loc_color - variavel linkada a variavel de cor na GPU
    GLint loc_matriz - variavel linkada a variavel de matriz na GPU
    int cor - define se a deve ser colorido, cinza ou preto
              0 - colorido
              1 - cinza
              2 - preto
              Esta variavel esta linkada com base.h, utilizando um enum com os nomes das cores
*/
void desenha_boneco(OBJ boneco_neve, GLint loc_color, GLint loc_matriz, int cor){

    //chamar a funcao para montar e enviar a matriz de transformacao para gpu
    matriz_transformacao_objeto(boneco_neve, loc_matriz);

    //qtd de pontos em cada circulo do boneco
    int qtd_circulo = 30;

    int atual = boneco_neve.vertice_inicial;

    //desenhando a borda preta e o corpo branco do circulo 1
    colorir(loc_color, 0.0, 0.0, 0.0, cor);
    desenha_circulo(atual, qtd_circulo);
    
    colorir(loc_color, 1.0, 1.0, 1.0, cor);
    desenha_circulo(atual + 3*qtd_circulo, qtd_circulo);
    atual += qtd_circulo;

    //desenhando a borda preta e o corpo branco do circulo 2
    colorir(loc_color, 0.0, 0.0, 0.0, cor);
    desenha_circulo(atual, qtd_circulo);
    
    colorir(loc_color, 1.0, 1.0, 1.0, cor);
    desenha_circulo(atual + 3*qtd_circulo, qtd_circulo);
    atual += qtd_circulo;

    //desenhando a borda preta e o corpo branco do circulo 3
    colorir(loc_color, 0.0, 0.0, 0.0, cor);
    desenha_circulo(atual, qtd_circulo);
    
    colorir(loc_color, 1.0, 1.0, 1.0, cor);
    desenha_circulo(atual + 3*qtd_circulo, qtd_circulo);
    atual += qtd_circulo;


    //pulando de atual,os tres circulos brancos, que ja desenhamos
    atual += 3*qtd_circulo;
    
    //desenhando os botoes da camisa do boneco
    colorir(loc_color, 1.0, 0.0, 0.0, cor);

    desenha_circulo(atual, qtd_circulo);
    atual += qtd_circulo;
    desenha_circulo(atual, qtd_circulo);;
    atual += qtd_circulo;

    //desenhando os olhos do boneco
    colorir(loc_color, 0.0, 0.0, 0.0, cor);

    desenha_circulo(atual, qtd_circulo);
    atual += qtd_circulo;
    desenha_circulo(atual, qtd_circulo);;
    atual += qtd_circulo;


    //desenhando o nariz do boneco
    colorir(loc_color, 1.0, 0.5, 0.0, cor);

    desenha_triangulo(atual);
    atual += 3;

    //desenhando o chapeu do python
    colorir(loc_color, 0.0, 0.0, 0.0, cor);

    desenha_quadrado(atual);
    atual += 4;
    desenha_quadrado(atual);
    atual += 4;

}