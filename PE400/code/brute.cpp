#include<bits/stdc++.h>
using namespace std;

// PE400 brute: Fibonacci tree game for k ≤ 6
// Build T(k), for each non-root node, check if removal leaves P-position
// P-position check: next player has no winning move

struct Node {
    Node *left, *right;
    int id;
    Node(int _id) : left(nullptr), right(nullptr), id(_id) {}
};

Node* build(int k, int& nid) {
    if (k == 0) return nullptr;
    Node* u = new Node(nid++);
    if (k == 1) return u;
    u->left = build(k-1, nid);
    u->right = build(k-2, nid);
    return u;
}

// Copy tree excluding the subtree rooted at node with id=exclude_id
Node* copy_excl(Node* u, int exclude_id) {
    if (!u || u->id == exclude_id) return nullptr;
    Node* v = new Node(u->id);
    v->left = copy_excl(u->left, exclude_id);
    v->right = copy_excl(u->right, exclude_id);
    return v;
}

void delete_tree(Node* u) {
    if (!u) return;
    delete_tree(u->left);
    delete_tree(u->right);
    delete u;
}

void get_ids(Node* u, vector<int>& ids) {
    if (!u) return;
    ids.push_back(u->id);
    get_ids(u->left, ids);
    get_ids(u->right, ids);
}

// Recursively determine if position is P-position (previous player wins / current player loses)
// In poison game: root cannot be taken (would lose). Only root = forced loss when alone.
map<string, bool> is_P_memo;

string encode(Node* u) {
    if (!u) return ".";
    return "(" + encode(u->left) + ")" + to_string(u->id) + "(" + encode(u->right) + ")";
}

// Returns true if this position is a P-position (current player loses with optimal play)
bool is_P(Node* u) {
    if (!u) return true; // no moves → lose → P-position
    
    vector<int> ids;
    get_ids(u, ids);
    if (ids.size() == 1) return true; // only root → must take it → lose → P-position
    
    string key = encode(u);
    if (is_P_memo.count(key)) return is_P_memo[key];
    
    // Current player's moves: any non-root node
    // If ANY move leads to P-position (for opponent), then this is N-position (winning)
    for (int vid : ids) {
        if (vid == u->id) continue;
        Node* after = copy_excl(u, vid);
        if (is_P(after)) {
            delete_tree(after);
            return is_P_memo[key] = false; // found winning move → N-position
        }
        delete_tree(after);
    }
    // No winning move found → P-position
    return is_P_memo[key] = true;
}

int f(int k) {
    if (k <= 1) return 0;
    
    is_P_memo.clear();
    int nid = 1;
    Node* root = build(k, nid);
    
    vector<int> ids;
    get_ids(root, ids);
    
    int win = 0;
    for (int vid : ids) {
        if (vid == root->id) continue;
        Node* after = copy_excl(root, vid);
        if (is_P(after)) win++;
        delete_tree(after);
    }
    
    delete_tree(root);
    return win;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int k; cin >> k;
    cout << f(k) << "\n";
}
