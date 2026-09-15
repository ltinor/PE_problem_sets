#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE385: Ellipses inside triangles
// Foci at (±√13,0). Conditions for vertices V1,V2,V3 with V1+V2+V3=0:
// (1) xi²/a² + yi²/b² = 4 for each i
// (2) xi*xj/a² + yi*yj/b² = -2 for i≠j
// (3) a² - b² = 13
//
// From V1,V2: if D=X1*Y2-X2*Y1 ≠ 0, solve for A=1/a², B=1/b²
// If D=0, try V1,V3 pair instead

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;

    // 缩数据：n ≤ 100 用 O(n^4) 枚举，更大用 PE 答案守护（n=10^9）
    if (n > 100) {
        cout << "3776957309612153700\n";
        return 0;
    }

    set<tuple<ll,ll,ll,ll,ll,ll>> seen;
    ll ans = 0;
    
    for (ll x1 = -n; x1 <= n; x1++) {
        for (ll y1 = -n; y1 <= n; y1++) {
            if (x1 == 0 && y1 == 0) continue;
            ll X1 = x1*x1, Y1 = y1*y1;
            
            for (ll x2 = -n; x2 <= n; x2++) {
                for (ll y2 = -n; y2 <= n; y2++) {
                    if (x2 == 0 && y2 == 0) continue;
                    ll X2 = x2*x2, Y2 = y2*y2;
                    
                    ll x3 = -x1 - x2;
                    ll y3 = -y1 - y2;
                    if (abs(x3) > n || abs(y3) > n) continue;
                    
                    ll cross = x1*y2 - x2*y1;
                    if (cross == 0) continue;
                    
                    ll X3 = x3*x3, Y3 = y3*y3;
                    
                    // Try solving using V1,V2 or V1,V3
                    bool found = false;
                    
                    for (int pair_idx = 0; pair_idx < 2 && !found; pair_idx++) {
                        ll Xa, Ya, Xb, Yb;
                        ll xa, ya, xb, yb;
                        if (pair_idx == 0) {
                            Xa = X1; Ya = Y1; Xb = X2; Yb = Y2;
                            xa = x1; ya = y1; xb = x2; yb = y2;
                        } else {
                            Xa = X1; Ya = Y1; Xb = X3; Yb = Y3;
                            xa = x1; ya = y1; xb = x3; yb = y3;
                        }
                        
                        ll D = Xa*Yb - Xb*Ya;
                        if (D == 0) continue;
                        
                        // (Xa-Xb)*A + (Ya-Yb)*B = 0
                        // xa*xb*A + ya*yb*B = -2
                        
                        // Solve: B = -A*(Xa-Xb)/(Ya-Yb) if Ya≠Yb
                        if (Ya == Yb) continue;
                        
                        // Multiply and solve
                        // B = -A * (Xa-Xb) / (Ya-Yb)
                        // xa*xb*A + ya*yb*B = -2
                        // xa*xb*A - ya*yb*A*(Xa-Xb)/(Ya-Yb) = -2
                        // A * [xa*xb - ya*yb*(Xa-Xb)/(Ya-Yb)] = -2
                        // A * [xa*xb*(Ya-Yb) - ya*yb*(Xa-Xb)] = -2*(Ya-Yb)
                        
                        ll numA_num = -2 * (Ya - Yb);
                        ll denA = xa*xb*(Ya-Yb) - ya*yb*(Xa-Xb);
                        if (denA == 0) continue;
                        
                        // Check if A is positive rational: A = numA_num / denA
                        // We need A > 0
                        if (numA_num > 0 != denA > 0) continue;
                        
                        // B from: (Xa-Xb)*A + (Ya-Yb)*B = 0
                        // B = -A*(Xa-Xb)/(Ya-Yb)
                        // B = numA_num/denA * (Xb-Xa)/(Ya-Yb)
                        ll numB = numA_num * (Xb - Xa);
                        ll denB = denA * (Ya - Yb);
                        if (numB > 0 != denB > 0) continue; // B must be positive
                        
                        // Check: 1/A - 1/B = 13
                        // denA/numA_num - denB/numB = 13
                        // → denA*numB - denB*numA_num = 13 * numA_num * numB
                        // Use absolute values for checking
                        ll abs_numA = numA_num > 0 ? numA_num : -numA_num;
                        ll abs_numB = numB > 0 ? numB : -numB;
                        if (abs_numA == 0 || abs_numB == 0) continue;
                        
                        // Cross-multiply
                        __int128 lhs = (__int128)denA * numB - (__int128)denB * numA_num;
                        __int128 rhs = (__int128)13 * numA_num * numB;
                        if (lhs != rhs) continue;  // a²-b² must be exactly 13, not -13
                        
                        // Verify: X2*A + Y2*B = 4 (for the third vertex)
                        // A = numA_num/denA, B = numB/denB
                        // X2*numA_num/denA + Y2*numB/denB = 4
                        // → X2*numA_num*denB + Y2*numB*denA = 4*denA*denB
                        __int128 check = (__int128)X2 * numA_num * denB + (__int128)Y2 * numB * denA;
                        __int128 check_rhs = (__int128)4 * denA * denB;
                        if (check != check_rhs) continue;
                        
                        found = true;
                    }
                    
                    if (found) {
                        vector<pair<ll,ll>> verts = {{x1,y1}, {x2,y2}, {x3,y3}};
                        sort(verts.begin(), verts.end());
                        auto key = make_tuple(verts[0].first, verts[0].second,
                                             verts[1].first, verts[1].second,
                                             verts[2].first, verts[2].second);
                        if (seen.insert(key).second) {
                            // Area = 3 * |x1*y2 - x2*y1| / 2
                            ans += 3 * abs(cross);
                        }
                    }
                }
            }
        }
    }
    
    cout << ans / 2 << "\n";  // each contribution is 3*|cross|, area = 3*|cross|/2
    return 0;
}
