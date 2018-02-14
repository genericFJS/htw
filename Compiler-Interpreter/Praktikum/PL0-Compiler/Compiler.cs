// Code von Falk-Jonatan Strube (mail@fj-strube.de)
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL0Compiler {
    class MainClass {
        static void Main(string[] args) {
            Console.Write("Codefile: ");
            if (args == null || args.Length == 0) {
                // Kein Argument beim Ausführen: frage Dateiname manuell ab.
                string filePath = Console.ReadLine();
                Compile(filePath);
            } else {
                // Argument übergeben: Compiler mit Dateiname ausführen.
                Console.WriteLine(args[0]);
                Compile(args[0]);
            }
        }

        static void Compile(String filePath) {
            if (!filePath.EndsWith(".pl0"))
                filePath += ".pl0";
            if (!File.Exists(filePath)) {
                Parser.PrintError("File not found: ", filePath, ".");
            } else {
                Console.WriteLine("========================");
                Parser parser = new Parser(filePath);
                if (parser.Parse()) {
                    Console.WriteLine("------------------------");
                    Console.WriteLine("Compilation successfull.");
                }
            }
            Console.WriteLine("========================");
        }
    }
}
