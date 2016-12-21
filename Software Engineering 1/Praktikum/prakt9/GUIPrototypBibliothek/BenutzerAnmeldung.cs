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
    public partial class BenutzerAnmeldung : Form
    {
        public BenutzerAnmeldung()
        {
            InitializeComponent();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Szenario 1: Benutzerdaten unvollständig
            if (this._txtName.Text.Trim() == String.Empty)
            {
                MessageBox.Show(
                "Die folgende Felder müssen noch ausgefüllt werden:\n- Name",
                "Die Benutzerdaten sind unvollständig",
                MessageBoxButtons.OK, MessageBoxIcon.Error
                );
                return;
            }
            if (this._rbWeiblich.Checked)
            {
                // Szenario 2: Benutzer wird angemeldet
                BenutzerausweisAbsage form = new BenutzerausweisAbsage(true);
                form.ShowDialog();
            }
            else
            {
                // Szenario 3: Benutzer ist schon vorhanden
                BenutzerausweisAbsage form = new BenutzerausweisAbsage(false);
                form.ShowDialog();
            }
            this.Close();
        }
    }
}
