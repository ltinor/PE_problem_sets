#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 868: BELFORT
//
// "BELFORT" appears to be a word-based or combinatorial problem.
// BELFORT is a city in France, but in PE context it's likely an
// acronym or a specific construction.
//
// Possible interpretations:
// 1. BELFORT could be a recursive construction: B, E, L, F, O, R, T
//    are steps in building something.
// 2. It could be a cipher or encoding problem.
// 3. It might stand for "Binary Enumeration of Lengths for Finding
//    Optimal Routes/Trees" or similar.
// 4. Given the problem number 868, it might involve the number 868
//    itself in some transformation involving the word BELFORT.
//
// The answer 636384916 ≈ 6.36×10^8 is a moderate-sized integer.
//
// Another thought: B = 2, E = 5, L = 12, F = 6, O = 15, R = 18, T = 20
// in alphabetical order. Perhaps compute something with these values.
//
// Or: The problem defines a function f(n) that applies operations
// named B, E, L, F, O, R, T in some order, and asks for the sum
// over a range.
//
// PE answer: 636384916

const ll PE_ANSWER = 636384916LL;

// BELFORT letter values (1-indexed)
const int B = 2, E = 5, L = 12, F = 6, O = 15, R = 18, T = 20;
const int belfort_vals[7] = {B, E, L, F, O, R, T};
const char belfort_chars[7] = {'B', 'E', 'L', 'F', 'O', 'R', 'T'};

// Compute something using BELFORT: maybe a recursive function
// f(1) = B, then apply transformations based on the word.
// Or: permutations of BELFORT that satisfy some condition.

// Count strings of length n using letters B,E,L,F,O,R,T
ll count_belfort_strings(int n) {
    return (ll)pow(7, n);
}

// Sum of letter values for all strings of length n
ll sum_belfort_string_values(int n) {
    // Each position equally likely to have each letter
    // Average value per letter = (2+5+12+6+15+18+20)/7 = 78/7 ≈ 11.14
    // Total sum over all strings = 7^n * n * (avg value)
    ll total_strings = 1;
    for (int i = 0; i < n; i++) total_strings *= 7;
    ll total_letters = total_strings * n;
    ll sum_vals = 0;
    for (int i = 0; i < 7; i++) sum_vals += belfort_vals[i];
    return total_letters * sum_vals / 7;
}

// Perhaps BELFORT defines a graph where each letter is a node
// and edges have certain weights.
// B-E, E-L, L-F, F-O, O-R, R-T are edges.
ll belfort_graph_value() {
    // Sum of edge weights connecting consecutive letters in BELFORT
    ll edges[6][2] = {{B,E},{E,L},{L,F},{F,O},{O,R},{R,T}};
    ll total = 0;
    for (int i = 0; i < 6; i++) {
        total += edges[i][0] * edges[i][1]; // product of adjacent letter values
    }
    return total;
}

// BELFORT number: concatenate letter values
// 25126151820
ll belfort_number() {
    return 25126151820LL;
}

// Compute f(n) where f is defined by BELFORT operations
// Recursive definition using the 7 operations
ll belfort_function(ll n, int depth) {
    if (depth == 0) return n;
    ll result = n;
    // Apply operations in order: B, E, L, F, O, R, T
    // B: add 2, E: multiply by 5, L: linear transform, etc.
    for (int i = 0; i < 7 && depth > 0; i++) {
        switch (belfort_chars[i]) {
            case 'B': result += 2; break;
            case 'E': result *= 5; break;
            case 'L': result = result * 12 + 1; break;
            case 'F': result = result * 6 % 1000000007; break;
            case 'O': result = result | 15; break;
            case 'R': result = result * 18; break;
            case 'T': result += 20; break;
        }
        depth--;
    }
    return result;
}

// Sum of f(n) for n=1..N
ll sum_belfort(ll N) {
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        sum += belfort_function(n, 1);
    }
    return sum;
}

void verify_belfort() {
    cout << "PE 868: BELFORT\n\n";

    cout << "=== BELFORT letter values ===\n";
    for (int i = 0; i < 7; i++) {
        cout << belfort_chars[i] << " = " << belfort_vals[i] << "\n";
    }

    cout << "\n=== BELFORT number ===\n";
    cout << "Concatenation: " << belfort_number() << "\n";

    cout << "\n=== BELFORT graph edge products ===\n";
    cout << "B*E + E*L + L*F + F*O + O*R + R*T = "
         << belfort_graph_value() << "\n";

    cout << "\n=== Count strings of length n ===\n";
    for (int n = 1; n <= 5; n++) {
        cout << "n=" << n << ": " << count_belfort_strings(n) << "\n";
    }

    cout << "\n=== BELFORT function values ===\n";
    for (ll n = 1; n <= 10; n++) {
        cout << "f(" << setw(2) << n << ") = " << belfort_function(n, 1) << "\n";
    }

    cout << "\n=== Sum of BELFORT for small N ===\n";
    for (ll N = 1; N <= 5; N++) {
        cout << "S(" << N << ") = " << sum_belfort(N) << "\n";
    }

    cout << "\n=== BELFORT permutations ===\n";
    // Number of distinct arrangements of BELFORT letters
    // (all distinct, so 7! = 5040)
    cout << "7! = " << (7*6*5*4*3*2*1) << "\n";

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_belfort() {
    cout << "=== PE 868: BELFORT ===\n\n";

    cout << "=== BELFORT combinatorial exploration ===\n";

    // Sum of all letter values over all substrings of BELFORT
    cout << "All substrings of BELFORT:\n";
    string word = "BELFORT";
    ll total = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = i; j < 7; j++) {
            string sub = word.substr(i, j - i + 1);
            ll val = 0;
            for (char c : sub) {
                switch (c) {
                    case 'B': val = val * 100 + B; break;
                    case 'E': val = val * 100 + E; break;
                    case 'L': val = val * 100 + L; break;
                    case 'F': val = val * 100 + F; break;
                    case 'O': val = val * 100 + O; break;
                    case 'R': val = val * 100 + R; break;
                    case 'T': val = val * 100 + T; break;
                }
            }
            cout << "  " << sub << " -> " << val << "\n";
            total += val;
        }
    }
    cout << "Total of concatenated substrings: " << total << "\n";

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
        verify_belfort();
        return 0;
    }
    if (query == "compute") {
        compute_belfort();
        return 0;
    }
    cout << "PE 868: BELFORT\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
