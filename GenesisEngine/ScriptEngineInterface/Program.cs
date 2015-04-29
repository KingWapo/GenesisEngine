using System;
using Mono.CSharp;

namespace ScriptEngineInterface
{
    public interface IStringModifier { string modify(string s); }
    public interface IGeneScript { void OnUpdate(); }

    class Program
    {
        static void Main(string[] args)
        {
            System.IO.StreamReader myFile = new System.IO.StreamReader("D:/Student Data/My Documents/Visual Studio 2013/Projects/GenesisEngine/GenesisEngine/ScriptEngineInterface/GeneScript.cs");
            string myString = myFile.ReadToEnd();

            Evaluator myEval = new Evaluator(
                new CompilerContext(new CompilerSettings(), new ConsoleReportPrinter()));

            myEval.ReferenceAssembly(typeof(IStringModifier).Assembly);
            myEval.Compile(myString);

            Console.WriteLine("Mini Console/n");

            while (true)
            {
                Console.Write(">");
                string line = Console.ReadLine();
                if (line == "@@") break;

                //object result;
                //bool result_set;
                myEval.Run(line);
                //myEval.Evaluate(line, out result, out result_set);

                //if (result_set) Console.WriteLine(result);
            }
        }
    }
}
