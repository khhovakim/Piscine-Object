#ifndef  __BANK_ACCOUNT_H__
# define __BANK_ACCOUNT_H__

# include "bank.h" 

# include <iostream> // For ostream
# include <string>   // For string

struct Bank::Account
{
private:
    friend class Bank;
    friend std::ostream& operator<<(std::ostream& os, const Account& acc)
    {
        os << "Account[" << acc._id << "] "
           << acc._ownerName << " : "
           << acc._balance << " units";
        return os;
    }

public:
    const std::string& getOwner()   const noexcept { return _ownerName; }
    std::size_t        getId()      const noexcept { return _id;        }
    int                getBalance() const noexcept { return _balance;   }

private:
// only Bank can creante account
    explicit Account(const std::string& owner, int balance = 0)
        : _id{ _nextId++ }, _ownerName{ owner }, _balance{ balance }
    {   }
    ~Account() = default;

    Account(Account&&)                 = delete;
    Account(const Account&)            = delete;
    Account& operator=(Account&&)      = delete;
    Account& operator=(const Account&) = delete;

private:
    // ---- Static members (class-wide) ----
    static std::size_t _nextId;

    // ---- Constant members (must be initialized in constructor) ----
    const std::size_t _id;
    const std::string _ownerName;

    // ---- Core data ----
    int               _balance;
};


#endif // end of __BANK_ACCOUNT_H__
