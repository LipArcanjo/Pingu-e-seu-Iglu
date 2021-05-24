all:
	gcc base.c tree.c boneco_neve.c cenario.c iglu.c pingu.c sol.c trab.c -o oi -lglfw -lGL -lGLEW -lm 
run:
	./oi