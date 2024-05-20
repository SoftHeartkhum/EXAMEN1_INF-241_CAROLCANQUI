#include <stdio.h>

//punteros



// la suma
void suma(int a, int b, int *resultados){
	*resultados = a + b;
}

// la resta
void resta(int a, int b, int *resultados){
	*resultados = a - b;
}

// la multiplicacion
void multiplicacion( int *b,int *a, int *resultados) {
    *resultados= 0;
    for (int i = 0; i < *b; i++) {
        *resultados += *a;
    }
}

// la division
void division(int *a, int *b, int *c, int *r) {
    *c = 0;
    *r = *a;
    while (*r >= *b) {
        *r -= *b;
        (*c)++;
    }
}



void main() {

    int a = 23;
    int b = 7;
    int res;
    int cociente;
    int residuo;
    
    	//+
	suma(a,b,&res);
	printf("La suma de %d y %d es: %d\n", a, b, res);
	//-
	resta(a,b,&res);
	printf("La resta de %d y %d es: %d\n", a, b, res);
    	// *
    	multiplicacion(&b, &a, &res);
    	printf("La multiplicación de %d y %d es: %d\n", a, b, res);
    	//  /
   	 division(&a, &b, &cociente, &residuo);
   	 printf("La división de %d entre %d da cociente: %d y residuo: %d\n", a, b, cociente, residuo);
}
