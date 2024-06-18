using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logica
{
    public class Class1
    {
        public double EvaluarExpresionPostfija(string expresion)
        {
            Stack<double> pila = new Stack<double>();
            string[] tokens = expresion.Split(' ');

            foreach (var token in tokens)
            {
                if (double.TryParse(token, out double numero))
                {
                    pila.Push(numero);
                }
                else
                {
                    double operando2 = pila.Pop();
                    double operando1 = pila.Pop();
                    double resultado;

                    if (token == "+")
                    {
                        resultado = operando1 + operando2;
                    }
                    else if (token == "-")
                    {
                        resultado = operando1 - operando2;
                    }
                    else if (token == "*")
                    {
                        resultado = operando1 * operando2;
                    }
                    else if (token == "/")
                    {
                        resultado = operando1 / operando2;
                    }
                    else
                    {
                        throw new InvalidOperationException("Operador desconocido");
                    }

                    pila.Push(resultado);
                }
            }
            return pila.Pop();
        }
    }
}
