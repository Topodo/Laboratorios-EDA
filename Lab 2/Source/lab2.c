#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definición de estructuras para las listas Letras y Codificacion

typedef struct lista{
	char letra;
	int posicion;
	int largo;
	struct lista *anterior;
	struct lista *siguiente;
}lista;

char *saltoLinea = "\n";

//Abecedario separado por vocales y consonates
char *vocales = "AEIOUaeiou ";
char *consonates = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

void mostrar(lista *actual);

//Funcion para verificar si una letra es vocal o consonante de tipo booleano
//si la funcion es 0, es vocal, si es 1 es consonante
int verificarLetra(char letra){
	int i;
	for(i=0; i<(int)strlen(vocales); i++){
		if(letra == vocales[i]){
			return 0;
		}
	}
	for(i=0; i<(int)strlen(consonates); i++){
		if(letra == consonates[i]){
			return 1;
		}
	}
	//Si no es una letra, retorna -1
	return -1;
}

//Funciones pertenecientes al método de ordenamiento 'Quicksort'
int buscarPivote(char *arreglo, int i, int j) {
	int primerValor, k;
	primerValor = arreglo[i];
	for(k = i + 1; k <= j; k++) {
		if(arreglo[k] > primerValor) {
		 	return k;
		}
		if(arreglo[k] < primerValor) {
			return i;
		}
	}
	return -1;
}
int particionar(char *arreglo, int i, int j, int pivote){
	int izquierda, derecha, auxiliar;
	izquierda = i;
	derecha = j;
	do {
		auxiliar = arreglo[izquierda];
		arreglo[izquierda] = arreglo[derecha];
		arreglo[derecha] = auxiliar;
		while(arreglo[izquierda] < pivote) {
			izquierda++;
		}
		while(arreglo[derecha] >= pivote) {
			derecha--;
		}
	} while(izquierda <= derecha);
	
	return izquierda;
}
char *quicksort(char *arreglo, int i, int j) {
	int indicePivote, pivote, k;
	indicePivote = buscarPivote(arreglo, i, j);
	if(indicePivote != -1) {
		pivote = arreglo[indicePivote];
		k = particionar(arreglo, i, j, pivote);
		arreglo = quicksort(arreglo, i, k - 1);
		arreglo = quicksort(arreglo, k, j);
	}
	return arreglo;
} 

//Funciones del TDA Lista

lista *crearNodo(){
	//Se crea un nodo e inicializan sus variables
	lista *nodo = (lista *)malloc(sizeof(lista));
	if(nodo != NULL){
		nodo -> letra = ' ';
		nodo -> posicion = 0;
		nodo -> largo = 0;
		nodo -> anterior = NULL;
		nodo -> siguiente = NULL;
		return nodo;
	}
	else return NULL;
}

//Funcion que agrega un nuevo nodo al final de la lista
lista *agregar(lista *actual, char letra, int posicion, int largo){
	//Se crean dos nodos, uno que será el nodo a agregar y el otro que sera una lista auxiliar 
	//para recorrer la lista original sin perder referencia de los nodos de esta
	lista *nuevo, *nodoAux;
	nuevo = crearNodo();
	nodoAux = crearNodo();

	if(nuevo != NULL){
		//Caso de que la lista sea vacía (primer nodo)
		if(actual == NULL){
			actual = nuevo;
			nuevo -> letra = letra;
			nuevo -> posicion = posicion;
			nuevo -> largo = largo;
			nuevo -> anterior = NULL;
			nuevo -> siguiente = NULL;
			return actual;
		}
		//Caso en que la lista no este vacia y se vaya a agregar un nuevo nodo al final
		else{
			nuevo -> letra = letra;
			nuevo -> posicion = posicion;
			nuevo -> largo = largo;
			nuevo -> siguiente = NULL;
			nodoAux = actual;
			while(nodoAux->siguiente != NULL){
				nodoAux = nodoAux->siguiente;
			}
			nuevo -> anterior = nodoAux;
			nodoAux -> siguiente = nuevo;
			return actual;
		}
	}
	else{
        printf("Error en la asignacion de memoria\n");
        return actual;
    }
}

//Funcion que borra un nodo de una lista, si es que la letra de este nodo ya se encuentra en un nodo anterior
lista *borrar(lista *actual, int posicion){
	
	lista *indice = actual;
	lista *nodoAux = NULL;
	int i;

	for(i=0; i<posicion - 1; i++){
		indice = indice -> siguiente;
	}

	nodoAux = indice -> siguiente;
	indice -> siguiente = nodoAux -> siguiente;
	indice -> siguiente -> anterior = indice;
	free(nodoAux);
	nodoAux = NULL;

	//Se modifica la variable posicion para los elementos posteriores 
	indice = indice -> siguiente;
	for(i=posicion; i<actual->largo; i++){
		if(i == indice -> posicion){
			indice -> posicion = i - 1;
			indice = indice -> siguiente;
		}
	}

	actual -> largo--;
	return actual;

}

