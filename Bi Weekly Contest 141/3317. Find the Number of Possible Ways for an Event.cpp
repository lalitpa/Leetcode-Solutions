
class Solution {
public:
    int MOD = 1000000007;
    int numberOfWays(int n, int x, int y) {

        if (x == 0) {
            return 0;
        }

        // Precompute combinations
        vector<vector<long long>> comb(x + 1, vector<long long>(x + 1, 0));
        comb[0][0] = 1;
        for (int i = 1; i <= x; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }

        // Precompute Stirling numbers of the second kind
        vector<vector<long long>> S(n + 1, vector<long long>(x + 1, 0));
        S[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, x); j++) {
                S[i][j] = (S[i - 1][j - 1] + (j * S[i - 1][j]) % MOD) % MOD;
            }
        }

        // Precompute factorials
        vector<long long> fact(x + 1, 1);
        for (int i = 1; i <= x; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        // Precompute powers of y
        vector<long long> powerY(x + 1, 1);
        for (int i = 1; i <= x; i++) {
            powerY[i] = (powerY[i - 1] * y) % MOD;
        }

        long long result = 0;
        for (int m = 1; m <= x && m <= n; m++) {
            long long combination = comb[x][m];
            long long stirling = S[n][m];
            long long factorial = fact[m];
            long long yPower = powerY[m];

            // Compute the term
            long long term = (((combination * stirling) % MOD) * factorial) % MOD;
            term = (term * yPower) % MOD;
            result = (result + term) % MOD;
        }

        return (int)result;
    }
};
