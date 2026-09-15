#include<bits/stdc++.h>
using namespace std;

long long my_gcd(long long a, long long b){
    while(b){ long long t = b; b = a % b; a = t; }
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input T (ignored)
    int t;
    cin >> t;

    // Independent implementation using rational comparison
    long long num_prod = 1, den_prod = 1;

    for(int a = 1; a <= 9; a++){
        for(int b = 0; b <= 9; b++){
            if(a == 0 && b == 0) continue;
            int numerator = a * 10 + b;

            for(int c = 1; c <= 9; c++){
                for(int d = 0; d <= 9; d++){
                    if(c == 0 && d == 0) continue;
                    int denominator = c * 10 + d;

                    if(numerator >= denominator) continue;
                    if(numerator % 10 == 0 && denominator % 10 == 0) continue;

                    // Check if cancelling a digit yields same value
                    // numerator/denominator == cancelled_num/cancelled_den
                    // Cross-multiply: numerator * cancelled_den == denominator * cancelled_num

                    int cancelled_num = -1, cancelled_den = -1;

                    if(a == c && d != 0){ cancelled_num = b; cancelled_den = d; }
                    else if(a == d && c != 0){ cancelled_num = b; cancelled_den = c; }
                    else if(b == c && d != 0 && a != 0){ cancelled_num = a; cancelled_den = d; }
                    else if(b == d && c != 0 && a != 0){ cancelled_num = a; cancelled_den = c; }

                    if(cancelled_num > 0 && cancelled_den > 0){
                        if(numerator * cancelled_den == denominator * cancelled_num){
                            num_prod *= numerator;
                            den_prod *= denominator;
                        }
                    }
                }
            }
        }
    }

    long long g = my_gcd(num_prod, den_prod);
    den_prod /= g;

    cout << den_prod << "\n";
}
