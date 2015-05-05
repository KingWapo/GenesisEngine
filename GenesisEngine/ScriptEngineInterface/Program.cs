using System;
using System.IO;
using System.Collections;
using Mono.CSharp;

namespace ScriptEngineInterface
{

    class Program
    {
        public static void processDirectory(string targetDirectory, Evaluator myEval, String[] exceptions)
        {
            //search directory for .cs files and read them in
            String[] fileNames = Directory.GetFiles(targetDirectory, "*.cs");

            //compile each .cs file that is read in and run its constructor
            foreach (string filePath in fileNames)
            {
                //read file from file path
                System.IO.StreamReader myFile = new System.IO.StreamReader(filePath);

                //create substring of file name from file path
                int fileNameIndex = filePath.IndexOf("\\") + 1;
                string fileName = filePath.Substring(fileNameIndex);

                //create substring of class name from file name
                int extIndex = fileName.IndexOf(".cs");
                string className = fileName.Substring(0, extIndex);

                //check list of exceptions. engine will not call the constructor for any classes in the exceptions array
                //this means that only the custom scripts are getting called, compiled and executed
                bool compileFlag = true;

                foreach (string exception in exceptions)
                {
                    if (className == exception)
                    {
                        compileFlag = false;
                    }
                }

                if (compileFlag)
                {
                    string myString = myFile.ReadToEnd();

                    myEval.Compile(myString);

                    myEval.Run(className + " obj = new " + className + "();");
                }              
            }
        }

        static void Main(string[] args)
        {
            String[] exceptions = { "Program", "AssemblyInfo" };

            Evaluator myEval = new Evaluator(new CompilerContext(new CompilerSettings(), new ConsoleReportPrinter()));

            processDirectory("../../../ScriptEngineInterface", myEval, exceptions);

            Console.ReadLine();
        }
    }
}
