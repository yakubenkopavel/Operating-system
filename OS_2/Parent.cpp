#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>


int main()
{
    TCHAR nameChild[] = _T("Child.exe");
    TCHAR* commandLine = nullptr;
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;
    std::string line;
    std::string size;

    std::cout << "Enter array size: ";
    std::getline(std::cin, size);
    std::cout << "Enter array elements: ";
    std::getline(std::cin, line);

    line = size + " " + line;
    commandLine = new TCHAR[line.size() + 1];
    std::copy(line.begin(), line.end(), commandLine);


    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USECOUNTCHARS;
    si.dwYCountChars = 100;

    if (!CreateProcess(nameChild, commandLine, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
    {
        std::cout << "The new process is not created.\n";
        return 0;
    }

    WaitForSingleObject(piApp.hProcess, INFINITE);

    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    delete[] commandLine;
    return 0;
}