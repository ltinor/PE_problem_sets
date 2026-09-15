#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 1: sample
    {
        ofstream fout("data/01.in");
        fout << "5\n2 10\n3 5\n5 3\n10 2\n4 4\n";
        fout.close();
        cout << "Generated data/01.in (sample)\n";
    }

    // 2-3: small
    for (int i = 1; i < 3; i++) {
        string filename = "data/0" + to_string(i + 1) + ".in";
        ofstream fout(filename);
        int N = rand_int(3, 15);
        fout << N << "\n";
        for (int j = 0; j < N; j++) {
            fout << rand_int(2, 50) << " " << rand_int(2, 50) << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    // 4-7: medium
    for (int i = 3; i < 7; i++) {
        string filename = "data/0" + to_string(i + 1) + ".in";
        ofstream fout(filename);
        int N = rand_int(50, 200);
        fout << N << "\n";
        for (int j = 0; j < N; j++) {
            fout << rand_int(2, 1000) << " " << rand_int(2, 1000) << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    // 8-10: large
    for (int i = 7; i < 10; i++) {
        string filename = (i < 9 ? "data/0" : "data/") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        int N = rand_int(800, 1000);
        fout << N << "\n";
        for (int j = 0; j < N; j++) {
            fout << rand_int(2, 1000) << " " << rand_int(2, 1000) << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
