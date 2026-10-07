#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Monopoly board: 40 squares indexed 0-39
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

struct CCDeck {
    vector<int> cards;
    int pos;
    CCDeck() {
        cards.resize(16);
        cards[0] = 0; // GO
        cards[1] = 1; // JAIL
        for (int i = 2; i < 16; i++) cards[i] = 2; // stay
        // Shuffle
        mt19937 rng(12345);
        shuffle(cards.begin(), cards.end(), rng);
        pos = 0;
    }
    int draw() {
        int c = cards[pos];
        pos = (pos + 1) % 16;
        return c;
    }
};

struct CHDeck {
    vector<int> cards;
    int pos;
    CHDeck() {
        cards.resize(16);
        for (int i = 0; i < 10; i++) cards[i] = i; // 0-9: movement cards
        for (int i = 10; i < 16; i++) cards[i] = 10; // stay
        mt19937 rng(54321);
        shuffle(cards.begin(), cards.end(), rng);
        pos = 0;
    }
    int draw() {
        int c = cards[pos];
        pos = (pos + 1) % 16;
        return c;
    }
};

int nextR(int pos) {
    for (int i = 0; i < 4; i++)
        if (R[i] > pos) return R[i];
    return R[0];
}

int nextU(int pos) {
    for (int i = 0; i < 2; i++)
        if (U[i] > pos) return U[i];
    return U[0];
}

int applyCH(int card, int pos) {
    switch(card) {
        case 0: return GO;
        case 1: return JAIL;
        case 2: return C1;
        case 3: return E3;
        case 4: return H2;
        case 5: return R1;
        case 6: return nextR(pos);
        case 7: return nextR(pos);
        case 8: return nextU(pos);
        case 9: return (pos - 3 + 40) % 40;
        default: return pos;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    const int ITER = 20000000;

    vector<long long> cnt(40, 0);
    mt19937 rng(99999); // different seed from std

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
                pos = JAIL;
                doubles = 0;
                cnt[pos]++;
                continue;
            }
        } else {
            doubles = 0;
        }

        pos = (pos + d1 + d2) % 40;

        if (pos == G2J) {
            pos = JAIL;
            cnt[pos]++;
            continue;
        }

        bool isCC = false;
        for (int i = 0; i < 3; i++) if (pos == CC[i]) isCC = true;
        if (isCC) {
            int card = cc.draw();
            if (card == 0) pos = GO;
            else if (card == 1) pos = JAIL;
            cnt[pos]++;
            continue;
        }

        bool isCH = false;
        for (int i = 0; i < 3; i++) if (pos == CH[i]) isCH = true;
        if (isCH) {
            int card = ch.draw();
            pos = applyCH(card, pos);
            // After CH card, check G2J
            if (pos == G2J) { pos = JAIL; cnt[pos]++; continue; }
            // After CH card "go back 3 squares", might land on CC
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

    vector<pair<long long, int>> v;
    for (int i = 0; i < 40; i++)
        v.push_back({cnt[i], i});
    sort(v.begin(), v.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    printf("%02d%02d%02d\n", v[0].second, v[1].second, v[2].second);

    return 0;
}