//Funcion que retorna la posicion del nodo que contiene la letra buscada
int buscarPorLetra(lista *actual, char letra){
	//Nodo auxiliar para recorrer la lista
	lista *nodoAux = actual;
	int i;

	for(i=0;i<actual->largo;i++){
		if(nodoAux -> letra == letra){
			return i;
		}
		nodoAux = nodoAux -> siguiente;
	}
	return i;
}

//Funcion que retorna el nodo con la posicion buscada
char buscarPorPosicion(lista *actual, int posicion){
	//Nodo auxiliar para recorrer la lista
	lista *nodoAux = actual;
	int i;

	for(i=0;i<posicion;i++){
		nodoAux = nodoAux -> siguiente;
	}
	return nodoAux -> letra;
}

//Funcion que desplaza una lista 3 espacios hacia la izquierda
lista *desplazarIzquierdaTresEspacios(lista *actual, int *desfase){
	//Variables utilizadas en la funcion
	lista *aux = actual;
	lista *desplazada = NULL;
	lista *nuevo = NULL;
	lista *nuevoAux = NULL;
	int i;
	
	for(i=0;i<actual->largo;i++){
		desplazada = aux -> siguiente -> siguiente -> siguiente;
		nuevo = agregar(nuevo, desplazada -> letra, aux -> posicion, actual -> largo);
		aux = aux -> siguiente;
	}
	
	nuevoAux = nuevo;
	
	while(nuevoAux -> siguiente != NULL){
		nuevoAux = nuevoAux -> siguiente;
	}

	nuevoAux -> siguiente = nuevo;
	nuevo -> anterior = nuevoAux;

	*desfase -= 3;
	return nuevo;
}

//Funcion que desplaza una lista un espacio hacia la izquierda
lista *desplazarIzquierdaUnEspacio(lista *actual, int *desfase){
	//Variables utilizadas en la funcion
	lista *aux = actual;
	lista *desplazada = NULL;
	lista *nuevo = NULL;
	lista *nuevoAux = NULL;
	int i;
	
	for(i=0;i<actual->largo;i++){
		desplazada = aux -> siguiente;
		nuevo = agregar(nuevo, desplazada -> letra, aux -> posicion, actual -> largo);
		aux = aux -> siguiente;
	}
	
	nuevoAux = nuevo;
	
	while(nuevoAux -> siguiente != NULL){
		nuevoAux = nuevoAux -> siguiente;
	}

	nuevoAux -> siguiente = nuevo;
	nuevo -> anterior = nuevoAux;

	*desfase -= 1;
	return nuevo;
}

//Funcion que desplaza una lista un espacio hacia la derecha
lista *desplazarDerechaUnEspacio(lista *actual, int *desfase){
	//Variables utilizadas en la funcion
	lista *aux = actual;
	lista *nuevoAux = NULL;
	lista *desplazada = NULL;
	lista *nuevo = NULL;
	int i;
	
	for(i=0;i<actual->largo;i++){
		desplazada = aux -> anterior;
		nuevo = agregar(nuevo, desplazada -> letra, aux -> posicion, actual -> largo);
		aux = aux -> siguiente;
	}
	
	nuevoAux = nuevo;
	
	while(nuevoAux -> siguiente != NULL){
		nuevoAux = nuevoAux -> siguiente;
	}

	nuevoAux -> siguiente = nuevo;
	nuevo -> anterior = nuevoAux;

	*desfase += 1;
	return nuevo;
}

//Funcion que desplaza una lista un espacio hacia la derecha
lista *desplazarDerechaTresEspacios(lista *actual, int *desfase){
	//Variables utilizadas en la funcion
	lista *aux = actual;
	lista *nuevoAux = NULL;
	lista *desplazada = NULL;
	lista *nuevo = NULL;
	int i;
	
	for(i=0;i<actual->largo;i++){
		desplazada = aux -> anterior -> anterior -> anterior;
		nuevo = agregar(nuevo, desplazada -> letra, aux -> posicion, actual -> largo);
		aux = aux -> siguiente;
	}
	
	nuevoAux = nuevo;
	
	while(nuevoAux -> siguiente != NULL){
		nuevoAux = nuevoAux -> siguiente;
	}

	nuevoAux -> siguiente = nuevo;
	nuevo -> anterior = nuevoAux;

	*desfase += 3;
	return nuevo;
}


