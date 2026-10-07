#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 212: Combined Volume of Cuboids (union volume)
// Original: K=50000, answer = 328968937309
// Adapted: parameterized K (≤ 50000)
// Algorithm: 3D sweep-line (x-sweep + y-sweep + segment tree on z)

struct Cuboid {
    int x0, y0, z0, dx, dy, dz;
};

struct Event {
    int y, z1, z2, type; // type: 1 = add, -1 = remove
};

// Segment tree for z-axis coverage
struct SegTree {
    int n;
    vector<int> cnt, sum;
    vector<int> zs; // compressed z coordinates

    void build(const vector<int>& _zs) {
        zs = _zs;
        n = zs.size() - 1; // number of intervals
        cnt.assign(4 * n, 0);
        sum.assign(4 * n, 0);
    }

    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (ql >= r || qr <= l) return;
        if (ql <= l && r <= qr) {
            cnt[idx] += val;
        } else {
            int mid = (l + r) / 2;
            update(idx * 2, l, mid, ql, qr, val);
            update(idx * 2 + 1, mid, r, ql, qr, val);
        }
        if (cnt[idx] > 0) {
            sum[idx] = zs[r] - zs[l];
        } else if (r - l == 1) {
            sum[idx] = 0;
        } else {
            sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
        }
    }

    void add(int l, int r, int val) {
        update(1, 0, n, l, r, val);
    }

    int total() {
        return sum[1];
    }
};

ll union_area_2d(const vector<Cuboid>& cuboids, int xl, int xr) {
    // Collect y-z rectangles from cuboids that cover [xl, xr)
    vector<int> ys, zs;
    vector<tuple<int,int,int,int>> rects; // y1, y2, z1, z2
    for (auto& c : cuboids) {
        if (c.x0 >= xr || c.x0 + c.dx <= xl) continue;
        int y1 = c.y0, y2 = c.y0 + c.dy;
        int z1 = c.z0, z2 = c.z0 + c.dz;
        ys.push_back(y1); ys.push_back(y2);
        zs.push_back(z1); zs.push_back(z2);
        rects.push_back({y1, y2, z1, z2});
    }

    if (rects.empty()) return 0;

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(zs.begin(), zs.end());
    zs.erase(unique(zs.begin(), zs.end()), zs.end());

    // Sweep y
    vector<Event> events;
    for (auto& [y1, y2, z1, z2] : rects) {
        int zi1 = lower_bound(zs.begin(), zs.end(), z1) - zs.begin();
        int zi2 = lower_bound(zs.begin(), zs.end(), z2) - zs.begin();
        events.push_back({y1, zi1, zi2, 1});
        events.push_back({y2, zi1, zi2, -1});
    }
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.y < b.y;
    });

    SegTree st;
    st.build(zs);

    ll area = 0;
    int prev_y = ys[0];
    for (auto& e : events) {
        int cur_y = e.y;
        area += (ll)(cur_y - prev_y) * st.total();
        st.add(e.z1, e.z2, e.type);
        prev_y = cur_y;
    }

    return area;
}

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
        if (S[k] < 0) S[k] += 1000000; // handle negative
    }
    for (int k = 56; k <= total_S; k++) {
        S[k] = (S[k - 24] + S[k - 55]) % 1000000;
    }

    // Generate cuboids
    vector<Cuboid> cuboids(K);
    for (int n = 1; n <= K; n++) {
        int idx = 6 * n;
        cuboids[n-1] = {
            (int)(S[idx - 5] % 10000),
            (int)(S[idx - 4] % 10000),
            (int)(S[idx - 3] % 10000),
            (int)(1 + (S[idx - 2] % 399)),
            (int)(1 + (S[idx - 1] % 399)),
            (int)(1 + (S[idx] % 399))
        };
    }

    // Collect all x boundaries
    vector<int> xs;
    for (auto& c : cuboids) {
        xs.push_back(c.x0);
        xs.push_back(c.x0 + c.dx);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    // Sweep x
    ll total_volume = 0;
    for (size_t i = 0; i + 1 < xs.size(); i++) {
        int xl = xs[i], xr = xs[i+1];
        ll area = union_area_2d(cuboids, xl, xr);
        total_volume += area * (xr - xl);
    }

    cout << total_volume << "\n";
}
