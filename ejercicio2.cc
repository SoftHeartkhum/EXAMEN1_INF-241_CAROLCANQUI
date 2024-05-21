#include <iostream>


//punteros

//SUMA
void  suma(int a, int b, int *res){
	*res = a+b;
}
//RESTA
void resta(int a, int b, int *res){
	*res = a - b;
}
//MULTIPLICACION
void multiplicacion(int *a, int *b, int *res) {
    *res= 0;
    for (int i = 0; i < *b; i++) {
        *res += *a;
    }
}
//DIVISION
void division(int *a, int *b, int *cociente, int *residuo) {
    *cociente = 0;
    *residuo = *a;
    while (*residuo >= *b) {
        *residuo -= *b;
        (*cociente)++;
    }
}
int main() {
    int a = 23;
    int b = 7;
    int res;
    int cociente;
    int residuo;
    	//Suma
	suma(a,b,&res);
	printf("La suma de %d y %d es: %d\n", a, b, res);
	//Resta
	resta(a,b,&res);
	printf("La resta de %d y %d es: %d\n", a, b, res);
    	// Multiplicación
   	 multiplicacion(&a, &b, &res);
    	printf("La multiplicación de %d y %d es: %d\n", a, b, res);
   	 // División
   	 division(&a, &b, &cociente, &residuo);
   	 printf("La división de %d entre %d da cociente: %d y residuo: %d\n", a, b, cociente, residuo);
	return 0;
}