//Funcion que se encarga de cifrar una palabra 
void cifrar(lista *letras, lista *codificacion, char *palabra, int largoPalabra){
	//Variables utilizadas en la funcion
	int i;
	int pos = 0;
	char letra = ' ';
	char palabraCifrada[100000];
	int desfase = 0;
	FILE *salida = fopen("Salida.out", "w");
	lista *letrasAux, *codificacionAux;
	letrasAux = letras;
	codificacionAux = codificacion;

	for(i=0;i<largoPalabra;i++){

		pos = buscarPorLetra(letrasAux, palabra[i]);
		letra = buscarPorPosicion(codificacionAux, pos);
		palabraCifrada[i] = letra;

		if(verificarLetra(letra) == 0){ //Si es una vocal o un espacio
			codificacionAux = desplazarIzquierdaTresEspacios(codificacionAux, &desfase);
		}

		else if(verificarLetra(letra) == 1){ //Si es una consonante
			codificacionAux = desplazarDerechaUnEspacio(codificacionAux, &desfase);
		}
	}
	
	fprintf(salida, "%s\n", palabraCifrada);
	fprintf(salida, "%d", desfase);
	fclose(salida);
}

//Funcion que se encarga de descifrar una palabra
void descifrar(lista *letras, lista *codificacion, char *palabra, int largoPalabra, int desfase){
	//Variables utilizadas en la funcion
	int i;
	int pos = 0;
	char letra = ' ';
	char palabraDescifrada[100000];
	int desfaseAux = desfase;
	FILE *salida = fopen("Salida.out", "w");
	lista *letrasAux, *codificacionAux;
	letrasAux = letras;
	codificacionAux = codificacion;

	for(i=0; i<largoPalabra; i++){

		letra = palabra[largoPalabra - i - 1];

		if(verificarLetra(letra) == 0){
			codificacionAux = desplazarDerechaTresEspacios(codificacionAux, &desfaseAux);
			pos = buscarPorLetra(codificacionAux, palabra[largoPalabra - i - 1]);
			letra = buscarPorPosicion(letrasAux, pos);
			palabraDescifrada[largoPalabra - i - 1] = letra;
		}
		else if(verificarLetra(letra) == 1){
			codificacionAux = desplazarIzquierdaUnEspacio(codificacionAux, &desfaseAux);
			pos = buscarPorLetra(codificacionAux, palabra[largoPalabra - i - 1]);
			letra = buscarPorPosicion(letrasAux, pos);
			palabraDescifrada[largoPalabra - i - 1] = letra;
		}
	}
	fprintf(salida, "%s\n", palabraDescifrada);
	fprintf(salida, "%d\n", desfaseAux);
	fclose(salida);
}


