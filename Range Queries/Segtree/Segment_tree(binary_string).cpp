// This segment tree assigns a range of [l,r) to either 0 or 1, and also maintains the count of number of
// 1s for each segment. One can find the resultant string by asking queries (i,i+1) for each index i.

struct segtree {

    int size;
    vector<int> cnt;
    vector<int> operations;
    int NO_OPERATION = INT_MAX;
    // 0 means all 0s and 1 means all 1s

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

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        cnt.assign(2 * size, 0ll);
        operations.assign(2 * size, NO_OPERATION);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;  // reached the leaf
        int m = (rx + lx) / 2;
        apply_mod_op(operations[2 * x + 1], operations[x], 1);
        apply_mod_op(operations[2 * x + 2], operations[x], 1);
        apply_mod_op(cnt[2 * x + 1], operations[x], m - lx);
        apply_mod_op(cnt[2 * x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }

    void build(string& s, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < s.length() && s[lx] == '1') cnt[x]++;
            return;
        }
        int m = (rx + lx) / 2;
        build(s, 2 * x + 1, lx, m);
        build(s, 2 * x + 2, m, rx);
        cnt[x] = calc_op(cnt[2 * x + 1], cnt[2 * x + 2]);
    }

    void build(string& s) {
        build(s, 0, 0, size);
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (lx >= l && rx <= r) {
            operations[x] = v;
            if (v == 1) cnt[x] = rx - lx;
            else cnt[x] = 0;
            return;
        }
        int m = (rx + lx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        cnt[x] = calc_op(cnt[2 * x + 1], cnt[2 * x + 2]);
    }

    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    int count(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || r <= lx) return 0;
        if (lx >= l && rx <= r) return cnt[x];
        int m = (rx + lx) / 2;
        int cnt1 = count(l, r, 2 * x + 1, lx, m);
        int cnt2 = count(l, r, 2 * x + 2, m, rx);
        return calc_op(cnt1, cnt2);
    }

    int count(int l, int r) {
        return count(l, r, 0, 0, size);
    }

};