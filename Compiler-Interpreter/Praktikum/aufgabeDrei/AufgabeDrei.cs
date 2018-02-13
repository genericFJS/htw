using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    class MainClass {
        static void Main(string[] args) {

            // Tests:
            int jump = 14-98;
            //TestPrint(testIntArr);
            //TestPrint(jump);

            while (true) {
                Console.Write("Dateiname: ");
                string filePath = Console.ReadLine();
                if (!filePath.EndsWith(".pl0"))
                    filePath += ".pl0";
                if (!File.Exists(filePath)) {
                    Console.WriteLine("File not found: '{0}'", filePath);
                    Console.WriteLine("========================");
                } else {
                    Console.WriteLine("========================");
                    Parser parser = new Parser(filePath);
                    if (parser.Parse()) {
                        Console.WriteLine("------------------------");
                        Console.WriteLine("Parsen erfolgreich");
                    }
                    Console.WriteLine("========================");
                }
            }
        }

        private static void TestPrint(params int[] parameters) {
            foreach (var parameter in parameters) {
                byte[] byteArray = BitConverter.GetBytes(parameter);
                // Füge erstes Byte (little Endian) in Liste ein.
                Console.WriteLine("{0}", byteArray[0].ToString("X"));
                Console.WriteLine("{0}", byteArray[1].ToString("X"));
            }
        }
    }
}
