#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "juego_15.h"




    int fila_vacia = 3, columna_vacia = 3, apuesta_movimientos = 0, movimientos_realizados = 0\
    , partidas_jugadas = 0, puntos =0;
    
    int resultados[10][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

    int matrices_posibles[20][5][4] = {
    {{0,3,0,0},{7, 3, 6, 0}, {10, 11, 9, 8}, {15, 2, 13, 4}, {14, 1, 5, 12}},
    {{2,2,0,0},{3, 6, 8, 12}, {5, 1, 10, 4}, {15, 14, 0, 7}, {2, 11, 13, 9}},
    {{1,0,0,0},{13, 3, 4, 12}, {0, 8, 10, 7}, {9, 2, 5, 6}, {11, 15, 14, 1}},
    {{3,2,0,0},{7, 11, 10, 14}, {12, 3, 8, 6}, {4, 9, 15, 2}, {13, 1, 0, 5}},
    {{1,1,0,0},{10, 2, 6, 9}, {8, 0, 12, 14}, {7, 13, 1, 3}, {5, 11, 15, 4}},
    {{3,1,0,0},{8, 3, 5, 2}, {12, 7, 10, 11}, {1, 6, 9, 13}, {4, 0, 14, 15}},
    {{1,0,0,0},{1, 3, 6, 11}, {0, 8, 2, 10}, {9, 5, 12, 13}, {4, 14, 7, 15}},
    {{1,0,0,0},{14, 8, 1, 3}, {0, 13, 7, 9}, {12, 10, 4, 6}, {5, 11, 15, 2}},
    {{2,2,0,0},{1, 5, 7, 14}, {6, 11, 9, 12}, {10, 15, 0, 8}, {3, 13, 4, 2}},
    {{2,2,0,0},{7, 4, 8, 11}, {9, 13, 12, 2}, {10, 3, 0, 14}, {6, 15, 1, 5}},
    {{3,2,0,0},{5, 2, 7, 12}, {9, 6, 10, 4}, {1, 11, 13, 15}, {14, 8, 0, 3}},
    {{2,2,0,0},{5, 6, 1, 14}, {13, 4, 10, 12}, {8, 7, 0, 11}, {3, 15, 2, 9}},
    {{1,1,0,0},{2, 4, 10, 14}, {6, 0, 8, 12}, {3, 5, 1, 15}, {13, 9, 11, 7}},
    {{1,1,0,0},{4, 2, 7, 3}, {6, 11, 0, 14}, {5, 9, 8, 1}, {10, 13, 15, 12}},
    {{3,2,0,0},{5, 9, 1, 3}, {2, 7, 10, 4}, {13, 14, 12, 15}, {11, 8, 0, 6}},
    {{2,3,0,0},{4, 1, 7, 14}, {5, 2, 8, 9}, {3, 6, 10, 0}, {12, 13, 11, 15}},
    {{0,3,0,0},{11, 6, 2, 0}, {3, 7, 9, 14}, {4, 1, 8, 15}, {5, 13, 12, 10}},
    {{1,3,0,0},{7, 6, 2, 10}, {11, 3, 8, 0}, {12, 14, 15, 1}, {5, 9, 4, 13}},
    {{2,3,0,0},{8, 5, 4, 14}, {7, 11, 6, 3}, {10, 1, 2, 0}, {13, 15, 12, 9}},
    {{1,1,0,0},{9, 3, 12, 11}, {8, 0, 14, 15}, {10, 4, 5, 1}, {13, 7, 6, 2}}
};





int main(){

        srand(time(NULL));
        int ch='x', matriz[4][4];
        char respuesta = 's';

        while(respuesta == 's' && partidas_jugadas <=10 || ch == 'Q'){
            jugar_partida(matriz, ch, respuesta);
        }

        for(int i=0;i<partidas_jugadas;i++){
            printw("\nPartida n° %d , puntos: %d", partidas_jugadas-1, resultados[partidas_jugadas-1][1]);
        }
    
    return 0;

}





//implementación de funciones:

void jugar_partida(int matr[4][4], int caracter, char resp){
    
        printf("¿En cuántos movimientos puedes resolverlo?\n");
        scanf("%d", &apuesta_movimientos);
        partidas_jugadas++;
        definir_matriz(matr);
        puntos == 0;
        apuesta_movimientos == 0;
        movimientos_realizados == 0;


        while(caracter!='q' && caracter!='Q') {

            initscr();		//comienza el modo ncurses
            raw();			//deshabilita el buffer
            noecho();		//no hace echo con los caracteres ingresados
            move(0,0);
	        system("clear");
            keypad(stdscr, TRUE);

            clear();

            imprimir_matriz(matr);
	        printw("\nMovimientos: %d\nUse las flechas o 'q' para salir:\n", movimientos_realizados);
	    
            comprobar_win(matr, resp, caracter);
        

	        caracter = getch();		
            movimiento_teclas(caracter, matr);


	        if (caracter=='q' || caracter=='Q'){
             endwin();
            }
        
	        refresh();
            endwin();		//finaliza el modo ncurses
        }
}



void movimiento_teclas(int caracter, int matr[4][4]){
    switch (caracter){        //esta sentencia se encarga del movimiento
                case KEY_UP:
                if(fila_vacia > 0){
                    matr[fila_vacia][columna_vacia] = matr[fila_vacia-1][columna_vacia];    //copia valor de la pieza a la que se mueve
                    matr[fila_vacia-1][columna_vacia] = 0;                                    //la nueva posición pasa a ser 0
                    fila_vacia -=1;                                                             //mueve la coordenada del valor 0 en la matriz
                    movimientos_realizados++;                                                   //aumenta contador de movimientos
                }
                break;
                case KEY_DOWN:
                if(fila_vacia < 3){
                    matr[fila_vacia][columna_vacia] = matr[fila_vacia+1][columna_vacia];
                    matr[fila_vacia+1][columna_vacia] = 0;
                    fila_vacia +=1;
                    movimientos_realizados++;
                }
                break;
                case KEY_RIGHT:
                if(columna_vacia < 3){
                    matr[fila_vacia][columna_vacia] = matr[fila_vacia][columna_vacia+1];
                    matr[fila_vacia][columna_vacia+1] = 0;
                    columna_vacia +=1;
                    movimientos_realizados++;
                }
                break;
                case KEY_LEFT:
                if(columna_vacia > 0){
                    matr[fila_vacia][columna_vacia] = matr[fila_vacia][columna_vacia-1];
                    matr[fila_vacia][columna_vacia-1] = 0;
                    columna_vacia -=1;
                    movimientos_realizados++;
                }
                break;
                default:
                break;
            }
}

void definir_matriz(int matr[4][4]){
        int numero = rand() % 20;

    if(matrices_posibles[numero][0][3] != 1){                   //se asegura d que la matriz elegida no tenga la marca
        for(int i=1;i<5;i++){
            for(int j=0; j<4; j++){
                matr[i-1][j] = matrices_posibles[numero][i][j];
            }
        }
        fila_vacia = matrices_posibles[numero][0][0];
        columna_vacia = matrices_posibles[numero][0][1];
        matrices_posibles[numero][0][3] = 1;                   //marca la matriz ya utilizada para que no se repitan
    } else {
        definir_matriz(matr);                                   //vuelve a ejecutarse hasta que encuentre una matriz que no haya sido usada
    }
}

void imprimir_matriz(int matr[4][4]){
    for(int i=0; i<4;i++){
            for(int j=0;j<4;j++){
                if(matr[i][j] > 0){
                printw("[%2d]", matr[i][j]);
                } else {
                    printw("[  ]");
                }
            }
            printw("\n");
        }
}




void comprobar_win(int matr[4][4], char resp, char caracter){

    //compara la matriz actual con la matriz ganadora 

    int matriz_correcta[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}, coinsidencias = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if( matr[i][j] == matriz_correcta[i][j]){
                coinsidencias++;
            }
        }
    }

    //sistema de puntuación

    if(coinsidencias >= 16){
        
        if(movimientos_realizados >= apuesta_movimientos -10 && movimientos_realizados < apuesta_movimientos){
            puntos += 1200;
        } else if (apuesta_movimientos == movimientos_realizados){
            puntos += 1000;
        } else if(apuesta_movimientos > movimientos_realizados && apuesta_movimientos <= movimientos_realizados+10){    
            puntos+=500;
        } else if(apuesta_movimientos <= movimientos_realizados-10){
            puntos+=1500;
        } else {
            puntos+=0;
        }

        resultados[partidas_jugadas-1][0] = partidas_jugadas;      //guardado de los resultados en el array
        resultados[partidas_jugadas-1][1] = puntos;
        
        for(int i=0; i<partidas_jugadas;i++){
            printw("\nPartida n° %d , puntos: %d", partidas_jugadas-1, resultados[partidas_jugadas-1][1]);
        }

        printw("\nJugar otra partida? s/n\n");
        scanw("%c", &resp);
        
        //algo que reinicie el juego
        
        jugar_partida(matr, caracter, resp);

    }
}