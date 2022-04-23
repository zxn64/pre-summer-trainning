#include <iostream>

using namespace std;
const int max_n = 2 << 22;
const int mod = 1e9 + 7;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int fa[max_n],dep[max_n];

int find(int x) {
    return (fa[x] == x) ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(dep[x]>dep[y]) {
        fa[y]=fa[x];
    }else {
        fa[x]=fa[y];
        if(dep[x]==dep[y]) {
            dep[y]++;
        }
    }
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

#define getchar() (frS==frT&&(frT=(frS=frBB)+fread(frBB,1,1<<15,stdin),frS==frT)?EOF:*frS++)
char frBB[1 << 15], *frS = frBB, *frT = frBB;

template<typename T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    while (!isdigit(c))c = getchar();
    while (isdigit(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

int main() {
    int m, n, u, v, q, ans = 0;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
        read(q);
        read(u);
        read(v);
        if (q == 1) {
            merge(u, v);
        } else {
            ans = (ans << 1) + (find(u) == find(v));
            if (ans > mod) {
                ans %= mod;
            }
        }
    }
    cout << ans;
    return 0;
}