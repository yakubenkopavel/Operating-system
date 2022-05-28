#include <windows.h>
#include <iostream>
#include <conio.h>

int main()
{
	wchar_t pipeName[] = L"\\\\WIN-6VC9URVTCAN\\pipe\\ipctest";
	
	char 	c;			
	int sizeArray1;
	int sizeArray2;
	int sizeResult = 0;
	char* result = nullptr;
	char* array1 = nullptr;
	__int8* array2 = nullptr;


	HANDLE 	hNamedPipe;
	char 	lpszInMessage[80];		
	DWORD 	dwBytesRead;				
	char 	lpszOutMessage[] = "The server has received a message."; 
	DWORD 	dwBytesWrite;				

	
	hNamedPipe = CreateNamedPipeA(
		"\\\\.\\pipe\\demo_pipe",
		PIPE_ACCESS_DUPLEX,		
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	
		1,		 
		0,		
		0,		
		INFINITE,	
		(LPSECURITY_ATTRIBUTES)NULL	
	);
	
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Creation of the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish server: ";
		std::cin >> c;
		return (0);
	}

	
	std::cout << "The server is waiting for connection with a client." << std::endl;
	if (!ConnectNamedPipe(
		hNamedPipe,	
		(LPOVERLAPPED)NULL	
	))
	{
		std::cerr << "The connection failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
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
		std::cerr << "Data writing to the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
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
		std::cerr << "Data writing to the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
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
	
	std::cout << "Press any char to finish the server: ";
	std::cin >> c;

	delete[] result;
	delete[] array1;
	delete[] array2;

	return (1);
}