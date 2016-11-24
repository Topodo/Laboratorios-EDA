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

//Funcion que inicializa la estructura nodo
grafo *crearNodo(grafo *nodo, int cantidad){
	int i;
	nodo -> verticesAdyacentes = (int **)malloc(sizeof(int *) * cantidad);
	nodo -> grados = (int **)malloc(sizeof(int) * cantidad);
	for (int i = 0; i < cantidad; ++i){
		nodo -> verticesAdyacentes[i] = (int *)malloc(sizeof(int));
		nodo -> grados[i] = (int *)malloc(sizeof(int) * 2);
	}
	nodo -> cantidadNodos = cantidad;
	return nodo;
}

//Funcion que crea una lista de adyacencia del grafo
grafo *crearListaAdyacencia(FILE *archivo){
	int i, k, N, cont, vertice;
	cont = 1;
	int *arregloAux;
	char espacio;
	fscanf(archivo, "%d", &N);
	espacio = fgetc(archivo);
	//Se crea una arreglo, donde cada elemento contendrá un arreglo con todos los vertices adyacentes al primero
	grafo *listaAdyacente = (grafo *)malloc(sizeof(grafo));
	listaAdyacente = crearNodo(listaAdyacente, N);
	
	//Se agregan los vertices al arreglo
	for(i=0; i<N; i++){
		arregloAux = (int *)malloc(sizeof(int));
		fscanf(archivo,"%d", &vertice);
		arregloAux[0] = vertice;
		espacio = fgetc(archivo); //Lee el espacio que separa los vertices
		while(espacio == ' ' && espacio != EOF && espacio != '\n'){
			//Se reasigna la memoria de cada arreglo
			arregloAux = (int *)realloc(arregloAux, sizeof(int) * (cont + 1));
			//Se lee el vertice y se almacena en el arreglo
			fscanf(archivo,"%d",&vertice);
			arregloAux[cont] = vertice;
			espacio = fgetc(archivo);
			cont ++;
		}
		//Se agrega la cantidad de vertices adyacentes al arreglo con los grados de cada vertice
		listaAdyacente -> grados[i][0] = cont - 1;
		listaAdyacente -> grados[i][1] = i + 1;
		//Se agrega el arreglo a la lista de adyacencia
		listaAdyacente -> verticesAdyacentes[i] = arregloAux;
		cont = 1;
	}
	return listaAdyacente;
}

//Operaciones del TDA Pila
pila *crearPila(){
	pila *nueva;
	nueva -> arreglo = NULL;
	nueva -> fin = 0;
	return nueva;
}

//Se inserta un elemento al inicio de la pila
pila *push(pila *actual, int elemento){
	int i;
	if(actual -> fin == 0){
		actual -> arreglo = (int *)malloc(sizeof(int));
		actual -> arreglo[0] = elemento;
	}
	else{
		//Se reasigna memoria
		actual -> arreglo = (int *)realloc(actual -> arreglo, sizeof(int) * actual -> fin + 1);
		for(i = actual -> fin; i > 0; i--){
			actual -> arreglo[i] = actual -> arreglo[i - 1];
		}
		actual -> arreglo[0] = elemento;
	}
	actual -> fin ++;
	return actual;
}

//Se elimina el primer elemento de la pila
pila *pop(pila *actual){
	int i;
	if(actual -> fin == 0){
		return actual;
	}
	for(i = 0; i < actual -> fin - 1; i++){
		actual -> arreglo[i] = actual -> arreglo[i + 1];
	}
	//Se reduce el largo del arreglo en una unidad
	actual -> arreglo = (int *)realloc(actual -> arreglo, sizeof(int) * (actual -> fin - 1));
	actual -> fin--;
	return actual;
}
//Funcion que busca si un elemento esta en una pila
int buscar(pila *actual, int elemento){
	int i;
	for(i = 0; i < actual -> fin; i++){
		if(actual -> arreglo[i] == elemento){
			return 1;
		}
	}
	return 0;
}

//Funcion que se encarga de marcar los vertices que son visitados en la busqueda en profundidad
int **visitarVertice(pila *Pila, int **marcados, grafo *actual, int vertice){
	marcados[vertice - 1][1] = 1;
	Pila = push(Pila, vertice);
	int adyacente;
	int i;
	for(i = 0; i < actual -> grados[vertice - 1][0]; i++){
		adyacente = actual -> verticesAdyacentes[vertice - 1][i + 1];
		if(marcados[adyacente - 1][1] == 0){
			marcados[adyacente - 1][1] = 1;
			marcados = visitarVertice(Pila, marcados, actual, adyacente);
		}
		else{
			if(buscar(Pila, adyacente) == 1 && marcados[adyacente - 1][1] != 1){
				marcados[adyacente - 1][1] == 2;
			}
		}
	}

	return marcados;
}

int busquedaProfundidad(grafo *actual){
	//Se crea un arreglo bidimensional con los vertices desmarcados
	int **marcados = (int **)malloc(sizeof(int *) * actual -> cantidadNodos);
	int i;
	for(i = 0; i < actual -> cantidadNodos; i++){
		marcados[i] = (int *)malloc(sizeof(int) * 2);
		marcados[i][0] = i + 1; 
		marcados[i][1] = 0;
	}
	int raiz = actual -> verticesAdyacentes[0][0];

	pila *vertices = crearPila();
	marcados = visitarVertice(vertices, marcados, actual, raiz);

	for(i = 0; i < actual -> cantidadNodos; i++){
		if(marcados[i][1] == 0){
			return 0;
		}
	}
	return 1;
}

//Implementacion del algoritmo de ordenamiento por burbuja, que ordena una matriz de Nx2, segun el grado de cada vertice
int **ordenarPorGrado(int **grados, int cantidadNodos){
	int i, j, gradoAux, verticeAux;

	for(i = 0; i < cantidadNodos - 2; i++){
		for(j = cantidadNodos - 1; j > i; j--){
			if(grados[j][0] > grados[j - 1][0]){
				gradoAux = grados[j][0];
				verticeAux = grados[j][1];
			 	grados[j][0] = grados[j - 1][0];
			    grados[j][1] = grados[j - 1][1];
			    grados[j - 1][0] = gradoAux;
			    grados[j - 1][1] = verticeAux;
			}
		}
	}
	
	return grados;
}


//Funcion que muestra los resultados
void mostrar(int **ordenadoPorGrado, grafo *lista){
	int i;
	if(busquedaProfundidad(lista) == 1){
		printf("El grafo es conexo.\n");
	}
	else{
		printf("El grafo no es conexo.\n");
	}
	printf("Vertices ordenados de mayor a menor, segun centralidad de grado:\n");
	for(i = 0; i < lista -> cantidadNodos; i++){
		printf("Vertice %d, grado %d\n", ordenadoPorGrado[i][1], ordenadoPorGrado[i][0]);
	}
	printf("\n");
}

