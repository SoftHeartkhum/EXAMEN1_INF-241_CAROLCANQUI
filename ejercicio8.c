#include <stdio.h>
#include <omp.h>

void generar_secuencia(int ini, int fin, int *secuencia) {
    for (int i = ini; i <= fin; i++) {
        secuencia[i - ini] = i * 2;
    }
}

int main() {
    int terminos = 100;  // Número de términos en la secuencia
    int num_hilos = omp_get_max_threads();  // Número de hilos (procesadores)
    
    // Distribuir el trabajo entre los hilos
    #pragma omp parallel num_threads(num_hilos)
    {
        int id = omp_get_thread_num();  // Identificador del hilo actual
        int inicio = id * (terminos / num_hilos) + 1;  // Calcular el inicio del rango para el hilo actual
        int fin = (id + 1) * (terminos / num_hilos);  // Calcular el final del rango para el hilo actual
        
        // Ajustar el final del rango para el último hilo si el número de términos no es divisible entre el número de hilos
        if (id == num_hilos - 1) {
            fin += terminos % num_hilos;
        }
        
        // Arreglo para almacenar la secuencia generada por el hilo actual
        int secuencia[terminos / num_hilos + 1];
        generar_secuencia(inicio, fin, secuencia);
        
        // Imprimir la secuencia generada por el hilo actual
        printf("Hilo %d: ", id);
        for (int i = 0; i < fin - inicio + 1; i++) {
            printf("%d ", secuencia[i]);
        }
        printf("\n");
    }

    return 0;
}
