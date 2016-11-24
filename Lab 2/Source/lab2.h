#ifndef LAB_2
#define LAB_2
//Se incluen las librerías utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct lista{
	char letra;
	int posicion;
	int largo;
	struct lista *anterior;
	struct lista *siguiente;
}lista;
//Cabeceras de las funciones
int verificarLetra(char letra);
int buscarPivote(char *arreglo, int i, int j);
int particionar(char *arreglo, int i, int j, int pivote);
char *quicksort(char *arreglo, int i, int j);
lista *crearNodo();
lista *agregar(lista *actual, char letra, int posicion, int largo);
lista *borrar(lista *actual, int posicion);
int buscarPorLetra(lista *actual, char letra);
char buscarPorPosicion(lista *actual, int posicion);
lista *desplazarIzquierdaTresEspacios(lista *actual, int *desfase);
lista *desplazarIzquierdaUnEspacio(lista *actual, int *desfase);
lista *desplazarDerechaUnEspacio(lista *actual, int *desfase);
lista *desplazarDerechaTresEspacios(lista *actual, int *desfase);
void cifrar(lista *letras, lista *codificacion, char *palabra, int largoPalabra);
void descifrar(lista *letras, lista *codificacion, char *palabra, int largoPalabra, int desfase);
void procedimiento();
#endif