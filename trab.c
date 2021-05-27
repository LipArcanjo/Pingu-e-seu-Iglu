/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc ex1.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc ex1.c -lglfw3dll -lglew32 -lopengl32 */


#include "base.h"

#include "boneco_neve.h"
#include "sol.h"
#include "cenario.h"
#include "pingu.h"
#include "iglu.h"
#include "tree.h"


/*
declaracao dos nossos objetos em cena,
sao declarados globalmente para poder mudar seus parametros
da matriz de tranformacao na funcao do teclado.
*/
OBJ cenario;
OBJ boneco_neve;
OBJ boneco_neve_cinza;
OBJ sol;
OBJ sol_cinza;
OBJ pingu;
OBJ pingu_cinza;
OBJ tree;
OBJ tree_cinza;
OBJ iglu;
OBJ iglu_cinza;

/*
funcao de captacao da entrada do teclado
*/
static void keyboard_event(GLFWwindow* window, int button, int scancode, int action, int mods){
    /*
    vendo se o sol ja esta no mesmo lugar que o sol_cinza, eh proibido mexer os objetos
    depois de estarem em suas respectivas posicoes
    */
    if( compara_objetos(sol, sol_cinza) == 0 ){
        if(button == 67 && action == GLFW_PRESS){
            /*botao c - abaixa a escala do sol*/
            sol.s -= 0.05;
        }else if( button == 86 && action == GLFW_PRESS ){
            /*botao v - aumenta a escala do iglu*/
            sol.s += 0.05;
        }
    }   

    /*
    vendo se o iglu ja esta no mesmo lugar que o iglu_cinza, eh proibido mexer os objetos
    depois de estarem em suas respectivas posicoes
    */
    if( compara_objetos(iglu, iglu_cinza) == 0){
        if(button == 90 && action == GLFW_PRESS){
            /*botao z - abaixa a escala do iglu*/
            iglu.s -= 0.05;
        }else if( button == 88 && action == GLFW_PRESS ){
            /*botao x - aumenta a escala do iglu*/
            iglu.s += 0.05;
        }
    }

    /*
    vendo se o boneco_neve ja esta no mesmo lugar que o boneco_neve_cinza, eh proibido mexer os objetos
    depois de estarem em suas respectivas posicoes
    */
    if( compara_objetos(boneco_neve, boneco_neve_cinza) == 0){
        if(button == 71 && action == GLFW_PRESS){
            /*botao f - rotaciona o boneco em sentido horario*/
            boneco_neve.theta += 0.05;
            if(boneco_neve.theta >= 2*M_PI){
                boneco_neve.theta = 0;
            }
        }else if( button == 70 && action == GLFW_PRESS ){
            /*botao f - rotaciona o boneco em sentido ant-horario*/
            boneco_neve.theta -= 0.05;
        }
    }

    /*
    vendo se o pingu ja esta no mesmo lugar que o pingu_cinza, eh proibido mexer os objetos
    depois de estarem em suas respectivas posicoes
    */
    if( compara_objetos(pingu, pingu_cinza) == 0){
        if(button == 262 && action == GLFW_PRESS){
            /*botao seta direcional direita → - translada o pingu para direta*/
            pingu.tx += 0.05;
        }else if( button == 263 && action == GLFW_PRESS ){
            /*botao seta direcional esquerda ← - translada o pingu para esquerda*/
            pingu.tx -= 0.05;
        }else if(button == 264 && action == GLFW_PRESS){
            /*botao seta direcional baixo ↓ - abaixa a escala do pingu*/
            pingu.s -= 0.05;
        }else if(button == 265 && action == GLFW_PRESS){
            /*botao seta direcional cima ↑ - aumenta a escala do pingu*/
            pingu.s += 0.05;
        }
    }
    
    /*
    vendo se o tree ja esta no mesmo lugar que o tree_cinza, eh proibido mexer os objetos
    depois de estarem em suas respectivas posicoes
    */
    if( compara_objetos(tree, tree_cinza) == 0){
        if(button == 65 && action == GLFW_PRESS){
            /*botao a - translada a arvore para esquerda*/
            tree.tx -= 0.05;
        }else if( button == 68 && action == GLFW_PRESS ){
            /*botao d - translada a arvore para direita*/
            tree.tx += 0.05;
        }else if(button == 83 && action == GLFW_PRESS){
            /*botao s - translada a arvore para baixo*/
            tree.ty -= 0.05;
        }else if(button == 87 && action == GLFW_PRESS){
            /*botao w - translada a arvore para cima*/
            tree.ty += 0.05;
        }
    }
    

        
}

