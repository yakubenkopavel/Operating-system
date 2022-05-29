#include <boost/thread/thread.hpp>
#include <boost/chrono/chrono.hpp>
#include <iostream>
#include <ctime>

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


int* worker(int time1, int sizeArray, int& amountNumbers, int* arrayNumbers, int* result) {
	srand(time(0));

	boost::this_thread::sleep_for(boost::chrono::milliseconds(time1));

	int start = randomStartInterval();
	int end = randomEndInterval(start);

	std::cout << "Отрезок [a;b]: а = " << start << " b = " << end << std::endl;
	std::cout << "Вывод в потоке: " << std::endl;

	for (int i = 0; i < sizeArray; i++) {
		if (start <= arrayNumbers[i] && arrayNumbers[i] <= end) {
			std::cout << arrayNumbers[i] << " ";
			amountNumbers++;
		}
	}
	std::cout << std::endl;


	result = new int[amountNumbers];


	for (int i = 0, index = 0; i < sizeArray; i++) {
		if (start <= arrayNumbers[i] && arrayNumbers[i] <= end) {
			if (index < amountNumbers) {
				result[index] = arrayNumbers[i];
			}
			index++;
		}
	}
	return result;
}


int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));


	int time = 0;
	int sizeArray = randomAmountNumbers();
	int amountNumbers = 0;
	int* result = nullptr;
	int* arrayNumbers = new int[sizeArray];

	for (int i = 0; i < sizeArray; i++) {
		arrayNumbers[i] = randomNumbers();
	}

	std::cout << "Введите время для остановки и запуска потока(мс):\n";
	std::cin >> time;


	boost::thread thrWorker([time, sizeArray, &amountNumbers, arrayNumbers, &result]() {
		result = worker(time, sizeArray, amountNumbers, arrayNumbers, result);
		}
	);



	std::cout << "Массив целых чисел: ";
	outputArray(sizeArray, arrayNumbers);

	thrWorker.join();

	std::cout << "Простой вывод: " << std::endl;
	outputArray(amountNumbers, result);

	delete[] arrayNumbers;
	delete[] result;


	system("pause");
	return 0;
}

