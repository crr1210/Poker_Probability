#include<iostream>
#include<algorithm>
#include<vector>
#include<time.h>
using namespace std;

enum class suit: short {SPADE, HEART, DIAMOND, CLUB};

ostream& operator << (ostream& out, const suit &s) {
        out << static_cast<int> (s);
        return out;
}

class pips {
public:
    pips() {v = 1;}
    pips(int val) {v = val;}
    friend ostream& operator << (ostream& out, const pips& p);
    int get_pips() {return v;}
private:
    int v;
};

ostream& operator << (ostream& out, const pips& p) {
    out << p.v;
    return out;
}

class card {
public:
    card() {s = suit::SPADE; v;}
    card(suit s, pips v):s(s), v(v) {}
    friend ostream& operator <<(ostream& out, const card& c);
    suit get_suit() {return s;}
    pips get_pips() {return v;}
private:
    suit s;
    pips v;
};

ostream& operator << (ostream& out, const card& c) {
    out << c.s << c.v;
    return out;
}

void init_deck(vector<card> &d) {
    for(int i = 1; i < 14; i++) {
        card c(suit::SPADE, i);
        d[i-1] = c;
    }

    for(int i = 1; i < 14; i++) {
        card c(suit::CLUB, i);
        d[i+12] = c;
    }

    for(int i = 1; i < 14; i++) {
        card c(suit::DIAMOND, i);
        d[i+25] = c;
    }

    for(int i = 1; i < 14; i++) {
        card c(suit::HEART, i);
        d[i+38] = c;
    }
}

void print(vector<card> &deck) {
    for(auto p = deck.begin(); p != deck.end(); p++) {
        cout << *p << endl;
    }
}

bool is_flush(vector<card> &hand) {
    suit s = hand[0].get_suit();
    for(auto p = hand.begin()+1; p != hand.end(); p++) {
        if(p -> get_suit() != s) return false;
    }
    return true;
}

bool is_straight(vector<card> &hand) {
    int pip_v[5] = {0};
    int i = 0;
    for(auto p = hand.begin(); p != hand.end(); p++) {
        pip_v[i++] = p->get_pips().get_pips();
    }

    sort(pip_v, pip_v+5);
    if(pip_v[0] == 1) {
        return pip_v[1] == 10 && pip_v[2] == 11 && pip_v[3] == 12 && pip_v[4] == 13;
    } else{
        return pip_v[0] == pip_v[1] -1 && pip_v[1] == pip_v[2] -1
        && pip_v[2] == pip_v[3] - 1 && pip_v[3] == pip_v[4] - 1;
    }
}

bool is_straight_flush(vector<card> &hand) {
    return is_straight(hand) && is_flush(hand);
}

int main() {
    vector<card> deck(52);
    srand(time(0));
    init_deck(deck);
    int how_many = 0;
    int flush_count = 0;
    int straight_count = 0;
    int flush_str_count = 0;
    cout << "How many shuffles?";
    cin >> how_many;

    for(int loop = 0; loop < how_many; loop++) {
        random_shuffle(deck.begin(), deck.end());
        vector<card> hand(5);
        int i = 0;
        for(auto p = hand.begin(); i < 5; p++) {
            hand[i++] = *p;
        }
        if(is_straight(hand)) {
            straight_count++;
            cout << straight_cout << " ";
        }
        if(is_flush(hand)) {
            flush_count++;
        }
        if(is_straight_flush(hand)) {
            flush_str_count++;
        }
    }

    cout << "Flushes: " << flush_count << " out of " << how_many << " decks       RATE: " << flush_count/how_many << endl;

    cout << "Straight: " << straight_count << " out of " << how_many << " decks       RATE: " << straight_count/how_many << endl;

    cout << "Straight flushes: " << flush_str_count << " out of " << how_many << " decks       RATE: " << flush_str_count/how_many << endl;
}