//Función que realiza el procedimiento principal del programa
void procedimiento(){
	//Variables utilizadas en la función
	char *eleccion = (char *)malloc(sizeof(char) * 10);
	char palabra[100000];
	char palabraOriginal[100000];
	char abecedario[100000];
	char *palabraOrdenada = NULL;
	char *palabraCifradaOrdenada = NULL;
	char letra;
	int pos;
	int largo;
	int desfase;
	int i = 0;
	lista *letras = NULL;
	lista *codificacion = NULL;
	//Se crea un ultimo nodo, el cual contiene en la variable letra un espacio
	lista *ultimoNodoLetras = crearNodo();
	lista *ultimoNodoCodificacion = crearNodo();
	lista *nodoAuxLetras, *nodoAuxCodificacion, *recorridoLetras, *recorridoCodificacion; //Nodos auxiliares para recorrer la lista
	//Se abre el archivo de entrada
	FILE *archivo = fopen("Entrada.in","r");
	//Lectura de la primera linea para así saber que proceso se debe llevar a cabo
	
	//fgets(eleccion, 11, archivo);
	fscanf(archivo, "%s", eleccion);
	//Cifrado de una palabra
	if(strcmp(eleccion, "Cifrado") == 0){
		
		/*do{
			letra = fgetc(archivo);
			palabra[i] = letra;
			i++;
		}
		while(fgetc(archivo) != '\n' && letra != EOF);*/
		fscanf(archivo, "%s", palabra);

		strcpy(palabraOriginal, palabra);
		palabraOrdenada = quicksort(palabra, 0, (int)strlen(palabra) - 1);
		largo = strlen(palabraOrdenada);

		for(pos = 0; pos < largo; pos++){
			//Se inserta en cada nodo una letra de la palabra y su posicion dentro del arreglo
			letras = agregar(letras, palabraOrdenada[pos], pos, largo + 1);
			codificacion = agregar(codificacion, palabra[pos], pos, largo + 1);
		}

		nodoAuxLetras = letras;
		nodoAuxCodificacion = codificacion;
		
		while(nodoAuxLetras -> siguiente != NULL){
			nodoAuxLetras = nodoAuxLetras -> siguiente;
			nodoAuxCodificacion = nodoAuxCodificacion -> siguiente;
		}

		//Se ubica el nodo con el caracter vacio al final de la lista enlazada. Ademas, al primer nodo 
		//de las listas se le asigna el ultimo nodo, para que toda la lista quede doblemente enlazada
		ultimoNodoLetras -> posicion = pos;
		ultimoNodoLetras -> largo = largo + 1;
		ultimoNodoLetras -> anterior = nodoAuxLetras;
		ultimoNodoCodificacion -> posicion = pos;
		ultimoNodoCodificacion -> largo = largo + 1;
		ultimoNodoCodificacion -> anterior = nodoAuxCodificacion;
		//Se indica que el puntero al siguiente nodo del ultimo nodo apunte al primer nodo de la lista
		//dando asi la forma de una lista enlazada circular
		ultimoNodoLetras -> siguiente = letras;
		letras -> anterior = ultimoNodoLetras;
		nodoAuxLetras -> siguiente = ultimoNodoLetras;
		ultimoNodoCodificacion -> siguiente = codificacion;
		codificacion -> anterior = ultimoNodoCodificacion;
		nodoAuxCodificacion -> siguiente = ultimoNodoCodificacion;
		recorridoLetras = letras;
		recorridoCodificacion = codificacion;

		//Se eliminan los nodos repetidos
		for(pos = 0; pos < largo; pos++){
			if(recorridoLetras -> letra == recorridoLetras -> siguiente -> letra){
				letras = borrar(letras, pos);
				codificacion = borrar(codificacion, pos);
			}
			recorridoLetras = recorridoLetras -> siguiente;
			recorridoCodificacion = recorridoCodificacion -> siguiente;
		}
		cifrar(letras, codificacion, palabraOriginal, (int)strlen(palabraOriginal));
	}

	//Descifrado de una palabra
	else if(strcmp(eleccion, "Descifrado") == 0){

		fscanf(archivo, "%d", &desfase);
		fscanf(archivo, "%s", palabra);
		/*letra = fgetc(archivo);
		while(letra != saltoLinea[0]){
			abecedario[i] = letra;
			letra = fgetc(archivo);
			i++;
		}*/
		fscanf(archivo, "%s", abecedario);
		strcpy(palabraOriginal, abecedario);
		palabraOrdenada = quicksort(abecedario, 0, strlen(abecedario) - 1);
		largo = strlen(palabraOrdenada);

		for(pos = 0; pos < largo; pos++){
			letras = agregar(letras, palabraOrdenada[pos], pos, largo + 1);
			codificacion = agregar(codificacion, palabraOrdenada[pos], pos, largo + 1);
		}

		nodoAuxLetras = letras;
		nodoAuxCodificacion = codificacion;
		
		while(nodoAuxLetras -> siguiente != NULL){
			nodoAuxLetras = nodoAuxLetras -> siguiente;
			nodoAuxCodificacion = nodoAuxCodificacion -> siguiente;
		}

		//Se ubica el nodo con el caracter vacio al final de la lista enlazada. Ademas, al primer nodo 
		//de las listas se le asigna el ultimo nodo, para que toda la lista quede doblemente enlazada
		ultimoNodoLetras -> posicion = pos;
		ultimoNodoLetras -> largo = largo + 1;
		ultimoNodoLetras -> anterior = nodoAuxLetras;
		ultimoNodoCodificacion -> posicion = pos;
		ultimoNodoCodificacion -> largo = largo + 1;
		ultimoNodoCodificacion -> anterior = nodoAuxCodificacion;
		//Se indica que el puntero al siguiente nodo del ultimo nodo apunte al primer nodo de la lista
		//dando asi la forma de una lista enlazada circular
		ultimoNodoLetras -> siguiente = letras;
		letras -> anterior = ultimoNodoLetras;
		nodoAuxLetras -> siguiente = ultimoNodoLetras;
		ultimoNodoCodificacion -> siguiente = codificacion;
		codificacion -> anterior = ultimoNodoCodificacion;
		nodoAuxCodificacion -> siguiente = ultimoNodoCodificacion;
		recorridoLetras = letras;
		recorridoCodificacion = codificacion;

		//Se eliminan los nodos repetidos
		for(pos = 0; pos < largo; pos++){
			if(recorridoLetras -> letra == recorridoLetras -> siguiente -> letra){
				letras = borrar(letras, pos);
				codificacion = borrar(codificacion, pos);
			}
			recorridoLetras = recorridoLetras -> siguiente;
			recorridoCodificacion = recorridoCodificacion -> siguiente;
		}
		descifrar(letras, codificacion, palabra, (int)strlen(palabra), desfase);
	}

	//Cualquier otro caso
	else{
		printf("Error.\n");
		return;
	}
}



