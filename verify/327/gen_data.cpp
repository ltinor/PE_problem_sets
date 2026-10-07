// PE 327 - Generate test data
#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    struct { int Cmax, R; string desc; } tc[10];
    
    tc[0] = {4, 6, "sample sum C=3,4 R=6 -> 146"};
    tc[1] = {10, 10, "PE partial: sum C=3..10 R=10 -> 10382"};
    tc[2] = {3, 3, "small"};
    tc[3] = {5, 4, "small"};
    tc[4] = {6, 6, "medium"};
    tc[5] = {8, 7, "medium"};
    tc[6] = {12, 8, "large"};
    tc[7] = {15, 10, "large"};
    tc[8] = {20, 12, "larger"};
    tc[9] = {30, 15, "max_adapted"};
    
    for (int i = 0; i < 10; i++) {
        char fn[32];
        snprintf(fn, sizeof(fn), "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].Cmax << " " << tc[i].R << "\n";
        printf("Generated %s: Cmax=%d R=%d (%s)\n", fn, tc[i].Cmax, tc[i].R, tc[i].desc.c_str());
    }
    
    // PE verification
    {
        ofstream f("data/pe_verify.in");
        f << "40 30\n";
        printf("Generated data/pe_verify.in: PE sum C=3..40 R=30\n");
    }
    
    return 0;
}
