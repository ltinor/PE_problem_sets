#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// 170: largest 0-9 pandigital concatenated product
// Search: base a, multipliers m1<m2, concatenation of a*m1 and a*m2 uses all 10 digits
// Also concatenation a||m1||m2 must be 0-9 pandigital
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int _; cin >> _;
    
    ll best=0;
    // a has 1-2 digits (makes products manageable)
    for(int a=2;a<100;a++){
        string sa=to_string(a);
        int da=sa.size();
        // Need at least 2 multipliers, total digits = 10
        // a+(m1+m2) = 10 digits, so m1+m2 digits = 10-da
        // Generate multipliers as permutations of remaining digits
        string digits="0123456789";
        for(char c:sa) digits.erase(digits.find(c),1);
        int rem=10-da;
        if(rem<4) continue; // need at least 2+2 digit multipliers
        
        // Try all permutations of remaining digits split into 2 multipliers
        sort(digits.begin(),digits.end());
        do{
            for(int d1=1;d1<rem-1;d1++){
                if(digits[0]=='0'||digits[d1]=='0') continue;
                ll m1=stoll(digits.substr(0,d1));
                ll m2=stoll(digits.substr(d1));
                string prod=to_string(a*m1)+to_string(a*m2);
                sort(prod.begin(),prod.end());
                if(prod=="0123456789" && a*m1>=a*m2) // ensure ordering
                    best=max(best,stoll(to_string(a*m1)+to_string(a*m2)));
            }
        }while(next_permutation(digits.begin(),digits.end()));
    }
    cout<<best<<"\n";
}
