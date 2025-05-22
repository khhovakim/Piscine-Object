#ifndef  __BANK_EXCEPTIO_H__
# define __BANK_EXCEPTIO_H__

# include "bank.h"

// --- Standard Library Includes ---
# include <exception> // For exception

// Exception thrown when a requested account does not exist
class Bank::AccountNotFound final : public std::exception
{
public:
    // Return explanatory string
    const char* what() const noexcept override { return "Account not found"; }
};

// Exception thrown when there are not enough funds for an operation
class Bank::InsufficientFunds final : public std::exception
{
public:
    // Return explanatory string
    const char* what() const noexcept override { return "Insufficient funds"; }
};

#endif // end of __BANK_EXCEPTIO_H__