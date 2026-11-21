#pragma once
#include <string>
#include <vector>

class User {
    std::string username, password, fullName, email;
public:
    User() {}
    User(std::string u, std::string p, std::string f, std::string e);

    const std::string& getUsername() const { return username; }
    const std::string& getFullName() const { return fullName; }
    const std::string& getEmail() const { return email; }
    bool checkPassword(const std::string& p) const { return password == p; }

    void setPassword(const std::string& p) { password = p; }
    void setFullName(const std::string& f) { fullName = f; }
    void setEmail(const std::string& e) { email = e; }

    void display() const;
    std::string serialize() const;
    static bool deserialize(const std::string& line, User& u);
};

class UserManager {
    std::vector<User> users;
    const std::string file = "users.txt";
public:
    UserManager();
    void load();
    void save() const;
    User* find(const std::string& username);
    bool registerUser(const std::string& username, const std::string& pass,
                      const std::string& name, const std::string& email);
    User* login(const std::string& username, const std::string& pass);
};
