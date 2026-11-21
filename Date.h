#pragma once
#include <string>

class Date {
    int d, m, y;
public:
    Date(int d = 1, int m = 1, int y = 2000);
    int getDay() const { return d; }
    int getMonth() const { return m; }
    int getYear() const { return y; }

    static bool isValid(int d, int m, int y);
    static Date today();
    static bool parse(const std::string& s, Date& out);
    std::string toString() const;
    bool operator==(const Date& o) const { return d == o.d && m == o.m && y == o.y; }
};

Date readDate(const std::string& prompt);   // Enter = hôm nay
