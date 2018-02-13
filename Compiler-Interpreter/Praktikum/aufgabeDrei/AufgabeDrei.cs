using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    class MainClass {
        static void Main(string[] args) {
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
    }
}
