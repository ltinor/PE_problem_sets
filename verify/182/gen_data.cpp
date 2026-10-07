#include <bits/stdc++.h>
using namespace std;
#define ll long long

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        if (tc == 0) {
            // Original PE problem: p=1009, q=3643 → 399788195976
            fout << "1009 3643\n";
        } else if (tc == 1) {
            // Small: p=19, q=37 (φ=648)
            fout << "19 37\n";
        } else if (tc == 2) {
            // Small: p=5, q=7 (φ=24)
            fout << "5 7\n";
        } else if (tc == 7) {
            // Small primes
            fout << "11 17\n";
        } else {
            // Random distinct small primes
            vector<int> primes;
            for (int i = 3; i <= 50; i++)
                if (is_prime(i)) primes.push_back(i);
            int a = rand_int(0, primes.size()-1);
            int b = rand_int(0, primes.size()-1);
            while (b == a) b = rand_int(0, primes.size()-1);
            fout << primes[a] << " " << primes[b] << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
