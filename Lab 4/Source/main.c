#include "lab4.h"
#include <time.h>

int main(){
	time_t inicio, fin;
	time(&inicio);
	FILE *archivo = fopen("Entrada.in", "r");
	procedimiento(archivo);
	time(&fin);
	printf("El algoritmo demoro un total de %f segundos en ejecutarse.\n\n", (double)difftime(fin, inicio));
	return 0;
}