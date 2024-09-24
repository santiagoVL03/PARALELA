#include <iostream>
#include <vector>

using namespace std;

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

int main(int argc, char const *argv[])
{
    vector<vector<int>> A(100, vector<int>(100, 1));
    vector<vector<int>> B(100, vector<int>(100, 1));
    vector<vector<int>> C(100, vector<int>(100, 0));
    multiplyMatrices(A, B, C, 100);
    return 0;
}
