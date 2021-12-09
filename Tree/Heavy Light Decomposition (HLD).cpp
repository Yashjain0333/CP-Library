// Inspired by galen_colin
// This currently works for XOR queries

template<int size, int lg, typename seg_t = long long>
struct HLD {

	// Items for HLD
	vector<int> edges[size];
	int bigchild[size];
	int sz[size];
	int depth[size];
	int chain[size];
	int label[size], label_time;
	int par[size];

	// Items for LCA
	int lca_lift[size][lg];

	// Items for Segtree
	seg_t seg_tree[4 * size];
	seg_t seg_lazy[4 * size];
	int N;

	/* ----------- Segment Tree ----------- */

	/* CHANGE THIS SECTION BY PROBLEM */

	// This combines two segments
	inline seg_t seg_combine(seg_t a, seg_t b) {
		return a ^ b;
	}

	// This helps propagate the operation downwards
	inline seg_t seg_lazy_apply(seg_t lazy_val, seg_t new_val) {
		return new_val;
	}

	// This applies the operation onto the segment
	inline seg_t seg_lazy_func(seg_t cur_val, seg_t lazy_val, int l, int r) {
		return lazy_val;
	}

	const seg_t seg_sentinel = 0;
	const seg_t seg_lazy_sentinel = -1;
	const seg_t seg_init_val = 0;

	/* END SECTION */

	seg_t seg_query_header(int l, int r) {
		return seg_query_rec(0, 0, N - 1, l, r);
	}

	seg_t seg_query_rec(int i, int tl, int tr, int ql, int qr) {
		seg_eval_lazy(i, tl, tr);

		if (ql <= tl && tr <= qr) return seg_tree[i]; // Completly inside
		if (tl > tr || tr < ql || qr < tl) return seg_sentinel; // Completly outside the segment

		int mid = (tl + tr) / 2;
		seg_t a = seg_query_rec(2 * i + 1, tl, mid, ql, qr);
		seg_t b = seg_query_rec(2 * i + 2, mid + 1, tr, ql, qr);
		return seg_combine(a, b);
	}

	void seg_update_header(int l, int r, seg_t v) {
		seg_update_rec(0, 0, N - 1, l, r, v);
	}

	seg_t seg_update_rec(int i, int tl, int tr, int ql, int qr, seg_t v) {
		seg_eval_lazy(i, tl, tr);

		if (tl > tr || tr < ql || qr < tl) return seg_tree[i]; // Completly inside
		if (ql <= tl && tr <= qr) {
			seg_lazy[i] = seg_lazy_apply(seg_lazy[i], v); // First apply it here
			seg_eval_lazy(i, tl, tr);  // Then do the lazy propagation for this operation
			return seg_tree[i];
		}
		if (tl == tr) return seg_tree[i];

		int mid = (tl + tr) / 2;
		seg_t a = seg_update_rec(2 * i + 1, tl, mid, ql, qr, v);
		seg_t b = seg_update_rec(2 * i + 2, mid + 1, tr, ql, qr, v);
		return seg_tree[i] = seg_combine(a, b);
	}

	void seg_eval_lazy(int i, int l, int r) {
		if (seg_lazy[i] == seg_lazy_sentinel) return;

		seg_tree[i] = seg_lazy_func(seg_tree[i], seg_lazy[i], l, r);

		if (l != r) {
			seg_lazy[i * 2 + 1] = seg_lazy_apply(seg_lazy[i * 2 + 1], seg_lazy[i]);
			seg_lazy[i * 2 + 2] = seg_lazy_apply(seg_lazy[i * 2 + 2], seg_lazy[i]);
		}

		seg_lazy[i] = seg_lazy_sentinel;
	}

	/* ----------- init phase 1 ----------- */
	/* initialize segtree, clear edges, etc. */

	void init_arrays(int n) {
		N = n;

		// Initialization for HLD
		for (int i = 0; i < N; i++) {
			edges[i].clear();
			chain[i] = i;  // Initially every node is a chain
		}

		// Initialization for segtree
		for (int i = 0; i < 4 * N; i++) {
			seg_tree[i] = seg_init_val;
			seg_lazy[i] = seg_lazy_sentinel;
		}
	}

	/* ----------- init phase 2 ----------- */
	/* put edges in */

