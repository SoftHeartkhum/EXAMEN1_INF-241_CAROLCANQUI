using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculadoraConsola
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Ingrese una expresión postfija:");
            string entrada = Console.ReadLine();

            var calculadora = new Logica.Class1();
            double resultado = calculadora.EvaluarExpresionPostfija(entrada);

            Console.WriteLine("El resultado es: " + resultado);
            Console.WriteLine("Presione cualquier tecla para salir...");
            Console.ReadKey();

        }
    }
}
