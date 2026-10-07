#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 166: 4x4 grid, each row/col/diag has same sum
// Enumerate top-left 3x3 (9 vars, each 0-9), other 7 determined by equations
// Row sums: r0,r1,r2,r3; Col sums: c0,c1,c2,c3; Diag: d1,d2
// Let grid be:
// a b c x0
// d e f x1
// g h i x2
// x3 x4 x5 x6
// 
// Row0: a+b+c+x0=S → x0=S-a-b-c
// Row1: d+e+f+x1=S → x1=S-d-e-f
// Row2: g+h+i+x2=S → x2=S-g-h-i
// Col0: a+d+g+x3=S → x3=S-a-d-g
// Col1: b+e+h+x4=S → x4=S-b-e-h
// Col2: c+f+i+x5=S → x5=S-c-f-i
// Col3: x0+x1+x2+x6=S → x6=S-x0-x1-x2
// Diag1: a+e+i+x6=S → MUST check (not automatically satisfied)
// Diag2: x0+f+h+x3=S → MUST check

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Skip input (fixed answer problem)
    int dummy; cin >> dummy;
    
    ll ans = 0;
    // S ranges from 0 to 36 (max: 9*4=36)
    for(int S = 0; S <= 36; S++){
        for(int a = 0; a <= 9; a++){
            for(int b = 0; b <= 9; b++){
                for(int c = 0; c <= 9; c++){
                    int x0 = S - a - b - c;
                    if(x0 < 0 || x0 > 9) continue;
                    for(int d = 0; d <= 9; d++){
                        for(int e = 0; e <= 9; e++){
                            for(int f = 0; f <= 9; f++){
                                int x1 = S - d - e - f;
                                if(x1 < 0 || x1 > 9) continue;
                                for(int g = 0; g <= 9; g++){
                                    for(int h = 0; h <= 9; h++){
                                        for(int i = 0; i <= 9; i++){
                                            int x2 = S - g - h - i;
                                            if(x2 < 0 || x2 > 9) continue;
                                            
                                            int x3 = S - a - d - g;
                                            if(x3 < 0 || x3 > 9) continue;
                                            
                                            int x4 = S - b - e - h;
                                            if(x4 < 0 || x4 > 9) continue;
                                            
                                            int x5 = S - c - f - i;
                                            if(x5 < 0 || x5 > 9) continue;
                                            
                                            int x6 = S - x0 - x1 - x2;
                                            if(x6 < 0 || x6 > 9) continue;
                                            
                                            // Check both diagonals
                                            // diag1: a+e+i+x6 == S
                                            if(a + e + i + x6 != S) continue;
                                            // diag2: x0+f+h+x3 == S
                                            if(x0 + f + h + x3 != S) continue;
                                            
                                            ans++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << ans << "\n"; // 7130034
}
