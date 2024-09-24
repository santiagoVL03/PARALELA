#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

double FileTimeToSeconds(const FILETIME& ft) {
    ULARGE_INTEGER li;
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    return li.QuadPart / 10000000.0;
}

double getCPUTime() {
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
        return FileTimeToSeconds(kernelTime) + FileTimeToSeconds(userTime);
    }
    return 0.0;
}

void multiplyMatricesBlock(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int bi = i; bi < min(i + blockSize, n); ++bi) {
                    for (int bj = j; bj < min(j + blockSize, n); ++bj) {
                        for (int bk = k; bk < min(k + blockSize, n); ++bk) {
                            C[bi][bj] += A[bi][bk] * B[bk][bj];
                        }
                    }
                }
            }
        }
    }
}

void evaluatePerformanceBlock(int n, int blockSize) {
    vector<vector<int>> A(n, vector<int>(n, 1));
    vector<vector<int>> B(n, vector<int>(n, 1));
    vector<vector<int>> C(n, vector<int>(n, 0));

    double startCPUTime = getCPUTime();

    multiplyMatricesBlock(A, B, C, n, blockSize);

    double endCPUTime = getCPUTime();
    double cpuTimeUsed = endCPUTime - startCPUTime;
    cout << "Tamaño de la matriz: " << n << "x" << n << " | Tiempo de CPU: " << cpuTimeUsed << " segundos" << endl;
}

int main() {
    evaluatePerformanceBlock(100, 50);
    evaluatePerformanceBlock(200, 60);
    evaluatePerformanceBlock(300, 80);
    evaluatePerformanceBlock(500, 100);
    evaluatePerformanceBlock(600, 120);

    return 0;
}
