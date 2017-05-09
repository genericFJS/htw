namespace prakt8 {
    partial class MainForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.title = new System.Windows.Forms.Label();
            this.combo_beruf = new System.Windows.Forms.ComboBox();
            this.combo_auto = new System.Windows.Forms.ComboBox();
            this.label_beruf = new System.Windows.Forms.Label();
            this.blinkLabel1 = new prakt8.BlinkLabel();
            this.label_auto = new System.Windows.Forms.Label();
            this.label_eignung = new System.Windows.Forms.Label();
            this.eignungResult = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // title
            // 
            this.title.AutoSize = true;
            this.title.BackColor = System.Drawing.Color.ForestGreen;
            this.title.Font = new System.Drawing.Font("Arial", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.title.Location = new System.Drawing.Point(12, 33);
            this.title.Name = "title";
            this.title.Padding = new System.Windows.Forms.Padding(20, 5, 5, 5);
            this.title.Size = new System.Drawing.Size(366, 66);
            this.title.TabIndex = 0;
            this.title.Text = "MyPartner 2.0";
            this.title.Click += new System.EventHandler(this.label1_Click);
            // 
            // combo_beruf
            // 
            this.combo_beruf.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.combo_beruf.FormattingEnabled = true;
            this.combo_beruf.Items.AddRange(new object[] {
            "Mathematiker",
            "Informatiker",
            "Arzt"});
            this.combo_beruf.Location = new System.Drawing.Point(12, 126);
            this.combo_beruf.Name = "combo_beruf";
            this.combo_beruf.Size = new System.Drawing.Size(366, 21);
            this.combo_beruf.TabIndex = 1;
            this.combo_beruf.SelectedIndexChanged += new System.EventHandler(this.comboSelectedIndexChanged);
            // 
            // combo_auto
            // 
            this.combo_auto.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.combo_auto.FormattingEnabled = true;
            this.combo_auto.Items.AddRange(new object[] {
            "Trabbi",
            "Citroen",
            "Ferrari"});
            this.combo_auto.Location = new System.Drawing.Point(12, 169);
            this.combo_auto.Name = "combo_auto";
            this.combo_auto.Size = new System.Drawing.Size(366, 21);
            this.combo_auto.TabIndex = 2;
            this.combo_auto.SelectedIndexChanged += new System.EventHandler(this.comboSelectedIndexChanged);
            // 
            // label_beruf
            // 
            this.label_beruf.AutoSize = true;
            this.label_beruf.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_beruf.Location = new System.Drawing.Point(12, 107);
            this.label_beruf.Name = "label_beruf";
            this.label_beruf.Size = new System.Drawing.Size(42, 16);
            this.label_beruf.TabIndex = 3;
            this.label_beruf.Text = "Beruf:";
            // 
            // blinkLabel1
            // 
            this.blinkLabel1.AutoSize = true;
            this.blinkLabel1.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.blinkLabel1.Location = new System.Drawing.Point(13, 13);
            this.blinkLabel1.Name = "blinkLabel1";
            this.blinkLabel1.Size = new System.Drawing.Size(281, 16);
            this.blinkLabel1.TabIndex = 4;
            this.blinkLabel1.Text = "Finde deinen Traumpartner im Null-Komma-Nix!";
            this.blinkLabel1.Click += new System.EventHandler(this.blinkLabel1_Click);
            // 
            // label_auto
            // 
            this.label_auto.AutoSize = true;
            this.label_auto.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_auto.Location = new System.Drawing.Point(12, 150);
            this.label_auto.Name = "label_auto";
            this.label_auto.Size = new System.Drawing.Size(39, 16);
            this.label_auto.TabIndex = 5;
            this.label_auto.Text = "Auto:";
            // 
            // label_eignung
            // 
            this.label_eignung.AutoSize = true;
            this.label_eignung.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_eignung.Location = new System.Drawing.Point(12, 193);
            this.label_eignung.Name = "label_eignung";
            this.label_eignung.Size = new System.Drawing.Size(59, 16);
            this.label_eignung.TabIndex = 6;
            this.label_eignung.Text = "Eignung:";
            // 
            // eignungResult
            // 
            this.eignungResult.AutoSize = true;
            this.eignungResult.Font = new System.Drawing.Font("Arial", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.eignungResult.Location = new System.Drawing.Point(12, 209);
            this.eignungResult.Name = "eignungResult";
            this.eignungResult.Size = new System.Drawing.Size(43, 22);
            this.eignungResult.TabIndex = 7;
            this.eignungResult.Text = "???";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(390, 242);
            this.Controls.Add(this.eignungResult);
            this.Controls.Add(this.label_eignung);
            this.Controls.Add(this.label_auto);
            this.Controls.Add(this.blinkLabel1);
            this.Controls.Add(this.label_beruf);
            this.Controls.Add(this.combo_auto);
            this.Controls.Add(this.combo_beruf);
            this.Controls.Add(this.title);
            this.Name = "MainForm";
            this.Text = "MyPartner 2.0";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label title;
        private System.Windows.Forms.ComboBox combo_beruf;
        private System.Windows.Forms.ComboBox combo_auto;
        private System.Windows.Forms.Label label_beruf;
        private BlinkLabel blinkLabel1;
        private System.Windows.Forms.Label label_auto;
        private System.Windows.Forms.Label label_eignung;
        private System.Windows.Forms.Label eignungResult;
    }
}

