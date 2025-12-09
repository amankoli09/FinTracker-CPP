#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include "Expense.h"
#include <vector>
#include <string>
#include <map>

class ExpenseManager {
public:
    ExpenseManager(const std::string &storage_path = "data/expenses.csv");
    ~ExpenseManager();

    void load();
    void save() const;

    int add_expense(const std::string &date, const std::string &category,
                    const std::string &desc, double amount);

    bool delete_expense(int id);

    std::vector<Expense> all() const;

    std::vector<Expense> search_by_keyword(const std::string &kw) const;

    std::map<std::string, double> totals_by_category() const;

private:
    mutable std::vector<Expense> expenses;
    std::string storage_path;
    int next_id{1};

    void recompute_next_id();
};

#endif // EXPENSE_MANAGER_H
