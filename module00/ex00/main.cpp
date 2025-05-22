#include <iostream>        // For std::cout, std::cerr, std::endl
#include <exception>       // For std::exception

#include "bank.h"          // For Bank
#include "bankAccount.h"   // For Bank::Account
#include "bankException.h" // For Bank exceptions

void test_create_and_get_account() {
    std::cout << "Running: test_create_and_get_account... ";
    try {
        Bank bank;
        bank.createAccount("Alice", 1000);

        const auto& acc = bank[0];
        bool pass = acc.getOwner() == "Alice" && acc.getBalance() > 0;
        std::cout << (pass ? "PASSED\n" : "FAILED\n");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void test_deposit_and_withdraw() {
    std::cout << "Running: test_deposit_and_withdraw... ";
    try {
        Bank bank;
        bank.createAccount("Bob", 500);

        int oldBalance = bank[0].getBalance();
        bank.deposit(0, 200);
        int newBalance = bank[0].getBalance();

        int withdrawn = bank.withdraw(0, 100);
        int finalBalance = bank[0].getBalance();

        bool pass = (newBalance > oldBalance) &&
                    (withdrawn == 100) &&
                    (finalBalance == newBalance - 100);

        std::cout << (pass ? "PASSED\n" : "FAILED\n");
    }  catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void test_insufficient_funds() {
    std::cout << "Running: test_insufficient_funds... ";
    try {
        Bank bank;
        bank.createAccount("Charlie", 100);
        bank.withdraw(0, 200); // Should throw
        std::cout << "FAILED (no exception)\n";
    }  catch (const std::exception& e) {
        std::cerr << e.what() << " <PASSED (an exception is thrown)>" << std::endl;
    }
}

void test_loan() {
    std::cout << "Running: test_loan... ";
    try {
        Bank bank(1000);
        bank.createAccount("David", 100);

        int beforeLoan = bank[0].getBalance();
        bank.giveLoan(0, 500);

        int afterLoan = bank[0].getBalance();
        bool pass = afterLoan == beforeLoan + 500 && bank.getFunds() == 500;

        std::cout << (pass ? "PASSED\n" : "FAILED\n");
    }  catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void test_invalid_account() {
    std::cout << "Running: test_invalid_account... ";
    try {
        Bank bank;
        bank.deposit(999, 100); // Should throw
        std::cout << "FAILED (no exception)\n";
    }  catch (const std::exception& e) {
        std::cerr << e.what() << " <PASSED (an exception is thrown)>" << std::endl;
    }
}

int main() {
    test_create_and_get_account();
    test_deposit_and_withdraw();
    test_insufficient_funds();
    test_loan();
    test_invalid_account();

    std::cout << "\nAll tests finished.\n";
    return 0;
}
