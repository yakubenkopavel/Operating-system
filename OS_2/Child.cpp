#include <iostream>
#include <conio.h>
#include <windows.h>


void ShellSort(int n, float mass[])
{
    int i, j, step;
    float tmp;

    for (step = n / 2; step > 0; step /= 2) {
        for (i = step; i < n; i++)
        {
            tmp = mass[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[j - step])
                    mass[j] = mass[j - step];
                else
                    break;
            }
            mass[j] = tmp;
        }
    }
}


int main(int argc, char* argv[])
{
    int size = std::atoi(argv[0]);
    if (size >= argc) {
        std::cout << "Error" << std::endl;
        system("pause");
        return 0;
    }


    float* arrays = new float[size];

    for (int i = 0; i < size; i++) {
        arrays[i] = std::atof(argv[i + 1]);
    }

    std::cout << "Size array: " << size;

    ShellSort(size, arrays);

    std::cout << "\nSorted array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arrays[i] << " ";
    }
    std::cout << std::endl;

    delete[] arrays;
    system("pause");
    return 0;
}
