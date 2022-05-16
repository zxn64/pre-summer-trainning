#include <iostream>
#include <vector>

using namespace std;
const int max_n = 2e5 + 5;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

vector<int> edge[max_n];
int dpn[max_n];

void dfs(int u, int fa) {
    for (int v: edge[u]) {
        if (v == fa) continue;
        dfs(v, u);
        if (dpn[v] > 0) dpn[u] += dpn[v];
    }
}

void dp(int u, int fa) {
    if (dpn[u] > 0) dpn[u] += max(0, dpn[fa] - dpn[u]);
    else dpn[u] += max(0, dpn[fa]);
    for (int v: edge[u]) {
        if (v == fa) continue;
        dp(v, u);
    }
}

int main() {
    io();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> dpn[i];
        dpn[i] = dpn[i] ? 1 : -1;
    }
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    dp(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << dpn[i] << ' ';
    }
    return 0;
}