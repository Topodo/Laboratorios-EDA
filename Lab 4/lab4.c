#include <stdio.h>
#include <stdlib.h>

//Definición de estructuras
typedef struct nodo{
	int **matriz;
	int N;
	int region;
	int uniformidad;
	int nivel;
	int esPadre;
	int idPadre;
	int mayor;
	int menor;
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
		nuevo -> uniformidad = 0;
		nuevo -> nivel = 0;
		nuevo -> esPadre = 0;
		nuevo -> idPadre = -1;
		nuevo -> mayor = 0;
		nuevo -> menor = 0;
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
	int i, j;
	int **matriz = (int **)malloc(N * sizeof(int *));
	for(i = 0; i < N; i++){
		matriz[i] = (int *)malloc(N * sizeof(int));
		for(j = 0; j < N; j++){
			matriz[i][j] = 0;
		}
	}
	return matriz;
}


//Función que verifica el criterio de uniformidad
int verificarCriterio(int **matriz, int N, int *uniformidad, int *Mayor, int *Menor){
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
	*uniformidad = mayor - menor;
	*Mayor = mayor;
	*Menor = menor;
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
	int **primeraMatriz = crearMatriz(actual -> N / 2);
	int **segundaMatriz = crearMatriz(actual -> N / 2);
	int  **terceraMatriz = crearMatriz(actual -> N / 2);
	int **cuartaMatriz = crearMatriz(actual -> N / 2);

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
		//Se asignan los nodos hijos y sus respectivas regiones
		actual -> primerHijo = primerHijo;
		actual -> segundoHijo = segundoHijo;
		actual -> tercerHijo = tercerHijo;
		actual -> cuartoHijo = cuartoHijo;
		actual -> primerHijo -> region = actual -> region * 10 + 1;
		actual -> segundoHijo -> region = actual -> region * 10 + 2;
		actual -> tercerHijo -> region = actual -> region * 10 + 3;
		actual -> cuartoHijo -> region = actual -> region * 10 + 4;
	}
	return actual;
}

//Funcion de recorrido en Preorden, que va particionando los nodos y formando el quadtree en funcion del criterio de uniformidad
nodo* preOrden(nodo *raiz, int nivel, int region, int idPadre){
	raiz -> nivel = nivel;
	raiz -> idPadre = idPadre;
	raiz -> region = region;
	if(raiz != NULL && verificarCriterio(raiz -> matriz, raiz -> N, &raiz -> uniformidad, &raiz -> mayor, &raiz -> menor) == 0){
		raiz -> esPadre = 1; //Si se cumple el criterio, el nodo es padre
		raiz = particionar(raiz);
		preOrden(raiz -> primerHijo, nivel + 1, raiz -> region * 10 + 1, raiz -> region);
		preOrden(raiz -> segundoHijo, nivel + 1, raiz -> region * 10 + 2, raiz -> region);
		preOrden(raiz -> tercerHijo, nivel + 1, raiz -> region * 10 + 3, raiz -> region);
		preOrden(raiz -> cuartoHijo, nivel + 1, raiz -> region * 10 + 4, raiz -> region);
	}	
	return raiz;
}

void mostrarPreOrden(nodo *raiz){
	if(raiz != NULL){
		printf("Nivel: %d, Es padre?: %d, Region: %d, Nodo padre: %d, uniformidad: %d, Mayor: %d, Menor: %d\n", raiz -> nivel, raiz -> esPadre, raiz -> region, raiz -> idPadre, raiz -> uniformidad, raiz -> mayor, raiz -> menor);
		mostrar(raiz -> matriz, raiz -> N);
		mostrarPreOrden(raiz -> primerHijo);
		mostrarPreOrden(raiz -> segundoHijo);
		mostrarPreOrden(raiz -> tercerHijo);
		mostrarPreOrden(raiz -> cuartoHijo);
	}
}
void mostrarPostOrden(nodo *raiz){
	if(raiz != NULL){
		
		mostrarPreOrden(raiz -> primerHijo);
		mostrarPreOrden(raiz -> segundoHijo);
		mostrarPreOrden(raiz -> tercerHijo);
		mostrarPreOrden(raiz -> cuartoHijo);
		printf("Nivel: %d, Es padre?: %d, Region: %d, Nodo padre: %d, uniformidad: %d\n", raiz -> nivel, raiz -> esPadre, raiz -> region, raiz -> idPadre, raiz -> uniformidad);
		mostrar(raiz -> matriz, raiz -> N);
	}
}



//Función que funsiona las regiones del arbol correspondientes
void fusionar(nodo *quadtree){
	//Se crea la matriz que contendrá las regiones respectivas, para luego escribirlas en el archivo de texto
	int **matriz = crearMatriz(quadtree -> N);
	FILE *salida = fopen("Salida.out", "w");
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
	//mostrar(quadtree -> matriz, quadtree -> N);
	preOrden(quadtree, 0, quadtree -> region, quadtree -> idPadre);
	mostrarPostOrden(quadtree);
}



int main(){
	FILE *archivo = fopen("Entrada.in", "r");
	procedimiento(archivo);
	return 0;
}