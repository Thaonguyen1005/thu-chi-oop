#include "Utils.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> split(const string& s, char sep) {
    vector<string> res;
    size_t start = 0, pos;
    while ((pos = s.find(sep, start)) != string::npos) {
        res.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    res.push_back(s.substr(start));
    return res;
}

string cleanField(string s) {
    replace(s.begin(), s.end(), '|', ' ');
    return s;
}

string money(long long v) {
    string s = to_string(v < 0 ? -v : v), out;
    int cnt = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        out.insert(out.begin(), s[i]);
        if (++cnt % 3 == 0 && i != 0) out.insert(out.begin(), '.');
    }
    return (v < 0 ? "-" : "") + out;
}

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt, int lo, int hi) {
    while (true) {
        string s = readLine(prompt);
        try {
            int v = stoi(s);
            if (v >= lo && v <= hi) return v;
        } catch (...) {}
        cout << "  -> Nhap so nguyen trong khoang [" << lo << ", " << hi << "].\n";
    }
}

long long readMoney(const string& prompt) {
    while (true) {
        string s = readLine(prompt);
        try {
            long long v = stoll(s);
            if (v > 0) return v;
        } catch (...) {}
        cout << "  -> So tien phai la so nguyen duong.\n";
    }
}
