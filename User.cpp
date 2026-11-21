#include "User.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
using namespace std;

User::User(string u, string p, string f, string e)
    : username(u), password(p), fullName(f), email(e) {}

void User::display() const {
    cout << "  Ten dang nhap : " << username << "\n"
         << "  Ho ten        : " << fullName << "\n"
         << "  Email         : " << email << "\n";
}

string User::serialize() const {
    return cleanField(username) + "|" + cleanField(password) + "|" +
           cleanField(fullName) + "|" + cleanField(email);
}

bool User::deserialize(const string& line, User& u) {
    auto p = split(line, '|');
    if (p.size() < 4) return false;
    u = User(p[0], p[1], p[2], p[3]);
    return true;
}

UserManager::UserManager() { load(); }

void UserManager::load() {
    ifstream f(file);
    string line;
    while (getline(f, line)) {
        User u;
        if (User::deserialize(line, u)) users.push_back(u);
    }
}

void UserManager::save() const {
    ofstream f(file);
    for (const auto& u : users) f << u.serialize() << "\n";
}

User* UserManager::find(const string& username) {
    for (auto& u : users)
        if (u.getUsername() == username) return &u;
    return nullptr;
}

bool UserManager::registerUser(const string& username, const string& pass,
                               const string& name, const string& email) {
    if (username.empty() || pass.empty() || find(username)) return false;
    users.emplace_back(username, pass, name, email);
    save();
    return true;
}

User* UserManager::login(const string& username, const string& pass) {
    User* u = find(username);
    return (u && u->checkPassword(pass)) ? u : nullptr;
}
