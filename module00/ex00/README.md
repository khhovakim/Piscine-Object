🏦 Bank Management System (C++)

A small object-oriented C++ project simulating a simple bank system that manages user accounts, deposits, withdrawals, and loans. The system handles internal bookkeeping and robust error handling via exceptions.

📁 Project Structure

    include/
        bank.h            # Bank class declaration
        bankAccount.h     # Nested Account struct interface
        bankException.h   # Custom exception classes
    src/
        bank.cpp          # Implementation of Bank methods
        bankAccount.cpp   # Implementation of Bank::Account methods
    main.cpp              # Basic test suite for Bank system
    README.md             # Project documentation

🚀 Features

    -Account creation with automatic unique IDs
    -Read/write access to accounts via operator[]
    -5% fee on all deposits
    -Loaning system (with internal bank funds tracking)
    -Custom exceptions for:
        *Account not found
        *Insufficient funds
        *Invalid amounts
    -Fully encapsulated Account (nested within Bank)
    -No raw pointers (uses std::unique_ptr)

🛠️ Build Instructions
You need a C++20-compatible compiler.
# Compile the project with tests
make

# Run
./banking
