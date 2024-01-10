APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
MULTIPLE_FLAGS= "-Wl,--allow-multiple-definition"

all: _src clean_apps _apps

_src: \
		$(OBJ)/cad_questao.o \
		$(OBJ)/cadastro_lista.o \
		$(OBJ)/cadastro.o \
		$(OBJ)/control_list.o \
		$(OBJ)/julgar.o \
		$(OBJ)/lista_login.o \
		$(OBJ)/login.o \
		$(OBJ)/struct_list.o \
		$(OBJ)/mostrar_lista.o \
		$(OBJ)/mostrar_questao.o

clean_apps:
	rm -rf $(BIN)/*

_apps: $(BIN)/Xerife
	$(BIN)/Xerife

clean:
	rm $(OBJ)/*

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc -c $< -I $(INCLUDE) -o $@ $(GTK_FLAGS) $(MULTIPLE_FLAGS)

$(BIN)/%: $(APPS)/%.c
	gcc $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(GTK_FLAGS) $(MULTIPLE_FLAGS)


a:
	rm _luis/* -rf
	cp * _luis/ -rf