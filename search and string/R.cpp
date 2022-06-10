#include <iostream>

using namespace std;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int move_x[8] = {1, -1, -2, -2, -1, 1, 2, 2},
        move_y[8] = {2, 2, 1, -1, -2, -2, -1, 1};
const char standard[5][6] = {"11111", "01111", "00*11", "00001", "00000"};
char chessboard[5][5];// -1='*'  1=1  0=0
bool dfs(int x0, int y0, int x, int y, int dif, int d) {
    if (x < 0 || x > 4 || y < 0 || y > 4 || dif > d + 2) return false;
    if (chessboard[x0][y0] == standard[x0][y0]) ++dif;
    if (chessboard[x][y] == standard[x][y]) ++dif;
    swap(chessboard[x0][y0], chessboard[x][y]);
    if (chessboard[x0][y0] == standard[x0][y0]) --dif;
    if (chessboard[x][y] == standard[x][y]) --dif;
    if (!dif) {
        swap(chessboard[x0][y0], chessboard[x][y]);
        return true;
    }
    int ans = 16, temp;
    for (int i = 0; i < 8; ++i) {
        if (dfs(x, y, x + move_x[i], y + move_y[i], dif, d - 1)) {
            return true;
        }
    }
    swap(chessboard[x0][y0], chessboard[x][y]);
    return false;
}

int main() {
    io();
    int t, x0, y0, dif, flag;
    cin >> t;
    while (t--) {
        dif = 0;
        flag = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                cin >> chessboard[i][j];
                if (standard[i][j] != chessboard[i][j]) {
                    ++dif;
                }
                if (chessboard[i][j] == '*') {
                    x0 = i;
                    y0 = j;
                }
            }
        }
        for (int i = 0; i <= 15; ++i) {
            if (dfs(x0, y0, x0, y0, dif, i)) {
                cout << i << '\n';
                flag = 1;
                break;
            }
        }
        if (!flag) cout << -1 << '\n';
    }
    return 0;
}