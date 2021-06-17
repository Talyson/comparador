CC = gcc
comparador: comparador.c funcoes.c funcoes.h
	$(CC) -o comparador comparador.c funcoes.c
