using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUIPrototypBibliothek
{
    public partial class Bibliothek : Form
    {
        public Bibliothek()
        {
            InitializeComponent();
        }

        private void beendenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            base.Close();
        }

        private void benutzerAnmeldenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BenutzerAnmeldung form = new BenutzerAnmeldung();
            form.ShowDialog();
        }
    }
}
