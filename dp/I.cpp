#include <iostream>

using namespace std;
const int max_n = 5005;
int f[max_n][max_n];
bool beq[max_n][max_n];

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void get_xor(int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            f[j][j + i] = f[j][j + i - 1] ^ f[j + 1][j + i];
        }
    }
}

int get_max(int l, int r) {
    if (beq[l][r]) return f[l][r];
    beq[l][r] = true;
    return f[l][r] = max(f[l][r], max(get_max(l, r - 1), get_max(l + 1, r)));
}

int main() {
    io();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> f[i][i];
        beq[i][i] = true;
    }
    get_xor(n);
    int q, l, r;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        cout << get_max(l, r) << '\n';
    }
    return 0;
}