#include <iostream>
#include <windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	int sizeArray1;
	int sizeArray2;
	int sizeResult = 0;
	char* result;
	char* array1 = nullptr;
	__int8* array2 = nullptr;

	DWORD dwBytesRead;
	DWORD dwBytesWritten;

	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead, hEnableRead1;

	
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"EnableRead");
	hEnableRead1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"EnableRead1");

	
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	

	
	WaitForSingleObject(hEnableRead, INFINITE);
	
	
	if (!ReadFile(
		hReadPipe,
		&sizeArray1,
		sizeof(sizeArray1),
		&dwBytesRead,
		NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	std::cout << "Size array1: " << sizeArray1 <<std::endl<< "Elements array1: ";
	array1 = new char[sizeArray1];
	for (int i = 0; i < sizeArray1; i++) {
		if (!ReadFile(
			hReadPipe,
			&array1[i],
			sizeof(array1[i]),
			&dwBytesRead,
			NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		std::cout << array1[i] << " ";
	}
	std::cout << std::endl;


	if (!ReadFile(
		hReadPipe,
		&sizeArray2,
		sizeof(sizeArray2),
		&dwBytesRead,
		NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	std::cout << "Size array2: " << sizeArray2 << std::endl<< "Elements array2: ";
	array2 = new __int8[sizeArray2];
	for (int i = 0; i < sizeArray2; i++) {
		if (!ReadFile(
			hReadPipe,
			&array2[i],
			sizeof(array2[i]),
			&dwBytesRead,
			NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		std::cout << array2[i] << " ";
	}
	std::cout << std::endl;


	if (sizeArray1 > sizeArray2) {
		result = new char[sizeArray1];
	}
	else {
		result = new char[sizeArray2];
	}

	for (int i = 0; i < sizeArray1; i++) {
		for (int j = 0; j < sizeArray2; j++) {
			if (array1[i] == array2[j]) {
				result[sizeResult] = array1[i];
				sizeResult++;
				break;
			}
		}
	}

	std::cout << "Result array size: " << sizeResult << std::endl << "Result array elements: ";
	for (int i = 0; i < sizeResult; i++) {
		std::cout << result[i] << " " << std::endl;
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
	SetEvent(hEnableRead1);


	_getch();

	
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableRead1);

	delete[] result;
	delete[] array1;
	delete[] array2;

	return 0;
}

