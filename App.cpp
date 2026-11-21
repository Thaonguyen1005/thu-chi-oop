#include "App.h"
#include "Statistics.h"
#include "Utils.h"
#include <iostream>
using namespace std;

void App::run() {
    while (true) {
        cout << "\n===== QUAN LY THU CHI CA NHAN =====\n"
             << "1. Dang nhap\n2. Dang ky\n0. Thoat\n";
        int c = readInt("Chon: ", 0, 2);
        if (c == 0) { cout << "Tam biet!\n"; return; }
        if (c == 1) doLogin();
        else doRegister();
        if (current) mainMenu();
    }
}

// ---------- Module 1: nguoi dung ----------
void App::doRegister() {
    string u = readLine("Ten dang nhap: ");
    string p = readLine("Mat khau: ");
    string n = readLine("Ho ten: ");
    string e = readLine("Email: ");
    if (userMgr.registerUser(u, p, n, e)) cout << "Dang ky thanh cong! Hay dang nhap.\n";
    else cout << "Dang ky that bai (ten rong hoac da ton tai).\n";
}

void App::doLogin() {
    string u = readLine("Ten dang nhap: ");
    string p = readLine("Mat khau: ");
    current = userMgr.login(u, p);
    if (!current) { cout << "Sai ten dang nhap hoac mat khau.\n"; return; }
    mgr = make_unique<TransactionManager>(current->getUsername());
    cout << "Xin chao, " << current->getFullName() << "!\n";
}

void App::accountMenu() {
    cout << "\n--- Tai khoan ---\n";
    current->display();
    cout << "1. Doi mat khau\n2. Sua thong tin ca nhan\n0. Quay lai\n";
    int c = readInt("Chon: ", 0, 2);
    if (c == 1) {
        string old = readLine("Mat khau cu: ");
        if (!current->checkPassword(old)) { cout << "Sai mat khau.\n"; return; }
        string np = readLine("Mat khau moi: ");
        if (np.empty()) { cout << "Mat khau khong duoc rong.\n"; return; }
        current->setPassword(np);
        userMgr.save();
        cout << "Da doi mat khau.\n";
    } else if (c == 2) {
        string n = readLine("Ho ten moi (Enter = giu nguyen): ");
        string e = readLine("Email moi (Enter = giu nguyen): ");
        if (!n.empty()) current->setFullName(n);
        if (!e.empty()) current->setEmail(e);
        userMgr.save();
        cout << "Da cap nhat.\n";
    }
}

// ---------- Module 2: thu/chi ----------
void App::addTransaction(bool isIncome) {
    cout << "\n--- Them khoan " << (isIncome ? "THU" : "CHI") << " ---\n";
    long long amt = readMoney("So tien: ");
    string cat = readLine("Danh muc (an uong, di lai, luong...): ");
    if (cat.empty()) cat = "Khac";
    Date d = readDate("Ngay");
    string note = readLine("Ghi chu: ");
    mgr->add(isIncome, amt, cat, d, note);
    cout << "Da them giao dich.\n";
    if (!isIncome) showBudgetStatus(d.getMonth(), d.getYear(), true);
}

void App::editTransaction() {
    mgr->list();
    int id = readInt("Nhap ID can sua (0 = huy): ", 0, 1000000);
    if (id == 0) return;
    Transaction* t = mgr->findById(id);
    if (!t) { cout << "Khong tim thay ID.\n"; return; }
    string s = readLine("So tien moi (Enter = giu " + money(t->getAmount()) + "): ");
    if (!s.empty()) {
        try { long long v = stoll(s); if (v > 0) t->setAmount(v); } catch (...) {}
    }
    s = readLine("Danh muc moi (Enter = giu '" + t->getCategory() + "'): ");
    if (!s.empty()) t->setCategory(s);
    s = readLine("Ngay moi dd/mm/yyyy (Enter = giu " + t->getDate().toString() + "): ");
    Date d;
    if (!s.empty() && Date::parse(s, d)) t->setDate(d);
    s = readLine("Ghi chu moi (Enter = giu nguyen): ");
    if (!s.empty()) t->setNote(s);
    mgr->save();
    cout << "Da cap nhat.\n";
}

