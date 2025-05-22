#include "bank.h"

// Standard library headers
#include <cstddef>          // For std::size_t
#include <cmath>            // For std::round
#include <iostream>         // For std::ostream
#include <string>           // For std::string
#include <memory>           // For std::unique_ptr
#include <utility>          // For std::move, std::as_const
#include <stdexcept>        // For std::invalid_argument
#include <unordered_map>    // For std::unordered_map

// Bank-specific internal headers
#include "bankAccount.h"    // For Bank::Account
#include "bankException.h"  // For Bank::AccountNotFoundException, Bank::InsufficientFunds

// Returns a const reference to an account by ID, throws if not found
const Bank::Account& Bank::operator[](std::size_t id) const
{
    accountExistCheck(id);
    const auto& it = _accounts.find(id);
    return *(it->second);
}

// Returns a non-const reference to an account by ID
Bank::Account& Bank::operator[](std::size_t id)
{
    return const_cast<Bank::Account&>(std::as_const(*this)[id]);
}

// Outputs the bank state to a stream
std::ostream& operator<<(std::ostream& os, const Bank& bank)
{
    os << "Bank funds: " << bank._bankFunds << " $\n";
    os << "Accounts:\n";
    for (const auto& [_, accPtr] : bank._accounts)
        os << "\t- " << *accPtr << "\n";
    return os;
}

// Creates a new account with a given owner and initial deposit
void Bank::createAccount(const std::string& ownerName, int initialDeposit /* default = 0 */)
{
    amountCheck(initialDeposit);

    // Allocate new account using constructor accessible within Bank
    auto bankAccount = std::unique_ptr<Account>(new Account(ownerName, initialDeposit));
    _accounts.emplace(bankAccount->getId(), std::move(bankAccount));
}

// Deletes an existing account by ID
void Bank::deleteAccount(std::size_t id)
{
    accountExistCheck(id);
    auto it = _accounts.find(id);
    _accounts.erase(it);
}

// Deposits money into the given account (with 5% fee)
void Bank::deposit(std::size_t id, int amount)
{
    amountCheck(amount);
    int deposit { takeFee(amount) };
    (*this)[id]._balance += deposit;
}

// Withdraws money from an account, throws if insufficient funds
int Bank::withdraw(std::size_t id, int amount)
{
    accountBalanceCheck(id, amount);
    (*this)[id]._balance -= amount;
    return amount;
}

// Loans money from the bank to an account, throws if bank lacks funds
void Bank::giveLoan(std::size_t id, int amount)
{
    bankBalanceCheck(amount);
    _bankFunds -= amount;
    (*this)[id]._balance += amount;
}

// Validates that the amount is non-negative
void Bank::amountCheck(int amount) const
{
    if (amount < 0) {
        throw std::invalid_argument("Deposit must be non-negative");
    }
}

// Ensures account has enough funds to perform a withdrawal
void Bank::accountBalanceCheck(std::size_t id, int amount) const
{
    amountCheck(amount);

    if ((*this)[id]._balance < amount) {
        throw InsufficientFunds();
    }
}

// Ensures the bank has enough funds to issue a loan
void Bank::bankBalanceCheck(int amount) const
{
    amountCheck(amount);

    if (_bankFunds < amount) {
        throw InsufficientFunds();
    }
}

// Checks if the account with the given ID exists
void Bank::accountExistCheck(std::size_t id) const
{
    if (_accounts.find(id) == _accounts.end()) {
        throw AccountNotFound();
    }
}

// Takes 5% fee from the deposit and returns the net amount
int Bank::takeFee(int deposit)
{
    int fee { static_cast<int>(std::round(deposit * 0.05)) };
    _bankFunds += fee;
    return deposit - fee;
}
