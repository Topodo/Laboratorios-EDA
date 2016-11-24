#ifndef LAB_3
#define LAB_3
//Se incluen las librerías utilizadas
#include <stdio.h>
#include <stdlib.h>
typedef struct grafo{
	int **verticesAdyacentes;
	int **grados;
	int cantidadNodos;
}grafo;

typedef struct pila{
	int *arreglo;
	int fin;
}pila;
//Cabeceras de las funciones
grafo *crearNodo(grafo *nodo, int cantidad);
grafo *crearListaAdyacencia(FILE *archivo);
pila *crearPila();
pila *push(pila *actual, int elemento);
pila *pop(pila *actual);
int buscar(pila *actual, int elemento);
int **visitarVertice(pila *Pila, int **marcados, grafo *actual, int vertice);
int busquedaProfundidad(grafo *actual);
int **ordenarPorGrado(int **grados, int cantidadNodos);
void mostrar(int **ordenadoPorGrado, grafo *lista);
#endif