	void add_edge(int u, int v) {
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	/* ----------- init phase 3 ----------- */
	/* Build the lca and hld stuff */
	/* First write the utility functions for HLD */

	void lca_dfs(int v, int par) {
		lca_lift[v][0] = par;

		for (int i = 1; i < lg; i++) {
			if (lca_lift[v][i - 1] == -1) lca_lift[v][i] = -1;
			else lca_lift[v][i] = lca_lift[lca_lift[v][i - 1]][i - 1];
		}

		for (int x : edges[v]) {
			if (x != par) {
				lca_dfs(x, v);
			}
		}
	}

	void dfs_size(int u, int p, int d) {
		sz[u] = 1;
		depth[u] = d;
		par[u] = p;
		int bigc = -1, bigv = -1;

		for (int x : edges[u]) {
			if (x == p) continue;
			dfs_size(x, u, d + 1);
			sz[u] += sz[x];
			if (sz[x] > bigv) {
				bigv = sz[x];
				bigc = x;
			}
		}

		bigchild[u] = bigc;
	}

	void dfs_chains(int u, int p) {
		if (bigchild[u] != -1) {
			chain[bigchild[u]] = chain[u];  // Unite The bigchild to the current chain
		}

		for (int x : edges[u]) {
			if (x == p) continue;
			dfs_chains(x, u);
		}
	}

	void dfs_labels(seg_t* arr, int u, int p) {
		// We are labelling edges such that every heavy chain forms a consecutive sequence of numbers

		label[u] = label_time++;
		seg_update_header(label[u], label[u], arr[u]);

		// If this node has a bigchild then go there First
		if (bigchild[u] != -1) {
			dfs_labels(arr, bigchild[u], u);
		}

		for (int x : edges[u]) {
			if (x != p && x != bigchild[u]) {
				dfs_labels(arr, x, u);
			}
		}

	}

	void init_tree(seg_t* arr, int root = 0) {
		// lca
		lca_dfs(root, -1);

		// size, compute biggest child
		dfs_size(root, -1, 0);

		// compute chains
		dfs_chains(root, -1);

		// label nodes
		label_time = 0;
		dfs_labels(arr, root, -1);
	}

	/* ----------- init phase 4 ----------- */
	/* Usage */

	int lca(int a, int b) {
		if (depth[a] < depth[b]) swap(a, b);
		int d = depth[a] - depth[b];
		int v = get_kth_ancestor(a, d);
		if (v == b) {
			return v;
		} else {
			for (int i = lg - 1; i >= 0; i--) {
				if (lca_lift[v][i] != lca_lift[b][i]) {
					v = lca_lift[v][i];
					b = lca_lift[b][i];
				}
			}
			return lca_lift[b][0];
		}
	}

	int get_kth_ancestor(int v, int k) {
		for (int i = lg - 1; i >= 0; i--) {
			if (v == -1) return v;
			if ((1 << i) <= k) {
				v = lca_lift[v][i];
				k -= (1 << i);
			}
		}
		return v;
	}

	/* This excludes the p node */
	seg_t query_chain(int u, int p) {
		seg_t val = seg_sentinel;
		while (depth[p] < depth[u]) {
			int top = chain[u];
			if (depth[top] <= depth[p]) { // Go as high as we can on this chain
				int diff = depth[u] - depth[p];
				top = get_kth_ancestor(u, diff - 1);
			}
			val = seg_combine(val, seg_query_header(label[top], label[u]));
			u = par[top];
		}
		return val;
	}

	seg_t query(int u, int v) {
		int lc = lca(u, v);
		seg_t val = seg_combine(query_chain(u, lc), query_chain(v, lc));
		return seg_combine(val, seg_query_header(label[lc], label[lc]));
	}

	/* excludes p */
	void update_chain(int u, int p, seg_t val) {
		while (depth[p] < depth[u]) {
			int top = chain[u];
			if (depth[top] <= depth[p]) {
				int diff = depth[u] - depth[p];
				top = get_kth_ancestor(u, diff - 1);
			}
			seg_update_header(label[top], label[u], val);
			u = par[top];
		}
	}

	void update(int u, int v, seg_t val) {
		int lc = lca(u, v);
		update_chain(u, lc, val);
		update_chain(v, lc, val);
		seg_update_header(label[lc], label[lc], val);
	}

};

/*

Step 1: hld.init_arrays(n);

Step 2: hld.add_edge(x,y);

Step 3: hld.init_tree(a);   // Note you will have to use an array here and not a vector

Step 4: Updates hld.update(l,r,v);

Step 5: Query, hld.query(u,v);

*/