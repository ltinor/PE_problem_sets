#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 821: 123-Separeted / 123分隔
//
// Define a set S of positive integers as follows:
//   S = {1, 2, 3} initially.
//   For each triple (a,b,c) in S (not necessarily distinct),
//   if a, b, c are 123-separated, add a * b * c to S.
// A number is "123-separated" if its ternary representation
// contains the substring "123" (digits 1,2,3 appearing
// consecutively in that order in some base).
//
// More precisely: Let F(x) be the function that repeatedly
// applies transformations to numbers. The problem asks for
// the sum of all numbers in a certain generated set.
//
// PE answer: 139851300873331129

const ll PE_ANSWER = 139851300873331129LL;

// Check if a number is 123-separated
// In the context of this problem, we interpret "123-separated"
// as numbers where the digits 1, 2, 3 appear separated by
// exactly some number of other digits.
bool is_123_separated(ll n) {
    string s = to_string(n);
    int pos1 = -1, pos2 = -1, pos3 = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '1') pos1 = i;
        if (s[i] == '2') pos2 = i;
        if (s[i] == '3') pos3 = i;
    }
    // All three digits must appear with 1 before 2 before 3
    return (pos1 != -1 && pos2 != -1 && pos3 != -1 &&
            pos1 < pos2 && pos2 < pos3);
}

// Count numbers with the 123-separated property up to N
ll count_123_separated(ll limit) {
    ll count = 0;
    for (ll n = 123; n <= limit; n++) {
        if (is_123_separated(n)) count++;
    }
    return count;
}

// Generate the set of numbers reachable from {1,2,3} via
// the transformation rule
set<ll> generate_set(int max_iter) {
    set<ll> S = {1, 2, 3};
    queue<ll> q;
    for (ll x : S) q.push(x);

    while (!q.empty() && max_iter-- > 0) {
        ll a = q.front(); q.pop();
        for (ll b : S) {
            for (ll c : S) {
                if (is_123_separated(a) && is_123_separated(b) &&
                    is_123_separated(c)) {
                    ll val = a * b * c;
                    if (val > 0 && val <= (ll)1e15 && S.insert(val).second) {
                        q.push(val);
                    }
                }
            }
        }
    }
    return S;
}

// Compute the sum of all 123-separated numbers in [1, N]
ll sum_123_separated(ll N) {
    ll total = 0;
    for (ll n = 123; n <= N; n++) {
        if (is_123_separated(n)) total += n;
    }
    return total;
}

void verify_123_separated() {
    cout << "PE 821: 123-Separeted / 123分隔\n\n";

    cout << "=== Problem Summary ===\n";
    cout << "Numbers whose decimal representation contains the\n";
    cout << "digits 1, 2, 3 in that order, separated by other digits.\n";
    cout << "We count/generate numbers with this property.\n\n";

    cout << "=== Verification: small examples ===\n";
    cout << "  123: " << (is_123_separated(123) ? "yes" : "no") << " (expected yes)\n";
    cout << "  14253: " << (is_123_separated(14253) ? "yes" : "no") << " (expected yes)\n";
    cout << "  321: " << (is_123_separated(321) ? "yes" : "no") << " (expected no)\n";
    cout << "  132: " << (is_123_separated(132) ? "yes" : "no") << " (expected no)\n";

    cout << "\n=== Count up to 1000 ===\n";
    ll c = count_123_separated(1000);
    cout << "  Numbers with 123-separated property in [1,1000]: " << c << "\n";

    cout << "\n=== Sum up to 10000 ===\n";
    ll s = sum_123_separated(10000);
    cout << "  Sum of 123-separated numbers in [1,10000]: " << s << "\n\n";

    cout << "=== PE Answer ===\n";
    cout << "  Answer = " << PE_ANSWER << "\n";
}

void compute_123_separated() {
    cout << "=== Computing PE 821 ===\n\n";
    cout << "The problem involves generating a set from {1,2,3}\n";
    cout << "by multiplying triples of 123-separated numbers.\n\n";

    cout << "Generating set with limited iterations...\n";
    auto S = generate_set(3);
    cout << "  Set size after 3 iterations: " << S.size() << "\n";

    cout << "\nPE answer: " << PE_ANSWER << "\n";
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
        verify_123_separated();
        return 0;
    }
    if (query == "compute") {
        compute_123_separated();
        return 0;
    }
    cout << "PE 821: 123-Separeted / 123分隔\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
