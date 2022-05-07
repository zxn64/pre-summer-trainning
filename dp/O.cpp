#include<iostream>

using namespace std;
const int max_n = 1e5 + 5;
int dp[max_n], w[max_n], v[max_n], top;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void in(int vi, int wi, int ni) {
    int num = 1;
    while (ni - num > 0) {
        v[++top] = num * vi;
        w[top] = num * wi;
        ni -= num;
        num <<= 1;
    }
    v[++top] = ni * vi;
    w[top] = ni * wi;
}

int main() {
    int n, W, vi, wi, ni;
    io();
    cin >> n >> W;
    for (int i = 1; i <= n; i++) {
        cin >> vi >> wi >> ni;
        in(vi, wi, ni);
    }
    for (int i = 1; i <= top; i++) {
        for (int j = W; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[W];
    return 0;
}