#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

struct Expense {
    int id{0};
    std::string date;    // YYYY-MM-DD
    std::string category;
    std::string description;
    double amount{0.0};

    // Serialize to CSV line
    std::string to_csv() const;
    // Create from CSV line (returns false on parse error)
    static bool from_csv(const std::string &line, Expense &out);
};

#endif // EXPENSE_H
