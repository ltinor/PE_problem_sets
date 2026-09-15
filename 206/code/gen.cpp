#include<bits/stdc++.h>
using namespace std;

// PE 206: Random pattern generator for check/brute comparison (small patterns)

string make_pattern(int len) {
    string p;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            p += char('0' + rand() % 10);
        else
            p += '_';
    }
    // Ensure last char is constraining for validation
    p.back() = '0'; // Makes step size 10
    return p;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        // Generate a small pattern (length 5-7) for quick brute check
        int len = rand() % 3 + 5; // 5-7
        string p = make_pattern(len);
        cout << p << "\n";
    } else if (mode == "pe") {
        cout << "1_2_3_4_5_6_7_8_9_0\n";
    } else {
        // large mode: use PE pattern
        cout << "1_2_3_4_5_6_7_8_9_0\n";
    }
}
