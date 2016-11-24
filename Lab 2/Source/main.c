#include "lab2.h"
#include <time.h>

int main(){
	printf("------------------ Inicio del procedimiento ------------------\n\n");
	time_t inicio, fin;
	procedimiento();
	time(&inicio);
	time(&fin);
	printf("El algoritmo demoro un total de %f segundos en ejecutarse.\n\n", (double)difftime(fin, inicio));
	printf("------------------- Fin del procedimiento --------------------\n");
	return 0;
}
int main(){
	char nombre[20];
	printf("\nIngrese el nombre del archivo. Procure incluir la extension de este.\n");
	scanf("%s",nombre);
	time_t inicio, fin;
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
	time(&inicio);
	time(&fin);
	printf("El algoritmo demoro un total de %f segundos en ejecutarse.\n\n", (double)difftime(fin, inicio));


	return 0;
}