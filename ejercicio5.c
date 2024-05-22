#include <stdio.h>
#include <mpi.h>

//Realizar en MPI la multiplicación de una matriz NxN, con un vector de dimensión N.

// tamaños de matriz y vector 
#define N 3  


void multiplyPart(int m[N][N], int v[N], int res[], int start, int num) {
    
    // Multiplicación de la parte de la matriz asignada por el vector
    for (int i = 0; i < num; i++) {
        res[i] = 0;
        for (int j = 0; j < N; j++) {
            res[i] += m[start + i][j] * v[j];
        }
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int r, s;//rank ,size
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int m[N][N] = {{2, 4, 2},{3, 6, 1},{1, 3, 2}};
    
    int v[N] = {2, 3, 4};
    
    int rl[N]; // Resultados locales de cada proceso
    int rf[N]; // Resultados finales 

    // Cada proceso calcula su rango de filas
    int fila_proc= N / s; // Número de filas por proceso ...rows_per_process
    int extra_rows = N % s; // Resto de filas (si N no es divisible por size)

    int start_row = r * fila_proc + (r < extra_rows ? r : extra_rows);
    int num_rows = fila_proc + (r < extra_rows ? 1 : 0);

    // Enviar el vector a todos los procesos si el rank es 0
    if (r == 0) {
        for (int i = 1; i < s; i++) {
            MPI_Send(v, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(v, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Cada proceso realiza la multiplicación para su rango de filas
    multiplyPart(m, v, rl, start_row, num_rows);

    // Enviar resultados locales al proceso maestro (rank 0)
    if (r == 0) {
            // Proceso maestro inicializa el resultado final con los resultados locales
        for (int i = 0; i < num_rows; i++) {
            rf[i] = rl[i];
        }

        // Proceso maestro recibe resultados locales de otros procesos
        for (int i = 1; i < s; i++) {
            int recv_start = i * fila_proc + (i < extra_rows ? i : extra_rows);
            int recv_num_rows = fila_proc + (i < extra_rows ? 1 : 0);
            MPI_Recv(rf+ recv_start, recv_num_rows, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Imprimir los resultados finales
        printf("Resultado de la multiplicación matriz-vector:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", rf[i]);
        }
        printf("\n");
    } else {
        MPI_Send(rl, num_rows, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
