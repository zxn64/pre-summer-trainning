#include<iostream>
#include<cstring>

#define MAX 5001
using namespace std;
struct edge {
    int node;
    edge *next;
};
struct node {
    edge *next;
} mynode[MAX];
int stk[MAX], instk[MAX], edges[MAX][MAX], top;
bool nm[MAX];

bool dfs(int u) {
    stk[++top] = u;
    instk[u] = nm[u] = true;
    for (edge *i = mynode[u].next; i != nullptr; i = i->next) {
        if (!nm[i->node]) {
            if (!dfs(i->node)) {
                return false;
            }
        } else if (instk[i->node]) {
            int sum = 0, temp = top;
            while (stk[temp] != i->node) {
                instk[stk[temp]] = 0;
                sum += edges[stk[--temp]][stk[temp + 1]];
            }
            sum += edges[u][stk[temp]];
            if (sum < 0) {
                return false;
            }
        }
    }
    top--;
    instk[u] = 0;
    return true;
}

int main() {
    int n, m, u, v, w;
    cin >> n >> m;
    edge *newedge;
    memset(mynode, 0, sizeof(mynode));
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        newedge = new edge;
        newedge->node = u;
        newedge->next = mynode[v].next;
        mynode[v].next = newedge;
        edges[v][u] = w;
    }
    for (int i = 1; i <= n; i++) {
        if (!nm[i]) {
            top = 0;
            if (!dfs(i)) {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES";
    return 0;
}
