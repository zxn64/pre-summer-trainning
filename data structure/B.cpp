#include <iostream>

using namespace std;
const int max_n = 1e5 + 1;
const int mod_num = 998244353;
int value[max_n];

struct node {
    long long val;
    long long lazy_multi, lazy_add;
    int l, r;
    node *ls, *rs;

    node(int val, int l, int r) {
        this->val = val;
        lazy_add = 0;
        lazy_multi = 1;
        this->l = l;
        this->r = r;
        ls = nullptr;
        rs = nullptr;
    }
};

void io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template<class T>
void mod(T &x) {
    if (x >= mod_num) {
        x %= mod_num;
    }
}

void upload(node *fa) {
    fa->val = fa->ls->val + fa->rs->val;
    mod(fa->val);
}

void download(node *fa) {
    fa->ls->val *= fa->lazy_multi;
    fa->rs->val *= fa->lazy_multi;
    fa->ls->lazy_add *= fa->lazy_multi;
    fa->rs->lazy_add *= fa->lazy_multi;
    fa->ls->lazy_multi *= fa->lazy_multi;
    fa->rs->lazy_multi *= fa->lazy_multi;
    fa->lazy_multi = 1;
    fa->ls->val += (fa->ls->r - fa->ls->l + 1) * fa->lazy_add;
    fa->rs->val += (fa->rs->r - fa->rs->l + 1) * fa->lazy_add;
    fa->ls->lazy_add += fa->lazy_add;
    fa->rs->lazy_add += fa->lazy_add;
    fa->lazy_add = 0;
    mod(fa->ls->val);
    mod(fa->rs->val);
    mod(fa->ls->lazy_add);
    mod(fa->rs->lazy_add);
    mod(fa->ls->lazy_multi);
    mod(fa->rs->lazy_multi);
}

void build(node *fa) {
    if (fa->l == fa->r) {
        fa->val = value[fa->l];
        return;
    }
    int mid = (fa->l + fa->r) / 2;
    build(fa->ls = new node(0, fa->l, mid));
    build(fa->rs = new node(0, mid + 1, fa->r));
    upload(fa);
}

void add(node *fa, int l, int r, int k) {
    if (fa->l >= l && fa->r <= r) {
        fa->val += (fa->r - fa->l + 1) * k;
        fa->lazy_add += k;
        mod(fa->val);
        mod(fa->lazy_add);
        return;
    }
    if(fa->r<l||fa->l>r) return;
    download(fa);
    int mid = (fa->l + fa->r) / 2;
    if (l <= mid) {
        add(fa->ls, l, r, k);
    }
    if (r > mid) {
        add(fa->rs, l, r, k);
    }
    upload(fa);
}

void multiply(node *fa, int l, int r, int k) {
    if (fa->l >= l && fa->r <= r) {
        fa->val *= k;
        fa->lazy_add *= k;
        fa->lazy_multi *= k;
        mod(fa->val);
        mod(fa->lazy_add);
        mod(fa->lazy_multi);
        return;
    }
    if(fa->r<l||fa->l>r) return;
    download(fa);
    int mid = (fa->l + fa->r) / 2;
    if (fa->l <= mid) {
        multiply(fa->ls, l, r, k);
    }
    if (fa->r > mid) {
        multiply(fa->rs, l, r, k);
    }
    upload(fa);
}

long long get_sum(node *fa, int l, int r) {
    if (fa->l >= l && fa->r <= r) {
        return fa->val;
    }
    if(fa->r<l||fa->l>r) return 0;
    download(fa);
    int mid = (fa->l + fa->r) / 2;
    long long sum = 0;
    if (fa->l <= mid) {
        sum += get_sum(fa->ls, l, r);
    }
    if (fa->r > mid) {
        sum += get_sum(fa->rs, l, r);
    }
    mod(sum);
    return sum;
}

int main() {
    io();
    int n, m, opt, l, r, k;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    node *head = new node(0, 1, n);
    build(head);
    for (int i = 0; i < m; i++) {
        cin >> opt;
        switch (opt) {
            case 1:
                cin >> l >> r >> k;
                multiply(head, l, r, k);
                break;
            case 2:
                cin >> l >> r >> k;
                add(head, l, r, k);
                break;
            case 3:
                cin >> l >> r;
                cout << get_sum(head, l, r) << '\n';
                break;
            default:
                break;
        }
    }
    return 0;
}