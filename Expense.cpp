#include "../include/Expense.h"
#include <sstream>
#include <iomanip>

std::string Expense::to_csv() const {
    std::ostringstream oss;
    // simple CSV, no escaping for commas in description for brevity
    oss << id << ',' << date << ',' << category << ',' << description << ',' << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}

bool Expense::from_csv(const std::string &line, Expense &out) {
    std::istringstream iss(line);
    std::string token;

    try {
        // id
        if (!std::getline(iss, token, ',')) return false;
        out.id = std::stoi(token);
        // date
        if (!std::getline(iss, out.date, ',')) return false;
        // category
        if (!std::getline(iss, out.category, ',')) return false;
        // description
        if (!std::getline(iss, out.description, ',')) return false;
        // amount
        if (!std::getline(iss, token, ',')) {
            // maybe EOF, try read rest
            if (!std::getline(iss, token)) return false;
        }
        out.amount = std::stod(token);
    } catch (...) {
        return false;
    }
    return true;
}
