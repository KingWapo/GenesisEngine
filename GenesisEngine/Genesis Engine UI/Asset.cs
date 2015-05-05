using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace Genesis_Engine_UI
{
    public abstract class Asset
    {
        public enum Type
        {
            ASSET,
            SCRIPT,
            SPRITE,
            ACTOR
        }
        public abstract Type type
        {
            get;
        }

        private string _path = "";
        public string path { 
            get
            {
                return _path;
            }
            set
            {
                _path = value;
            }
        }
        public string filename
        {
            get
            {
                if (valid)
                    return path.Substring(path.LastIndexOf('\\')+1);
                else
                    return "";
            }
        }
        public bool valid
        {
            get
            {
                return File.Exists(path);
            }
        }

        public Asset( string path )
        {
            this.path = path;
        }

        public void Open()
        {
            if (valid)
                System.Diagnostics.Process.Start(path);
            else
                MessageBox.Show("Failed to open file.");
        }

        public bool Delete()
        {
            if (valid)
                File.Delete(path);
            else
                return false;
            return true;
        }
    }
}
