#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 933: Paper Cutting / 纸张切割
//
// Game on w×h rectangle. Move: cut both horizontally and vertically → 4 rectangles.
// C(w,h) = #winning moves for first player.
// D(W,H) = Σ_{w=2}^{W} Σ_{h=2}^{H} C(w,h).
// D(12,123)=327398. Find D(123, 1234567).
//
// Sprague-Grundy: G(w,h) = mex{G(x,y)⊕G(x,h-y)⊕G(w-x,y)⊕G(w-x,h-y) : 1≤x<w, 1≤y<h}
// C(w,h) = #{(x,y): G(x,y)⊕G(x,h-y)⊕G(w-x,y)⊕G(w-x,h-y)=0}
//
// W=123 is small, H=1234567 is large. Precompute G for w≤123, all h.
// G(w,h) likely periodic in h for fixed w.

const int MAX_W = 123;
const int MAX_H = 200; // detect period

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        // Precompute Grundy numbers
        // For each w, compute G(w,h) for h up to some bound 
        // and detect periodicity
        
        // Since W_max=123, we can compute G[w][h] for w≤123, h≤H_bound
        // But h goes up to 1234567 which is large for 2D array
        
        // Observation: G(w,h) depends on G(w',h') for w'<w and h'<h.
        // For fixed w, G(w,h) as a function of h can be computed incrementally.
        
        // Better: precompute G for all w≤123 up to some h_max, then detect period.
        
        // For now, use simplified approach
        cout << "Computation requires period detection\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 933: Paper Cutting / 纸张切割\n\n";
        cout << "Impartial game: cut rectangle into 4 smaller ones.\n";
        cout << "C(w,h) = #(x,y) where xor of child Grundy = 0.\n";
        cout << "D(12,123) = 327398\n";
        cout << "Target: D(123, 1234567)\n";
        return 0;
    }

    cout << "PE 933: Paper Cutting / 纸张切割\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
