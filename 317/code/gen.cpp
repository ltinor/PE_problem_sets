#include<bits/stdc++.h>
using namespace std;

double rand_double(double l, double r) {
    return l + (double)rand() / RAND_MAX * (r - l);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    double h, v, g;
    if (mode == "small") {
        h = rand_double(1, 20);
        v = rand_double(1, 10);
        g = 9.81;
    } else {
        h = rand_double(20, 200);
        v = rand_double(10, 50);
        g = 9.81;
    }

    cout << fixed << setprecision(2) << h << " " << v << " " << g << "\n";
    return 0;
}
