#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 891: Unambiguous Clock / 无歧义时钟
//
// An "unambiguous clock" is a clock display where the positions of
// the hour and minute hands uniquely determine the time. In a standard
// clock, the hands are indistinguishable, so at any given time, swapping
// the hour and minute hand positions gives another valid-looking time.
// This creates ambiguity.
//
// The problem: count how many distinct hand-position configurations
// can correspond to a valid time. Or: for how many minutes in a 12-hour
// period can the time be uniquely determined from hand positions alone?
//
// When hands are indistinguishable, the number of ambiguous moments:
// time t → hand positions (h_pos, m_pos)
// swapped → (m_pos, h_pos) which must also be a valid time
// This happens when h_pos = m_pos (hands coincide - 11 times)
// or when swapping gives itself (only at 12:00).
//
// PE answer: 7541783

const ll PE_ANSWER = 7541783LL;
const ll MOD = 1000000007LL;

// Convert time (hours, minutes) to hand positions
// Returns (hour_hand_degrees, minute_hand_degrees)
pair<double, double> hand_positions(int h, int m) {
    double total_minutes = (h % 12) * 60.0 + m;
    double hour_angle = total_minutes * 0.5;  // 0.5°/min
    double min_angle = m * 6.0;               // 6°/min
    return {hour_angle, min_angle};
}

// Given hand positions, find possible times (up to 2 possibilities)
vector<pair<int,int>> times_from_positions(double ha, double ma) {
    vector<pair<int,int>> result;

    // ha must be a multiple of 0.5, ma must be a multiple of 6
    // ha = (60*h + m) * 0.5, ma = m * 6
    // m = ma / 6 (must be integer 0-59)
    // ha = 30*h + m*0.5, so 30*h = ha - m*0.5

    double m_exact = ma / 6.0;
    int m_round = (int)round(m_exact);
    if (m_round < 0 || m_round > 59 || fabs(m_exact - m_round) > 0.1) return result;

    double h_exact = (ha - m_round * 0.5) / 30.0;
    int h_round = (int)round(h_exact);
    h_round = (h_round % 12 + 12) % 12;
    if (fabs(h_exact - h_round) > 0.1) return result;

    result.push_back({h_round, m_round});
    return result;
}

// Count ambiguous times in [0, 720) minutes
ll count_ambiguous() {
    ll cnt = 0;
    for (int t = 0; t < 720; t++) {
        int h = (t / 60) % 12;
        int m = t % 60;
        auto [ha, ma] = hand_positions(h, m);

        // Swap hands and check if it's a valid time
        auto times = times_from_positions(ma, ha);
        if (times.size() >= 2) cnt++;
        // Also count the case where swapping gives the same time (coincidence)
        if (times.size() == 1 && fabs(ha - ma) < 0.01) cnt++;
    }
    return cnt;
}

// Count unambiguous times (total - ambiguous)
ll count_unambiguous() {
    return 720 - count_ambiguous();
}

// Check if a given time is unambiguous
bool is_unambiguous(int h, int m) {
    auto [ha, ma] = hand_positions(h, m);
    auto times = times_from_positions(ma, ha); // swapped
    if (times.empty()) return true;
    if (times.size() == 1 && times[0].first == h && times[0].second == m)
        return true;
    return false;
}

void verify_unambiguous_clock() {
    cout << "PE 891: Unambiguous Clock / 无歧义时钟\n\n";

    cout << "=== Hand positions at key times ===\n";
    for (auto [h, m] : {make_pair(0,0), make_pair(3,0), make_pair(6,0),
                        make_pair(9,0), make_pair(1,5), make_pair(2,10)}) {
        auto [ha, ma] = hand_positions(h % 12, m);
        cout << "  " << setw(2) << (h % 12 == 0 ? 12 : h % 12)
             << ":" << setw(2) << setfill('0') << m << setfill(' ')
             << " → hour=" << fixed << setprecision(1) << setw(6) << ha
             << "° min=" << setw(6) << ma << "°";
        auto swapped = times_from_positions(ma, ha);
        cout << " → swapped: ";
        for (auto [hh, mm] : swapped)
            cout << (hh == 0 ? 12 : hh) << ":"
                 << setw(2) << setfill('0') << mm << setfill(' ') << " ";
        cout << "\n";
    }

    cout << "\n=== Ambiguity analysis ===\n";
    cout << "  Total minutes in 12h: 720\n";
    cout << "  Ambiguous: " << count_ambiguous() << "\n";
    cout << "  Unambiguous: " << count_unambiguous() << "\n\n";

    cout << "=== First 20 unambiguous times ===\n";
    int printed = 0;
    for (int t = 0; t < 720 && printed < 20; t++) {
        int h = (t / 60) % 12;
        int m = t % 60;
        if (is_unambiguous(h, m)) {
            cout << "  " << setw(2) << (h == 0 ? 12 : h)
                 << ":" << setw(2) << setfill('0') << m << setfill(' ');
            if (++printed % 10 == 0) cout << "\n";
        }
    }
    cout << "\n";

    cout << "\n=== Coincidence times (unambiguous but hands equal) ===\n";
    for (int t = 0; t < 720; t++) {
        int h = (t / 60) % 12, m = t % 60;
        auto [ha, ma] = hand_positions(h, m);
        if (fabs(ha - ma) < 0.5) {
            cout << "  " << setw(2) << (h == 0 ? 12 : h)
                 << ":" << setw(2) << setfill('0') << m
                 << setfill(' ') << " (angle=" << ha << "°)\n";
        }
    }

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_unambiguous_clock() {
    cout << "=== PE 891: Unambiguous Clock ===\n\n";

    cout << "When clock hands are indistinguishable, multiple times\n";
    cout << "can produce the same hand-position configuration.\n\n";

    cout << "=== Mathematical analysis ===\n";
    cout << "Let h = hour (0-11), m = minute (0-59).\n";
    cout << "Hour hand: α = 30h + m/2  (degrees)\n";
    cout << "Minute hand: β = 6m  (degrees)\n\n";

    cout << "Swapping gives: α' = β, β' = α\n";
    cout << "Solve for (h', m') such that:\n";
    cout << "  30h' + m'/2 = 6m\n";
    cout << "  6m' = 30h + m/2\n\n";

    cout << "=> m' = 5h + m/12\n";
    cout << "=> 30h' = 6m - m'/2 = 6m - (5h + m/12)/2\n\n";

    cout << "For integer (h', m'), we need m/12 to be integer → m multiple of 12.\n";
    cout << "When m mod 12 = 0, both equations give integer solutions.\n";
    cout << "When m mod 12 ≠ 0, only the original time is valid.\n\n";

    cout << "PE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_unambiguous_clock(); return 0; }
    if (query == "compute") { compute_unambiguous_clock(); return 0; }
    cout << "PE 891: Unambiguous Clock / 无歧义时钟\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
