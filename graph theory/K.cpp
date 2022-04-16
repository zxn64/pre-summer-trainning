#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>

#define maxn 500001
using namespace std;
vector<int> to[maxn];
int fa[maxn][20], dep[maxn], bs[maxn];

void dfs(int u, int father) {

    //cout<<u<<endl;

    fa[u][0] = father;
    dep[u] = dep[father] + 1;

    //cout<<u<<' '<<0<<' '<<fa[u][0]<<endl;

    for (int i = 1; i < 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

        //cout<<u<<' '<<i<<' '<<fa[u][i]<<endl;

    }

    bs[u] = 1;
    int l = to[u].size();
    for (int i = 0; i < l; i++) {
        if (!bs[to[u][i]]) {
            dfs(to[u][i], u);
        }
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int d = dep[v] - dep[u], i = 0; d; d >>= 1, i++) {
        if (d & 1) {
            v = fa[v][i];
        }
    }

    //cout<<u<<' '<<v<<endl;

    if (u == v) {

        //cout<<u<<endl;

        return u;
    }
    for (int i = 19; i >= 0 && u != v; i--) {
        //cout<<i<<' '<<u<<' '<<v<<endl;
        //cout<<i<<' '<<fa[u][i]<<' '<<fa[v][i]<<endl;
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
        //cout<<i<<' '<<u<<' '<<v<<endl;
    }

    //cout<<fa[u][0]<<endl;

    return fa[u][0];
}

/*
15 3
1 2
3 4
3 2
8 6
3 6
7 6
5 4
13 14
15 14
10 9
1 9
11 12
11 10
12 13
9 15
8 14
4 10
*/
int main() {
    int m, n, u, v;
    cin >> n >> m;
    memset(bs, 0, sizeof(bs));
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        to[u].push_back(v);
        to[v].push_back(u);
    }
    dfs(1, 0);
/*
	for(int i=1; i<=n; i++) {
		cout<<i<<'-';
		for(int j=0; j<20; j++) {
			cout<<fa[i][j]<<' ';
		}
		cout<<endl;
	}
	for(int i=1; i<=n; i++) {
		cout<<i<<' '<<dep[i]<<endl;
	}
*/
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        cout << dep[u] + dep[v] - 2 * dep[lca(u, v)] << endl;
    }
}
