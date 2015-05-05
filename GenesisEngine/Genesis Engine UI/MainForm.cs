using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Genesis_Engine_UI
{
    public partial class MainForm : Form
    {
        public Project project { get; private set; }

        TreeNode scriptsNode, spritesNode, actorsNode;

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            // Show the form for creating/loading projects.
            ProjectWizardForm form = new ProjectWizardForm();
            form.ShowDialog();

            if( form.project == null )
            {
                MessageBox.Show("Failed to load project.");
                this.Close();
                return;
            }
            else
            {
                project = form.project;
            }

            // Initialize our browse tree.
            browseTreeView.Nodes.Clear();

            TreeNode root = new TreeNode("Assets");
            browseTreeView.Nodes.Add(root);

            scriptsNode = new TreeNode("Scripts");
            root.Nodes.Add(scriptsNode);

            spritesNode = new TreeNode("Sprites");
            root.Nodes.Add(spritesNode);

            actorsNode = new TreeNode("Actors");
            root.Nodes.Add(actorsNode);

            // Refresh assets, loading existing files and populating the tree view.
            RefreshAssets();
        }

        private void menuQuit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        void RefreshAssets()
        {
            RefreshScripts();
            RefreshSprites();
            RefreshActors();
        }

        void RefreshScripts()
        {
            project.RefreshScripts();

            scriptsNode.Nodes.Clear();
            foreach (Script script in project.scripts)
            {
                TreeNode node = new TreeNode(script.filename);
                node.Tag = script;
                scriptsNode.Nodes.Add(node);
            }
        }

        void RefreshSprites()
        {
            project.RefreshSprites();

            spritesNode.Nodes.Clear();
            foreach( Sprite sprite in project.sprites)
            {
                TreeNode node = new TreeNode(sprite.filename);
                node.Tag = sprite;
                spritesNode.Nodes.Add(node);
            }
        }

        void RefreshActors()
        {
            project.RefreshActors();

            actorsNode.Nodes.Clear();
            foreach( Actor actor in project.actors )
            {
                TreeNode node = new TreeNode(actor.filename);
                node.Tag = actor;
                actorsNode.Nodes.Add(node);
            }
        }

        private void browseTreeView_DoubleClick(object sender, EventArgs e)
        {
            TreeNode node = browseTreeView.SelectedNode;
            if (node == null || node.Tag == null)
                return;

            Asset asset = node.Tag as Asset;
            if (asset == null)
            {
                MessageBox.Show("Found something that wasn't an asset in the tree.");
                return;
            }

            // This is where we would differentiate what type of asset to open, but for now just open it in whatever the default is.
            switch( asset.type )
            {
                case Asset.Type.ACTOR:
                    ActorForm form = new ActorForm(project, asset as Actor);
                    form.Show();
                    break;
                default:
                    asset.Open();
                    break;
            }
        }

        private void scriptsNewButton_Click(object sender, EventArgs e)
        {
            ScriptNamingForm form = new ScriptNamingForm();
            form.ShowDialog();

            if (form.filename.Length > 0)
            {
                if (project.CreateScript(form.filename))
                    RefreshScripts();
                else
                    MessageBox.Show("Failed to create script.");
            }
        }

        private void browseTreeView_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                TreeNode node = browseTreeView.SelectedNode;
                if (node == null || node.Tag == null)
                    return;

                Asset asset = node.Tag as Asset;
                if (asset == null)
                {
                    MessageBox.Show("Found something that wasn't an asset in the tree.");
                    return;
                }

                asset.Delete();
                RefreshAssets();
            }
        }

        private void fileBuildButton_Click(object sender, EventArgs e)
        {
            DialogResult result = buildSaveDialog.ShowDialog();
            if (result != System.Windows.Forms.DialogResult.OK)
                return;

            project.Build(buildSaveDialog.FileName);
        }

        private void fileBuildRunButton_Click(object sender, EventArgs e)
        {
            DialogResult result = buildSaveDialog.ShowDialog();
            if (result != System.Windows.Forms.DialogResult.OK)
                return;

            project.Build(buildSaveDialog.FileName,true);
        }

        private void actorsNewButton_Click(object sender, EventArgs e)
        {
            ActorForm form = new ActorForm(project);
            form.Show();
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            RefreshAssets();
        }

        private void scenesNewButton_Click(object sender, EventArgs e)
        {
            SceneForm form = new SceneForm(project);
            form.Show();
        }
    }
}
