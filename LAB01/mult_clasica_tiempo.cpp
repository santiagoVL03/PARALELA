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

void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void evaluatePerformance(int n) {
    vector<vector<int>> A(n, vector<int>(n, 1));
    vector<vector<int>> B(n, vector<int>(n, 1));
    vector<vector<int>> C(n, vector<int>(n, 0));

    double startCPUTime = getCPUTime();

    multiplyMatrices(A, B, C, n);

    double endCPUTime = getCPUTime();
    
    double cpuTimeUsed = endCPUTime - startCPUTime;
    cout << "Tamaño de la matriz: " << n << "x" << n << " | Tiempo de CPU: " << cpuTimeUsed << " segundos" << endl;
}

int main() {
    evaluatePerformance(100);
    evaluatePerformance(200);
    evaluatePerformance(300);
    evaluatePerformance(500);
    evaluatePerformance(600);

    return 0;
}
