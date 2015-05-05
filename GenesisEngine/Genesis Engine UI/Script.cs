using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;

namespace Genesis_Engine_UI
{
    public class Script : Asset
    {
        public override Asset.Type type
        {
            get {
                return Type.SCRIPT;
            }
        }

        public Script( string path ) : base(path)
        {

        }
    }
}
