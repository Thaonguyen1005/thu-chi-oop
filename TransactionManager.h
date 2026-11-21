#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Transaction.h"
#include "Budget.h"

class TransactionManager {
    std::vector<std::unique_ptr<Transaction>> items;
    Budget budget;
    int nextId = 1;
    std::string username;
public:
    explicit TransactionManager(const std::string& user);

    Budget& getBudget() { return budget; }
    const Budget& getBudget() const { return budget; }
    const std::vector<std::unique_ptr<Transaction>>& getAll() const { return items; }

    void add(bool isIncome, long long amount, const std::string& cat,
             const Date& d, const std::string& note);
    Transaction* findById(int id);
    bool remove(int id);

    long long total(bool income) const;
    long long totalInMonth(bool income, int m, int y) const;
    long long spentInMonth(int m, int y) const { return totalInMonth(false, m, y); }

    void list() const;
    static void printHeader();

    void save() const;
    void load();
};
