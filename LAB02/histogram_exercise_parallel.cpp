#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

void generateData(std::vector<float>& data, int numValues, float minVal, float maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(minVal, maxVal);

    for (int i = 0; i < numValues; ++i) {
        data.push_back(dis(gen));
    }
}

void calculateLocalHistogram(const std::vector<float>& data, std::vector<int>& localHistogram, float minVal, float maxVal, int numBins) {
    float binWidth = (maxVal - minVal) / numBins;
    for (float value : data) {
        int binIndex = static_cast<int>((value - minVal) / binWidth);
        if (binIndex >= 0 && binIndex < numBins) {
            localHistogram[binIndex]++;
        }
    }
}

int main(int argc, char* argv[]) {
    int numValues = 200;
    float minVal = 1.0f;
    float maxVal = 20.0f;
    int numBins = 10;

    MPI_Init(&argc, &argv);
    
    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int localNumValues = numValues / num_procs;

    if (rank < numValues % num_procs) {
        localNumValues++;
    }

    std::vector<float> localData(localNumValues); // Pre-allocate space for received data

    std::vector<int> localHistogram(numBins, 0);

    if (rank == 0) {
        std::vector<float> data;
        generateData(data, numValues, minVal, maxVal);
        std::cout << "Contenido de data:\n";
        for (float value : data) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        MPI_Scatter(data.data(), localNumValues, MPI_FLOAT, localData.data(), localNumValues, MPI_FLOAT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(nullptr, 0, MPI_DATATYPE_NULL, localData.data(), localNumValues, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }

    calculateLocalHistogram(localData, localHistogram, minVal, maxVal, numBins);

    // Imprimir los datos y el histograma local del proceso actual
    std::cout << "Proceso " << rank << " datos:\n";
    for (float value : localData) {
        std::cout << value << " ";
    }
    std::cout << "\nHistograma local en el proceso " << rank << ":\n";
    float binWidth = (maxVal - minVal) / numBins;
    for (int i = 0; i < numBins; ++i) {
        float binStart = minVal + i * binWidth;
        float binEnd = binStart + binWidth;
        int count = localHistogram[i];

        std::cout << "[" << std::fixed << std::setprecision(1) << binStart << ", " << binEnd << "): ";
        std::cout << std::string(count, '*') << " (" << count << ")\n";
    }

    // Reducción del histograma
    std::vector<int> globalHistogram(numBins, 0);
    MPI_Reduce(localHistogram.data(), globalHistogram.data(), numBins, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Imprimir el histograma final en el proceso 0
    if (rank == 0) {
        std::cout << "\nHistograma final:\n";
        for (int i = 0; i < numBins; ++i) {
            float binStart = minVal + i * binWidth;
            float binEnd = binStart + binWidth;
            int count = globalHistogram[i];

            // Imprimir el intervalo del bin y el recuento
            std::cout << "[" << std::fixed << std::setprecision(1) << binStart << ", " << binEnd << "): ";
            std::cout << std::string(count, '*') << " (" << count << ")\n";
        }
    }

    MPI_Finalize();
    return 0;
}
