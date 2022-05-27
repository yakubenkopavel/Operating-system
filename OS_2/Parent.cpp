#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#include <errno.h>
#include <string>


int main()
{
    TCHAR nameChild[] = _T("Child.exe");

    std::string line;
    std::getline(std::cin, line);

    TCHAR* commandLine = new TCHAR[line.size() + 1];
    std::copy(line.begin(), line.end(), commandLine);

    STARTUPINFO si;
    PROCESS_INFORMATION piApp;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USECOUNTCHARS;
    si.dwYCountChars = 100;

    if (!CreateProcess(nameChild, commandLine, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
    {
        _cputs("The new process is not created.\n");
        return 0;
    }

    WaitForSingleObject(piApp.hProcess, INFINITE);

    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    return 0;
}