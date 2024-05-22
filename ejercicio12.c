#include <stdio.h>
#include <mpi.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int rango, tamano;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamano);

    if (tamano < 2) {
        printf("Se necesitan al menos dos procesos para ejecutar este programa.\n");
        MPI_Finalize();
        return 1;
    }

    if (rango == 0) {
        // Proceso maestro
        int limite;
        printf("Introduce el número de términos de Fibonacci a calcular: ");
        scanf("%d", &limite);

        // Solicitar cada término a los procesos esclavos y mostrar los resultados
        for (int i = 0; i < limite; i++) {
            int resultado;
            MPI_Recv(&resultado, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Término %d de Fibonacci: %d\n", i + 1, resultado);
        }
    } else {
        // Procesos esclavos
        int termino;
        while (1) {
            // Esperar la solicitud del término de Fibonacci
            MPI_Recv(&termino, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (termino < 0)
                break;

            // Calcular el término de Fibonacci y enviarlo de vuelta al proceso maestro
            int resultado = fibonacci(termino);
            MPI_Send(&resultado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
