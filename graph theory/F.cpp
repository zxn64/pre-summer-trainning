#include<iostream>
#include<cstring>

#define MAX 5001
/*5 6
1 2 -1
2 3 -1
3 1 -1
3 4 1
4 5 1
5 3 1*/
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

/*6 6
1 2 1
2 3 1
3 1 1
4 5 -1
5 6 -1
6 4 1*/
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
                //cout<<stk[top]<<' '<<stk[top+1]<<' ';
                //cout<<sum<<' '<<endl;
            }
            sum += edges[u][stk[temp]];
            //cout<<u<<' '<<i->node<<' ';
            //cout<<sum<<' '<<endl;
            //cout<<top<<endl;
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
