#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <process.h>
#include<ctime>


int randomStartInterval() {
	return rand() % 5;
}
int randomEndInterval(int start) {
	return start + rand() % 4 + 1;
}
int randomAmountNumbers() {
	return rand() % 10 + 5;
}
int randomNumbers() {
	return rand() % 10 + 1;
}

void outputArray(int count, int* arrays) {
	for (int i = 0; i < count; i++) {
		std::cout << arrays[i] << " ";
	}
	std::cout << std::endl;
}

struct tagParam {
public:
	int time;
	int sizeArray;
	int amountNumbers;
	int* result;
	int* arrayNumbers;

	tagParam(int time) {
		this->sizeArray = randomAmountNumbers();
		this->time = time;
		amountNumbers = 0;

		result = nullptr;
		arrayNumbers = new int[sizeArray];


		for (int i = 0; i < sizeArray; i++) {
			arrayNumbers[i] = randomNumbers();
		}
	}

	tagParam() {
		sizeArray = 0;
		time = 0;
		amountNumbers = 0;
		result = nullptr;
		arrayNumbers = nullptr;
	}

	~tagParam() {
		delete[] arrayNumbers;
		delete[] result;
	}
};

void worker(LPVOID lpParam) {
	tagParam* param = (tagParam*)lpParam;

	srand(time(0));
	Sleep(param->time);

	int* arrayNumbers = param->arrayNumbers;
	int start = randomStartInterval();
	int end = randomEndInterval(start);

	std::cout << "Отрезок [a;b]: а = " << start << " b = " << end << std::endl;
	std::cout << "Вывод в потоке: " << std::endl;

	for (int i = 0; i < param->sizeArray; i++) {
		if (start <= arrayNumbers[i] && arrayNumbers[i] <= end) {
			std::cout << arrayNumbers[i] << " ";
			param->amountNumbers++;
		}
	}
	std::cout << std::endl;


	param->result = new int[param->amountNumbers];


	for (int i = 0, index = 0; i < param->sizeArray; i++) {
		if (start <= arrayNumbers[i] && arrayNumbers[i] <= end) {
			if (index < param->amountNumbers) {
				param->result[index] = arrayNumbers[i];
			}
			index++;
		}
	}

	ExitThread(0);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int time = 0;
	std::cout << "Введите время для остановки и запуска потока(мс):\n";
	std::cin >> time;

	HANDLE hWorker;
	DWORD IDWorker;
	tagParam param(time);


	hWorker = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, &param, 0, &IDWorker);
	if (NULL == hWorker) {
		return GetLastError();
	}
	SuspendThread(hWorker);

	std::cout << "Массив целых чисел: ";
	outputArray(param.sizeArray, param.arrayNumbers);

	ResumeThread(hWorker);
	WaitForSingleObject(hWorker, INFINITE);

	std::cout << "Простой вывод: " << std::endl;
	outputArray(param.amountNumbers, param.result);

	CloseHandle(hWorker);

	return 0;
}