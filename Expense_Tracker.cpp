#include <iostream>
#include <iomanip>
#include <limits>


static void clear_stdin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ExpenseManager mgr;
    bool running = true;

    while (running) {
        std::cout << "\n--- Expense Tracker ---\n";
        std::cout << "1) Add expense\n";
        std::cout << "2) View all\n";
        std::cout << "3) Search\n";
        std::cout << "4) Totals by category\n";
        std::cout << "5) Delete by ID\n";
        std::cout << "6) Exit\n";
        std::cout << "Choose: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            clear_stdin();
            continue;
        }
        clear_stdin();

        if (choice == 1) {
            std::string date, cat, desc;
            double amt;

            std::cout << "Date (YYYY-MM-DD): ";
            std::getline(std::cin, date);

            std::cout << "Category: ";
            std::getline(std::cin, cat);

            std::cout << "Description: ";
            std::getline(std::cin, desc);

            std::cout << "Amount: ";
            if (!(std::cin >> amt)) {
                std::cout << "Invalid amount\n";
                std::cin.clear();
                clear_stdin();
                continue;
            }
            clear_stdin();

            int id = mgr.add_expense(date, cat, desc, amt);
            std::cout << "Added with ID: " << id << "\n";
        }

        else if (choice == 2) {
            auto all = mgr.all();
            if (all.empty()) {
                std::cout << "No expenses yet.\n";
                continue;
            }

            std::cout << std::left
                << std::setw(6)  << "ID"
                << std::setw(12) << "Date"
                << std::setw(15) << "Category"
                << std::setw(30) << "Description"
                << std::setw(10) << "Amount"
                << "\n";

            std::cout << std::string(80, '-') << "\n";

            for (const auto &e : all) {
                std::cout << std::left
                    << std::setw(6)  << e.id
                    << std::setw(12) << e.date
                    << std::setw(15) << e.category
                    << std::setw(30) << e.description
                    << std::setw(10) << std::fixed << std::setprecision(2) << e.amount
                    << "\n";
            }
        }

        else if (choice == 3) {
            std::string kw;
            std::cout << "Enter date/category/keyword: ";
            std::getline(std::cin, kw);

            auto res = mgr.search_by_keyword(kw);
            if (res.empty()) {
                std::cout << "No matches\n";
                continue;
            }

            for (const auto &e : res) {
                std::cout << e.id << " | "
                          << e.date << " | "
                          << e.category << " | "
                          << e.description << " | "
                          << std::fixed << std::setprecision(2) << e.amount << "\n";
            }
        }

        else if (choice == 4) {
            auto totals = mgr.totals_by_category();
            std::cout << "Totals by category:\n";

            for (const auto &p : totals) {
                std::cout << std::setw(15) << p.first << " : "
                          << std::fixed << std::setprecision(2) << p.second << "\n";
            }
        }

        else if (choice == 5) {
            int id;
            std::cout << "Enter ID to delete: ";

            if (!(std::cin >> id)) {
                std::cout << "Invalid ID\n";
                std::cin.clear();
                clear_stdin();
                continue;
            }
            clear_stdin();

            bool ok = mgr.delete_expense(id);
            std::cout << (ok ? "Deleted\n" : "Not found\n");
        }

        else if (choice == 6) {
            running = false;
        }
    }

    std::cout << "Bye!\n";
    return 0;
}