int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

    // GLSL para Vertex Shader
    char* vertex_code =
    "attribute vec3 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation * vec4(position, 1.0);\n"
    "}\n";

    // GLSL para Fragment Shader
    char* fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n"; 

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, (const GLchar *const *)&vertex_code, NULL);
    glShaderSource(fragment, 1,(const GLchar *const *) &fragment_code, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",info);

    }

    

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",info);

    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);
 

    // Preparando dados para enviar a GPU
    coordenadas vertices[2000];
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //variavel que guarda a primeira posicao livre do nosso vetor de coordenadas
    int atual = 0;

    /*chamando as funcoes de criar os objetos e atualizando atual*/

    cenario = cria_cenario(vertices, 0);
    atual = cenario.num_vertices;

    boneco_neve = cria_boneco_neve(vertices, atual);
    atual += boneco_neve.num_vertices;

    boneco_neve_cinza = cria_boneco_neve(vertices, atual);
    atual += boneco_neve_cinza.num_vertices;

    sol = cria_sol(vertices, atual);
    atual += sol.num_vertices;

    sol_cinza = cria_sol(vertices, atual);
    atual += sol_cinza.num_vertices;

    pingu = cria_pingu(vertices, atual);
    atual += pingu.num_vertices;

    pingu_cinza = cria_pingu(vertices, atual);
    atual += pingu_cinza.num_vertices;

    iglu = cria_iglu(vertices, atual);
    atual += iglu.num_vertices;

    iglu_cinza = cria_iglu(vertices, atual);
    atual += iglu_cinza.num_vertices;

    tree = cria_tree(vertices, atual);
    atual += tree.num_vertices;

    tree_cinza = cria_tree(vertices, atual);
    atual += tree_cinza.num_vertices;
    

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    

    GLint loc_color = glGetUniformLocation(program, "color");
    GLint loc_matriz = glGetUniformLocation(program, "mat_transformation");

    //posicionando os objetos cinzas
    posiciona_objeto(&boneco_neve_cinza, 0.5, -0.5, 0.9, 0);
    posiciona_objeto(&sol_cinza, -0.6, 0.7, 0.7, 0);
    posiciona_objeto(&iglu_cinza, -0.4, 0, 0.7, 0);
    posiciona_objeto(&pingu_cinza, -0.5, -0.5, 0.7, 0);
    posiciona_objeto(&tree_cinza, 0.6, 0.25, 0.5,0);

    //posiciona objetos coloridos _cinzanas suas posicoes iniciais
    posiciona_objeto(&boneco_neve, 0.5, -0.5, 0.9, 2);
    posiciona_objeto(&sol, -0.6, 0.7, 0.2, 0);
    posiciona_objeto(&iglu, -0.4, 0, 0.3, 0);
    posiciona_objeto(&pingu, 0.8, -0.5, 0.4, 0);
    posiciona_objeto(&tree, 0.1, -0.25, 0.5,0);

    // Exibindo nossa janela
    glfwShowWindow(window);
    double angulo = 0;

    glfwSetKeyCallback(window, keyboard_event); // teclado

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        //cenario eh inicialmente apagado
        int COR_CENARIO = PRETO;

        //verificando se todos os objetos estao em suas respectivas posicoes
        int pinta_cenario = 1;
        pinta_cenario &= compara_objetos(iglu, iglu_cinza);
        pinta_cenario &= compara_objetos(sol, sol_cinza);
        pinta_cenario &= compara_objetos(boneco_neve, boneco_neve_cinza);
        pinta_cenario &= compara_objetos(pingu, pingu_cinza);
        pinta_cenario &= compara_objetos(tree, tree_cinza);

        //se todos os objetos estao em suas respectivas posicoes, pinta o cenario
        if(pinta_cenario) COR_CENARIO = COLORIDO;

        /*desenhando o cenario*/
        desenha_cenario(cenario, loc_color, loc_matriz, COR_CENARIO);

        //deseshando objetos cinza
        desenha_boneco(boneco_neve_cinza, loc_color, loc_matriz, CINZA);
        desenha_sol(sol_cinza, loc_color, loc_matriz, CINZA);
        desenha_iglu(iglu_cinza, loc_color, loc_matriz, CINZA);
        desenha_pingu(pingu_cinza, loc_color, loc_matriz, CINZA);
        desenha_tree(tree_cinza, loc_color, loc_matriz, CINZA);

        //desenhando objetos coloridos
        desenha_boneco(boneco_neve, loc_color, loc_matriz, COLORIDO);
        desenha_sol(sol, loc_color, loc_matriz, COLORIDO);
        desenha_iglu(iglu, loc_color, loc_matriz, COLORIDO);
        desenha_pingu(pingu, loc_color, loc_matriz, COLORIDO);
        desenha_tree(tree, loc_color, loc_matriz, COLORIDO);

        glfwSwapBuffers(window);
        
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
