#include <iostream>
#include <vector>
#include <algorithm>

const int max_n = 1001;
using namespace std;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int dfn[max_n], num;//dfs序
int stack[max_n], top;//栈
int low[max_n], max_dcc_edge = -1;
int cut_edge, cut_vertex;//割边、割点数量
int fa[max_n], num_dcc;//fa为dcc序号
bool cut[max_n];
vector<int> edge[max_n];
vector<int> dcc[max_n];

void Tarjan(int u, int father) {
    dfn[u] = low[u] = ++num;
    stack[++top] = u;
    int l = edge[u].size();
    int child=0;
    for (int i = 0; i < l; i++) {
        if(edge[u][i]==father) {
            continue;
        }
        if (dfn[edge[u][i]]) {
            low[u] = min(low[u], dfn[edge[u][i]]);
        } else {
            child++;
            Tarjan(edge[u][i], u);
            low[u] = min(low[u], low[edge[u][i]]);
            if (low[edge[u][i]] >= dfn[u]) {
                if (!cut[u]&&(father!=u||child>1)) {
                    cut[u] = true;
                    cut_vertex++;
                }
                if (low[edge[u][i]] > dfn[u]) {
                    cut_edge++;
                }
                int v;
                do {
                    dcc[num_dcc].push_back(v = stack[top--]);
                } while (v != edge[u][i]);
                dcc[num_dcc++].push_back(u);
            }
        }
    }
}

int main() {
    io();
    int m, n, u, v;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            Tarjan(i, i);
        }
    }
    for (int i = 0; i < num_dcc; i++) {
        int sum = 0, l_dcc = dcc[i].size();
        for (int j = 0; j < l_dcc; j++) {
            int l_edge = edge[dcc[i][j]].size();
            for (int k = 0; k < l_edge; k++) {
                if (find(dcc[i].begin(), dcc[i].end(),edge[dcc[i][j]][k]) != dcc[i].end()) {
                    sum++;
                }
            }
        }
        max_dcc_edge = max(max_dcc_edge, sum / 2);
    }
    cout << cut_vertex << ' ' << cut_edge << ' ' << num_dcc << ' ' << max_dcc_edge;
    return 0;
}