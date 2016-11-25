#ifndef LAB_4
#define LAB_4
#include <stdio.h>
#include <stdlib.h>
typedef struct nodo{
	int **matriz;
	int ***matrizPos;
	int N;
	int esPadre;
	int mayor;
	int menor;
	int fusionado;
	struct nodo *hermanoDerecho;
	struct nodo *primerHijo;
	struct nodo *segundoHijo;
	struct nodo *tercerHijo;
	struct nodo *cuartoHijo;
}nodo;
nodo *crearNodo(int N);
void liberarMatriz(int **matriz, int N);
void liberarMatrizPos(int ***matriz, int N);
void liberar(nodo *actual);
int **crearMatriz(int N);
int ***crearMatrizPos(int N);
int verificarCriterio(int **matriz, int N, int *Mayor, int *Menor);
nodo *particionar(nodo *actual);
nodo* preOrden(nodo *raiz);
int **llenarPreOrden(nodo *raiz, int **matriz, int region);
void fusionar(nodo *quadtree);
void procedimiento(FILE *archivo);
#endif