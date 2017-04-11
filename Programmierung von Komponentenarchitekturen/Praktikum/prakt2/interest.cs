using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt2 {
    class Interest {
        static void Main(string[] args) {
            Console.OutputEncoding = Encoding.UTF8; // Eurozeichen usw.
            CultureInfo cultureDE = new CultureInfo("de-DE");   // Kommasymbol
            CultureInfo.DefaultThreadCurrentCulture = cultureDE;
            Console.Write("Startkapital in {0}: ",cultureDE.NumberFormat.CurrencySymbol);
            double start;
            if (!double.TryParse(Console.ReadLine(), out start)) {
                Console.WriteLine("Kein gültiges Startkapital!");
                return;
            }
            Console.Write("Laufzeit in Jahren: ");
            int years;
            if (!int.TryParse(Console.ReadLine(), out years)) {
                Console.WriteLine("Keine gültige Laufzeit!");
                return;
            }
            Console.Write("Zinssatz: ");
            float interest;
            if (!float.TryParse(Console.ReadLine(), out interest)) {
                Console.WriteLine("Kein gültiger Zinssatz!");
                return;
            }
            double end = start;
            for (int i = years; i > 0; i--) {
                end *= interest+1;
                Console.Write("Jahr " + (years-i+1));
                Console.Write(": {0:c2}\n",end);
            }
            Console.Write("Das Endkapital beträgt {0:c2}", start*Math.Pow(1+interest,years));
            Console.Write(" bei einem Zinssatz von {0:P2}\n", interest);
        }
    }
}
