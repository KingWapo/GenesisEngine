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
    public partial class SceneForm : Form
    {
        Project project;

        public SceneForm( Project project )
        {
            InitializeComponent();

            this.project = project;

            UpdatePrefabsList();
        }

        void UpdatePrefabsList()
        {
            lstPrefabs.Items.Clear();

            foreach( Actor actor in project.actors )
                lstPrefabs.Items.Add(actor.name);
        }
    }
}
