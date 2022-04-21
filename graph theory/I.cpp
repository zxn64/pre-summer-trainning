#include <iostream>
#include <vector>

using namespace std;
const int max_n = 1e7 + 1;
vector<int> edge[max_n * 2];
int dfn[max_n * 2], dfn_cnt;//dfs序
int low[max_n * 2];
int stack[max_n * 2], top;
bool in_stack[max_n * 2];
int scc[max_n * 2], scc_cnt;//所属scc编号及各scc大小

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfn_cnt;
    stack[++top] = u;
    in_stack[u] = true;
    for (auto i: edge[u]) {
        if (!dfn[i]) {
            Tarjan(i);
            low[u] = min(low[u], low[i]);
        } else if (in_stack[i]) {
            low[u] = min(low[u], dfn[i]);
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        do {
            scc[stack[top]] = scc_cnt;
            in_stack[stack[top]] = false;
        } while (stack[top--] != u);
    }
}

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    io();
    int m, n, u, x, v, y;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> x >> v >> y;
        if (x && y) {
            edge[u + n].push_back(v);
            edge[v + n].push_back(u);
        } else if (!x && y) {
            edge[u].push_back(v);
            edge[v + n].push_back(u + n);
        } else if (x && !y) {
            edge[u + n].push_back(v + n);
            edge[v].push_back(u);
        } else if (!x && !y) {
            edge[u].push_back(v + n);
            edge[v].push_back(u + n);
        } else {
            cout << "Error.\n";
        }
    }
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) {
            Tarjan(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}