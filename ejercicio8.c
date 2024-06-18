#include <stdio.h>
#include <omp.h>

void generar_serie(int inicial, int final, int *serie) {
    for (int i = inicial; i <= final; i++) {
        serie[i - inicial] = i * 2;
    }
}
int main() {
    int limite = 100;  // Número de términos en la serie
    int num_proc = omp_get_max_threads();  // Número de procesadores(vectores)
    // Distribuir el trabajo entre los procesadores
    #pragma omp parallel num_threads(num_proc)
    {
        int id = omp_get_thread_num();  // Identificador del procesador actual
        int inicio = id * (limite / num_proc) + 1;  // Calcular el inicio del rango para el procesador actual
        int fin = (id + 1) * (limite / num_proc);  // Calcular el final del rango para el procesador actual        
// El último procesador maneje los términos restantes si el límite no es divisible entre el número de procesadores
        if (id == num_proc - 1) {
            fin += limite % num_proc;
        }
        // Arreglo para almacenar la serie generada por el procesador actual
        int serie[limite / num_proc + 1];
        generar_serie(inicio, fin, serie);
        // Imprimir la serie generada por el procesador actual
        printf("Procesador %d: ", id);
        for (int i = 0; i < fin - inicio + 1; i++) {
            printf("%d ", serie[i]);
        }
        printf("\n");
    }

    return 0;
}

