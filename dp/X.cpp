#include <iostream>
#include <vector>

using namespace std;
struct edge {
    int to, t;
};
const int max_n = 500000 + 5;
const long long inf = 0x3f3f3f3f3f3f3f3f;
vector<edge> edges[max_n];
long long t[max_n];
long long max_t = -1, ans;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void get_max(int u, int fa) {
    for (auto v: edges[u]) {
        if (v.to == fa) continue;
        t[v.to] = t[u] + v.t;
        get_max(v.to, u);
    }
    max_t = max(max_t, t[u]);
}

void dfs(int u, int fa) {
    long long m = inf;
    for (auto v: edges[u]) {
        if (v.to == fa) continue;
        dfs(v.to, u);
        m = min(m, t[v.to]);
    }
    for (auto v: edges[u]) {
        if (v.to == fa) continue;
        ans += t[v.to] - m;
    }
    t[u] = m == inf ? max_t - t[u] : m;
}

int main() {
    io();
    int n, root;
    cin >> n >> root;
    int u, v, w;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    get_max(root, 0);
    dfs(root, 0);
    cout << ans;
    return 0;
}