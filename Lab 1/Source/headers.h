#ifndef LAB_1
#define LAB_1
//Se incluen las librerías utilizadas
#include <stdio.h>
#include <stdlib.h>
//Cabeceras de las funciones
int ***initMatrix(int N, int M);
int ***readImage(FILE *archivo, int *filas, int *cols);
int comparacion(int ***imagenPrincipal, int filas_main, int cols_main, int ***subImagen, int filas_sub, int cols_sub);
int ***rotar(int *** matriz, int N, int M);
void procedimiento(FILE *imagenPrincipal, FILE *subImagen);
#endif