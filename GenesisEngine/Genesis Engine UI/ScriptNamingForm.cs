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
    public partial class ScriptNamingForm : Form
    {
        public string filename
        {
            get
            {
                return txtFilename.Text;
            }
        }

        public ScriptNamingForm()
        {
            InitializeComponent();
        }

        private void btnCreate_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            txtFilename.Text = "";
            this.Close();
        }
    }
}
