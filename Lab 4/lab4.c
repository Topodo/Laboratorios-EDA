#include <stdio.h>
#include <stdlib.h>

//Definición de estructuras
typedef struct nodo{
	int **matriz;
	int uniformidad;
	int N;
	int region;
	struct nodo *primerHijo;
	struct nodo *segundoHijo;
	struct nodo *tercerHijo;
	struct nodo *cuartoHijo;
}nodo;

//Función que crea un nodo vacío del árbol
nodo *crearNodo(int N){
	nodo *nuevo = (nodo *)malloc(sizeof(nodo));
	if(nuevo != NULL){
		nuevo -> matriz = NULL;
		nuevo -> uniformidad = 0;
		nuevo -> N = N;
		nuevo -> region = 0;
		nuevo -> primerHijo = NULL;
		nuevo -> segundoHijo = NULL;
		nuevo -> tercerHijo = NULL;
		nuevo -> cuartoHijo = NULL;
		return nuevo;
	}
	else{
		printf("Error al asignar memoria para el nodo.\n");
		return NULL;
	}
}

//Función que crea una matriz de enteros
int **crearMatriz(int N){
	int i;
	int **matriz = (int **)malloc(N * sizeof(int *));
	for(i = 0; i < N; i++){
		matriz[i] = (int *)malloc(N * sizeof(int));
	}
	return matriz;
}

//Función que verifica el criterio de uniformidad
int verificarCriterio(int **matriz, int N){
	int i, j, menor, mayor;
	menor = matriz[0][0];
	mayor = matriz[0][0];
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){

			if(menor > matriz[i][j]){
				menor = matriz[i][j];
			}
			if(mayor < matriz[i][j]){
				mayor = matriz[i][j];
			}

		}
	}
	printf("El menor es: %d y el mayor: %d\n", menor, mayor);
	if(mayor - menor > 10){
		return 0;
	}
	else{
		return 1;
	}
}	

void mostrar(int **matriz, int N){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

//Función que realiza el procedimiento
void procedimiento(FILE *archivo){
	//Variables utilizadas en la función
	nodo *quadtree;
	int N, i, j;
	int **matriz;

	//Se procede a leer el archivo
	fscanf(archivo, "%d", &N);
	matriz = crearMatriz(N);
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			fscanf(archivo, "%d ", &matriz[i][j]);
		}
	}
	quadtree = crearNodo(N);
	quadtree -> matriz = matriz;
	mostrar(quadtree -> matriz, N);
	i = verificarCriterio(quadtree -> matriz, N);
}



int main(){
	FILE *archivo = fopen("Entrada.in", "r");
	procedimiento(archivo);
	return 0;
}