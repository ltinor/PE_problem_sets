#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // 10 test cases
    vector<string> tests(10);
    
    // Test case 1: short pattern
    tests[0] = "1_2_3_0";
    
    // Test case 2: another short pattern
    tests[1] = "1_4_9_0";
    
    // Test case 3: 
    tests[2] = "4_5_6_0";
    
    // Test case 4:
    tests[3] = "1_6_0";
    
    // Test case 5:
    tests[4] = "2_5_0";
    
    // Test case 6:
    tests[5] = "1_4_4_0";
    
    // Test case 7:
    tests[6] = "1_1_1_1_0";
    
    // Test case 8:
    tests[7] = "9_8_7_6_5_0";
    
    // Test case 9: PE pattern
    tests[8] = "1_2_3_4_5_6_7_8_9_0";
    
    // Test case 10:
    tests[9] = "2_4_6_8_0";
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with pattern = " << tests[i] << "\n";
    }
    
    return 0;
}
