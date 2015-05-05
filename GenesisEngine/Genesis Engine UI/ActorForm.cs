using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Genesis_Engine_UI
{
    public partial class ActorForm : Form
    {
        Actor actor;

        public ActorForm( Project project, Actor actor = null )
        {
            InitializeComponent();

            if( actor == null )
                actor = new Actor();

            this.actor = actor;

            nameTextBox.Text = actor.name;

            foreach( Sprite sprite in project.sprites )
                spriteComboBox.Items.Add(sprite.filename);

            if (actor.sprite.Length == 0)
                spriteComboBox.SelectedIndex = 0;
            else
            {
                int i = 0;
                foreach (object obj in spriteComboBox.Items)
                {
                    string str = obj.ToString();
                    if (str == actor.sprite)
                    {
                        spriteComboBox.SelectedIndex = i;
                        break;
                    }
                    i++;
                }
            }

            if (project.scripts.Count > 0)
            {
                foreach (Script script in project.scripts)
                    addScriptsComboBox.Items.Add(script.filename);
                addScriptsComboBox.SelectedIndex = 0;
            }
            else
                addScriptButton.Enabled = false;

            foreach(string str in actor.scripts)
                scriptsListBox.Items.Add(str);
        }

        private void ActorForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (actor.saved)
                return;

            DialogResult result = MessageBox.Show("Would you like to save your actor?", "Save?", MessageBoxButtons.YesNoCancel);
            if (result == System.Windows.Forms.DialogResult.Yes)
            {
                Save();   
            }
            else if (result == System.Windows.Forms.DialogResult.Cancel)
                e.Cancel = true;

        }

        private void nameTextBox_TextChanged(object sender, EventArgs e)
        {
            actor.name = nameTextBox.Text;
        }

        private void ActorForm_Paint(object sender, PaintEventArgs e)
        {
            Text = actor.name;
            if (!actor.saved)
                Text += "*";
        }

        private void ActorForm_KeyDown(object sender, KeyEventArgs e)
        {
            if( e.KeyCode == Keys.S && e.Control )
            {
                Save();
            }
        }

        void Save()
        {
            if (actor.hasPath)
                actor.Save();
            else
            {
                DialogResult result2 = saveDialog.ShowDialog();
                if (result2 == System.Windows.Forms.DialogResult.OK)
                {
                    actor.path = saveDialog.FileName;
                    actor.Save();
                }
            }
        }

        private void spriteComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (spriteComboBox.SelectedIndex == 0)
                actor.sprite = "";
            else
            {
                actor.sprite = spriteComboBox.SelectedItem.ToString();
            }
        }

        private void addScriptButton_Click(object sender, EventArgs e)
        {
            string str = addScriptsComboBox.SelectedItem.ToString();
            actor.AddScript(str);
            scriptsListBox.Items.Add(str);
        }

        private void scriptsListBox_KeyUp(object sender, KeyEventArgs e)
        {
            if( e.KeyCode == Keys.Delete )
            {
                actor.RemoveScript(scriptsListBox.SelectedIndex);

                scriptsListBox.Items.Clear();
                foreach (string str in actor.scripts)
                    scriptsListBox.Items.Add(str);
            }
        }
    }
}
