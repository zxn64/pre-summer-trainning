#include <iostream>
#include <cmath>

using namespace std;
const int inf = 0x3f3f3f3f;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int ans = inf, flag = 0;

void dfs(int n, int m, int r, int h, int S) {
    if(S+2*n/r>=ans) return;
    if (!m) {
        if (n) {
            return;
        }
        ans = min(ans, S);
        flag = 1;
        return;
    }
    int ur = min(r - 1, (int) sqrt(n)), uh, v, s;
    for (int i = m; i <= ur; ++i) {
        uh = min(h - 1, n / (i * i));
        for (int j = n / m / i / i; j <= uh; ++j) {
            v = i * i * j;
            s = 2 * i * j;
            dfs(n - v, m - 1, i, j, S + s);
        }
    }
}

int main() {
    io();
    int n, m;
    cin >> n >> m;
    int ur = sqrt(n), uh, v, S;
    for (int i = m; i <= ur; ++i) {
        uh = n / (i * i);
        for (int j = n / m / i / i; j <= uh; ++j) {
            v = i * i * j;
            S = i * (i + 2 * j);
            dfs(n - v, m - 1, i, j, S);
        }
    }
    if (flag) {
        cout << ans;
    } else {
        cout << 0;
    }
    return 0;
}