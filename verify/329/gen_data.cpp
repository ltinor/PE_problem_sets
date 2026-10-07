// PE 329 - Generate test data
#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    string tc[10];
    tc[0] = "PPPPNNPPPNPPNPN"; // PE original sequence
    tc[1] = "PPP";              // short
    tc[2] = "NNN";              // short
    tc[3] = "PNPNP";            // alternating
    tc[4] = "PPPPPP";           // all P
    tc[5] = "NNNNNN";           // all N
    tc[6] = "PPNNPP";           // randomish
    tc[7] = "NPPNPN";           // randomish
    tc[8] = "PNPNPNPN";         // alternating 8
    tc[9] = "PPPNNNPPPNNN";     // 12
    
    for (int i = 0; i < 10; i++) {
        char fn[32];
        snprintf(fn, sizeof(fn), "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
        printf("Generated %s: %s\n", fn, tc[i].c_str());
    }
    
    // PE verification
    {
        ofstream f("data/pe_verify.in");
        f << "PPPPNNPPPNPPNPN\n";
        printf("Generated data/pe_verify.in: PE sequence\n");
    }
    
    return 0;
}
