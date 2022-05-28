#include <iostream>
#include <conio.h>
#include <windows.h>


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"Mutex");
    HANDLE hA = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"A");
    HANDLE hB = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"B");
    HANDLE hW = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"W");

    WaitForSingleObject(hMutex, INFINITE);
    char str;
    std::cout << "Введите А или В: ";
    std::cin >> str;

    if (str == 'A') {
        SetEvent(hA);
    }
    else {
        SetEvent(hB);
    }
    SetEvent(hW);

    ReleaseMutex(hMutex);


    _getch();

}
