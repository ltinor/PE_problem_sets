#include<bits/stdc++.h>
using namespace std;

int main() {

    for(int a = 9; a >= 1; a--) {
        for(int b = 9; b >= 0; b--) {
            for(int c = 9; c >= 0; c--) {

                int pal = a*100000 + b*10000 + c*1000
                        + c*100 + b*10 + a;

                for(int d = 999; d >= 100; d--) {

                    if(pal / d > 999) continue;
                    if(pal / d < 100) break;

                    if(pal % d == 0) {
                        cout << pal << endl;
                        return 0;
                    }
                }
            }
        }
    }
}