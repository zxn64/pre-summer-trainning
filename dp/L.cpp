#include <iostream>

using namespace std;
const int max_n = 100000 + 5;
int vase[max_n], stack[max_n], top = 1;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    long long n, w;
    cin >> n >> w;
    stack[1] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> vase[i];
    }
    int l, r, m;
    for (int i = 2; i <= n; i++) {
        if (vase[i] - vase[stack[top]] >= i - stack[top]) {
            stack[++top] = i;
        } else {
            l = 0;
            r = top;
            m = (l + r + 1) / 2;
            while (l != r) {
                if (vase[i] - vase[stack[m]] >= i - stack[m]) {
                    l = m;
                    m = (l + r + 1) / 2;
                } else {
                    r = m - 1;
                    m = (l + r + 1) / 2;
                }
            }
            stack[m + 1] = i;
        }
    }
    cout << (n - top) * w;
    return 0;
}