#include "headers.h"
#include <time.h>

//Archivo que contiene solo el main del programa
int main(){
	printf("\n\n||------------------------------------------------------------------------------------------------------------------------------------||\n");
	printf("||------------------------------------------------------------------------------------------------------------------------------------||\n");
	printf("|| Recordatorio: Cada vez que ingrese el nombre de un archivo, procure ingresar tambien su extension, por ejemplo, nombre_archivo.txt ||");
	printf("\n||------------------------------------------------------------------------------------------------------------------------------------||\n");
	printf("||------------------------------------------------------------------------------------------------------------------------------------||\n");
	//Se almacenan los nombres de los archivos en cadenas de carácteres
	char direccion_principal[70];
	char direccion_comparacion[70];
	//Variables de tipo time_t, las cuales serán utilizadas para analizar cuanto tiempo demora en ejecutarse el algoritmo
	time_t inicio, fin;
	printf("Ingrese el nombre del archivo que contiene la imagen principal: ");
	scanf("%s",direccion_principal);
	printf("Ingrese el nombre del archivo que contiene las imagenes a comparar: ");
	scanf("%s",direccion_comparacion);
	printf("\n");
	//Se abren los respectivos archivos
	FILE *archivo_main = fopen(direccion_principal, "r");
	FILE *archivo_comp = fopen(direccion_comparacion, "r");
	if(archivo_main == NULL) printf("El archivo de nombre '%s' no existe, por favor compruebe que este bien escrito el nombre.\n", direccion_principal);
	if(archivo_comp == NULL) printf("El archivo de nombre '%s' no existe, por favor compruebe que este bien escrito el nombre.\n", direccion_comparacion);
	time(&inicio);
	procedimiento(archivo_main, archivo_comp);
	time(&fin);
	printf("El algoritmo demoro un total de %f segundos en ejecutarse.\n\n", (double)difftime(fin, inicio));
	return 0;
}