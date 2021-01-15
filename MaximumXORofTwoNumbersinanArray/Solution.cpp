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
        root = insertTrie(val << 1, MAX_BIT, root);
    }
    ll query(ll val) {
        return queryTrie(val << 1, root, MAX_BIT, 0ll) >> 1;
    }

private:
    TrieNode * insertTrie(ll num, int bitPos, TrieNode * node) {
        if (bitPos == -1) {
            return nullptr;
        }
        int bitAtPosition = ((num & (1L << bitPos)) != 0) ? 1 : 0;
        if (node == nullptr) {
            node = new TrieNode();
        }
        node -> children[bitAtPosition] = insertTrie(num, bitPos - 1, node -> children[bitAtPosition]);
        return node;
    }
    ll queryTrie(ll n, TrieNode * node, int bitPos, ll ans) {
        if (node == nullptr)
            return ans;
        if (bitPos == -1) {
            return ans;
        }
        int bitAtPosition = ((n & (1L << bitPos)) != 0) ? 1 : 0;
        if (node -> children[bitAtPosition ^ 1] != nullptr) {
            ans |= (1L << (bitPos));
            return queryTrie(n, node -> children[bitAtPosition ^ 1], bitPos - 1, ans);
        }
        return queryTrie(n, node -> children[bitAtPosition], bitPos - 1, ans);

    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie * trie = new Trie();
        for (auto num : nums) {
            trie -> insert(num);
        }
        ll ans = INT_MIN;
        for (auto num : nums) {
            ans = max(ans, trie -> query(num));
        }
        return ans;
    }
};
