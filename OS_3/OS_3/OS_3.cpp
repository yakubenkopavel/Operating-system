#include <iostream>
#include <Windows.h>

CRITICAL_SECTION cs;
HANDLE hEvent[2];
int size;
int k;
int mult;

void work(LPVOID arrays) {
    int time;
    int* arr = (int*)arrays;
    puts("\nВведите временной интервал: ");
    std::cin >> time;

    int j = 0;
    int temp = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            j = i + 1;
            while (j < size && arr[j] % 2 != 0) {
                j++;
            }
            
            if (j == size) {
                i = size;
            }
            else {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Sleep(time);
    }

    SetEvent(hEvent[0]);
}

void multElement(LPVOID arrays) {
    EnterCriticalSection(&cs);
    WaitForSingleObject(hEvent[1], INFINITE);
    int* arr = (int*)arrays;
    mult = 1;

    for (int i = 0; i < k; i++) {
        mult *= arr[i];
    }
    LeaveCriticalSection(&cs);


    WaitForSingleObject(hEvent[1], INFINITE);
    for (int i = k; i < size; i++) {
        mult *= arr[i];
    }
    std::cout << mult;
}


int main()
{
    setlocale(LC_ALL, "rus");

    HANDLE hThread[2];
    DWORD  IDThread[2];

    InitializeCriticalSection(&cs);
    hEvent[0] = CreateEventA(NULL, FALSE, FALSE, NULL);
    hEvent[1] = CreateEventA(NULL, FALSE, FALSE, NULL);
    if (hEvent[0] == NULL || hEvent[1] == NULL) {
        return GetLastError();
    }

    int* arrays;

    puts("Введите размерность: ");
    std::cin >> size;
    arrays = new int[size];

    puts("Введите элементы массива: ");
    for (int i = 0; i < size; i++) {
        std::cin >> arrays[i];
    }

    std::cout << "Размерность: "<< size << "\nЭлементы массива: ";
    for (int i = 0; i < size; i++) {
        std::cout << arrays[i] << " ";
    }


    hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, (void*) arrays, CREATE_SUSPENDED, &IDThread[0]);
    if (hThread[0] == NULL) {
        return GetLastError();
    }


    puts("\n\nВведите число k: ");
    std::cin >> k;
    if (k > size) {
        k = 1;
    }

    ResumeThread(hThread[0]);
    hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)multElement, (void*) arrays, 0, &IDThread[1]);
    if (hThread[1] == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(hEvent[0], INFINITE);
    std::cout << "\nЭлементы итогового массива: ";
    for (int i = 0; i < k; i++) {
        std::cout << arrays[i] << " ";
    }
    
    SetEvent(hEvent[1]);
    TryEnterCriticalSection(&cs);

    for (int i = k; i < size; i++) {
        std::cout << arrays[i] << " ";
    }

    std::cout << std::endl << "Main: " << mult << std::endl;
    SetEvent(hEvent[1]);
    LeaveCriticalSection(&cs);

    DeleteCriticalSection(&cs);

    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    CloseHandle(hEvent[0]);
    CloseHandle(hEvent[1]);

    delete[] arrays;
    return 0;
}
