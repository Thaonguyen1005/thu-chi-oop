#include "Statistics.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;

void Statistics::printSummary(long long inc, long long exp) {
    cout << "  Tong thu : " << money(inc) << " VND\n"
         << "  Tong chi : " << money(exp) << " VND\n"
         << "  So du    : " << money(inc - exp) << " VND\n";
}

void Statistics::byDay(const Date& d) const {
    long long inc = 0, exp = 0;
    cout << "\n--- Thong ke ngay " << d.toString() << " ---\n";
    bool any = false;
    for (const auto& t : mgr.getAll()) {
        if (t->getDate() == d) {
            if (!any) { TransactionManager::printHeader(); any = true; }
            t->display();
            (t->getCode() == 'I' ? inc : exp) += t->getAmount();
        }
    }
    if (!any) cout << "  (Khong co giao dich)\n";
    printSummary(inc, exp);
}

void Statistics::byMonth(int m, int y) const {
    cout << "\n--- Thong ke thang " << m << "/" << y << " ---\n";
    printSummary(mgr.totalInMonth(true, m, y), mgr.totalInMonth(false, m, y));
}

void Statistics::byCategory(int m, int y) const {
    map<string, long long> cat;
    long long maxV = 0, total = 0;
    for (const auto& t : mgr.getAll()) {
        if (t->getCode() == 'E' && t->getDate().getMonth() == m && t->getDate().getYear() == y) {
            cat[t->getCategory()] += t->getAmount();
            maxV = max(maxV, cat[t->getCategory()]);
            total += t->getAmount();
        }
    }
    cout << "\n--- Chi tieu theo danh muc, thang " << m << "/" << y << " ---\n";
    if (cat.empty()) { cout << "  (Khong co khoan chi)\n"; return; }
    for (auto& kv : cat) {
        int bar = (int)(kv.second * 30 / maxV);
        double pct = 100.0 * kv.second / total;
        cout << left << setw(15) << kv.first << "| " << string(max(bar, 1), '#')
             << " " << money(kv.second) << " (" << fixed << setprecision(1) << pct << "%)\n";
    }
}

void Statistics::report() const {
    cout << "\n=========== BAO CAO TONG HOP ===========\n";
    printSummary(mgr.total(true), mgr.total(false));
}
