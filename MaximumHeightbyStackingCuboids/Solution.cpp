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
    static bool cuboid_comparator(vector<int>& a, vector<int>& b) {
        if (a[0] != b[0]) {
            return a[0] > b[0];
        }
        if (a[1] != b[1]) {
            return a[1] > b[1];
        }
        return a[2] > b[2];
    }
    int maxHeight(vector<vector<int>>& cuboids) {
        for (auto & cuboid : cuboids) {
            sort(cuboid.begin(), cuboid.end());
        }
        vector<int> base = {0, 0, 0};
        cuboids.push_back(base);
        sort(cuboids.begin(), cuboids.end(), cuboid_comparator);
        int n = cuboids.size();
        int dp[n];
        for (int i = 0; i < n; i++) {
            dp[i] = cuboids[i][2];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (cuboids[j][0] >= cuboids[i][0] && cuboids[j][1] >= cuboids[i][1] && cuboids[j][2] >= cuboids[i][2]) {
                    dp[i] = max((ll)dp[i], dp[j] + (ll)cuboids[i][2]);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max((ll)res, (ll)dp[i]);
        }
        return res;
    }
};
