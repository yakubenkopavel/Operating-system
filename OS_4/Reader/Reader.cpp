#include <iostream>
#include <conio.h>
#include <windows.h>


int main(int argc, char* argv[])
{
    HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE, TRUE, L"S");
    
    HANDLE h[2];
    h[0] = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"C");
    h[1] = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"D");
    HANDLE hR = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"R");

    WaitForMultipleObjects(2,h, TRUE, INFINITE);
    std::cout << "C ";
    std::cout << "D";

   
    ReleaseSemaphore(hSemaphore, 1, NULL);

    SetEvent(hR);

    _getch();

}
