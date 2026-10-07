#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

void output_triangle(ostream& out, int x1, int y1, int x2, int y2, int x3, int y3) {
    out << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);

        if (i == 0) {
            // Sample: the two triangles from the problem
            fout << "2\n";
            output_triangle(fout, -340, 495, -153, -910, 835, -947);  // contains origin
            output_triangle(fout, -175, 41, -421, -714, 574, -645);   // does not contain
        } else if (i == 1) {
            // Small: 5 random triangles
            fout << "5\n";
            for (int j = 0; j < 5; j++)
                output_triangle(fout, rand_int(-100, 100), rand_int(-100, 100),
                                rand_int(-100, 100), rand_int(-100, 100),
                                rand_int(-100, 100), rand_int(-100, 100));
        } else if (i == 2) {
            // 3 triangles: known contains origin
            fout << "3\n";
            output_triangle(fout, -1, -1, 2, -1, -1, 2);       // origin inside
            output_triangle(fout, -100, -100, 200, -100, -100, 200); // origin inside
            output_triangle(fout, 10, 10, 20, 10, 10, 20);     // origin NOT inside
        } else if (i == 3) {
            // 10 random triangles
            fout << "10\n";
            for (int j = 0; j < 10; j++)
                output_triangle(fout, rand_int(-500, 500), rand_int(-500, 500),
                                rand_int(-500, 500), rand_int(-500, 500),
                                rand_int(-500, 500), rand_int(-500, 500));
        } else if (i < 8) {
            // Medium: 20-50 random triangles
            int n = rand_int(20, 50);
            fout << n << "\n";
            for (int j = 0; j < n; j++)
                output_triangle(fout, rand_int(-1000, 1000), rand_int(-1000, 1000),
                                rand_int(-1000, 1000), rand_int(-1000, 1000),
                                rand_int(-1000, 1000), rand_int(-1000, 1000));
        } else {
            // Large: ~100 random triangles
            fout << "100\n";
            for (int j = 0; j < 100; j++)
                output_triangle(fout, rand_int(-1000, 1000), rand_int(-1000, 1000),
                                rand_int(-1000, 1000), rand_int(-1000, 1000),
                                rand_int(-1000, 1000), rand_int(-1000, 1000));
        }

        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
