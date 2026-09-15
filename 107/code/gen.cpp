#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int V;
    if (mode == "small") {
        V = rand_int(3, 8);
    } else if (mode == "large") {
        V = rand_int(20, 40);
    } else {
        V = rand_int(3, 40);
    }

    cout << V << "\n";
    // Generate random symmetric matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                cout << "-";
            } else if (j < i) {
                // Mirror value (already printed)
                cout << "-";
            } else {
                // 60% chance of edge
                if (rand_int(1, 10) <= 6) {
                    cout << rand_int(1, 100);
                } else {
                    cout << "-";
                }
            }
            if (j < V - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
