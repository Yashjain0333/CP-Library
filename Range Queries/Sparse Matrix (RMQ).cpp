// O(1) query sparse matrix for Max/Min/GCD
// O(NlogN) build time

const int M = 2e5, N = 2e5;

int n;
int a[N];
int RMQ[20][N], floorlog[N];

void precompute() {
	for (int i = 0; (1 << i) < N; i++) {
		for (int j = (1 << i); j < N && j < (1 << (i + 1)); j++)
			floorlog[j] = i;
	}

	for (int i = n - 1; i >= 0; i--) {
		RMQ[0][i] = a[i];
		int mxj = floorlog[n - i + 1]; //2^j <= n-i+1
		int pw = 1;
		for (int j = 1; j <= mxj; j++) {
			RMQ[j][i] = min(RMQ[j - 1][i], RMQ[j - 1][i + pw]);
			pw <<= 1;
		}
	}
}

int getMin(int L, int R) {
	int k = floorlog[R - L + 1]; //2^k <= R-L+1
	return min(RMQ[k][L], RMQ[k][R - (1 << k) + 1]);
}

//Sample Problem 1: http://codeforces.com/contest/373/problem/E
//Sample Solution 1: http://codeforces.com/contest/373/submission/39948771
