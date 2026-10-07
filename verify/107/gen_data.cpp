#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

void generate_test(int V, const string& fname) {
    ofstream fout(fname);
    fout << V << "\n";
    // Generate a connected random graph
    // First ensure connectivity: add V-1 edges forming a tree
    vector<vector<int>> mat(V, vector<int>(V, -1));
    for (int i = 1; i < V; i++) {
        int parent = rand_int(0, i - 1);
        int w = rand_int(1, 100);
        mat[parent][i] = mat[i][parent] = w;
    }
    // Add extra random edges
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (mat[i][j] == -1 && rand_int(1, 10) <= 3) {
                mat[i][j] = mat[j][i] = rand_int(1, 100);
            }
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (j > 0) fout << " ";
            if (mat[i][j] == -1) fout << "-";
            else fout << mat[i][j];
        }
        fout << "\n";
    }
    fout.close();
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Test cases: various V sizes
    vector<int> sizes = {3, 4, 7, 8, 10, 15, 20, 25, 30, 35};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        generate_test(sizes[i], filename);
        cout << "Generated " << filename << " with V = " << sizes[i] << "\n";
    }

    return 0;
}
