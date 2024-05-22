#include <stdio.h>
#include <mpi.h>

void generar_secuencia(int ini, int fin, int *secuencia) {
    // Generar la secuencia en el rango dado
    for (int i = ini; i <= fin; i++) {
        secuencia[i - ini] = i * 2;
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int limite = 100; // Número total de términos en la secuencia
    int num_procs = size; // Número de procesos (vectores) para distribuir el trabajo
    int secuencia_local[limite / num_procs + 1]; // Arreglo para almacenar la secuencia local de cada proceso

    // Calcular el rango de términos para cada proceso
    int inicio = rank * (limite / num_procs) + 1;
    int fin = (rank + 1) * (limite / num_procs);

    // Asegurar que el último proceso maneje los términos restantes si el límite no es divisible entre el número de procesos
    if (rank == num_procs - 1) {
        fin += limite % num_procs;
    }

    // Generar la secuencia local para cada proceso
    generar_secuencia(inicio, fin, secuencia_local);

    // Proceso maestro
    if (rank == 0) {
        // Imprimir la secuencia local del proceso maestro
        printf("Proceso %d: ", rank);
        for (int i = 0; i < fin - inicio + 1; i++) {
            printf("%d ", secuencia_local[i]);
        }
        printf("\n");

        // Recibir y mostrar las secuencias de los otros procesos
        for (int i = 1; i < size; i++) {
            int recv_inicio = i * (limite / num_procs) + 1;
            int recv_fin = (i + 1) * (limite / num_procs);
            if (i == size - 1) {
                recv_fin += limite % num_procs;
            }
            int recv_size = recv_fin - recv_inicio + 1;
            int recv_secuencia[recv_size];
            MPI_Recv(recv_secuencia, recv_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proceso %d: ", i);
            for (int j = 0; j < recv_size; j++) {
                printf("%d ", recv_secuencia[j]);
            }
            printf("\n");
        }
    } else {
        // Enviar la secuencia local al proceso maestro
        MPI_Send(secuencia_local, fin - inicio + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
