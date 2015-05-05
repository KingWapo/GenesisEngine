using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace Genesis_Engine_UI
{
    public class Project
    {
        public string path { get; private set; }
        public bool valid { get; private set; }

        public static string engineFolder = "/Engine";
        public static string engineToCopyPath
        {
            get
            {
                return AppDomain.CurrentDomain.BaseDirectory + engineFolder;
            }
        }
        public static string engineExePath = "/GenesisEngine.exe";

        public static string scriptsFolder = "/Scripts";
        public string scriptsPath
        {
            get
            {
                return path + scriptsFolder;
            }
        }

        public static string spritesFolder = "/Textures";
        public string spritesPath
        {
            get
            {
                return path + spritesFolder;
            }
        }
        public static string[] spritesExtensions = { "*.png" };

        public static string actorsFolder = "/Actors";
        public string actorsPath
        {
            get
            {
                return path + actorsFolder;
            }
        }

        public List<Script> scripts { get; private set; }
        public List<Sprite> sprites { get; private set; }
        public List<Actor> actors { get; private set; }

        public Project( string path )
        {
            this.path = path;

            if (!Directory.Exists(path))
            {
                valid = false;
                return;
            }
            
            RefreshScripts();

            valid = true;
        }

        public void RefreshScripts()
        {
            if (scripts == null)
                scripts = new List<Script>();
            else
                scripts.Clear();

            if (Directory.Exists(scriptsPath))
            {
                string[] files = Directory.GetFiles(scriptsPath, "*.cs");
                foreach( string path in files )
                {
                    Script script = new Script(path);
                    if (script.valid)
                        scripts.Add(script);
                    else
                        Console.WriteLine("Failed to load script " + path);
                }
            }
            else
            {
                Directory.CreateDirectory(scriptsPath);
            }
        }

        public void RefreshSprites()
        {
            if (sprites == null)
                sprites = new List<Sprite>();
            else
                sprites.Clear();

            if (Directory.Exists(spritesPath))
            {
                foreach (string extension in spritesExtensions)
                {
                    string[] files = Directory.GetFiles(spritesPath, extension);
                    foreach (string path in files)
                    {
                        Sprite sprite = new Sprite(path);
                        if (sprite.valid)
                            sprites.Add(sprite);
                        else
                            Console.WriteLine("Failed to load sprite " + path);
                    }
                }
            }
            else
            {
                Directory.CreateDirectory(spritesPath);
            }
        }

        public void RefreshActors()
        {
            if (actors == null)
                actors = new List<Actor>();
            else
                actors.Clear();

            if (Directory.Exists(actorsPath))
            {
                string[] files = Directory.GetFiles(actorsPath, "*.actor");
                foreach (string path in files)
                {
                    Actor actor = new Actor(path);
                    if (actor.valid)
                        actors.Add(actor);
                    else
                        Console.WriteLine("Failed to load actor " + actor);
                }
            }
            else
            {
                Directory.CreateDirectory(actorsPath);
            }
        }

        public bool CreateScript( string filename )
        {
            string path = scriptsPath + "/" + filename;
            if (path.Substring(path.Length - 3) != ".cs")
                path += ".cs";
            if (File.Exists(path))
                return false;
            FileStream stream = File.Create(path);
            stream.Close();
            return true;
        }

        public bool Build( string exePath, bool run = false )
        {
            if (File.Exists(exePath))
                File.Delete(exePath);

            string path = exePath.Substring(0, exePath.LastIndexOf('\\'));
            if (!DirectoryCopy(engineToCopyPath, path, true))
                return false;
            if (!DirectoryCopy(scriptsPath, path + scriptsFolder, true))
                return false;
            if (!DirectoryCopy(spritesPath, path + spritesFolder, true))
                return false;

            File.Move(path + engineExePath, exePath);

            if (run)
            {
                System.Diagnostics.Process process = new System.Diagnostics.Process();
                process.StartInfo.FileName = exePath;
                process.StartInfo.WorkingDirectory = path;
                process.Start();
            }
            else
                System.Diagnostics.Process.Start(path);

            return true;
        }

        private static bool DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);
            DirectoryInfo[] dirs = dir.GetDirectories();

            if (!dir.Exists)
                return false;

            // If the destination directory doesn't exist, create it. 
            if (!Directory.Exists(destDirName))
                Directory.CreateDirectory(destDirName);

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, true);
            }

            // If copying subdirectories, copy them and their contents to new location. 
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }

            return true;
        }
    }
}
