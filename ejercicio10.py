import math
import multiprocessing as mp
from multiprocessing import Pool

def generar_secuencia(inicial, final):
    secuencia = []
    for i in range(inicial, final + 1):
        secuencia.append(i * 2)
    return secuencia

if __name__=='__main__':
    limite = 100  # Número de términos en la serie
    num_proc = mp.cpu_count()    # Número de procesadores (núcleos) para distribuir el trabajo
    parametros = [(i*(limite//num_proc), (i+1)*(limite//num_proc)) for i in range(num_proc)]
    print("Número de procesadores:", num_proc)
    print("Parámetros:", parametros)
    with Pool() as pool:
        resultado_secuencia = pool.starmap(generar_secuencia, parametros)
    print("Resultado de la secuencia:", resultado_secuencia)
