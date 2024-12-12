# esep-extra
extra credit assignment for esep class

# In-Memory Database with Transaction Support

A C++ implementation of an in-memory key-value database that supports atomic transactions.

## Features

- Key-value storage with string keys and integer values
- Transaction support with commit and rollback capabilities
- ACID compliance for transactions
- Thread-safe single transaction handling

## Requirements

- C++ compiler with C++11 support (e.g., g++, MSVC)
- Windows/Linux/MacOS operating system

## Installation

1. Clone the repository or download the source files
2. Navigate to the project directory
3. Compile the code:

```bash```
g++ -std=c++11 main.cpp -o inmemorydb

Usage
Running the Program

./inmemorydb

API Reference
class InMemoryDB {
    void begin_transaction();  // Start a new transaction
    void put(string key, int value);  // Store or update a key-value pair
    int get(string key);  // Retrieve a value (-1 if key doesn't exist)
    void commit();  // Commit the current transaction
    void rollback();  // Rollback the current transaction
};

Example Usage
InMemoryDB db;
db.begin_transaction();
db.put("A", 5);  // Store value in transaction
db.commit();     // Commit changes
int value = db.get("A");  // Retrieve value

Error Handling
Throws runtime_error if attempting to put without an active transaction
Throws runtime_error if committing/rolling back without an active transaction
Returns -1 for non-existent keys in get operations
Future Improvements
Add support for multiple concurrent transactions
Implement persistence to disk
Add more data type support beyond integers
Include comprehensive test suite

Author
Taran Ramu
