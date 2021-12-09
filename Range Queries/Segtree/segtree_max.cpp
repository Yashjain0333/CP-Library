struct segtree {

    int size;    // This considers extra elements also to fill upto 2^k elements
    vector<int> maxs;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        maxs.assign(2 * size, 0ll);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        int n = a.size();
        if (rx - lx == 1) {
            if (lx < n) {
                maxs[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        maxs[x] = max(maxs[2 * x + 1], maxs[2 * x + 2]);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {   // we are at the leaf
            maxs[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            set(i, v, 2 * x + 1, lx, m);
        }
        else {
            set(i, v, 2 * x + 2, m, rx);
        }
        maxs[x] = max(maxs[2 * x + 1], maxs[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int maxc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return -INF; // completly outside
        if (lx >= l && rx <= r) return maxs[x]; // completly inside
        int m = (lx + rx) / 2;
        int max1 = maxc(l, r, 2 * x + 1, lx, m);
        int max2 = maxc(l, r, 2 * x + 2, m, rx);
        return max(max1, max2);
    }

    int maxc(int l, int r) {
        return maxc(l, r, 0, 0, size);
    }

};