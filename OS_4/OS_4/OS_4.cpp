#include <iostream>
#include <string>
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "");

    HANDLE hA = CreateEvent(NULL, FALSE, FALSE, L"A");
    HANDLE hB = CreateEvent(NULL, FALSE, FALSE, L"B");
    HANDLE hC = CreateEvent(NULL, FALSE, FALSE, L"C");
    HANDLE hD = CreateEvent(NULL, FALSE, FALSE, L"D");
    HANDLE hR = CreateEvent(NULL, FALSE, FALSE, L"R");
    HANDLE hW = CreateEvent(NULL, FALSE, FALSE, L"W");
    HANDLE hSemaphore;
    HANDLE hMutex;
    HANDLE mas[2];

    TCHAR nameReader[] = L"Reader.exe";
    TCHAR nameWriter[] = L"Writer.exe";

    int countProcess;
    int messages;
    std::cout << "Введите количество процессов: " << std::endl;
    std::cin >> countProcess;
    std::cout << "Введите количество отправленных и принятых сообщений: " << std::endl;
    std::cin >> messages;

    hSemaphore = CreateSemaphore(NULL, 0, 2, L"S");
    hMutex = CreateMutex(NULL, FALSE, L"Mutex");

    STARTUPINFO si;
    PROCESS_INFORMATION* piApp = new PROCESS_INFORMATION[countProcess];
    HANDLE* pi = new HANDLE[countProcess];

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USECOUNTCHARS;
    si.dwYCountChars = 100;

    for (int i = 0; i < countProcess; i++) {
        if (!CreateProcess(nameReader, NULL, NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp[i]))
        {
            std::cout << "The new process is not created.\n";
            return 0;
        }


        if (!CreateProcess(nameWriter, NULL, NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp[i]))
        {
            std::cout << "The new process is not created.\n";
            return 0;
        }

        pi[i] = piApp[i].hProcess;
    }

    for (int i = 0; i < countProcess; i++) {
        mas[0] = hA;
        mas[1] = hB;
        DWORD dw = WaitForMultipleObjects(2, mas, FALSE, INFINITE);
        if (dw == WAIT_OBJECT_0 + 0) {
            std::cout << "A ";
        }
        else {
            std::cout << "B";
        }

        SetEvent(hC);
        SetEvent(hD);
        WaitForSingleObject(hR, INFINITE);
    }




    WaitForMultipleObjects(countProcess, pi, TRUE, INFINITE);

    CloseHandle(hMutex);
    CloseHandle(hSemaphore);

    for (int i = 0; i < 2; i++) {
        CloseHandle(mas[i]);
    }

    for (int i = 0; i < countProcess; i++) {
        CloseHandle(piApp[i].hThread);
        CloseHandle(piApp[i].hProcess);
    }

    return 0;
}