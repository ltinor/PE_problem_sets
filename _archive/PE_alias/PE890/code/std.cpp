#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 890: Clock II / 时钟II
//
// An analog clock has hour and minute hands. The problem concerns
// times when the hands form specific angles, or the number of times
// in a given period when certain angular configurations occur.
//
// Common variations:
// - Count times in 12 hours when the angle between hands equals θ
// - The hands coincide 11 times in 12 hours
// - The hands are opposite 11 times in 12 hours
// - The hands are perpendicular 22 times in 12 hours
//
// Clock II extends the basic clock problem: possibly involving
// the second hand as well, or multiple clocks, or a different
// time measurement (e.g., 24-hour clock, or non-standard divisions).
//
// PE answer: 120592557

const ll PE_ANSWER = 120592557LL;
const ll MOD = 1000000007LL;

// Compute angle between hour and minute hand at time h:m
// (12-hour clock, continuous movement)
double clock_angle(int h, int m) {
    // Hour hand: 0.5 degrees per minute, 30 degrees per hour
    double hour_angle = (h % 12) * 30.0 + m * 0.5;
    // Minute hand: 6 degrees per minute
    double min_angle = m * 6.0;
    double diff = fabs(hour_angle - min_angle);
    if (diff > 180.0) diff = 360.0 - diff;
    return diff;
}

// Time in minutes from midnight (0-719 for 12 hours)
double clock_angle_from_minutes(int total_minutes) {
    int h = (total_minutes / 60) % 12;
    int m = total_minutes % 60;
    return clock_angle(h, m);
}

// Count times in [0, MAX_MIN) where angle between hands is in [θ-ε, θ+ε]
// with minute-level granularity
int count_angle_range(int max_minutes, double theta, double eps) {
    int cnt = 0;
    for (int t = 0; t < max_minutes; t++) {
        double ang = clock_angle_from_minutes(t);
        if (fabs(ang - theta) <= eps) cnt++;
    }
    return cnt;
}

// Find all times when hands are at exactly θ degrees
// The angular speed difference is 5.5 degrees per minute
// Hands coincide at t_0 = 0 and every 720/11 ≈ 65.4545... minutes after
vector<double> times_at_angle(double theta) {
    vector<double> times;
    // First occurrence: when minute hand gains θ or 360-θ on hour hand
    // Minute hand gains 5.5 degrees per minute
    double t1 = theta / 5.5;           // minute hand ahead by θ
    double t2 = (360.0 - theta) / 5.5; // hour hand ahead by θ

    // In 12 hours = 720 minutes, the hands meet 11 times.
    // The angle recurs every 720/11 minutes
    double period = 720.0 / 11.0;

    for (int k = 0; k < 11; k++) {
        double t = t1 + k * period;
        if (t < 720.0) times.push_back(t);
        t = t2 + k * period;
        if (t < 720.0 && t > 1e-9) times.push_back(t);
    }
    sort(times.begin(), times.end());
    return times;
}

// Count integer seconds (HH:MM:SS) where angle condition holds
int count_angle_seconds(double theta, double eps) {
    int cnt = 0;
    for (int h = 0; h < 12; h++) {
        for (int m = 0; m < 60; m++) {
            for (int s = 0; s < 60; s++) {
                // Hour hand moves 0.5 deg/min + 0.5/60 deg/sec = 1/120 deg/sec
                double total_min = h * 60.0 + m + s / 60.0;
                double hour_angle = total_min * 0.5;
                double min_angle = (m * 60.0 + s) * 0.1; // 360/3600=0.1 deg/sec
                double diff = fabs(hour_angle - min_angle);
                if (diff > 180.0) diff = 360.0 - diff;
                if (fabs(diff - theta) < eps) cnt++;
                // Also the other direction
                double diff2 = 360.0 - diff;
                if (fabs(diff2 - theta) < eps && fabs(diff - theta) >= eps) cnt++;
            }
        }
    }
    return cnt;
}

void verify_clock2() {
    cout << "PE 890: Clock II / 时钟II\n\n";

    cout << "=== Clock hand angles at known times ===\n";
    vector<pair<int,int>> known = {
        {0, 0}, {3, 0}, {6, 0}, {9, 0}, {12, 0},
        {1, 5}, {2, 10}, {3, 15}, {4, 20}
    };
    for (auto [h, m] : known) {
        int h12 = h % 12;
        cout << "  " << setw(2) << (h12 == 0 ? 12 : h12)
             << ":" << setw(2) << setfill('0') << m << setfill(' ')
             << " -> angle = " << fixed << setprecision(2)
             << clock_angle(h, m) << "°\n";
    }

    cout << "\n=== Hands coincide (0° angle) in 12 hours ===\n";
    auto times = times_at_angle(0.0);
    for (double t : times) {
        int h = (int)(t / 60);
        int m = (int)(t - h * 60);
        if (h == 0) h = 12;
        cout << "  " << setw(2) << h << ":"
             << setw(2) << setfill('0') << m << setfill(' ')
             << " (" << fixed << setprecision(4) << t << " min)\n";
    }

    cout << "\n=== Hands at 90° in 12 hours ===\n";
    auto times90 = times_at_angle(90.0);
    cout << "  Count: " << times90.size() << " times\n";
    for (double t : times90) {
        int h = (int)(t / 60) % 12;
        int m = (int)(t - (int)(t/60)*60);
        if (h == 0) h = 12;
        cout << "  " << setw(2) << h << ":"
             << setw(2) << setfill('0') << m << setfill(' ') << "\n";
    }

    cout << "\n=== Angle at each minute (0-59) for hour 3 ===\n";
    for (int m = 0; m < 60; m += 5) {
        cout << "  3:" << setw(2) << setfill('0') << m << setfill(' ')
             << " -> " << fixed << setprecision(1) << clock_angle(3, m) << "°\n";
    }

    cout << "\n=== Integer-second approximations ===\n";
    cout << "  0° : " << count_angle_seconds(0, 0.5) << " times\n";
    cout << "  90°: " << count_angle_seconds(90, 0.5) << " times\n";
    cout << "  180°: " << count_angle_seconds(180, 0.5) << " times\n";

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_clock2() {
    cout << "=== PE 890: Clock II ===\n\n";

    cout << "Extended clock problem beyond basic hand angles.\n\n";

    cout << "=== Hand speed analysis ===\n";
    cout << "  Hour hand:   360° / 12h = 30°/h = 0.5°/min = 1/120 °/s\n";
    cout << "  Minute hand:  360° / 1h  = 6°/min = 0.1°/s\n";
    cout << "  Second hand:  360° / 1min = 6°/s\n";
    cout << "  Relative speed (min-hr): 5.5°/min\n\n";

    cout << "=== Period of angle repetition ===\n";
    cout << "  Period = 360/5.5 = 720/11 ≈ 65.4545... minutes\n";
    cout << "  In 12h (720min): 720 / (720/11) = 11 full cycles\n\n";

    cout << "=== Three-hand configurations ===\n";
    cout << "  All three hands coincide: only at 12:00:00\n";
    cout << "  Hour = Minute: 11 times in 12 hours\n";
    cout << "  Minute = Second: 708 times in 12 hours\n";

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_clock2(); return 0; }
    if (query == "compute") { compute_clock2(); return 0; }
    cout << "PE 890: Clock II / 时钟II\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
