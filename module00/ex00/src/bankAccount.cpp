#include "bankAccount.h"

#include <cstddef>  // For std::size_t

// Initialize the static member for unique account IDs
// This counter is shared across all Account instances
std::size_t Bank::Account::_nextId { 0 };
