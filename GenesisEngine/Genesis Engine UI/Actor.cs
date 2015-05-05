using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Genesis_Engine_UI
{
    public class Actor : Asset
    {
        public override Type type
        {
            get {
                return Type.ACTOR; 
            }
        }

        public Actor() : base("")
        {
            saved = hasPath = false;
        }

        public Actor( string path ) : base(path)
        {
            if (File.Exists(path))
            {
                saved = hasPath = true;

                StreamReader reader = new StreamReader(path);
                if(!reader.EndOfStream)
                    name = reader.ReadLine();
                if (!reader.EndOfStream)
                    sprite = reader.ReadLine();
                while(!reader.EndOfStream)
                {
                    string str = reader.ReadLine();

                    if (str.Length > 0)
                        AddScript(str);
                }
                reader.Close();
            }
            else
                saved = hasPath = false;
        }

        public bool hasPath { get; private set; }
        public bool saved { get; private set; }

        public bool Save()
        {
            if (!File.Exists(path))
                File.Create(path).Close();

            StreamWriter writer = new StreamWriter(path);

            writer.WriteLine(name);
            writer.WriteLine(sprite);

            foreach (string str in scripts)
                writer.WriteLine(str);

            writer.Close();

            saved = true;
            hasPath = true;
            return true;
        }

        public static string ValidateName( string name )
        {
            name = name.Trim();

            return name;
        }

        private string _name = "Actor";
        public string name
        {
            get
            {
                return _name;
            }
            set
            {
                value = ValidateName(value);

                if (_name == value)
                    return;

                _name = value;
                saved = false;
            }
        }

        private string _sprite = "";
        public string sprite
        {
            get
            {
                return _sprite;
            }
            set
            {
                if (_sprite == value)
                    return;

                _sprite = value;
                saved = false;
            }
        }

        private List<string> _scripts = new List<String>();
        public List<String> scripts
        {
            get
            {
                return _scripts;
            }
        }
        public void AddScript(string script)
        {
            scripts.Add(script);
            saved = false;
        }
        public void RemoveScript(int item)
        {
            if (item < 0 || item >= scripts.Count)
                return;
            scripts.RemoveAt(item);
        }
    }
}
