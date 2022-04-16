#include <iostream>
#include <cstring>

const int max_n = 301;
const int inf = 0x3f3f3f3f;

using namespace std;
int edge[max_n][max_n], dis[max_n];
bool in_A[max_n], vis[max_n];

void io() {//解绑加速输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int Stoer_Wagner(int n) {//n为目前点的数量
    int min_cut = inf, m = n;
    while (m > 1) {
        memset(in_A, 0, sizeof(in_A));
        memset(dis, false, sizeof(dis));
        int s, t, w;
        for (int i = 1; i <= n; i++) {//寻找w最大边所连通的点并加入A
            int max_dis = -1, max_dis_node = -1;
            for (int j = 1; j <= n; j++) {
                if (!in_A[j] && !vis[j] && dis[j] > max_dis) {
                    max_dis = dis[j];
                    max_dis_node = j;
                }
            }
            if (max_dis == -1) {
                break;
            }
            w = max_dis;
            s = t;
            t = max_dis_node;
            in_A[max_dis_node] = true;
            for (int j = 0; j <= n; j++) {
                if (!vis[j] && !in_A[j]) {
                    dis[j] += edge[max_dis_node][j];
                }
            }
        }
        vis[t] = true;
        min_cut = min(min_cut, w);
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                edge[s][i] += edge[t][i];
                edge[i][s] += edge[i][t];
            }
        }
        m--;
    }
    return ((min_cut == inf) ? 0 : min_cut);
}

int main() {
    io();
    int m, n, x, y;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        edge[x][y]++;
        edge[y][x]++;
    }
    cout << Stoer_Wagner(n);
    return 0;
}