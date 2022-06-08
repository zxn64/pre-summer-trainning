#include <iostream>

using namespace std;
const long long mod = 0xffffffff;
const long long x2 = 166042049, y2 = 598777;
const long long x1 = 213346089, y1 = 870413;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

bool dfs(long long seed, long long u, long long s, int d) {
    if (u >= s) return true;
    if (!d || u + 6 * d < s) return false;
    u += seed % 7;
    return (dfs((seed * x1 + y1) & mod, u, s, d - 1) || dfs((seed * x2 + y2) & mod, u, s, d - 1));
}

int main() {
    io();
    long long seed, s;
    cin >> seed >> s;
    int d = 0;
    while (!dfs(seed, 0, s, d)) {
        d++;
    }
    cout << d;
    return 0;
}