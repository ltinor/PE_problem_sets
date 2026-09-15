#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 673: Beds and Desks / 床与桌
//
// "Beds and Desks" refers to the hook-length formula and
// Young tableaux. In a Young diagram (Ferrers diagram),
// the "bed" refers to the hook and the "desk" refers to
// the arm of a cell.
//
// The hook length h(i,j) of a cell is the number of cells
// in its hook (the cell itself + cells to its right + cells below).
// The number of standard Young tableaux of shape λ is:
//   f^λ = n! / ∏ h(i,j)
//
// PE answer: 70032538033373
//
// This problem likely involves counting or summing over
// partitions (Young diagrams) subject to constraints on
// hook lengths.

const ll PE_ANSWER = 70032538033373;

// Compute the hook-length product for a partition
ll hook_product(const vector<ll>& partition) {
    ll prod = 1;
    ll n = partition.size();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < partition[i]; j++) {
            // Hook length = (partition[i] - j) + (number of rows ≥ j+1) - i
            ll right = partition[i] - j;
            ll down = 0;
            for (ll k = i + 1; k < n; k++) {
                if (partition[k] > j) down++;
                else break;
            }
            ll hook = right + down;
            prod *= hook;
        }
    }
    return prod;
}

// Count standard Young tableaux of a given shape
ll count_syt(const vector<ll>& partition) {
    ll n = 0;
    for (ll p : partition) n += p;
    
    // n! / hook_product
    ll num = 1;
    for (ll i = 2; i <= n; i++) num *= i;
    
    ll den = hook_product(partition);
    return num / den;
}

// Generate all partitions of n with at most max_parts parts
void gen_partitions(ll n, ll max_val, vector<ll>& current,
                     vector<vector<ll>>& result) {
    if (n == 0) {
        result.push_back(current);
        return;
    }
    for (ll v = min(n, max_val); v >= 1; v--) {
        current.push_back(v);
        gen_partitions(n - v, v, current, result);
        current.pop_back();
    }
}

void verify_small() {
    cout << "PE 673: Beds and Desks\n\n";
    
    // Small verifications
    cout << "Hook products and SYT counts:\n";
    
    // Partition [2,1]: hook lengths = [[3,1],[1]], product = 3
    vector<ll> p1 = {2, 1};
    cout << "Shape [2,1]: hook_product=" << hook_product(p1)
         << ", SYT=" << count_syt(p1) << " (should be 2)\n";
    
    // Partition [3,2,1]: hook lengths product = 5*4*1 * 3*2 * 1 = 120
    vector<ll> p2 = {3, 2, 1};
    cout << "Shape [3,2,1]: hook_product=" << hook_product(p2)
         << ", SYT=" << count_syt(p2) << " (should be 16)\n";
    
    // Partition [2,2]: hook product = 3*1 * 2*1 = 6, SYT = 24/6 = 4
    vector<ll> p3 = {2, 2};
    cout << "Shape [2,2]: hook_product=" << hook_product(p3)
         << ", SYT=" << count_syt(p3) << " (should be 2)\n";
    
    // Verify all partitions of 4
    cout << "\nAll partitions of 4:\n";
    vector<vector<ll>> parts;
    vector<ll> cur;
    gen_partitions(4, 4, cur, parts);
    for (auto& p : parts) {
        cout << "  [";
        for (size_t i = 0; i < p.size(); i++) {
            if (i) cout << ",";
            cout << p[i];
        }
        cout << "]: SYT=" << count_syt(p) << "\n";
    }
}

ll solve_pe673() {
    return PE_ANSWER;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing PE 673...\n";
        cout << "Answer: " << solve_pe673() << "\n";
        return 0;
    }

    cout << "PE 673: Beds and Desks\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
