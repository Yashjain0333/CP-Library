const int MAXN = 300005, MAXL = 555555;
const int D = 998244353, G = 3, invG = 332748118;
int n, m, Q, q[MAXN], a[MAXN], b[10], ans[MAXN << 1];
int cnt[MAXN], fac[MAXN], inv[MAXN];

int C(int x, int y) {return 1ll * fac[x] * inv[y] % D * inv[x - y] % D;}

int rev[MAXL];
typedef vector<int> Poly;

int add(int x, int y) {return x + y < D ? x + y : x + y - D;}
int dec(int x, int y) {return x < y ? x - y + D : x - y;}
int qpow(int x, int y) {
    int ret = 1;
    while (y) {
        if (y & 1) ret = 1ll * ret * x % D;
        x = 1ll * x * x % D;
        y >>= 1;
    }
    return ret;
}
void NTT(Poly &f, int lim, int op) {
    for (int i = 1; i < lim; i++) if (i > rev[i]) swap(f[i], f[rev[i]]);
    for (int i = 1; i < lim; i <<= 1)
        for (int sta = qpow((~op) ? G : invG, (D - 1) / (i << 1)), j = 0; j < lim; j += (i << 1))
            for (int w = 1, t1, t2, k = 0; k < i; k++, w = 1ll * w * sta % D)
                t1 = f[j + k], t2 = 1ll * w * f[i + j + k] % D, f[j + k] = add(t1, t2), f[i + j + k] = dec(t1, t2);
    if (!~op) for (int inv_lim = qpow(lim, D - 2), i = 0; i < lim; i++) f[i] = 1ll * f[i] * inv_lim % D;
}

Poly operator * (Poly aa, Poly bb) {
    Poly ret;
    int len = aa.size() + bb.size() - 1, lim;
    for (lim = 1; lim <= len; lim <<= 1);
    for (int i = 1; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? lim >> 1 : 0);
    aa.resize(lim), bb.resize(lim), ret.resize(lim);
    NTT(aa, lim, 1), NTT(bb, lim, 1);
    for (int i = 0; i < lim; i++) ret[i] = 1ll * aa[i] * bb[i] % D;
    NTT(ret, lim, -1);
    ret.resize(len);
    return ret;
}

Poly A, B, F;

// Coded by G_keng (cf)