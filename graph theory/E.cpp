#include <iostream>
#include <vector>

using namespace std;
const int max_n = 1e5 + 1;
const int inf = 2e9;
vector<int> edge[max_n], tree[max_n * 2];
int value[max_n], tree_value[max_n * 2];

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int m, n, tree_cnt, dis[max_n * 2];
int dfn[max_n], low[max_n], dfs_cnt;
int stack[max_n], top;

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfs_cnt;
    stack[++top] = u;
    tree_value[u] = value[u];
    for (auto i: edge[u]) {
        if (!dfn[i]) {
            Tarjan(i);
            low[u] = min(low[u], low[i]);
            if (low[i] >= dfn[u]) {
                tree_value[++tree_cnt] = inf;
                for(int j=0; j!=i; top--) {
                    j=stack[top];
                    tree[tree_cnt].push_back(j);
                    tree[j].push_back(tree_cnt);
                    tree_value[tree_cnt] = min(tree_value[tree_cnt], value[j]);
                }
                tree[tree_cnt].push_back(u);
                tree[u].push_back(tree_cnt);
            }
        } else {
            low[u] = min(low[u], dfn[i]);
        }
    }
}

void dfs(int u, int father, int min_dis) {
    dis[u] = min(min_dis, tree_value[u]);
    for (auto i: tree[u]) {
        if (i != father) {
            dfs(i, u, dis[u]);
        }
    }
}

int main() {
    io();
    int q, u, v;
    cin >> n >> m >> q;
    tree_cnt = n;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u = -u;
        v = -v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    Tarjan(1);
    dfs(1, 1, tree_value[1]);
    int f;
    for (int i = 0; i < q; i++) {
        cin >> f;
        cout << dis[f] << '\n';
    }
    return 0;
}