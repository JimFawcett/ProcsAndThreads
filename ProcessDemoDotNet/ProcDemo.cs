/////////////////////////////////////////////////////////////////////
// ProcDemo.cs  -  Demonstrates creation of child process          //
//                                                                 //
// Language:    C#, version 1.0                                    //
// Platform:    Dell Inspiron 8100, Win2000, SP2                   //
// Application: CSE681 - SW Modeling & Analysis, Fall 2002         //
// Author:      Jim Fawcett, CST 2-187, Syracuse University        //
//              (315) 443-3948, jfawcett@twcny.rr.com              //
/////////////////////////////////////////////////////////////////////
///
using System;
using System.Diagnostics;

namespace ProcessDemo
{
  class ProcDemo
  {
    [STAThread]
    static void Main(string[] args)
    {
      Console.Write("\n  Parent Process ");
      Console.Write("\n ================\n");

      // get information about this process
      
      Process myProc = Process.GetCurrentProcess();
      Console.Write("\n  Process Name = {0}",myProc.ProcessName);
      Console.Write("\n  Main Module  = {0}",myProc.MainModule);
      Console.Write("\n  File Name    = {0}",myProc.MainModule.FileName);

      // start a child process

      try
      {
        string fileToStart 
          = "../../SimpleConsoleApp/bin/debug/SimpleConsoleApp.exe";
        string arguments = "FirstArg SecondArg ThirdArg";
        Console.Write("\n\n  Setting Arguments for child process: {0}",arguments);

        Process p = new Process();

     //////////////////////////////////////////////////////////////////////
     // remove comments to capture child standard output in this process
     //////////////////////////////////////////////////////////////////////
        p.StartInfo.UseShellExecute = false;  // don't show console
        p.StartInfo.RedirectStandardOutput = true;
       
        p.StartInfo.FileName = fileToStart;
        p.StartInfo.Arguments = arguments;
        if (p.Start())
          Console.Write("\n  process started - press key to see output\n");
        else
          Console.Write("\n  process failed to start\n");

     //////////////////////////////////////////////////////////////////////
        string output = p.StandardOutput.ReadToEnd();
        p.WaitForExit();
        Console.Write("\n\n  child output is:\n\n  {0}", output);
      }
      catch(Exception ex)
      {
        Console.Write("\n\n  {0}\n\n",ex.Message);
      }
      finally
      {
        Console.Write("\n\n");
      }
    }
  }
}
