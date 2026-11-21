#include "Transaction.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Transaction::Transaction(int id, long long amount, string category, Date date, string note)
    : id(id), amount(amount), category(category), note(note), date(date) {}

void Transaction::display() const {
    cout << left << setw(5) << id << setw(6) << getType()
         << setw(12) << date.toString()
         << setw(16) << category
         << right << setw(14) << money(amount) << "  "
         << left << note << "\n";
}

string Transaction::serialize() const {
    return string("T|") + getCode() + "|" + to_string(id) + "|" +
           to_string(amount) + "|" + cleanField(category) + "|" +
           to_string(date.getDay()) + "|" + to_string(date.getMonth()) + "|" +
           to_string(date.getYear()) + "|" + cleanField(note);
}
