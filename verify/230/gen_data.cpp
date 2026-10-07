#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

string rand_digits(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += (char)('0' + rand() % 10);
    return s;
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Test cases: each is (A, B, n)
    struct TC {
        string A, B;
        ll n;
    };

    vector<TC> test_cases(10);

    // 1: PE example (verify: D(35) = 9)
    test_cases[0] = {"1415926535", "8979323846", 35};

    // 2-3: tiny
    test_cases[1] = {"12", "34", 3};
    test_cases[2] = {"12", "34", 5};

    // 4-5: small
    test_cases[3] = {"123", "456", 10};
    test_cases[4] = {"999", "888", 15};

    // 6-7: medium
    test_cases[5] = {rand_digits(5), rand_digits(5), rand_ll(10, 50)};
    test_cases[6] = {rand_digits(8), rand_digits(8), rand_ll(20, 100)};

    // 8-9: larger
    test_cases[7] = {rand_digits(10), rand_digits(10), rand_ll(50, 500)};
    test_cases[8] = {rand_digits(10), rand_digits(10), 1000000LL};

    // 10: PE full-size (first 100 digits of pi)
    test_cases[9] = {
        "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679",
        "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196",
        127LL * 1LL  // n=127 for testing (PE asks for sum over (127+19k)*7^k)
    };

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].A << "\n" << test_cases[i].B << "\n" << test_cases[i].n << "\n";
        fout.close();
        cout << "Generated " << filename << " n=" << test_cases[i].n << "\n";
    }

    return 0;
}
