#ifndef  __BANK_H__
# define __BANK_H__

// --- Standard Library Includes ---
# include <cstddef>        // For std::size_t
# include <iostream>       // For std::ostream
# include <unordered_map>  // For std::unordered_map
# include <string>         // For std::string
# include <memory>         // For std::unique_ptr

// The Bank class manages user accounts and internal bank funds.
// It allows account creation, deletion, deposits, withdrawals, and loans.
class Bank
{
private:
    // --- Forward Declarations ---

    // Nested Account structure; users interact through Bank interface only
    struct Account;

    // Custom exceptions defined in separate files
    class AccountNotFound;
    class InsufficientFunds;

public:
    // --- Aliases ---

    // Alias for a container mapping account IDs to accounts
    using AccountMap = std::unordered_map<std::size_t, std::unique_ptr<Account>>;

public:
    // --- Constructors / Destructor ---

    // Construct bank with optional initial funds (default = 0)
    explicit Bank(int funds = 0)
        : _bankFunds { funds }
    { }

    // Default destructor
    ~Bank() = default;

    // Disable copy and move operations (Bank should not be duplicated)
    Bank(Bank&&)                 = delete;
    Bank(const Bank&)            = delete;
    Bank& operator=(Bank&&)      = delete;
    Bank& operator=(const Bank&) = delete;

public:
    // --- Access to Account by ID ---

    // Read-only access to an account by ID (throws if not found)
    const Account& operator[](std::size_t) const;

    // Writable access to an account by ID (throws if not found)
    Account& operator[](std::size_t);

public:
    // --- Print Bank Summary ---

    // Print a summary of bank state and all accounts
    friend std::ostream& operator<<(std::ostream&, const Bank&);

public:
    // --- Bank Operations ---

    // Create a new account for an owner, with optional initial deposit
    void createAccount(const std::string&, int initialDeposit = 0);

    // Delete an account by ID
    void deleteAccount(std::size_t);

    // Deposit money into account (bank takes a 5% fee)
    void deposit(std::size_t, int);

    // Withdraw money from account (throws if insufficient balance)
    int withdraw(std::size_t, int);

    // Give a loan from bank funds to an account (throws if bank funds too low)
    void giveLoan(std::size_t, int);

public:
    // --- Bank Information ---

    // Get current available funds in the bank
    int getFunds() const noexcept { return _bankFunds; }

private:
    // --- Internal Helper Functions ---

    // Deduct 5% fee from deposits and return remaining amount
    int takeFee(int);

    // Check that amount is not negative (throws if invalid)
    void amountCheck(int) const;

    // Check if bank has sufficient funds to give a loan
    void bankBalanceCheck(int) const;

    // Check if account exists by ID (throws if not found)
    void accountExistCheck(std::size_t) const;

    // Check if account has enough funds for withdrawal
    void accountBalanceCheck(std::size_t id, int amount) const;

private:
    // --- Internal State ---

    // Total funds available in the bank (used for issuing loans)
    int _bankFunds;

    // Container for managing accounts via unique ID
    AccountMap _accounts;
};

#endif // __BANK_H__
