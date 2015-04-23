using System;
using Mono.CSharp;

namespace ScriptEngineInterface
{
    public interface IStringModifier { string modify(string s); }

    class Program
    {
        static void Main(string[] args)
        {
            Evaluator myEval = new Evaluator(
                new CompilerContext(new CompilerSettings(), new ConsoleReportPrinter()));

            myEval.ReferenceAssembly(typeof(IStringModifier).Assembly);
            myEval.Compile(
                @"
                 public class Upper : ScriptEngineInterface.IStringModifier
                {
                    public string modify(string s) { return s.ToUpper(); }
                }");

            Console.WriteLine("Mini Console\n");

            while (true)
            {
                Console.Write(">");
                string line = Console.ReadLine();
                if (line == null || line == "") break;

                object result;
                bool result_set;
                myEval.Evaluate(line, out result, out result_set);

                if (result_set) Console.WriteLine(result);
            }
        }
    }
}
