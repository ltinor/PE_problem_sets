#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    int T = 10; 
    cout << T << "\n";

    for(int t = 0; t < T; t++) {
        int S;

        if(t < 7) {
            int m, n, a, b, c;
            while(true) {
                n = rand() % 20 + 1;         
                m = n + rand() % 20 + 1;     
                a = m*m - n*n;
                b = 2*m*n;
                c = m*m + n*n;
                S = a + b + c;
                if(S <= 1000) break;         
            }
        } else {
            
            S = rand() % 100 + 1;           
            while(true) {
                bool found = false;
                for(int a=1; a<S/3; a++) {
                    for(int b=a+1; b<S/2; b++) {
                        int c = S - a - b;
                        if(c <= b) continue;
                        if(a*a + b*b == c*c) {
                            found = true;
                            break;
                        }
                    }
                    if(found) break;
                }
                if(!found) break;           
                S++;                        
            }
        }

        cout << S << "\n";
    }

    return 0;
}