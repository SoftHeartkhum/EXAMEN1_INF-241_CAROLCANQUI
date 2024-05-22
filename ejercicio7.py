import math
import multiprocessing as np
from multiprocessing import Pool

def cal_pi(ini,fin):
  v=[]
  for i in range(ini,fin):
    if (i==0):
      continue
    t= (1/(i**4))
    v.append(t)
  return v
if __name__=='__main__':
  limite = 1000000
  parametros = [((i*limite),(limite*(i+1))) for i in range(np.cpu_count())]
  print(parametros)
  pool=Pool()
  resultado = pool.starmap(cal_pi,parametros)
  pi=(90*sum(sum(resultado,[])))**(1/4)
  print(pi)
