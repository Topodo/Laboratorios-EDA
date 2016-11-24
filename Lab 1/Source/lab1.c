#include <stdio.h>
#include <stdlib.h>

//Cantidad de capas de la matriz con la imagen principal
#define MAX_NUMBER 3

//Se inicializa la matriz principal donde se almacenará el archivo principal
int ***initMatrix(int N, int M){
	int i, j = 0;
	int ***matriz = (int ***)malloc(sizeof(int **)*N);
	if(matriz != NULL){
		for(i=0;i<N;i++){
		matriz[i] = (int **)malloc(sizeof(int *)*M);
		for(j=0;j<M;j++){
			matriz[i][j] = (int *)malloc(sizeof(int)*MAX_NUMBER);
		}
	}
	return matriz;
	}
	else{
		printf("Error al asignar memoria\n");
		return NULL;
	}
}

//Se realiza el proceso de lectura del archivo principal y se almacena en una matriz tridimensional
int ***readImage(FILE *archivo, int *filas, int *cols){

	int i,j=0;
	//Definición del RGB de cada pixel
	int r,g,b;
	//Dimensiones de la matriz
	int N,M;
	//Lectura del archivo
	if(archivo){
		//Inicio de la lectura
		fscanf(archivo, "%d %d", &N, &M);
		//Se crea una matriz almacenadora
		int ***matriz = initMatrix(N, M);
		//Se lee la matriz
		if(matriz != NULL){
			for(i=0;i<N;i++){
				for(j=0;j<M;j++){
					fscanf(archivo, "%d,%d,%d ", &r, &g, &b);
					//Se almacena el pixel en la matriz
					matriz[i][j][0] = r;
					matriz[i][j][1] = g;
					matriz[i][j][2] = b;
				}
			}
			*filas = N;
			*cols = M;
			return matriz;
		}
	}
	//Si ocurre algun error, se retorna NULL
	else return NULL;
}

//Se realiza la comparación entre las imágenes
int comparacion(int ***imagenPrincipal, int filas_main, int cols_main, int ***subImagen, int filas_sub, int cols_sub){
	//Definición de contadores
	int i,j,x,y=0;
	//Estado de la comparación, si es 0 no hay coincidencia, si es 1 se encontró coincidencia
	int estado = 1;
	//Inicio de la iteración
	if(imagenPrincipal != NULL && subImagen != NULL){
		for(i=0;i<=(filas_main - filas_sub);i++){
			for(j=0;j<=(cols_main - cols_sub);j++){
				for(x=0;x<filas_sub;x++){
					for(y=0;y<cols_sub;y++){
						if(imagenPrincipal[i+x][j+y][0] != subImagen[x][y][0] || imagenPrincipal[i+x][j+y][1] != subImagen[x][y][1] || imagenPrincipal[i+x][j+y][2] != subImagen[x][y][2]){
							//Si no se cumple la condición, se fuerza la condición de borde de la iteración sobre la subimagen
							estado = 0;
							x=filas_sub;
							y=cols_sub;
						}
						else estado = 1;
					}
				}
				//Si se logró terminar toda la iteracion sobre la sub imagen, se retorna true (1).
				if(estado == 1) return 1;
				else estado = 1;
			}
		}
		if (estado == 0) return 0;
	}
	return 0;
}

//Función que rota una matriz en 90 grados
int ***rotar(int *** matriz, int N, int M){
	int ***matriz_rotada = initMatrix(N, M);
	int i,j=0;
	if(matriz_rotada != NULL){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				matriz_rotada[i][j][0] = matriz[M-j-1][i][0];
				matriz_rotada[i][j][1] = matriz[M-j-1][i][1];
				matriz_rotada[i][j][2] = matriz[M-j-1][i][2];
			}
		}
		return matriz_rotada;	
	}
	else{
		printf("ERROR\n");
		return NULL;
	}
	
}

//Procedimiento principal donde se realizan las comparaciones pertinentes y se escribe el resultado en un archivo de texto
void procedimiento(FILE *imagenPrincipal, FILE *subImagen){
	//Dimensiones de las matrices
	int filas_main, cols_main, filas_sub, cols_sub;
	//Se definen las matrices tridimensionales donde se almacenarán las imágenes
	int ***main_matrix = readImage(imagenPrincipal, &filas_main, &cols_main);
	//Archivo con el resultado
	FILE *resultado = fopen("resultado.txt", "w");
	//Contador del ID de la sub imagen
	int id = 1;
	//Guiones
	char guiones[5];
	if(main_matrix != NULL && subImagen != NULL){
		//Se realiza un ciclo que se ejecutará mientras el archivo siga abierto
		while(!feof(subImagen)){
			//Se escanea la sub imagen y se almacenan todas las rotaciones
			int ***matriz_uno = readImage(subImagen, &filas_sub, &cols_sub); //Matriz sin rotación
			int ***matriz_dos = rotar(matriz_uno, cols_sub, filas_sub); //Rotación en 90°
			int ***matriz_tres = rotar(matriz_dos, filas_sub,cols_sub); //Rotación en 180°
			int ***matriz_cuatro = rotar(matriz_tres, cols_sub, filas_sub); //Rotación en 270°

			//Se leen los cinco guiones para continuar con el formato
			if(!feof(subImagen)) {
				fscanf(subImagen, "%s", guiones);
			}
			else;
			//Se compara la imagen principal con las sub imagenes y se procede a escribir en el archivo de texto el resultado
			if(comparacion(main_matrix, filas_main, cols_main, matriz_uno, filas_sub, cols_sub) == 1
			|| comparacion(main_matrix, filas_main, cols_main, matriz_dos, cols_sub, filas_sub) == 1
			|| comparacion(main_matrix, filas_main, cols_main, matriz_tres, filas_sub, cols_sub) == 1
			|| comparacion(main_matrix, filas_main, cols_main, matriz_cuatro, cols_sub, filas_sub) == 1){
				fprintf(resultado, "Imagen %d: Encontrada.\n", id);
			}
			else{
				fprintf(resultado, "Imagen %d: No encontrada.\n", id);
			}
			id++;
			free(matriz_uno);
			free(matriz_dos);
			free(matriz_tres);
			free(matriz_cuatro);
		}
		free(main_matrix);
		fclose(subImagen);
		fclose(imagenPrincipal);
	}
	else return;
}
