#ifndef  __BANK_ACCOUNT_H__
# define __BANK_ACCOUNT_H__

# include "bank.h" 

// --- Standard Library Includes ---
# include <cstddef>  // For std::size_t
# include <iostream> // For std::ostream
# include <string>   // For std::string

// Definition of the Account structure nested inside Bank
struct Bank::Account
{
private:
    // --- Friends ---

    // Granting Bank full access to private members
    friend class Bank;

    // Allow printing an account's details via std::ostream
    friend std::ostream& operator<<(std::ostream& os, const Account& acc)
    {
        os << "Account["     << acc._id << "] "
           << acc._ownerName << " : "
           << acc._balance   << " $";
        return os;
    }

public:
    // --- Const Getters (no copies allowed) ---

    // Get the account owner's name (read-only reference)
    const std::string& getOwner()   const noexcept { return _ownerName; }

    // Get the unique ID of the account
    std::size_t        getId()      const noexcept { return _id; }

    // Get the current balance in the account
    int                getBalance() const noexcept { return _balance; }

public:
    // --- Destructor ---

    // Updateing static member data
    ~Account() { _nextId = 0; }

private:
    // --- Constructor ---

    // Constructor is private: only Bank can create an Account
    explicit Account(const std::string& owner, int balance = 0)
        : _balance{ balance }, _id{ _nextId++ }, _ownerName{ owner }
    { }

    // Disable copy/move operations
    Account(Account&&)                 = delete;
    Account(const Account&)            = delete;
    Account& operator=(Account&&)      = delete;
    Account& operator=(const Account&) = delete;

private:
    // --- Static Members ---

    // Global counter used to generate unique account IDs
    static std::size_t _nextId;

private:
    // --- Instance Data ---

    // Current account balance (modifiable by Bank only)
    int               _balance;

    // Unique ID assigned at creation (never changes)
    const std::size_t _id;

    // Account owner name (immutable)
    const std::string _ownerName;
};

#endif // __BANK_ACCOUNT_H__
