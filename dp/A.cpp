#include <iostream>

using namespace std;
const int max_n = 5005;
int f[max_n][max_n];

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    io();
    int m, n, x, y, z;
    string a, b;
    cin >> n >> m >> x >> y >> z >> a >> b;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                ans = max(ans, f[i + 1][j + 1] = max(0, max(x - y - z, f[i][j] + x - y - z)));
            } else {
                f[i + 1][j + 1] = max(0, max(f[i][j + 1] - y, f[i + 1][j] - z));
            }
        }
    }
    cout << ans;
    return 0;
}