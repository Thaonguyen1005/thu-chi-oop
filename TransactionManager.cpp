#include "TransactionManager.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

TransactionManager::TransactionManager(const string& user) : username(user) { load(); }

void TransactionManager::add(bool isIncome, long long amount, const string& cat,
                             const Date& d, const string& note) {
    if (isIncome) items.push_back(make_unique<Income>(nextId++, amount, cat, d, note));
    else          items.push_back(make_unique<Expense>(nextId++, amount, cat, d, note));
    save();
}

Transaction* TransactionManager::findById(int id) {
    for (auto& t : items)
        if (t->getId() == id) return t.get();
    return nullptr;
}

bool TransactionManager::remove(int id) {
    auto it = find_if(items.begin(), items.end(),
                      [id](const unique_ptr<Transaction>& t) { return t->getId() == id; });
    if (it == items.end()) return false;
    items.erase(it);
    save();
    return true;
}

long long TransactionManager::total(bool income) const {
    long long s = 0;
    for (const auto& t : items)
        if ((t->getCode() == 'I') == income) s += t->getAmount();
    return s;
}

long long TransactionManager::totalInMonth(bool income, int m, int y) const {
    long long s = 0;
    for (const auto& t : items)
        if ((t->getCode() == 'I') == income &&
            t->getDate().getMonth() == m && t->getDate().getYear() == y)
            s += t->getAmount();
    return s;
}

void TransactionManager::list() const {
    if (items.empty()) { cout << "  (Chua co giao dich)\n"; return; }
    printHeader();
    for (const auto& t : items) t->display();
}

void TransactionManager::printHeader() {
    cout << left << setw(5) << "ID" << setw(6) << "Loai" << setw(12) << "Ngay"
         << setw(16) << "Danh muc" << right << setw(14) << "So tien" << "  "
         << left << "Ghi chu\n" << string(70, '-') << "\n";
}

void TransactionManager::save() const {
    ofstream f(username + "_data.txt");
    f << "BUDGET|" << budget.getLimit() << "\n";
    for (const auto& t : items) f << t->serialize() << "\n";
}

void TransactionManager::load() {
    ifstream f(username + "_data.txt");
    string line;
    while (getline(f, line)) {
        auto p = split(line, '|');
        try {
            if (p[0] == "BUDGET" && p.size() >= 2) {
                budget.setLimit(stoll(p[1]));
            } else if (p[0] == "T" && p.size() >= 8) {
                int id = stoi(p[2]);
                long long amt = stoll(p[3]);
                Date d(stoi(p[5]), stoi(p[6]), stoi(p[7]));
                string note = p.size() >= 9 ? p[8] : "";
                if (p[1] == "I") items.push_back(make_unique<Income>(id, amt, p[4], d, note));
                else             items.push_back(make_unique<Expense>(id, amt, p[4], d, note));
                nextId = max(nextId, id + 1);
            }
        } catch (...) { /* bo qua dong loi */ }
    }
}
