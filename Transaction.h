#pragma once
#include <string>
#include "Date.h"

// Lớp trừu tượng: một giao dịch thu hoặc chi
class Transaction {
protected:
    int id;
    long long amount;
    std::string category, note;
    Date date;
public:
    Transaction(int id, long long amount, std::string category, Date date, std::string note);
    virtual ~Transaction() = default;

    virtual std::string getType() const = 0;   // "Thu" / "Chi"
    virtual char getCode() const = 0;          // 'I' / 'E' (dùng khi lưu file)

    int getId() const { return id; }
    long long getAmount() const { return amount; }
    const std::string& getCategory() const { return category; }
    const std::string& getNote() const { return note; }
    const Date& getDate() const { return date; }

    void setAmount(long long a) { amount = a; }
    void setCategory(const std::string& c) { category = c; }
    void setNote(const std::string& n) { note = n; }
    void setDate(const Date& d) { date = d; }

    virtual void display() const;
    std::string serialize() const;
};

class Income : public Transaction {
public:
    using Transaction::Transaction;
    std::string getType() const override { return "Thu"; }
    char getCode() const override { return 'I'; }
};

class Expense : public Transaction {
public:
    using Transaction::Transaction;
    std::string getType() const override { return "Chi"; }
    char getCode() const override { return 'E'; }
};
