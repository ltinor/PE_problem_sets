#include<bits/stdc++.h>
using namespace std;

long long my_gcd(long long a, long long b){
    while(b){ long long t = b; b = a % b; a = t; }
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input T (ignored, answer is always 100)
    int t;
    cin >> t;

    // Verify: there are exactly 4 non-trivial digit cancelling fractions
    // 16/64, 19/95, 26/65, 49/98
    long long num_prod = 1, den_prod = 1;

    for(int num = 11; num <= 98; num++){
        for(int den = num + 1; den <= 99; den++){
            // Non-trivial: can't both end in 0
            if(num % 10 == 0 && den % 10 == 0) continue;

            int n1 = num / 10, n2 = num % 10;
            int d1 = den / 10, d2 = den % 10;

            double orig = (double)num / den;
            double cancelled = -1;

            // Try cancelling common digit
            if(n1 == d1 && d2 != 0) cancelled = (double)n2 / d2;
            else if(n1 == d2 && d1 != 0) cancelled = (double)n2 / d1;
            else if(n2 == d1 && d2 != 0) cancelled = (double)n1 / d2;
            else if(n2 == d2 && d1 != 0) cancelled = (double)n1 / d1;

            if(abs(orig - cancelled) < 1e-9){
                num_prod *= num;
                den_prod *= den;
            }
        }
    }

    // Simplify
    long long g = my_gcd(num_prod, den_prod);
    den_prod /= g;

    // Output the denominator of the simplified product
    cout << den_prod << "\n";
}
