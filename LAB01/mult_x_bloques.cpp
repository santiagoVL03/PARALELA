#include <iostream>
#include <vector>

using namespace std;


void multiplyMatricesBlock(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                // Multiplicar bloques A(i,k) x B(k,j)
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

int main(int argc, char const *argv[])
{
    vector<vector<int>> A(100, vector<int>(100, 1));
    vector<vector<int>> B(100, vector<int>(100, 1));
    vector<vector<int>> C(100, vector<int>(100, 0));    return 0;
    multiplyMatricesBlock(A, B, C, 100, 20);
}
