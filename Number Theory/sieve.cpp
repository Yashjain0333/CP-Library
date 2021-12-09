const int MAX_SIZE = 2800001;
vector<int>isprime(MAX_SIZE , true);
vector<int> idx(MAX_SIZE);
vector<int> prime;
vector<int>SPF(MAX_SIZE);

void manipulated_seive(int N) {
    isprime[0] = isprime[1] = false ;
    for (int i = 2; i < N ; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            SPF[i] = i;
        }
        for (int j = 0; j < (int)prime.size() && i * prime[j] < N && prime[j] <= SPF[i]; j++) {
            isprime[i * prime[j]] = false;
            SPF[i * prime[j]] = prime[j] ;
        }
    }
    for (int i = 0; i < (int)prime.size(); i++) {
        idx[prime[i]] = i + 1;
    }
}

vector<int> primeFactors(int n) {
    vector<int> factors;
    while (n > 1) {
        factors.push_back(SPF[n]);
        n /= SPF[n];
    }
    return factors;
}
