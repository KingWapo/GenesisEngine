namespace Genesis_Engine_UI
{
    partial class ActorForm
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
            this.nameLabel = new System.Windows.Forms.Label();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.saveDialog = new System.Windows.Forms.SaveFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.spriteComboBox = new System.Windows.Forms.ComboBox();
            this.scriptsGroup = new System.Windows.Forms.GroupBox();
            this.scriptsListBox = new System.Windows.Forms.ListBox();
            this.addScriptButton = new System.Windows.Forms.Button();
            this.addScriptsComboBox = new System.Windows.Forms.ComboBox();
            this.scriptsGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(13, 13);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(38, 13);
            this.nameLabel.TabIndex = 0;
            this.nameLabel.Text = "Name:";
            // 
            // nameTextBox
            // 
            this.nameTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.nameTextBox.Location = new System.Drawing.Point(57, 10);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(215, 20);
            this.nameTextBox.TabIndex = 1;
            this.nameTextBox.Text = "Actor";
            this.nameTextBox.TextChanged += new System.EventHandler(this.nameTextBox_TextChanged);
            this.nameTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ActorForm_KeyDown);
            // 
            // saveDialog
            // 
            this.saveDialog.DefaultExt = "actor";
            this.saveDialog.Filter = "Actor|*.actor";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 39);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Sprite:";
            // 
            // spriteComboBox
            // 
            this.spriteComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.spriteComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.spriteComboBox.FormattingEnabled = true;
            this.spriteComboBox.Items.AddRange(new object[] {
            "None"});
            this.spriteComboBox.Location = new System.Drawing.Point(57, 36);
            this.spriteComboBox.Name = "spriteComboBox";
            this.spriteComboBox.Size = new System.Drawing.Size(215, 21);
            this.spriteComboBox.TabIndex = 3;
            this.spriteComboBox.SelectedIndexChanged += new System.EventHandler(this.spriteComboBox_SelectedIndexChanged);
            // 
            // scriptsGroup
            // 
            this.scriptsGroup.Controls.Add(this.scriptsListBox);
            this.scriptsGroup.Controls.Add(this.addScriptButton);
            this.scriptsGroup.Controls.Add(this.addScriptsComboBox);
            this.scriptsGroup.Location = new System.Drawing.Point(12, 63);
            this.scriptsGroup.Name = "scriptsGroup";
            this.scriptsGroup.Size = new System.Drawing.Size(260, 187);
            this.scriptsGroup.TabIndex = 4;
            this.scriptsGroup.TabStop = false;
            this.scriptsGroup.Text = "Scripts";
            // 
            // scriptsListBox
            // 
            this.scriptsListBox.FormattingEnabled = true;
            this.scriptsListBox.Location = new System.Drawing.Point(6, 47);
            this.scriptsListBox.Name = "scriptsListBox";
            this.scriptsListBox.Size = new System.Drawing.Size(248, 134);
            this.scriptsListBox.TabIndex = 2;
            this.scriptsListBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.scriptsListBox_KeyUp);
            // 
            // addScriptButton
            // 
            this.addScriptButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.addScriptButton.Location = new System.Drawing.Point(179, 17);
            this.addScriptButton.Name = "addScriptButton";
            this.addScriptButton.Size = new System.Drawing.Size(75, 23);
            this.addScriptButton.TabIndex = 1;
            this.addScriptButton.Text = "Add";
            this.addScriptButton.UseVisualStyleBackColor = true;
            this.addScriptButton.Click += new System.EventHandler(this.addScriptButton_Click);
            // 
            // addScriptsComboBox
            // 
            this.addScriptsComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addScriptsComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.addScriptsComboBox.FormattingEnabled = true;
            this.addScriptsComboBox.Location = new System.Drawing.Point(6, 19);
            this.addScriptsComboBox.Name = "addScriptsComboBox";
            this.addScriptsComboBox.Size = new System.Drawing.Size(167, 21);
            this.addScriptsComboBox.TabIndex = 0;
            // 
            // ActorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.scriptsGroup);
            this.Controls.Add(this.spriteComboBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nameTextBox);
            this.Controls.Add(this.nameLabel);
            this.Name = "ActorForm";
            this.Text = "Actor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ActorForm_FormClosing);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ActorForm_Paint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ActorForm_KeyDown);
            this.scriptsGroup.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.SaveFileDialog saveDialog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox spriteComboBox;
        private System.Windows.Forms.GroupBox scriptsGroup;
        private System.Windows.Forms.ListBox scriptsListBox;
        private System.Windows.Forms.Button addScriptButton;
        private System.Windows.Forms.ComboBox addScriptsComboBox;
    }
}