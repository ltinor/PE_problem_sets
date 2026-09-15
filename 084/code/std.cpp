#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Monopoly board: 40 squares indexed 0-39
// GO=0, A1=1, CC1=2, A2=3, T1=4, R1=5, B1=6, CH1=7, B2=8, B3=9
// JAIL=10, C1=11, U1=12, C2=13, C3=14, R2=15, D1=16, CC2=17, D2=18, D3=19
// FP=20, E1=21, CH2=22, E2=23, E3=24, R3=25, F1=26, F2=27, U2=28, F3=29
// G2J=30, G1=31, G2=32, CC3=33, G3=34, R4=35, CH3=36, H1=37, T2=38, H2=39

const int CC[3] = {2, 17, 33};
const int CH[3] = {7, 22, 36};
const int R[4] = {5, 15, 25, 35};
const int U[2] = {12, 28};
const int G2J = 30;
const int JAIL = 10;
const int GO = 0;
const int C1 = 11;
const int E3 = 24;
const int H2 = 39;
const int R1 = 5;

// CC cards: shuffle at start, draw from top, return to bottom
// Only 2/16 cause movement; we track position in deck
struct CCDeck {
    int pos; // next card to draw (0-15)
    CCDeck() : pos(0) {}
    int draw() {
        // Cards 0: Advance to GO, 1: Go to JAIL, 2-15: stay
        int card = pos;
        pos = (pos + 1) % 16;
        return card;
    }
};

// CH cards: 10/16 cause movement
struct CHDeck {
    int pos;
    CHDeck() : pos(0) {}
    int draw() {
        int card = pos;
        pos = (pos + 1) % 16;
        return card;
    }
};

// Find next R (railway) from current position
int nextR(int pos) {
    for (int i = 0; i < 4; i++) {
        if (R[i] > pos) return R[i];
    }
    return R[0]; // wrap around
}

// Find next U (utility) from current position
int nextU(int pos) {
    for (int i = 0; i < 2; i++) {
        if (U[i] > pos) return U[i];
    }
    return U[0];
}

// Apply CH card effect, return new position
int applyCH(int card, int pos) {
    switch(card) {
        case 0: return GO;      // Advance to GO
        case 1: return JAIL;    // Go to JAIL
        case 2: return C1;      // Go to C1
        case 3: return E3;      // Go to E3
        case 4: return H2;      // Go to H2
        case 5: return R1;      // Go to R1
        case 6: return nextR(pos); // Go to next R
        case 7: return nextR(pos); // Go to next R
        case 8: return nextU(pos); // Go to next U
        case 9: return (pos - 3 + 40) % 40; // Go back 3
        default: return pos;    // Stay
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    const int ITER = 20000000; // 20 million rolls

    vector<long long> cnt(40, 0);
    mt19937 rng(42); // fixed seed for reproducibility

    uniform_int_distribution<int> die(1, S);

    CCDeck cc;
    CHDeck ch;

    int pos = GO;
    int doubles = 0;

    for (int iter = 0; iter < ITER; iter++) {
        int d1 = die(rng);
        int d2 = die(rng);

        if (d1 == d2) {
            doubles++;
            if (doubles == 3) {
                // 3 consecutive doubles → JAIL
                pos = JAIL;
                doubles = 0;
                cnt[pos]++;
                continue;
            }
        } else {
            doubles = 0;
        }

        int steps = d1 + d2;
        pos = (pos + steps) % 40;

        // Check G2J
        if (pos == G2J) {
            pos = JAIL;
            cnt[pos]++;
            continue;
        }

        // Check CC
        bool isCC = false;
        for (int i = 0; i < 3; i++) {
            if (pos == CC[i]) { isCC = true; break; }
        }
        if (isCC) {
            int card = cc.draw();
            if (card == 0) pos = GO;
            else if (card == 1) pos = JAIL;
            cnt[pos]++;
            continue;
        }

        // Check CH
        bool isCH = false;
        for (int i = 0; i < 3; i++) {
            if (pos == CH[i]) { isCH = true; break; }
        }
        if (isCH) {
            int card = ch.draw();
            pos = applyCH(card, pos);
            // After CH card, check G2J
            if (pos == G2J) { pos = JAIL; cnt[pos]++; continue; }
            // After CH card "go back 3 squares", might land on CC
            // e.g., CH3(36) → back 3 → CC3(33)
            bool isCC2 = false;
            for (int i = 0; i < 3; i++)
                if (pos == CC[i]) { isCC2 = true; break; }
            if (isCC2) {
                int card2 = cc.draw();
                if (card2 == 0) pos = GO;
                else if (card2 == 1) pos = JAIL;
            }
            cnt[pos]++;
            continue;
        }

        cnt[pos]++;
    }

    // Find top 3 most visited squares
    vector<pair<long long, int>> v;
    for (int i = 0; i < 40; i++) {
        v.push_back({cnt[i], i});
    }
    sort(v.begin(), v.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    // Output 6-digit modal string
    printf("%02d%02d%02d\n", v[0].second, v[1].second, v[2].second);

    return 0;
}
