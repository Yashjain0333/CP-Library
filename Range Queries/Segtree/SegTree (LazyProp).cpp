#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
#define long long int
#define f first
#define s second

struct segtree {

    int size;    // This considers extra elements also to fill upto 2^k elements
    vector<int> operations;
    vector<int> values;
    int NEUTRAL_ELEMENT = 0;
    int NO_OPERATION = LLONG_MAX;

    int modify_op(int a, int b, int len) {
        if (b == NO_OPERATION) return a;
        else return (b * len);
    }

    int calc_op(int a, int b) {
        return a + b;
    }

    void apply_mod_op(int& a, int b, int len) {
        a = modify_op(a, b, len);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = 1ll;
            return;
        }
        int m = (lx + rx) / 2;
        build(2 * x + 1, lx, m);
        build(2 * x + 2, m, rx);
        values[x] = calc_op(values[2 * x + 1], values[2 * x + 2]);
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        operations.assign(2 * size, 0ll);
        values.assign(2 * size, 0ll);
        // build(0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return; // don't propagate
        int m = (lx + rx) / 2;
        apply_mod_op(operations[2 * x + 1], operations[x], 1);
        apply_mod_op(operations[2 * x + 2], operations[x], 1);
        apply_mod_op(values[2 * x + 1], operations[x], m - lx);
        apply_mod_op(values[2 * x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx) return; // completly outside
        if (lx >= l && rx <= r) {
            apply_mod_op(operations[x], v, 1);
            apply_mod_op(values[x], v, rx - lx);
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        values[x] = calc_op(values[2 * x + 1], values[2 * x + 2]);
    }

    void modify(int l, int r, int v) {
        return modify(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r) return values[x];
        int m = (lx + rx) / 2;
        int val1 = calc(l, r, 2 * x + 1, lx, m);
        int val2 = calc(l, r, 2 * x + 2, m, rx);
        int res = calc_op(val1, val2);
        return res;
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

};

int32_t main() {
    return 1;
}