#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

void generateData(std::vector<float>& data, int numValues, float minVal, float maxVal) {
    // Random number generator for floating point values between minVal and maxVal
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(minVal, maxVal);

    for (int i = 0; i < numValues; ++i) {
        data.push_back(dis(gen));
    }
}

void createHistogram(const std::vector<float>& data, int numBins, float minVal, float maxVal) {
    std::vector<int> bins(numBins, 0);
    float binWidth = (maxVal - minVal) / numBins;

    // Count occurrences in each bin
    for (float value : data) {
        int binIndex = static_cast<int>((value - minVal) / binWidth);
        if (binIndex >= 0 && binIndex < numBins) {
            bins[binIndex]++;
        }
    }

    std::cout << "\nHistogram:\n";
    for (int i = 0; i < numBins; ++i) {
        float binStart = minVal + i * binWidth;
        float binEnd = binStart + binWidth;
        std::cout << "[" << std::fixed << std::setprecision(1) << binStart << ", " << binEnd << "): ";
        std::cout << std::string(bins[i], '*') << " (" << bins[i] << ")\n";
    }
}

int main() {
    int numValues = 20;
    float minVal = 1.0f;
    float maxVal = 20.0f;
    int numBins = 5;

    std::vector<float> data;
    generateData(data, numValues, minVal, maxVal);

    std::cout << "Generated data:\n";
    for (float value : data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    createHistogram(data, numBins, minVal, maxVal);

    return 0;
}
