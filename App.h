#pragma once
#include <memory>
#include "User.h"
#include "TransactionManager.h"

// Giao diện console + tích hợp các module
class App {
    UserManager userMgr;
    User* current = nullptr;
    std::unique_ptr<TransactionManager> mgr;

    void doRegister();
    void doLogin();
    void accountMenu();
    void addTransaction(bool isIncome);
    void editTransaction();
    void deleteTransaction();
    void showBudgetStatus(int m, int y, bool onlyWarn);
    void budgetMenu();
    void statsMenu();
    void mainMenu();
public:
    void run();
};
