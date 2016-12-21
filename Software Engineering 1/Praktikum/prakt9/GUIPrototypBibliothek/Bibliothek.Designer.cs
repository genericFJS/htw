namespace GUIPrototypBibliothek
{
    partial class Bibliothek
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.beendenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.benutzerverwaltungToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.benutzerAnmeldenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.benutzerAbmeldenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.benutzerausweisVerlängernToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.medienverwaltungToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mahnungsverwaltungToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.hilfeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.beendenToolStripMenuItem,
            this.benutzerverwaltungToolStripMenuItem,
            this.medienverwaltungToolStripMenuItem,
            this.mahnungsverwaltungToolStripMenuItem,
            this.hilfeToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(833, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // beendenToolStripMenuItem
            // 
            this.beendenToolStripMenuItem.Name = "beendenToolStripMenuItem";
            this.beendenToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.beendenToolStripMenuItem.Text = "Beenden";
            this.beendenToolStripMenuItem.Click += new System.EventHandler(this.beendenToolStripMenuItem_Click);
            // 
            // benutzerverwaltungToolStripMenuItem
            // 
            this.benutzerverwaltungToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.benutzerAnmeldenToolStripMenuItem,
            this.benutzerAbmeldenToolStripMenuItem,
            this.benutzerausweisVerlängernToolStripMenuItem});
            this.benutzerverwaltungToolStripMenuItem.Name = "benutzerverwaltungToolStripMenuItem";
            this.benutzerverwaltungToolStripMenuItem.Size = new System.Drawing.Size(124, 20);
            this.benutzerverwaltungToolStripMenuItem.Text = "Benutzerverwaltung";
            // 
            // benutzerAnmeldenToolStripMenuItem
            // 
            this.benutzerAnmeldenToolStripMenuItem.Name = "benutzerAnmeldenToolStripMenuItem";
            this.benutzerAnmeldenToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.benutzerAnmeldenToolStripMenuItem.Text = "Benutzer anmelden";
            this.benutzerAnmeldenToolStripMenuItem.Click += new System.EventHandler(this.benutzerAnmeldenToolStripMenuItem_Click);
            // 
            // benutzerAbmeldenToolStripMenuItem
            // 
            this.benutzerAbmeldenToolStripMenuItem.Name = "benutzerAbmeldenToolStripMenuItem";
            this.benutzerAbmeldenToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.benutzerAbmeldenToolStripMenuItem.Text = "Benutzer abmelden";
            // 
            // benutzerausweisVerlängernToolStripMenuItem
            // 
            this.benutzerausweisVerlängernToolStripMenuItem.Name = "benutzerausweisVerlängernToolStripMenuItem";
            this.benutzerausweisVerlängernToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.benutzerausweisVerlängernToolStripMenuItem.Text = "Benutzerausweis verlängern";
            // 
            // medienverwaltungToolStripMenuItem
            // 
            this.medienverwaltungToolStripMenuItem.Name = "medienverwaltungToolStripMenuItem";
            this.medienverwaltungToolStripMenuItem.Size = new System.Drawing.Size(118, 20);
            this.medienverwaltungToolStripMenuItem.Text = "Medienverwaltung";
            // 
            // mahnungsverwaltungToolStripMenuItem
            // 
            this.mahnungsverwaltungToolStripMenuItem.Name = "mahnungsverwaltungToolStripMenuItem";
            this.mahnungsverwaltungToolStripMenuItem.Size = new System.Drawing.Size(135, 20);
            this.mahnungsverwaltungToolStripMenuItem.Text = "Mahnungsverwaltung";
            // 
            // hilfeToolStripMenuItem
            // 
            this.hilfeToolStripMenuItem.Name = "hilfeToolStripMenuItem";
            this.hilfeToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.hilfeToolStripMenuItem.Text = "Hilfe";
            // 
            // Bibliothek
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(833, 421);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimizeBox = false;
            this.Name = "Bibliothek";
            this.Text = "Bibliothek";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem beendenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem benutzerverwaltungToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem benutzerAnmeldenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem benutzerAbmeldenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem benutzerausweisVerlängernToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem medienverwaltungToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mahnungsverwaltungToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem hilfeToolStripMenuItem;
    }
}