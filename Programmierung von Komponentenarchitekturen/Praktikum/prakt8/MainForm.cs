using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace prakt8 {
    public partial class MainForm : Form {

        string[,] eignung = new string[3, 3] { {"ausgezeichnet", "ok", "nicht geeignet" }, { "ok", "ausgezeichnet", "nicht geeignet" }, { "nicht geeignet", "nicht geeignet", "ausgezeichnet" } };

        public MainForm() {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private void blinkLabel1_Click(object sender, EventArgs e) {

        }

        private void comboSelectedIndexChanged(object sender, EventArgs e) {
            if (combo_auto.SelectedIndex > -1 && combo_beruf.SelectedIndex > -1) {
                int indexX = 0;
                int indexY = 0;
                switch (combo_beruf.Text) {
                    case "Informatiker":
                        indexX = 1;
                        break;
                    case "Arzt":
                        indexX = 2;
                        break;
                }
                switch (combo_auto.Text) {
                    case "Citroen":
                        indexY = 1;
                        break;
                    case "Ferrari":
                        indexY = 2;
                        break;
                }
                eignungResult.Text = eignung[indexX, indexY];
                switch (eignungResult.Text) {
                    case "nicht geeignet":
                        eignungResult.BackColor = System.Drawing.Color.Red;
                        break;
                    case "ausgezeichnet":
                        eignungResult.BackColor = System.Drawing.Color.Green;
                        break;
                    default:
                        eignungResult.BackColor = System.Drawing.Color.Orange;
                        break;

                }
            } else {
                eignungResult.Text = "Bitte beide Comboboxen setzen.";
            }
        }
    }
}
