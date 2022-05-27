#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <process.h>
#include<ctime>

struct tagParam {
public:
	int time;
	int size;
	int count;
	int* result;
	int* arrays;

	tagParam( int size, int time) {
		this->size = size;
		this->time = time;
		count = 0;

		result = nullptr;
		arrays = new int[size];

		for (int i = 0; i < size; i++) {
			arrays[i] = rand() % 10 + 1;
		}
	}

	tagParam() {
		size = 0;
		time = 0;
		count = 0;
		result = nullptr;
		arrays = nullptr;
	}
};

void worker(LPVOID lpParam) {
	tagParam* param = (tagParam*)lpParam;
	Sleep(param->time);

	int* mas = param->arrays;

	int a = rand() % 5;
	int b = a + rand() % 4 + 1;


	std::cout << "a:" << a << " b:" << b << std::endl;
	std::cout << "Вывод в потоке: " << std::endl;

	for (int i = 0; i < param->size; i++) {
		if (a <= mas[i] && mas[i] <= b) {
			std::cout << mas[i] << " ";
			param->count++;
		}
	}
	std::cout << std::endl;


	param->result = new int[param->count];
	int counter = 0;

	for (int i = 0; i < param->size; i++) {
		if (a <= mas[i] && mas[i] <= b) {
			param->result[counter] = mas[i];
			counter++;
		}
	}

	ExitThread(0);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int time1 = 0;
	std::cout << "Введите время для остановки и запуска потока:\n";
	std::cin >> time1;

	HANDLE hWorker;
	DWORD IDWorker;
	tagParam param(rand() % 10 + 5, time1);

	
	hWorker = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, &param, 0, &IDWorker);
	if (hWorker == NULL) {
		return GetLastError();
	}

	SuspendThread(hWorker);

	for (int i = 0; i < param.size; i++) {
		std::cout << param.arrays[i] << " ";
	}
	std::cout << std::endl;
	ResumeThread(hWorker);


	WaitForSingleObject(hWorker, INFINITE);

	std::cout << "Простой вывод: " << std::endl;
	for (int i = 0; i < param.count; i++) {
		std::cout << param.result[i] << " ";
	}

	CloseHandle(hWorker);

	return 0;

}