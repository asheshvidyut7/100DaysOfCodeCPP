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

class TrieNode {
public:
    TrieNode * children[2];
};

class Trie {
    TrieNode * root;
    int MAX_BIT = 35;
public:
    void insert(ll val) {
        root = insert_trie(val << 1, MAX_BIT, root);
    }
    ll query(ll val) {
        return query_trie(val << 1, root, MAX_BIT, 0ll) >> 1;
    }

private:
    TrieNode * insert_trie(ll num, int bitPos, TrieNode * node) {
        if (bitPos == -1) {
            return nullptr;
        }
        int bitAtPosition = ((num & (1L << bitPos)) != 0) ? 1 : 0;
        if (node == nullptr) {
            node = new TrieNode();
        }
        node -> children[bitAtPosition] = insert_trie(num, bitPos - 1, node->children[bitAtPosition]);
        return node;
    }
    ll query_trie(ll n, TrieNode * node, int bitPos, ll ans) {
        if (node == nullptr)
            return ans;
        if (bitPos == -1) {
            return ans;
        }
        int bitAtPosition = ((n & (1L << bitPos)) != 0) ? 1 : 0;
        if (node -> children[bitAtPosition ^ 1] != nullptr) {
            ans |= (1L << (bitPos));
            return query_trie(n, node->children[bitAtPosition ^ 1], bitPos - 1, ans);
        }
        return query_trie(n, node->children[bitAtPosition], bitPos - 1, ans);

    }
};

class Solution {
public:
    static bool compare_queries(vector<int> & x, vector<int> & y) {
        return x[1] < y[1];
    };
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        for (int i = 0; i < queries.size(); ++i) {
            queries[i].push_back(i);
        }
        sort(queries.begin(), queries.end(), compare_queries);
        sort(nums.begin(), nums.end());
        int index_num = 0;
        vector<int> ans(queries.size());
        Trie* t = new Trie();
        for (int i = 0; i < queries.size(); ++i) {
            int m = queries[i][1];
            while(index_num < nums.size() && nums[index_num] <= m) {
                t -> insert(nums[index_num]);
                index_num++;
            }
            if (index_num != 0)
                ans[queries[i][2]] = (int)(t -> query(queries[i][0]));
            else
                ans[queries[i][2]] = -1;
        }
        return ans;
    }
};

