#include <iostream>

using namespace std;
const int max_n = 1e5 + 5;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct node {
    int value;
    int num;
    int size;
    int fa, son[2];
    void clear() {
        value=0;
        num=0;
        size=0;
        fa=0;
        son[0]=0;
        son[1]=0;
    }
} nodes[max_n];

int head, num;

int get_location(int x) {
    return x == nodes[nodes[x].fa].son[1];
}

void update_size(int x) {
    nodes[x].size = nodes[x].num + nodes[nodes[x].son[0]].size + nodes[nodes[x].son[1]].size;
}

void rotate(int x) {
    int fa = nodes[x].fa, gf = nodes[fa].fa, loc = get_location(x);
    nodes[fa].son[loc] = nodes[x].son[loc ^ 1];
    if (nodes[x].son[loc ^ 1]) nodes[nodes[x].son[loc ^ 1]].fa = fa;
    nodes[x].son[loc ^ 1] = fa;
    nodes[fa].fa = x;
    nodes[x].fa = gf;
    if (gf) nodes[gf].son[fa == nodes[gf].son[1]] = x;
    update_size(fa);
    update_size(x);
}

void splay(int x) {
    for (int fa = nodes[x].fa; fa = nodes[x].fa, fa; rotate(x))
        if (nodes[fa].fa) rotate((get_location(x) == get_location(fa)) ? fa : x);
    head = x;
}

void insert(int x) {
    if (!head) {
        nodes[++num].value = x;
        nodes[num].num = 1;
        head = num;
        update_size(head);
        return;
    }
    int now = head, fa = 0;
    while (true) {
        if (nodes[now].value == x) {
            nodes[now].num++;
            update_size(now);
            update_size(fa);
            splay(now);
            return;
        }
        fa = now;
        now = nodes[now].son[x > nodes[now].value];
        if (!now) {
            nodes[++num].value = x;
            nodes[num].num = 1;
            nodes[num].fa = fa;
            nodes[fa].son[x > nodes[fa].value] = num;
            update_size(num);
            update_size(fa);
            splay(num);
            return;
        }
    }
}

int query_rank(int x) {
    int rank = 0, now = head;
    while (true) {
        if (x < nodes[now].value) {
            now = nodes[now].son[0];
        } else {
            rank += nodes[nodes[now].son[0]].size;
            if (x == nodes[now].value) {
                splay(now);
                return rank + 1;
            }
            rank += nodes[now].num;
            now = nodes[now].son[1];
        }
    }
}

int find_num(int x) {
    int now = head;
    while (true) {
        if (nodes[now].son[0] && x <= nodes[nodes[now].son[0]].size) {
            now = nodes[now].son[0];
        } else {
            x -= nodes[nodes[now].son[0]].size + nodes[now].num;
            if (x <= 0) {
                splay(now);
                return nodes[now].value;
            }
            now = nodes[now].son[1];
        }
    }
}

int find_front() {
    int now = nodes[head].son[0];
    if(!now) {
        return -1;
    }
    while (nodes[now].son[1]) {
        now = nodes[now].son[1];
    }
    splay(now);
    return nodes[now].value;
}

int find_next() {
    int now = nodes[head].son[1];
    if(!now) {
        return -1;
    }
    while (nodes[now].son[0]) {
        now = nodes[now].son[0];
    }
    splay(now);
    return nodes[now].value;
}

void del(int x) {
    query_rank(x);
    if (nodes[head].num > 1) {
        nodes[head].num--;
        update_size(head);
        return;
    }
    if (!nodes[head].son[0] && !nodes[head].son[1]) {
        nodes[head].clear();
        head = 0;
        return;
    }
    if (!nodes[head].son[0]) {
        int now = head;
        head = nodes[now].son[1];
        nodes[now].clear();
        nodes[head].fa = 0;
        return;
    }
    if (!nodes[head].son[1]) {
        int now = head;
        head = nodes[now].son[0];
        nodes[now].clear();
        nodes[head].fa = 0;
        return;
    }
    int now = head;
    find_front();
    nodes[nodes[now].son[1]].fa = head;
    nodes[head].son[1] = nodes[now].son[1];
    nodes[now].clear();
    update_size(head);
}

int main() {
    io();
    int n;
    cin >> n;
    int opt, x, ans;
    while (n--) {
        cin >> opt >> x;
        switch (opt) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                cout << query_rank(x) << '\n';
                break;
            case 4:
                cout << find_num(x) << '\n';
                break;
            case 5:
                insert(x);
                if((ans=find_front())==-1) {
                    cout<<"NOT FOUND\n";
                } else {
                    cout<<ans<<'\n';
                }
                del(x);
                break;
            case 6:
                insert(x);
                if((ans=find_next())==-1) {
                    cout<<"NOT FOUND\n";
                } else {
                    cout<<ans<<'\n';
                }
                del(x);
                break;
            default:
                break;
        }
    }
    return 0;
}