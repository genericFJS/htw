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
    public partial class BenutzerausweisAbsage : Form
    {
        public BenutzerausweisAbsage()
        {
            InitializeComponent();
        }

        public BenutzerausweisAbsage(bool szenarioBenutzerausweis)
        {
            InitializeComponent();
            if (szenarioBenutzerausweis)
            {
                // Szenario: Benutzerausweis drucken
                DateTime date = DateTime.Now;
                this._txtGueltigkeit.Text = (date.AddYears(1)).ToShortDateString();
                this._txtAusgestellt.Text = date.ToShortDateString();
                cmdAbsageDrucken.Hide();
            }
            else
            {
                // Szenario: Absage und Benutzerausweis drucken
                this.Text = "Absage: Benutzer ist bereits vorhanden";
                DateTime date = (DateTime.Now).AddMonths(-8);
                this._txtGueltigkeit.Text = (date.AddYears(1)).ToShortDateString();
                this._txtAusgestellt.Text = date.ToShortDateString();
                cmdAbsageDrucken.Select();
            }
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Der Benutzerausweis wurde erfolgreich gedruckt.",
                "Druckerinformation", MessageBoxButtons.OK,
                MessageBoxIcon.Information);
            this.Close();
        }

        private void BenutzerausweisAbsage_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Die Absage wurde erfolgreich gedruckt.",
                "Druckerinformation", MessageBoxButtons.OK,
                MessageBoxIcon.Information);
            this.Close();
        }
    }
}
