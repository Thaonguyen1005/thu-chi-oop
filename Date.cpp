#include "Date.h"
#include "Utils.h"
#include <ctime>
#include <cstdio>
#include <iostream>
using namespace std;

Date::Date(int d, int m, int y) : d(d), m(m), y(y) {}

bool Date::isValid(int d, int m, int y) {
    if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1) return false;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    if (leap) days[1] = 29;
    return d <= days[m - 1];
}

Date Date::today() {
    time_t t = time(nullptr);
    tm* lt = localtime(&t);
    return Date(lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}

bool Date::parse(const string& s, Date& out) {
    int d, m, y;
    if (sscanf(s.c_str(), "%d/%d/%d", &d, &m, &y) == 3 && isValid(d, m, y)) {
        out = Date(d, m, y);
        return true;
    }
    return false;
}

string Date::toString() const {
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", d, m, y);
    return buf;
}

Date readDate(const string& prompt) {
    while (true) {
        string s = readLine(prompt + " (dd/mm/yyyy, Enter = hom nay): ");
        if (s.empty()) return Date::today();
        Date dt;
        if (Date::parse(s, dt)) return dt;
        cout << "  -> Ngay khong hop le.\n";
    }
}
