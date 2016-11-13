#include <stdio.h>
#include <stdlib.h>

//Definición de estructuras
typedef struct nodo{
	int **matriz;
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
	if(mayor - menor > 2){
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

//Función que particiona un nodo del árbol en 4 partes
nodo *particionar(nodo *actual){
	nodo *primerHijo = crearNodo(actual -> N / 2);
	nodo *segundoHijo = crearNodo(actual -> N / 2);
	nodo *tercerHijo = crearNodo(actual -> N / 2); 
	nodo *cuartoHijo = crearNodo(actual -> N / 2);
	int i, j;
	//Se asigna memoria para las submatrices
	int **primeraMatriz = (int **)malloc(sizeof(int *) * actual -> N / 2);
	int **segundaMatriz = (int **)malloc(sizeof(int *) * actual -> N / 2);
	int  **terceraMatriz = (int **)malloc(sizeof(int *) * actual -> N / 2);
	int **cuartaMatriz = (int **)malloc(sizeof(int *) * actual -> N / 2);
	for(i = 0; i < actual -> N / 2; i++){
		primeraMatriz[i] = (int *)malloc(sizeof(int) * actual -> N / 2);
		segundaMatriz[i] = (int *)malloc(sizeof(int) * actual -> N / 2);
	 	terceraMatriz[i] = (int *)malloc(sizeof(int) * actual -> N / 2); 
	 	cuartaMatriz[i] = (int *)malloc(sizeof(int) * actual -> N / 2);
	}
	//Se realiza el proceso de partición de la matriz del nodo
	for(i = 0; i < actual -> N / 2; i++){
		for(j = 0; j < actual -> N / 2; j++){
			primeraMatriz[i][j] = actual -> matriz[i][j];
		}	
	}
	for(i = 0; i < actual -> N / 2; i++){
		for(j = actual -> N / 2; j < actual -> N; j++){
			segundaMatriz[i][j - actual -> N / 2] = actual -> matriz[i][j];
		}
	}
	for(i = actual -> N / 2; i < actual -> N; i++){
		for(j = 0; j < actual -> N / 2; j++){
			terceraMatriz[i - actual -> N / 2][j] = actual -> matriz[i][j];
		}
	}
	for(i = actual -> N / 2; i < actual -> N; i++){
		for(j = actual -> N / 2; j < actual -> N; j++){
			cuartaMatriz[i - actual -> N / 2][j - actual -> N / 2] = actual -> matriz[i][j];
		}
	}
	//Se asignan las submatrices a cada hijo del nodo
	primerHijo -> matriz = primeraMatriz;
	segundoHijo -> matriz = segundaMatriz;
	tercerHijo -> matriz = terceraMatriz;
	cuartoHijo -> matriz = cuartaMatriz;

	if(primerHijo != NULL && segundoHijo != NULL && tercerHijo != NULL && cuartoHijo != NULL){
		actual -> primerHijo = primerHijo;
		actual -> segundoHijo = segundoHijo;
		actual -> tercerHijo = tercerHijo;
		actual -> cuartoHijo = cuartoHijo;
	}
	return actual;
}

nodo* preOrden(nodo *raiz){
	if(raiz != NULL && verificarCriterio(raiz -> matriz, raiz -> N) == 0){
		raiz = particionar(raiz);
		preOrden(raiz -> primerHijo);
		preOrden(raiz -> segundoHijo);
		preOrden(raiz -> tercerHijo);
		preOrden(raiz -> cuartoHijo);
	}
	return raiz;
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
	mostrar(quadtree -> matriz, quadtree -> N);
	preOrden(quadtree);
}



int main(){
	FILE *archivo = fopen("Entrada.in", "r");
	procedimiento(archivo);
	return 0;
}