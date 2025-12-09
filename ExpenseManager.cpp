#include "../include/ExpenseManager.h"
#include "../include/Expense.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

ExpenseManager::ExpenseManager(const std::string &storage_path) : storage_path(storage_path) {
    load();
}

ExpenseManager::~ExpenseManager() {
    try { save(); } catch(...) {}
}

void ExpenseManager::load() {
    expenses.clear();
    std::ifstream ifs(storage_path);
    if (!ifs.is_open()) {
        // create data directory/file if necessary
        std::ofstream ofs(storage_path, std::ios::app);
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.size() == 0) continue;
        if (line[0] == '#') continue; // comment
        Expense e;
        if (Expense::from_csv(line, e)) expenses.push_back(e);
    }
    recompute_next_id();
}

void ExpenseManager::save() const {
    std::ofstream ofs(storage_path, std::ios::trunc);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open storage file for writing");
    }
    ofs << "# id,date,category,description,amount\n";
    for (const auto &e: expenses) ofs << e.to_csv() << '\n';
}

int ExpenseManager::add_expense(const std::string &date, const std::string &category,
                    const std::string &desc, double amount) {
    Expense e;
    e.id = next_id++;
    e.date = date;
    e.category = category;
    e.description = desc;
    e.amount = amount;
    expenses.push_back(e);
    save();
    return e.id;
}

bool ExpenseManager::delete_expense(int id) {
    auto it = std::remove_if(expenses.begin(), expenses.end(), [id](const Expense &e){ return e.id==id; });
    if (it==expenses.end()) return false;
    bool removed = (it!=expenses.end());
    expenses.erase(it, expenses.end());
    save();
    return removed;
}

std::vector<Expense> ExpenseManager::all() const { return expenses; }

std::vector<Expense> ExpenseManager::search_by_keyword(const std::string &kw) const {
    std::vector<Expense> r;
    for (const auto &e: expenses) {
        if (e.date.find(kw) != std::string::npos || e.category.find(kw) != std::string::npos || e.description.find(kw) != std::string::npos) {
            r.push_back(e);
        }
    }
    return r;
}

std::map<std::string, double> ExpenseManager::totals_by_category() const {
    std::map<std::string, double> m;
    for (const auto &e: expenses) m[e.category] += e.amount;
    return m;
}

void ExpenseManager::recompute_next_id() {
    int mx = 0;
    for (const auto &e: expenses) if (e.id > mx) mx = e.id;
    next_id = mx + 1;
}
