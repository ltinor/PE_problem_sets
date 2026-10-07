// PE 330 - Generate test data
#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    int tc[10];
    tc[0] = 10;   // sample: A(10)=328161643, B(10)=-652694486
    tc[1] = 0;    // base case
    tc[2] = 1;
    tc[3] = 2;
    tc[4] = 3;
    tc[5] = 5;
    tc[6] = 8;
    tc[7] = 12;
    tc[8] = 15;
    tc[9] = 20;   // max for brute
    
    for (int i = 0; i < 10; i++) {
        char fn[32];
        snprintf(fn, sizeof(fn), "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
        printf("Generated %s: N=%d\n", fn, tc[i]);
    }
    
    // PE verification
    {
        ofstream f("data/pe_verify.in");
        f << "1000000000\n";
        printf("Generated data/pe_verify.in: PE N=10^9\n");
    }
    
    return 0;
}
