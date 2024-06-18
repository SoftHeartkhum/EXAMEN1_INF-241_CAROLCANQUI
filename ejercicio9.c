#include <stdio.h>
#include <mpi.h>

void generar_serie(int inicio, int fin, int *serie) {
    for (int i = inicio; i <= fin; i++) {
        serie[i - inicio] = i * 2;
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int limite = 100; // Número de términos en la serie
    int num_proc = size; // Número de procesadores (vectores) para distribuir el trabajo
    int serie_local[limite / num_proc + 1]; // Arreglo para almacenar la serie local de cada proceso

    // Calcular el rango de términos para cada proceso
    int inicio = rank * (limite / num_proc) + 1;
    int fin = (rank + 1) * (limite / num_proc);

    // Asegurarse de que el último proceso maneje los términos restantes si el límite no es divisible entre el número de procesos
    if (rank == num_proc - 1) {
        fin += limite % num_proc;
    }

    // Generar la serie local para cada proceso
    generar_serie(inicio, fin, serie_local);

    // Proceso maestro
    if (rank == 0) {
        // Imprimir la serie local del proceso maestro
        printf("Procesador %d: ", rank);
        for (int i = 0; i < fin - inicio + 1; i++) {
            printf("%d ", serie_local[i]);
        }
        printf("\n");

        // Recibir las series de los otros procesos y mostrarlas
        for (int i = 1; i < size; i++) {
            int recv_inicio = i * (limite / num_proc) + 1;
            int recv_fin = (i + 1) * (limite / num_proc);
            if (i == size - 1) {
                recv_fin += limite % num_proc;
            }
            int recv_tam = recv_fin - recv_inicio + 1;
            int recv_serie[recv_tam];
            MPI_Recv(recv_serie, recv_tam, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Procesador %d: ", i);
            for (int j = 0; j < recv_tam; j++) {
                printf("%d ", recv_serie[j]);
            }
            printf("\n");
        }
    } else {
        // Enviar la serie local al proceso maestro
        MPI_Send(serie_local, fin - inicio + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
