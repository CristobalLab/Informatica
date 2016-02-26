#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define SIZE_OF_LINE 255

//Definición de las funciones

//Leer matriz
int** read_matrix(const char* filename, int* n, int* m){
	int i, fila=0;
	int **matrix=NULL;
	char token, line[SIZE_OF_LINE];

	//Se abre el fichero y se comprueba que se ha abierto correctamente
	FILE* f=fopen(filename,"r");
	if (f==NULL){
		puts("Error al abrir el archivo");
		return 0;
	}

	//En el bucle while se comprueba que no haya errores durante la lectura
	while(!feof(f)){
		//Lee la cabecera del documento
		fscanf(f,"%c",&token);

		if (token=='d'){
			//Copiamos la linea en el array "line"
			fgets(line,SIZE_OF_LINE,f);
			//Comprobamos que la dimensión sea correcta
			if(sscanf(line,"%d %d",n,m)!=2){
				puts("Error de dimension\n");
				return NULL;
			}
			//Si es correcta, asignamos memoria dinámica
			matrix=(int**)malloc(sizeof(int*)*(*n));
			for (i=0; i<(*n);i++){
				matrix[i]=(int*)malloc(sizeof(int)*(*m));
			}
		}

		else if (token=='r'){
			//Lectura de elementos fila a fila
			for (i=0; i<(*m);i++){
				fscanf (f,"%d",&matrix[fila][i]);
			}
			fgets(line, SIZE_OF_LINE,f);
			fila++;
		}
		else{
			puts ("No se reconoce el protocolo");
			return 0;
		}
	}
	return matrix;
	fclose(f);
}


//Imprimir matriz
void print_matrix(int n, int m, int **matrix){
	int i,j;
	for (i=0; i<n; i++){
		for (j=0;j<m;j++){
			printf ("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
	
}


//Liberar memoria
void free_matrix(int n, int m, int ** matrix){
	int i;
	free(matrix);
	for (i=0;i<n;i++){
		free(matrix[i]);
	}
	
}


void main(){

	int n, m;
	int** matrix;
	matrix=read_matrix("matriz.txt", &n, &m);
	print_matrix(n, m, matrix);
	free_matrix(n, m, matrix);
	system("pause");
}
