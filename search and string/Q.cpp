#include <iostream>

using namespace std;
const int max_l = 2e6 + 5;
int prefix[max_l];

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void get_prefix(const string &s) {
    int l = s.length();
    int j = prefix[0];
    for (int i = 1; i < l; ++i) {
        while (j > 0 && s[i] != s[j]) j = prefix[j - 1];
        if (s[i] == s[j]) ++j;
        prefix[i] = j;
    }
}

int main() {
    io();
    string s, t;
    cin >> s >> t;
    int l_t = t.length();
    s = t + ' ' + s;
    get_prefix(s);
    int l_s = s.length(), ans = 0;
    for (int i = 2 * l_t; i < l_s; ++i) {
        if (prefix[i] == l_t) ++ans;
    }
    cout << ans;
    return 0;
}
