#include <iostream>
#include <conio.h>
#include <windows.h>


void ShellSort(int n, float mass[])
{
    int i, j, step;
    float tmp;

    for (step = n / 2; step > 0; step /= 2)
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


int main(int argc, char* argv[])
{
    float* arrays = new float[argc];
    for (int i = 0; i < argc; i++) {
        arrays[i] = std::atof(argv[i]);
    }

    wprintf(L"%d\n", argc);

    ShellSort(argc, arrays);
    for (int i = 0; i < argc; i++) {
        wprintf(L"%.1f ", arrays[i]);
    }
	_getch();

}
