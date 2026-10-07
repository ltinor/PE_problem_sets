// PE 328 - Generate test data
#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    int tc[10];
    tc[0] = 8;     // sample: C(8)=12
    tc[1] = 100;   // PE partial: sum C(1..100)=17575
    tc[2] = 3;
    tc[3] = 10;
    tc[4] = 50;
    tc[5] = 200;
    tc[6] = 500;
    tc[7] = 1000;
    tc[8] = 5000;
    tc[9] = 20000; // large adapted
    
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
        f << "200000\n";
        printf("Generated data/pe_verify.in: PE sum C(1..200000)\n");
    }
    
    return 0;
}
