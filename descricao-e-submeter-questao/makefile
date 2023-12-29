nome = descricao-e-submeter-questoes
flags = `pkg-config --cflags --libs gtk+-3.0` 

all:
	gcc $(nome).c julgar.c -o $(nome) $(flags)
	./$(nome)
