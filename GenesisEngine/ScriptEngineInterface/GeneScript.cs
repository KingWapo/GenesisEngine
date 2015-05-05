using System;

public class GeneScript
{
    public GeneScript()
    {
        OnUpdate();
    }

    public virtual void OnStart()
    {

    }

    public virtual void OnUpdate()
    {
        Console.Write("Hello World\n");
    }
}