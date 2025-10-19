#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> matrix;

int N;
long long B;

matrix matrixMulti(const matrix A, const matrix B);
matrix matrixPower(const matrix &A, long long B);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> B;
    matrix A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
            A[i][j] %= 1000;
        }
    }
    matrix res = matrixPower(A, B);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << res[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
matrix matrixMulti(const matrix A, const matrix B) {
    matrix ret(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                ret[i][j] += A[i][k] * B[k][j] % 1000;
                ret[i][j] %= 1000;
            }
        }
    }
    return ret;
}
matrix matrixPower(const matrix &A, long long B) {
    if (B == 1)
        return A;
    if (B % 2 == 1)
        return matrixMulti(matrixPower(A, B - 1), A);
    matrix half = matrixPower(A, B / 2);
    return matrixMulti(half, half);
}