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

class SegmentTreeNode {
public:
    SegmentTreeNode *left;
    SegmentTreeNode *right;
    int l, r, max;
    SegmentTreeNode(int l, int r) {
        this -> l = l;
        this -> r = r;
        this -> max = INT_MIN;
        this -> left = nullptr;
        this -> right = nullptr;
    }

};

class SegmentTree {
    SegmentTreeNode* root;
public:
    void build(vector<int> &ar, int l, int r) {
        root = build(root, l, r, ar);
    }
    int query(int l, int r) {
        return query_tree(root, l, r);
    }
    void update(int indx, int val) {
        update_tree(root, indx, val);
    }

private:
    SegmentTreeNode* build(SegmentTreeNode * node, int l, int r, vector<int> &ar) {
        if (node == nullptr)
            node = new SegmentTreeNode(l, r);
        if (l < r) {
            int mid = (l + r) >> 1;
            node -> left = build(node->left, l, mid, ar);
            node -> right = build(node->right, mid + 1, r, ar);
            node -> max = max(node -> left -> max, node -> right -> max);
        }
        else if (l == r){
            node -> max = ar[l];
        }
        return node;
    }
    int query_tree(SegmentTreeNode * node, int l, int r) {
        if (node -> r < l || node -> l > r) {
            return INT_MIN;
        }
        if (node -> l >= l && node -> r <= r) {
            return node -> max;
        }
        return max(query_tree(node->left, l, r), query_tree(node->right, l, r));
    }
    void update_tree(SegmentTreeNode * node, int index, int val) {
        if (node -> r < index || node -> l > index) {
            return;
        }
        if (node -> l == index && node -> r == index) {
            node -> max = val;
            return;
        }
        update_tree(node->left, index, val);
        update_tree(node->right, index, val);
        node -> max = max(node -> left -> max, node -> right -> max);
    }
};

class Solution {

public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        map<int, int> index;
        map<int, int> revIndex;
        for (int i = 0; i < target.size(); ++i) {
            index[i] = target[i];
            revIndex[target[i]] = i;
        }
        vector<int> res(target.size());
        fill(res.begin(), res.end(), 0);
        SegmentTree * st = new SegmentTree();
        st -> build(res, 0, target.size() - 1);
        for (int i = 0; i < arr.size(); ++i) {
            if (revIndex.find(arr[i]) != revIndex.end()) {
                int indx = revIndex[arr[i]];
                int maxValueBefore = st->query(0, indx - 1);
                if (maxValueBefore != INT_MIN) {
                    st -> update(indx, maxValueBefore + 1);
                }
                else {
                    st -> update(indx, 1);
                }
            }
        }
        int ans = INT_MAX;
        for (int i = 0; i < target.size(); ++i) {
            int val = st->query(i, i);
            if (val != INT_MIN) {
                ans = min((ll)target.size() - val, (ll)ans);
            }
        }
        return ans;
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Solution* s = new Solution();
    vector<int> target;
    target.push_back(6);
    target.push_back(4);
    target.push_back(8);
    target.push_back(1);
    target.push_back(3);
    target.push_back(2);
    vector<int> arr;
    arr.push_back(4);
    arr.push_back(7);
    arr.push_back(6);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(8);
    arr.push_back(6);
    arr.push_back(1);
    cout << s -> minOperations(target, arr) << endl;
    return 0;
}
