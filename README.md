# Pingu e seu Iglu
Este projeto consiste no projeto prático da disciplina de computação gráfica. Para este projeto foi desenvolvido um cenário que se inicia sem cor, mas ao colocar os objetos na posição correta através de comando no teclado, o cenário se acende.
## Comandos
### Pingu
↑ ; ↓: Escala  
→ ; ← : Translação
### Árvore
w ; a ; s ; d: Translação
### Iglu
z ; x: Escala
### Sol
c ; v: Escala
### Boneco de Neve
f ; g: Rotação
## Compilação
Para compilar o código pode ser utilizar o comando ‘make’ do Makefile
```
$ make
```
Também pode ser feito através de linha de comando
```
$ gcc base.c tree.c boneco_neve.c cenario.c iglu.c pingu.c sol.c trab.c -lglfw -lGL -lGLEW -lm
```
### Executando o programa
Para executar o programa pode ser utilizar o comando ‘make run’ do Makefile
```
$ make run
```
Também pode ser executado diretamente o arquivo compilado
## Vídeo
Um vídeo de apresentação rápida do projeto pode ser encontrado no seguinte link:
[Vídeo](https://youtu.be/nZ0lWT8bt7M)
## Membros
Luan Ícaro Pinto Arcanjo 10799230  
Rodrigo Cesar Arboleda 10416722  
Victor Graciano de Souza Correia 10431201
## Sistema testado
Ubuntu 20.04 LTS
