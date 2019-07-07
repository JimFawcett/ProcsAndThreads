/////////////////////////////////////////////////////////////////////
// SimpleApp.cs  -  Will be run as a child process by ProcDemo     //
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

namespace simpleConsoleApp
{
  class simpleApp
  {
    [STAThread]
    static void Main(string[] args)
    {
      Console.Write("\n  Child Process ");
      Console.Write("\n ===============\n");

      Process myProc = Process.GetCurrentProcess();
      Console.Write("\n  Process Name = {0}",myProc.ProcessName);
      Console.Write("\n  Main Module  = {0}",myProc.MainModule);
      Console.Write("\n  File Name    = {0}",myProc.MainModule.FileName);

      Console.Write("\n\n  my arguments are:");
      foreach(string arg in args)
        Console.Write("\n    {0}",arg);

      Console.Write("\n\nPress key to exit: ");
      Console.ReadKey();
    }
  }
}
