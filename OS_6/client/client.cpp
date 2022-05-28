#include <windows.h>
#include <iostream>

int main()
{
	char c;		
	int sizeArray1;
	int sizeArray2;
	int sizeResult = 0;
	char* result = nullptr;
	char* array1 = nullptr;
	__int8* array2 = nullptr;

	HANDLE 	hNamedPipe;
	char 	pipeName[80];
	char 	lpszOutMessage[] = "How do you do server?";	
	DWORD 	dwBytesWritten;	
	char 	lpszInMessage[80];	
	DWORD 	dwBytesRead;		

	
	wsprintfA(pipeName, "\\\\WIN-6VC9URVTCAN\\pipe\\demo_pipe",
		"");

	
	hNamedPipe = CreateFileA(
		pipeName,				
		GENERIC_READ | GENERIC_WRITE,		
		FILE_SHARE_READ | FILE_SHARE_WRITE,	
		(LPSECURITY_ATTRIBUTES)NULL,		
		OPEN_EXISTING,				
		FILE_ATTRIBUTE_NORMAL,			
		(HANDLE)NULL				
	);


	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Connection with the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish the client: ";
		std::cin >> c;
		return (0);
	}


	
	if (!ReadFile(
		hNamedPipe,	
		&sizeArray1,		
		sizeof(sizeArray1),	
		&dwBytesRead,		
		(LPOVERLAPPED)NULL	
	))
	{
		std::cerr << "Reading to the named pipe failed: " << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish the client: ";
		std::cin >> c;
		CloseHandle(hNamedPipe);
		return (0);
	}
	std::cout << "Size array1: " << sizeArray1 << std::endl << "Elements array1: ";
	array1 = new char[sizeArray1];
	for (int i = 0; i < sizeArray1; i++) {
		if (!ReadFile(
			hNamedPipe,
			&array1[i],
			sizeof(array1[i]),
			&dwBytesRead,
			NULL))
		{
			return GetLastError();
		}
		std::cout << array1[i] << " ";
	}
	std::cout << std::endl;
	if (!ReadFile(
		hNamedPipe,
		&sizeArray2,
		sizeof(sizeArray2),
		&dwBytesRead,
		(LPOVERLAPPED)NULL
	))
	{
		std::cerr << "Reading to the named pipe failed: " << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish the client: ";
		std::cin >> c;
		CloseHandle(hNamedPipe);
		return (0);
	}
	std::cout << "Size array2: " << sizeArray2 << std::endl << "Elements array2: ";
	array2 = new __int8[sizeArray2];
	for (int i = 0; i < sizeArray2; i++) {
		if (!ReadFile(
			hNamedPipe,
			&array2[i],
			sizeof(array2[i]),
			&dwBytesRead,
			NULL))
		{
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
		hNamedPipe,
		&sizeResult,
		sizeof(sizeResult),
		&dwBytesWritten,
		NULL))
	{
		return GetLastError();
	}
	for (int i = 0; i < sizeResult; i++) {
		if (!WriteFile(
			hNamedPipe,
			&result[i],
			sizeof(result[i]),
			&dwBytesWritten,
			NULL))
		{
			return GetLastError();
		}
	}



	CloseHandle(hNamedPipe);

	std::cout << "Press any char to finish the client: ";
	std::cin >> c;

	delete[] result;
	delete[] array1;
	delete[] array2;

	return 0;
}
