using System;

public class GeneScript : ScriptEngineInterface.IGeneScript
{
    public GeneScript()
    {

    }

    public virtual void OnStart()
    {

    }

    public virtual void OnUpdate()
    {
        Console.Write("Hello World\n");
    }
}