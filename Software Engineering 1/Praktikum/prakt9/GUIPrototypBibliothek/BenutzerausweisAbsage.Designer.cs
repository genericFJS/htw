namespace GUIPrototypBibliothek
{
    partial class BenutzerausweisAbsage
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
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.cmdAbsageDrucken = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this._txtGueltigkeit = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this._txtAusgestellt = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Benutzernummer: ";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(208, 132);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(212, 23);
            this.button1.TabIndex = 8;
            this.button1.Text = "Benutzerausweis drucken";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // cmdAbsageDrucken
            // 
            this.cmdAbsageDrucken.Location = new System.Drawing.Point(90, 132);
            this.cmdAbsageDrucken.Name = "cmdAbsageDrucken";
            this.cmdAbsageDrucken.Size = new System.Drawing.Size(112, 23);
            this.cmdAbsageDrucken.TabIndex = 9;
            this.cmdAbsageDrucken.Text = "Absage drucken";
            this.cmdAbsageDrucken.UseVisualStyleBackColor = true;
            this.cmdAbsageDrucken.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox1
            // 
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Location = new System.Drawing.Point(132, 9);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(288, 13);
            this.textBox1.TabIndex = 10;
            this.textBox1.Text = "1001";
            // 
            // textBox2
            // 
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox2.Location = new System.Drawing.Point(132, 35);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(288, 13);
            this.textBox2.TabIndex = 10;
            this.textBox2.Text = "Mustermann";
            // 
            // textBox3
            // 
            this.textBox3.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox3.Location = new System.Drawing.Point(132, 61);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(288, 13);
            this.textBox3.TabIndex = 10;
            this.textBox3.Text = "Erika";
            // 
            // _txtGueltigkeit
            // 
            this._txtGueltigkeit.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this._txtGueltigkeit.Location = new System.Drawing.Point(132, 87);
            this._txtGueltigkeit.Name = "_txtGueltigkeit";
            this._txtGueltigkeit.Size = new System.Drawing.Size(288, 13);
            this._txtGueltigkeit.TabIndex = 10;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Name:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 61);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Vorname(n):";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 87);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Gültigkeit:";
            // 
            // _txtAusgestellt
            // 
            this._txtAusgestellt.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this._txtAusgestellt.Location = new System.Drawing.Point(132, 113);
            this._txtAusgestellt.Name = "_txtAusgestellt";
            this._txtAusgestellt.Size = new System.Drawing.Size(288, 13);
            this._txtAusgestellt.TabIndex = 10;
            this._txtAusgestellt.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 113);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(61, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Ausgestellt:";
            // 
            // BenutzerausweisAbsage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(430, 164);
            this.Controls.Add(this._txtAusgestellt);
            this.Controls.Add(this._txtGueltigkeit);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.cmdAbsageDrucken);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BenutzerausweisAbsage";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "BenutzerausweisAbsage";
            this.Load += new System.EventHandler(this.BenutzerausweisAbsage_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button cmdAbsageDrucken;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox _txtGueltigkeit;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox _txtAusgestellt;
        private System.Windows.Forms.Label label5;
    }
}