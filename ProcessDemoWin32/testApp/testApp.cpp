///////////////////////////////////////////////////////////////////////////
//  testApp.cpp - will become a child process spawned by spawnProc.exe   //
//                                                                       //
//  Jim Fawcett, CSE691 - Software Modeling & Analysis, Fall 2001        //
///////////////////////////////////////////////////////////////////////////

#include <windows.h>    // GetCurrentThreadID(), GetCurrentProcessId()
#include <iostream>
#include <conio.h>
using namespace std;

int main(int argc, char *argv[]) {

  cout << "\n  Child Application "
       << "\n ===================\n";
  
  const int bufferSize = 256;
  char namebuffer[bufferSize];
  if(GetModuleFileName(NULL,namebuffer,bufferSize))
    cout << "\n  my name       = " << namebuffer;

  cout << "\n  my process ID = " << GetCurrentProcessId()
       << "\n  my thread ID  = " << GetCurrentThreadId() << endl;
  
  cout << "\n    number of arguments = " << argc
       << "\n    my arguments are: ";

  int i;
  for(i=0; i<argc; i++)
    cout << argv[i] << ", ";
  cout << "\n";

  cout << "\n  press a key to finish: ";
  cout.flush();
  int ch = getche();
  cout << "\n\n";
  return 0;
}