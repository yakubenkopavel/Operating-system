#include <windows.h>
#include <iostream>
#include <conio.h>

wchar_t pipeName[] = L"\\\\WIN-6VC9URVTCAN\\pipe\\ipctest";
using namespace std;

int main()
{
	char 	c;			// служебный
	int sizeArray1;
	int sizeArray2;
	int sizeResult = 0;
	char* result = nullptr;
	char* array1 = nullptr;
	__int8* array2 = nullptr;


	HANDLE 	hNamedPipe;
	char 	lpszInMessage[80];		// для сообщения от клиента
	DWORD 	dwBytesRead;				// для числа прочитанных байт
	char 	lpszOutMessage[] = "The server has received a message."; // обратное сообщение
	DWORD 	dwBytesWrite;				// для числа записанных байт

	
	hNamedPipe = CreateNamedPipeA(
		"\\\\.\\pipe\\demo_pipe",	// имя канала
		PIPE_ACCESS_DUPLEX,		// читаем из канала и пишем в канал
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	// синхронная передача сообщений
		1,		// максимальное количество экземпляров канала 
		0,		// размер выходного буфера по умолчанию
		0,		// размер входного буфера по умолчанию
		INFINITE,	// клиент ждет связь 500 мс
		(LPSECURITY_ATTRIBUTES)NULL	// защита по умолчанию
	);
	
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Creation of the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish server: ";
		cin >> c;
		return (0);
	}

	
	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(
		hNamedPipe,	
		(LPOVERLAPPED)NULL	
	))
	{
		cerr << "The connection failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}


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

	
	if (!WriteFile(
		hNamedPipe,			
		&sizeArray1,			
		sizeof(sizeArray1),		
		&dwBytesWrite,			
		(LPOVERLAPPED)NULL	
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	for (int i = 0; i < sizeArray1; i++) {
		if (!WriteFile(
			hNamedPipe,
			&array1[i],
			sizeof(array1[i]),
			&dwBytesWrite,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}


	if (!WriteFile(
		hNamedPipe,
		&sizeArray2,
		sizeof(sizeArray2),
		&dwBytesWrite,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	for (int i = 0; i < sizeArray2; i++) {
		if (!WriteFile(
			hNamedPipe,
			&array2[i],
			sizeof(array2[i]),
			&dwBytesWrite,
			NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}


	if (!ReadFile(
		hNamedPipe,
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
			hNamedPipe,
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

	
	CloseHandle(hNamedPipe);
	
	cout << "Press any char to finish the server: ";
	cin >> c;

	delete[] result;
	delete[] array1;
	delete[] array2;

	return (1);
}