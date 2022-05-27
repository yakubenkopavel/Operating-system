//#include <windows.h>
//#include <iostream>
//using namespace std;
//volatile int n;
//
//DWORD WINAPI Add(LPVOID iNum)
//{
//	cout << "Thread is started." << endl;
//	n = n + (int)iNum;
//	cout << "Thread is finished." << endl;
//	return 0;
//}
//
//
//int main()
//{
//	int inc = 10;
//	HANDLE hThread;
//	DWORD IDThread;
//	cout << "n = " << n << endl;
//
//
//	hThread = CreateThread(NULL, 0, Add, (void*)inc, 0, &IDThread);
//	if (hThread == NULL)
//		return GetLastError();
//
//	int count = SuspendThread(hThread);
//	std::cout << count << std::endl;
//
//	count = ResumeThread(hThread);
//	std::cout << count << std::endl;
//
//	// ждем пока поток Add закончит работу
//	//WaitForSingleObject(hThread, INFINITE);
//
//	// закрываем дескриптор потока
//	CloseHandle(hThread);
//	cout << "n = " << n << endl;
//	return 0;
//}