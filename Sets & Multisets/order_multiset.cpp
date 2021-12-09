struct ordered_multiset { // multiset supporting duplicating values in set
    int len = 0;
    const int ADD = 1000010;
    const int MAXVAL = 1000000010;
    unordered_map<int, int> mp; // hash = 96814
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> T;

    ordered_multiset() { len = 0; T.clear(), mp.clear(); }

    inline void insert(int x) {
        len++, x += MAXVAL;
        int c = mp[x]++;
        T.insert((x * ADD) + c);
    }

    inline void erase(int x) {
        x += MAXVAL;
        int c = mp[x];
        if (c) {
            c--, mp[x]--, len--;
            T.erase((x * ADD) + c);
        }
    }

    inline int kth(int k) {       // 1-based index,  returns the
        if (k < 1 || k > len) return -1; // K'th element in the treap,
        auto it = T.find_by_order(--k); // -1 if none exists
        return ((*it) / ADD) - MAXVAL;
    }

    inline int lower_bound(int x) {     // Count of value <x in treap
        x += MAXVAL;
        int c = mp[x];
        return (T.order_of_key((x * ADD) + c));
    }

    inline int upper_bound(int x) {     // Count of value <=x in treap
        x += MAXVAL;
        int c = mp[x];
        return (len - T.order_of_key((x * ADD) + c));
    }

    inline int size() { return len; }   // Number of elements in treap
};