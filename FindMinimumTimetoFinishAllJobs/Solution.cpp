#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <climits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <deque>
#include <climits>
#include <algorithm>
#include <utility>
#include <bitset>
#include <iterator>
#include <iomanip>
#include <cmath>

#define ll long long int

using namespace std;


class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        ll dp[1 << n][k + 1];
        int val_mask[1 << n];
        fill(val_mask, val_mask + (1 << n), 0);
        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    val_mask[i] += jobs[j];
                }
            }
        }
        for (int i = 0; i < 1 << n; ++i) {
            fill(dp[i], dp[i] + k + 1, INT_MAX);
        }
        for (int i = 0; i < 1 << n; ++i) {
            dp[i][1] = val_mask[i];
        }
        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 2; j <= k; ++j) {
                dp[i][j] = dp[i][j - 1];
                for (int l = 0; l < i; ++l) {
                    if ((i & l) == l) {
                        dp[i][j] = min((ll) dp[i][j], max((ll) dp[l][j - 1], (ll) val_mask[i ^ l]));
                    }
                }
            }
        }
        return (int)dp[(1 << n) -  1][k];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Solution * solution = new Solution();
    vector<int> vec = {3, 2, 3};
    cout << solution -> minimumTimeRequired(vec, 3) << endl;
    Solution * solution1 = new Solution();
    vector<int> v = {1,2,4,7,8};
    cout << solution1 -> minimumTimeRequired(v, 2) << endl;
    return 0;
}
