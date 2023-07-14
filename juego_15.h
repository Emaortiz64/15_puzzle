#ifndef JUEGO_15_H
#define JUEGO_15_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>



void definir_matriz(int matr[4][4]);
void imprimir_matriz(int matr[4][4]);
void movimiento_teclas(int caracter, int matr[4][4]);
void jugar_partida(int matr[4][4], int caracter, char resp);

void comprobar_win(int matr[4][4], char resp, char caracter);






#endif 