#include<bits/stdc++.h>
using namespace std;
#define ll long long

int mygcd(int a,int b){while(b){int t=b;b=a%b;a=t;}return a;}

// Sum of all Gaussian integer divisors (positive real part) of n
// Algorithm: for each Gaussian integer g = a+bi (a>0, b>=0, gcd(a,b)=1),
// the condition for g to divide n is: (a^2+b^2) | n*gcd(a,b)
// Actually: g divides n when n*(a-bi)/(a^2+b^2) has integer real and imag parts.
// This means a^2+b^2 divides n*a and n*b, equivalent to (a^2+b^2)/gcd(a,b) divides n.
// For each such primitive (a,b) pair, all multiples contribute.

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    
    ll total = 0;
    // For each rational integer divisor, add it
    for(int d=1; d<=N; d++) total += (ll)N/d * d;
    
    // Precompute: for each value d, which primitive (a,b) have a^2+b^2 = d or d/gcd?
    // Simpler: enumerate all (a,b) with a>0, b>=0, gcd(a,b)=1, a^2+b^2 <= 2*N
    // For each, the norm N(a+bi) = a^2+b^2. g divides n iff norm(g) | n*gcd(a,b)
    
    int limit = (int)sqrt(2*N) + 1;
    for(int a=1; a<=limit; a++) {
        for(int b=0; b<=limit; b++) {
            if(b > a) continue; // avoid duplicates? No, we need both a>0,b>=0
            if(b==0 && a==1) continue; // already counted as rational
            int norm = a*a + b*b;
            if(norm > 2*N) break;
            int g = mygcd(a,b);
            if(g != 1) continue;
            
            // For each multiple k such that k*norm <= N, add 2*a*k (real part of divisor + its conjugate)
            // Actually the sum of all divisors of the form (a+bi)*k + (a-bi)*k = 2*a*k
            for(int k=1; k*norm <= N; k++) {
                total += 2LL * a * k * ((ll)N / (k*norm));
            }
        }
    }
    
    cout << total << "\n";
}
