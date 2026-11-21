#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char sep);
std::string cleanField(std::string s);   // thay '|' để không hỏng file dữ liệu
std::string money(long long v);          // 1500000 -> 1.500.000
std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt, int lo, int hi);
long long readMoney(const std::string& prompt);