void App::deleteTransaction() {
    mgr->list();
    int id = readInt("Nhap ID can xoa (0 = huy): ", 0, 1000000);
    if (id == 0) return;
    cout << (mgr->remove(id) ? "Da xoa.\n" : "Khong tim thay ID.\n");
}

// ---------- Module 3: ngan sach ----------
void App::showBudgetStatus(int m, int y, bool onlyWarn) {
    const Budget& b = mgr->getBudget();
    long long spent = mgr->spentInMonth(m, y);
    switch (b.check(spent)) {
        case Budget::NOT_SET:
            if (!onlyWarn) cout << "Chua dat han muc chi tieu.\n";
            break;
        case Budget::OK:
            if (!onlyWarn)
                cout << "Thang " << m << "/" << y << ": da chi " << money(spent) << "/"
                     << money(b.getLimit()) << " - con lai " << money(b.remaining(spent)) << " VND. An toan.\n";
            break;
        case Budget::NEAR_LIMIT:
            cout << "[CANH BAO] Thang " << m << "/" << y << ": da chi " << money(spent) << "/"
                 << money(b.getLimit()) << " - SAP VUOT han muc (con " << money(b.remaining(spent)) << " VND)!\n";
            break;
        case Budget::EXCEEDED:
            cout << "[VUOT NGAN SACH] Thang " << m << "/" << y << ": da chi " << money(spent) << "/"
                 << money(b.getLimit()) << " - vuot " << money(-b.remaining(spent)) << " VND!\n";
            break;
    }
}

void App::budgetMenu() {
    Date t = Date::today();
    cout << "\n--- Ngan sach ---\n";
    cout << "Han muc hien tai: " << money(mgr->getBudget().getLimit()) << " VND/thang\n";
    showBudgetStatus(t.getMonth(), t.getYear(), false);
    cout << "1. Dat han muc chi tieu thang\n0. Quay lai\n";
    if (readInt("Chon: ", 0, 1) == 1) {
        mgr->getBudget().setLimit(readMoney("Han muc moi (VND/thang): "));
        mgr->save();
        showBudgetStatus(t.getMonth(), t.getYear(), false);
    }
}

// ---------- Module 4: thong ke + menu ----------
void App::statsMenu() {
    Statistics st(*mgr);
    cout << "\n--- Thong ke ---\n1. Theo ngay\n2. Theo thang\n3. Theo danh muc (bieu do)\n"
         << "4. Bao cao tong hop\n0. Quay lai\n";
    int c = readInt("Chon: ", 0, 4);
    if (c == 1) st.byDay(readDate("Ngay"));
    else if (c == 2 || c == 3) {
        int m = readInt("Thang: ", 1, 12);
        int y = readInt("Nam: ", 1900, 2100);
        if (c == 2) st.byMonth(m, y); else st.byCategory(m, y);
    } else if (c == 4) st.report();
}

void App::mainMenu() {
    Date t = Date::today();
    showBudgetStatus(t.getMonth(), t.getYear(), true);
    while (current) {
        cout << "\n======== MENU CHINH ========\n"
             << "1. Them khoan thu\n2. Them khoan chi\n3. Xem danh sach giao dich\n"
             << "4. Sua giao dich\n5. Xoa giao dich\n6. Ngan sach & canh bao\n"
             << "7. Thong ke & bao cao\n8. Tai khoan\n0. Dang xuat\n";
        switch (readInt("Chon: ", 0, 8)) {
            case 1: addTransaction(true); break;
            case 2: addTransaction(false); break;
            case 3: mgr->list(); break;
            case 4: editTransaction(); break;
            case 5: deleteTransaction(); break;
            case 6: budgetMenu(); break;
            case 7: statsMenu(); break;
            case 8: accountMenu(); break;
            case 0: mgr.reset(); current = nullptr; cout << "Da dang xuat.\n"; break;
        }
    }
}
