#include <stdio.h>
#include <omp.h>
// En openMP realice la multiplicación y división en base a sumas y restas.

// multiplicacion de a y b  con sumas repetitivas en base a punteros
void multiplicacion(int *a, int *b, int *res2) {
    int res=0;
    #pragma omp parallel for
    for (int i = 0; i < *b; i++) {
        res += *a;
    }
    *res2 = res;
}

// division de a y b  con restas repetitivas en base a punteros
void division(int *a, int *b, int *co, int *re) {
    *co = 0;
    *re = *a;
    #pragma omp parallel reduction(+:var)
    {
    	while (*re >= *b) {
			*re -= *b;
			(*co)++;
		}
    }
}
void main() {
    int a = 23;
    int b = 7;
    int res;
    int co;
    int re;
    
    // *
    multiplicacion(&a, &b, &res);
    printf("La multiplicación de %d y %d es: %d\n", a, b, res);

    //  /
    division(&a, &b, &co, &re);
    printf("La división de %d entre %d da cociente: %d y residuo: %d\n", a, b, co, re);
}
