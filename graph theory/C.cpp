#include <iostream>
#include <deque>
#include <vector>
#include <cstring>

struct edge {
    int x, y;
    bool w;
};
using namespace std;
const int max_n = 502;
int dis[max_n][max_n];
bool vis[max_n][max_n];
vector<edge> edges[max_n][max_n];

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int bfs(int n, int m) {
    memset(dis, 63, sizeof(dis));
    deque<pair<int, int>> next;
    dis[1][1] = 0;
    next.push_front({1, 1});
    while (!next.empty()) {
        int x = next.front().first, y = next.front().second;
        next.pop_front();
        vis[x][y] = true;
        if (x == n && y == m) {
            return dis[x][y];
        }
        for (auto &i: edges[x][y]) {
            if (vis[i.x][i.y]) {
                continue;
            }
            if (i.w) {
                next.emplace_front(i.x, i.y);
                dis[i.x][i.y] = min(dis[i.x][i.y], dis[x][y]);
            } else {
                next.emplace_back(i.x, i.y);
                dis[i.x][i.y] = min(dis[i.x][i.y], dis[x][y] + 1);
            }
        }
    }
    return -1;
}

int main() {
    io();
    int n, m, ans;
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c;
            if (c == '\\') {
                edges[i][j].push_back({i + 1, j + 1, true});
                edges[i + 1][j + 1].push_back({i, j, true});
                edges[i + 1][j].push_back({i, j + 1, false});
                edges[i][j + 1].push_back({i + 1, j, false});
            } else if (c == '/') {
                edges[i][j].push_back({i + 1, j + 1, false});
                edges[i + 1][j + 1].push_back({i, j, false});
                edges[i + 1][j].push_back({i, j + 1, true});
                edges[i][j + 1].push_back({i + 1, j, true});
            }
        }
    }
    if ((ans = bfs(n+1, m+1)) == -1) {
        cout << "NO SOLUTION";
    } else {
        cout << ans;
    }
    return 0;
}