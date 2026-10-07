#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: same algorithm as std, for verification

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int dummy; cin >> dummy;
    
    ll ans = 0;
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
                                            
                                            if(a + e + i + x6 != S) continue;
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
    
    cout << ans << "\n";
}
