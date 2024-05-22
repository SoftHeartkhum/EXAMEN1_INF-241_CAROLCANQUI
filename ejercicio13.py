import multiprocessing as mp
from multiprocessing import Pool

def fibonacci(n):
    fibo = [0, 1]
    for i in range(2, n):
        fibo.append(fibo[-1] + fibo[-2])
    return fibo

def calcular_fibonacci(ini, fin):
    return fibonacci(fin)[ini:fin]

if __name__ == "__main__":
    num_terminos = 20
    num_procesos = mp.cpu_count()
    # Calcular el número de términos por proceso
    terminos_por_proceso = num_terminos // num_procesos
    # Generar los rangos de términos para cada proceso
    rangos = [(i * terminos_por_proceso, (i + 1) * terminos_por_proceso) for i in range(num_procesos)]
    with Pool() as pool:
        resultados = pool.starmap(calcular_fibonacci, rangos)
    # Imprimir los términos de Fibonacci
    print("Resultados:", resultados)
    secuencia = []
    for sublista in resultados:
        for termino in sublista:
            secuencia.append(termino)
    print("Secuencia completa:", secuencia)
