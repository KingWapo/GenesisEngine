namespace Genesis_Engine_UI
{
    partial class MainForm
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Scripts");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Assets", new System.Windows.Forms.TreeNode[] {
            treeNode1});
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fileBuildButton = new System.Windows.Forms.ToolStripMenuItem();
            this.fileBuildRunButton = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.fileQuitButton = new System.Windows.Forms.ToolStripMenuItem();
            this.scriptsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.scriptsNewButton = new System.Windows.Forms.ToolStripMenuItem();
            this.actorsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.actorsNewButton = new System.Windows.Forms.ToolStripMenuItem();
            this.scriptsSaveDialog = new System.Windows.Forms.SaveFileDialog();
            this.browseTreeView = new System.Windows.Forms.TreeView();
            this.buildSaveDialog = new System.Windows.Forms.SaveFileDialog();
            this.refreshButton = new System.Windows.Forms.Button();
            this.scenesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.scenesNewButton = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenuItem,
            this.scriptsMenuItem,
            this.actorsMenuItem,
            this.scenesToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(288, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            // 
            // fileMenuItem
            // 
            this.fileMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileBuildButton,
            this.fileBuildRunButton,
            this.toolStripSeparator1,
            this.fileQuitButton});
            this.fileMenuItem.Name = "fileMenuItem";
            this.fileMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileMenuItem.Text = "File";
            // 
            // fileBuildButton
            // 
            this.fileBuildButton.Name = "fileBuildButton";
            this.fileBuildButton.Size = new System.Drawing.Size(148, 22);
            this.fileBuildButton.Text = "Build";
            this.fileBuildButton.Click += new System.EventHandler(this.fileBuildButton_Click);
            // 
            // fileBuildRunButton
            // 
            this.fileBuildRunButton.Name = "fileBuildRunButton";
            this.fileBuildRunButton.Size = new System.Drawing.Size(148, 22);
            this.fileBuildRunButton.Text = "Build and Run";
            this.fileBuildRunButton.Click += new System.EventHandler(this.fileBuildRunButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(145, 6);
            // 
            // fileQuitButton
            // 
            this.fileQuitButton.Name = "fileQuitButton";
            this.fileQuitButton.Size = new System.Drawing.Size(148, 22);
            this.fileQuitButton.Text = "Quit";
            this.fileQuitButton.Click += new System.EventHandler(this.menuQuit_Click);
            // 
            // scriptsMenuItem
            // 
            this.scriptsMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.scriptsNewButton});
            this.scriptsMenuItem.Name = "scriptsMenuItem";
            this.scriptsMenuItem.Size = new System.Drawing.Size(54, 20);
            this.scriptsMenuItem.Text = "Scripts";
            // 
            // scriptsNewButton
            // 
            this.scriptsNewButton.Name = "scriptsNewButton";
            this.scriptsNewButton.Size = new System.Drawing.Size(98, 22);
            this.scriptsNewButton.Text = "New";
            this.scriptsNewButton.Click += new System.EventHandler(this.scriptsNewButton_Click);
            // 
            // actorsMenuItem
            // 
            this.actorsMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.actorsNewButton});
            this.actorsMenuItem.Name = "actorsMenuItem";
            this.actorsMenuItem.Size = new System.Drawing.Size(53, 20);
            this.actorsMenuItem.Text = "Actors";
            // 
            // actorsNewButton
            // 
            this.actorsNewButton.Name = "actorsNewButton";
            this.actorsNewButton.Size = new System.Drawing.Size(152, 22);
            this.actorsNewButton.Text = "New";
            this.actorsNewButton.Click += new System.EventHandler(this.actorsNewButton_Click);
            // 
            // scriptsSaveDialog
            // 
            this.scriptsSaveDialog.DefaultExt = "cs";
            this.scriptsSaveDialog.Filter = "C# Files|#.cs";
            // 
            // browseTreeView
            // 
            this.browseTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.browseTreeView.Location = new System.Drawing.Point(13, 54);
            this.browseTreeView.Name = "browseTreeView";
            treeNode1.Name = "scriptsNode";
            treeNode1.Text = "Scripts";
            treeNode2.Name = "assetsNode";
            treeNode2.Text = "Assets";
            this.browseTreeView.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2});
            this.browseTreeView.Size = new System.Drawing.Size(263, 296);
            this.browseTreeView.TabIndex = 1;
            this.browseTreeView.DoubleClick += new System.EventHandler(this.browseTreeView_DoubleClick);
            this.browseTreeView.KeyUp += new System.Windows.Forms.KeyEventHandler(this.browseTreeView_KeyUp);
            // 
            // buildSaveDialog
            // 
            this.buildSaveDialog.DefaultExt = "exe";
            this.buildSaveDialog.Filter = "Executable Files|*.exe";
            // 
            // refreshButton
            // 
            this.refreshButton.Location = new System.Drawing.Point(201, 27);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 23);
            this.refreshButton.TabIndex = 2;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseVisualStyleBackColor = true;
            this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
            // 
            // scenesToolStripMenuItem
            // 
            this.scenesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.scenesNewButton});
            this.scenesToolStripMenuItem.Name = "scenesToolStripMenuItem";
            this.scenesToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.scenesToolStripMenuItem.Text = "Scenes";
            // 
            // scenesNewButton
            // 
            this.scenesNewButton.Name = "scenesNewButton";
            this.scenesNewButton.Size = new System.Drawing.Size(152, 22);
            this.scenesNewButton.Text = "New";
            this.scenesNewButton.Click += new System.EventHandler(this.scenesNewButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(288, 362);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.browseTreeView);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "MainForm";
            this.Text = "Genesis Engine";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem fileQuitButton;
        private System.Windows.Forms.ToolStripMenuItem fileBuildRunButton;
        private System.Windows.Forms.ToolStripMenuItem scriptsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem scriptsNewButton;
        private System.Windows.Forms.SaveFileDialog scriptsSaveDialog;
        private System.Windows.Forms.TreeView browseTreeView;
        private System.Windows.Forms.ToolStripMenuItem fileBuildButton;
        private System.Windows.Forms.SaveFileDialog buildSaveDialog;
        private System.Windows.Forms.ToolStripMenuItem actorsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem actorsNewButton;
        private System.Windows.Forms.Button refreshButton;
        private System.Windows.Forms.ToolStripMenuItem scenesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem scenesNewButton;
    }
}

