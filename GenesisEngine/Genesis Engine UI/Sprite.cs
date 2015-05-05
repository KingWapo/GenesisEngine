using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Genesis_Engine_UI
{
    public class Sprite : Asset
    {
        public override Type type
        {
            get
            {
                return Type.SPRITE;
            }
        }

        public Sprite( string path ) : base (path)
        {

        }
    }
}
