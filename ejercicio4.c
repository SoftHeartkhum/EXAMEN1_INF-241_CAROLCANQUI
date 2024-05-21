#include <stdio.h>
#include <omp.h>

#define M 3
#define N 3
//Realizar en OPENMP la multiplicación de una matriz NxN, con un vector de dimensión N.
//la funcion
void matrix_x_vector(int m[N][N], int v[N], int res[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        res[i] = 0;
        for (int j = 0; j < N; j++) {
            res[i] += m[i][j] * v[j];
        }
    }
}

int main() {
    int m[N][N] = {{2, 3, 6},
                        {1, 2, 3},
                        {7, 5, 1}};
    int v[N] = {1, 4, 2};
    int res[N];
// programa principal :D
    matrix_x_vector(m, v, res);

    printf("Resultado de la matriz por el vector:\n");
    #pragma omp parallel for
    
    for (int i = 0; i < N; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}
