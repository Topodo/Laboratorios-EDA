#include "Lab3.h"
#include <time.h>

int main(){
	char nombre[20];
	printf("\nIngrese el nombre del archivo. Procure incluir la extension de este.\n");
	scanf("%s",nombre);
	time_t inicio, fin;
	time(&inicio);
	FILE *archivo = fopen(nombre, "r");
	grafo *lista = crearListaAdyacencia(archivo);
	int i, j;
	int **aux = (int **)malloc(sizeof(int*) * lista -> cantidadNodos);
	for(i = 0; i < lista -> cantidadNodos; i++){
		aux[i] = (int *)malloc(sizeof(int) * 2);
		for(j = 0; j < 2; j++){
			aux[i][j] = lista -> grados[i][j];
		}
	}
	printf("\n");
	aux = ordenarPorGrado(aux, lista -> cantidadNodos);
	mostrar(aux, lista);
	time(&fin);
	printf("El algoritmo demoro un total de %f segundos en ejecutarse.\n\n", (double)difftime(fin, inicio));


	return 0;
}