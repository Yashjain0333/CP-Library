void solve() {
    int x, n, a[200002];
    set <int> s;
    multiset <int> m;
    cin >> x >> n;
    s.insert(0); s.insert(x);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        auto l = s.lower_bound(a[i]), r = --s.upper_bound(a[i]);
        deb(*l)
        deb(*r)
        if (*l > a[i]) --l;
        if (*r < a[i]) ++r;
        auto f = m.find(*r - *l);
        if (f != m.end()) m.erase(f);
        m.insert(a[i] - *l);
        m.insert(*r - a[i]);
        s.insert(a[i]);
        cout << *--m.end() << ' ';
    }
}

i / p:

8 3
3 6 2

o / p:

*l: 8
*r: 0
5 * l: 8
*r: 3
3 * l: 3
*r: 0
3