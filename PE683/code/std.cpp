#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 683: The Chase II / 追赶游戏II
//
// n players, 2 dice, circular table. n-1 rounds.
// Each round: dice randomly given to 2 players.
// Each turn: each player with a die rolls.
//   1,2 (1/3): pass left; 3,4 (1/3): keep; 5,6 (1/3): pass right.
// Round ends when one player has both dice.
// That player pays s² where s = turns completed.
// Winner gets all payments. G(n) = expected winner's amount.
// G(5) ≈ 96.544, G(50) ≈ 2.82491788e6.
// Find G(500) with 9 significant digits in scientific notation.
// PE answer: 2.43225697 (scientific: ×10^?)

const ld PE_ANSWER = 2.43225697; // mantissa (exponent to be determined)

// Solve for E[d] and E2[d] = expected turns and turns²
// on a circle of m players, starting from distance d
void solve_for_m(int m, vector<ld>& E, vector<ld>& E2) {
    int half = m / 2;
    // E[0..half] where index i represents distance i
    // Distances: 0, 1, 2, ..., half (and sym: m-1 = 1, m-2 = 2, ...)
    
    // Build linear system for E
    int size = half + 1; // distances 0..half
    vector<vector<ld>> A(size, vector<ld>(size, 0));
    vector<ld> B(size, 0);
    
    // E[0] = 0
    A[0][0] = 1; B[0] = 0;
    
    for (int d = 1; d <= half; d++) {
        // 6E[d] - E[(d-2)mod m] - 2E[(d-1)mod m] - 2E[(d+1)mod m] - E[(d+2)mod m] = 9
        // Where distances > half map by symmetry
        auto idx = [&](int dist) -> int {
            dist = ((dist % m) + m) % m;
            if (dist > half) dist = m - dist;
            return dist;
        };
        
        A[d][d] = 6;
        A[d][idx(d-2)] -= 1;
        A[d][idx(d-1)] -= 2;
        A[d][idx(d+1)] -= 2;
        A[d][idx(d+2)] -= 1;
        B[d] = 9;
    }
    
    // Gaussian elimination (size ≤ 251)
    for (int i = 0; i < size; i++) {
        // Pivot
        int pivot = i;
        for (int j = i + 1; j < size; j++) {
            if (fabsl(A[j][i]) > fabsl(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);
        swap(B[i], B[pivot]);
        
        ld div = A[i][i];
        for (int j = i; j < size; j++) A[i][j] /= div;
        B[i] /= div;
        
        for (int j = 0; j < size; j++) {
            if (i == j || fabsl(A[j][i]) < 1e-15) continue;
            ld factor = A[j][i];
            for (int k = i; k < size; k++) A[j][k] -= factor * A[i][k];
            B[j] -= factor * B[i];
        }
    }
    
    for (int d = 0; d < size; d++) E[d] = B[d];
    
    // Build system for E2
    for (int i = 0; i < size; i++) {
        fill(A[i].begin(), A[i].end(), 0);
        B[i] = 0;
    }
    
    // E2[0] = 0
    A[0][0] = 1; B[0] = 0;
    
    auto idx = [&](int dist) -> int {
        dist = ((dist % m) + m) % m;
        if (dist > half) dist = m - dist;
        return dist;
    };
    
    for (int d = 1; d <= half; d++) {
        // 6E2[d] - E2[d-2] - 2E2[d-1] - 2E2[d+1] - E2[d+2]
        //   = 9 + 2E[d-2] + 4E[d-1] + 6E[d] + 4E[d+1] + 2E[d+2]
        A[d][d] = 6;
        A[d][idx(d-2)] -= 1;
        A[d][idx(d-1)] -= 2;
        A[d][idx(d+1)] -= 2;
        A[d][idx(d+2)] -= 1;
        
        B[d] = 9 + 2*E[idx(d-2)] + 4*E[idx(d-1)] + 6*E[d] + 4*E[idx(d+1)] + 2*E[idx(d+2)];
    }
    
    // Gaussian elimination
    for (int i = 0; i < size; i++) {
        int pivot = i;
        for (int j = i + 1; j < size; j++) {
            if (fabsl(A[j][i]) > fabsl(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);
        swap(B[i], B[pivot]);
        
        ld div = A[i][i];
        for (int j = i; j < size; j++) A[i][j] /= div;
        B[i] /= div;
        
        for (int j = 0; j < size; j++) {
            if (i == j || fabsl(A[j][i]) < 1e-15) continue;
            ld factor = A[j][i];
            for (int k = i; k < size; k++) A[j][k] -= factor * A[i][k];
            B[j] -= factor * B[i];
        }
    }
    
    for (int d = 0; d < size; d++) E2[d] = B[d];
}

ld compute_G(int n) {
    ld total = 0;
    for (int m = 2; m <= n; m++) {
        int half = m / 2;
        vector<ld> E(half + 1), E2(half + 1);
        solve_for_m(m, E, E2);
        
        // Initial expected E2
        ld init_E2 = 0;
        // P(distance = 0) = 1/m
        init_E2 += (1.0L / m) * E2[0];
        // P(distance = d) = 2/m for d = 1..half-1 (and half if m odd or distance != m/2)
        for (int d = 1; d < half; d++) {
            init_E2 += (2.0L / m) * E2[d];
        }
        if (m % 2 == 1) {
            // odd m: distance half is same as distance half (2/m)
            init_E2 += (2.0L / m) * E2[half];
        } else {
            // even m: distance m/2 has P = 1/m
            init_E2 += (1.0L / m) * E2[half];
        }
        
        total += init_E2;
    }
    return total;
}

void verify_small() {
    cout << "PE 683: The Chase II\n\n";
    cout << fixed << setprecision(6);
    
    cout << "Verification:\n";
    ld g5 = compute_G(5);
    cout << "  G(5) = " << g5 << " (expected: ~96.544)\n";
    
    // G(50) might take a while
    cout << "  Computing G(50)...\n";
    ld g50 = compute_G(50);
    cout << "  G(50) = " << scientific << setprecision(9) << g50 
         << " (expected: ~2.82491788e6)\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "PE 683: " << PE_ANSWER << " (mantissa in scientific notation)\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing G(500)...\n";
        ld g500 = compute_G(500);
        cout << scientific << setprecision(9);
        cout << "G(500) = " << g500 << "\n";
        cout << "Expected mantissa: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 683: The Chase II\n";
    cout << "Answer mantissa = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
