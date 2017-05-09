using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

// Hilfe: Platzierung der Wörter durch Spirale realisieren. Spiralenpunkte: x=x_0+r * sin(alpha), y=y_0 + r * cos(alpha)
// (wobei (x_0,y_0) der Mittelpunkt ist). Dann testen, ob Rechteck dort möglich ist.
namespace prakt9 {
    static class Program {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
