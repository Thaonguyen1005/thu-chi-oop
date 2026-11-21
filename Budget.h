#pragma once

// Ngân sách: hạn mức chi tiêu theo tháng + mức cảnh báo
class Budget {
    long long limit = 0;
    double warnRatio = 0.8;      // cảnh báo khi chi >= 80% hạn mức
public:
    enum Status { NOT_SET, OK, NEAR_LIMIT, EXCEEDED };

    void setLimit(long long l) { limit = l; }
    long long getLimit() const { return limit; }

    Status check(long long spent) const {
        if (limit <= 0) return NOT_SET;
        if (spent > limit) return EXCEEDED;
        if (spent >= limit * warnRatio) return NEAR_LIMIT;
        return OK;
    }
    long long remaining(long long spent) const { return limit - spent; }
};
