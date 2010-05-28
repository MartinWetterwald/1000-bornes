CC = cc
LD = ld
NOM = 1000_bornes
PATH_BIN = ../build/bin/
PATH_OBJ = ../build/obj/

all: $(NOM)

$(NOM): $(PATH_OBJ)main.o $(PATH_OBJ)ia.o $(PATH_OBJ)jeu.o $(PATH_OBJ)joueur.o $(PATH_OBJ)fichiers.o $(PATH_OBJ)menu.o $(PATH_OBJ)cartes.o $(PATH_OBJ)liste.o $(PATH_OBJ)divers.o

$(PATH_OBJ)%.o: %.c
	$(CC) $(CFLAGS) -o $(PATH_BIN)$(NOM) -c $<
