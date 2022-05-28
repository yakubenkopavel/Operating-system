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
	char* array1 = nullptr;
	__int8* array2 = nullptr;
	char* result = nullptr;
	int sizeResult;
	int sizeArray1 = 0;
	int sizeArray2 = 0;


	_cputs("Enter array dimension 1:\n");
	std::cin >> sizeArray1;
	array1 = new char[sizeArray1];
	_cputs("Enter elements(char) of array 1:\n");
	for (int i = 0; i < sizeArray1; i++) {
		std::cin >> array1[i];
	}

	_cputs("Enter array dimension 2:\n");
	std::cin >> sizeArray2;
	array2 = new __int8[sizeArray2];
	_cputs("Enter elements(__int8) of array 2:\n");
	for (int i = 0; i < sizeArray2; i++) {
		std::cin >> array2[i];
	}


	TCHAR nameChild[] = _T("search.exe");
	TCHAR nameChild1[] = _T("Controler.exe");
	std::string line = "C ";
	TCHAR* commandLine;

	HANDLE hEnableRead;
	HANDLE hEnableRead1;
	HANDLE hEnableRead2;

	DWORD dwBytesRead;
	DWORD dwBytesWritten;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;

	
	hEnableRead = CreateEvent(NULL, FALSE, FALSE, L"EnableRead");
	hEnableRead1 = CreateEvent(NULL, FALSE, FALSE, L"EnableRead1");
	hEnableRead2 = CreateEvent(NULL, FALSE, FALSE, L"EnableRead2");


	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;		
	sa.bInheritHandle = TRUE;		

	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
	{
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	line += std::to_string((int)hWritePipe) + " " + std::to_string((int)hReadPipe);
	commandLine = new TCHAR[line.size() + 1];
	std::copy(line.begin(), line.end(), commandLine);

	
	if (!CreateProcess(nameChild, commandLine, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		_cputs("The new process is not created.\n");
		return 0;
	}

	if (!WriteFile(
		hWritePipe,
		&sizeArray1,
		sizeof(sizeArray1),
		&dwBytesWritten,
		NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	for (int i = 0; i < sizeArray1; i++) {
		if (!WriteFile(
			hWritePipe,
			&array1[i],
			sizeof(array1[i]),
			&dwBytesWritten,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	if (!WriteFile(
		hWritePipe,
		&sizeArray2,
		sizeof(sizeArray2),
		&dwBytesWritten,
		NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	for (int i = 0; i < sizeArray2; i++) {
		if (!WriteFile(
			hWritePipe,
			&array2[i],
			sizeof(array2[i]),
			&dwBytesWritten,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	SetEvent(hEnableRead);

	WaitForSingleObject(hEnableRead1, INFINITE);

	if (!ReadFile(
		hReadPipe,
		&sizeResult,
		sizeof(sizeArray1),
		&dwBytesRead,
		NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	std::cout << "Result array size: " << sizeResult << std::endl << "Result array elements: ";
	result = new char[sizeResult];
	for (int i = 0; i < sizeResult; i++) {
		if (!ReadFile(
			hReadPipe,
			&result[i],
			sizeof(result[i]),
			&dwBytesRead,
			NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;

	if (!CreateProcess(nameChild1, commandLine, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		_cputs("The new process is not created.\n");
		return 0;
	}
	
	if (!WriteFile(
		hWritePipe,
		&sizeArray1,
		sizeof(sizeArray1),
		&dwBytesWritten,
		NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	for (int i = 0; i < sizeArray1; i++) {
		if (!WriteFile(
			hWritePipe,
			&array1[i],
			sizeof(array1[i]),
			&dwBytesWritten,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	if (!WriteFile(
		hWritePipe,
		&sizeArray2,
		sizeof(sizeArray2),
		&dwBytesWritten,
		NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	for (int i = 0; i < sizeArray2; i++) {
		if (!WriteFile(
			hWritePipe,
			&array2[i],
			sizeof(array2[i]),
			&dwBytesWritten,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}

	if (!WriteFile(
		hWritePipe,
		&sizeResult,
		sizeof(sizeResult),
		&dwBytesWritten,
		NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	for (int i = 0; i < sizeResult; i++) {
		if (!WriteFile(
			hWritePipe,
			&result[i],
			sizeof(result[i]),
			&dwBytesWritten,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	SetEvent(hEnableRead2);
	
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableRead1);
	CloseHandle(hEnableRead2);

	
	_getch();

	delete[] result;
	delete[] array1;
	delete[] array2;

	return 0;
}


