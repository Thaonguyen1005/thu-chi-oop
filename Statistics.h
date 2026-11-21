#pragma once
#include "TransactionManager.h"

class Statistics {
    const TransactionManager& mgr;
    static void printSummary(long long inc, long long exp);
public:
    explicit Statistics(const TransactionManager& m) : mgr(m) {}
    void byDay(const Date& d) const;
    void byMonth(int m, int y) const;
    void byCategory(int m, int y) const;   // biểu đồ cột bằng ký tự
    void report() const;
};
