#include <iostream>

using namespace std;
const int max_n = 4501;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int f[max_n][max_n];

int main() {
    io();
    int n, mod;
    cin >> n >> mod;
    f[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            f[i][j] = f[i][j - 1] + f[i - 1][i - j];
            f[i][j] %= mod;
        }
    }
    cout << (f[n][n] * 2) % mod;
    return 0;
}