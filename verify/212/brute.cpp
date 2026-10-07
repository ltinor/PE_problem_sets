#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 212: Brute force - discretized 3D array for small K only
// Uses coordinate compression in all 3 dimensions

struct Cuboid {
    int x0, y0, z0, dx, dy, dz;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Generate S sequence
    int total_S = 6 * K;
    vector<ll> S(total_S + 1);
    for (int k = 1; k <= 55 && k <= total_S; k++) {
        ll val = 100003LL - 200003LL * k + 300007LL * k * k * k;
        S[k] = val % 1000000;
        if (S[k] < 0) S[k] += 1000000;
    }
    for (int k = 56; k <= total_S; k++) {
        S[k] = (S[k - 24] + S[k - 55]) % 1000000;
    }

    vector<Cuboid> cuboids(K);
    vector<int> xs, ys, zs;
    for (int n = 1; n <= K; n++) {
        int idx = 6 * n;
        Cuboid c = {
            (int)(S[idx - 5] % 10000),
            (int)(S[idx - 4] % 10000),
            (int)(S[idx - 3] % 10000),
            (int)(1 + (S[idx - 2] % 399)),
            (int)(1 + (S[idx - 1] % 399)),
            (int)(1 + (S[idx] % 399))
        };
        cuboids[n-1] = c;
        xs.push_back(c.x0); xs.push_back(c.x0 + c.dx);
        ys.push_back(c.y0); ys.push_back(c.y0 + c.dy);
        zs.push_back(c.z0); zs.push_back(c.z0 + c.dz);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(zs.begin(), zs.end());
    zs.erase(unique(zs.begin(), zs.end()), zs.end());

    int NX = xs.size() - 1, NY = ys.size() - 1, NZ = zs.size() - 1;

    // Mark compressed cells
    vector<vector<vector<bool>>> grid(NX, vector<vector<bool>>(NY, vector<bool>(NZ, false)));

    for (auto& c : cuboids) {
        int xi1 = lower_bound(xs.begin(), xs.end(), c.x0) - xs.begin();
        int xi2 = lower_bound(xs.begin(), xs.end(), c.x0 + c.dx) - xs.begin();
        int yi1 = lower_bound(ys.begin(), ys.end(), c.y0) - ys.begin();
        int yi2 = lower_bound(ys.begin(), ys.end(), c.y0 + c.dy) - ys.begin();
        int zi1 = lower_bound(zs.begin(), zs.end(), c.z0) - zs.begin();
        int zi2 = lower_bound(zs.begin(), zs.end(), c.z0 + c.dz) - zs.begin();

        for (int xi = xi1; xi < xi2; xi++)
            for (int yi = yi1; yi < yi2; yi++)
                for (int zi = zi1; zi < zi2; zi++)
                    grid[xi][yi][zi] = true;
    }

    ll total = 0;
    for (int xi = 0; xi < NX; xi++)
        for (int yi = 0; yi < NY; yi++)
            for (int zi = 0; zi < NZ; zi++)
                if (grid[xi][yi][zi])
                    total += (ll)(xs[xi+1] - xs[xi]) * (ys[yi+1] - ys[yi]) * (zs[zi+1] - zs[zi]);

    cout << total << "\n";
}
