///////////////////////////////////////////////////////////////////////
//  spawnProc.cpp - Demonstrate Creation of a Child Process          //
//                                                                   //
//  Jim Fawcett, CSE691 - SW Modeling & Analysis, Fall 2000          //
///////////////////////////////////////////////////////////////////////
//  Note:                                                            //
//    Place execution image of program to run in same directory      //
//    as the execution image of this program.                        //
//                                                                   //
///////////////////////////////////////////////////////////////////////

#include <windows.h>  // GetCurrentThreadId(), CreateProcess(...)
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  cout << "\n Demonstrating CreateProcess "
       << "\n=============================\n";

  cout << "\n  my process ID = " << GetCurrentProcessId()
       << "\n  my thread ID  = " << GetCurrentThreadId() << endl;

  if(argc < 2) {
    cout << "\n  please enter the name of a program to execute, including .exe";
    return 1;
  }

  // Command line arguments:
  //   CreateProcess will pass a single C string containing one or more words
  //   to the spawned process.  Each word in the string will appear as one
  //   argument on the spawned process command line.

  char *pCL;
  if(argc < 3)
    pCL = "default argument";
  else
    pCL = argv[2];  // expect quoted string containing one or more words

  // arguments for create process:
  
  STARTUPINFO startInfo;          // establishes properties of child process
  PROCESS_INFORMATION procInfo;   // holds info returned from CreateProcess
  LPCTSTR appName                = argv[1];            // program to run
  LPTSTR  commandLine            = pCL;                // main's args
  LPSECURITY_ATTRIBUTES procSec  = NULL;               // default security
  LPSECURITY_ATTRIBUTES thrdSec  = NULL;               // default security
  BOOL inheritHandles            = FALSE;              // don't inherit hndls
  DWORD createFlags              = CREATE_NEW_CONSOLE; // make a console
  LPVOID environment             = NULL;               // caller's evironmt
  LPCTSTR currentPath            = NULL;               // default dir
  LPSTARTUPINFO pStartInfo       = &startInfo;         // set process style
  LPPROCESS_INFORMATION pPrInfo  = &procInfo;          // retrieve info
 
//
  string buildTitle = string("child process: ") += argv[1];
  GetStartupInfo(&startInfo);
  startInfo.lpTitle = (char*)buildTitle.c_str();
  startInfo.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
  startInfo.dwX     = 200;
  startInfo.dwY     = 250;
  startInfo.dwXSize = 600;
  startInfo.dwYSize = 300;

  cout << "\n  Attempting to start: " << argv[1] 
       << "\n  with arguments: " << pCL << endl;

  BOOL OK =
  CreateProcess(
    appName,commandLine,procSec,thrdSec,inheritHandles,
    createFlags,environment,currentPath,pStartInfo,pPrInfo
  );
  
  CloseHandle(procInfo.hThread);  // parent needs no access to child thread
  
  if(!OK) {
    cout << "\n failed to create process: " << appName << "\n\n";

  // ask system what type of error occurred

    DWORD errorCode = GetLastError();

  // map errorCode into a system defined error string
    
    DWORD dwFlags = 
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
    LPCVOID lpSource = NULL;
    DWORD dwMessageID = errorCode;
    DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
    LPSTR lpBuffer;
    DWORD nSize = 0;
    va_list *Arguments = NULL;

    FormatMessage(
      dwFlags,lpSource,dwMessageID,dwLanguageId, 
      (LPTSTR)&lpBuffer,nSize,Arguments
    );

    cout << "\n  error: ";
    if(lpBuffer)
      cout << lpBuffer << "\n  --- did you forget extension .exe?" << "\n\n";
    return 1;
  }
  
  cout << "\n\n";

  // wait for child process to terminate before terminating

  WaitForSingleObject(procInfo.hProcess,INFINITE);
  CloseHandle(procInfo.hProcess);

  return 0;
}
