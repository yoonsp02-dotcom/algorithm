#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<long long>> matrix;

const int PERIOD = 1500 * 1000;
const int MOD = 1 * 1000 * 1000;
const int N = 2;
long long n;

matrix matrixMulti(const matrix A, const matrix B);
matrix matrixPower(const matrix &A, long long B);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    matrix A = {{1, 1}, {1, 0}};
    cin >> n;
    // n %= PERIOD;
    matrix fibonacci = matrixPower(A, n);
    cout << fibonacci[1][0] << endl;
    return 0;
}
matrix matrixMulti(const matrix A, const matrix B) {
    matrix ret(N, vector<long long>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                ret[i][j] += A[i][k] * B[k][j] % MOD;
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}
matrix matrixPower(const matrix &A, long long B) {
    if (B == 1)
        return A;
    matrix half = matrixPower(A, B / 2);
    half = matrixMulti(half, half);
    if (B % 2 == 1)
        half = matrixMulti(half, A);
    return half;
}