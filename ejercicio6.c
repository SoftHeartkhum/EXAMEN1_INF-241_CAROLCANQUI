#include <stdio.h>
#include <math.h>
#include <mpi.h>

double calcular_pi(int inicio, int fin) {
    double suma = 0;
    for (int i = inicio; i < fin; i++) {
        if (i == 0) {
            continue;
        }
        double termino = 1.0 / pow(i, 4);
        suma += termino;
    }
    return suma;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int limite = 1000000;
    int inicio = rank * limite;
    int fin = (rank + 1) * limite;
    double local_suma = calcular_pi(inicio, fin);
    if (rank == 0) {
        double total_suma = local_suma;
        double recv_suma;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&recv_suma, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_suma += recv_suma;
        }
        double pi = pow(90 * total_suma, 0.25);
        printf("Valor aproximado de pi: %lf\n", pi);
    } else {
        MPI_Send(&local_suma, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
