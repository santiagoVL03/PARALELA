#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <chrono> 

int main(int argc, char const *argv[])
{
    int MAX = 200;
    double A[MAX][MAX];
    double x[MAX];
    double y[MAX] = {0};
    double y2[MAX] = {0};

    std::srand(std::time(nullptr));

    for (int i = 0; i < MAX; i++)
    {
        x[i] = std::rand() % 10;
        for (int j = 0; j < MAX; j++)
        {
            A[i][j] = std::rand() % 10;  
        }
    }

    auto start_y1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }
    auto end_y1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_y1 = end_y1 - start_y1;

    auto start_y2 = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            y2[i] += A[i][j] * x[j];
        }
    }
    auto end_y2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_y2 = end_y2 - start_y2;

    /*
    std::cout << "Matriz A:\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Vector resultado y1:\n";
    for (int i = 0; i < MAX; i++)
    {
        std::cout << y[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector resultado y2:\n";
    for (int i = 0; i < MAX; i++)
    {
        std::cout << y2[i] << " ";
    }
    std::cout << std::endl;
    */
    std::cout << "Tiempo de cálculo para y1: " << elapsed_y1.count() << " ms\n";
    std::cout << "Tiempo de cálculo para y2: " << elapsed_y2.count() << " ms\n";

    return 0;
}
