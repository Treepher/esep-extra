#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

class InMemoryDB {
private:
    std::map<std::string, int> mainDB;
    std::map<std::string, int> transactionDB;
    bool isTransactionActive;

public:
    InMemoryDB() : isTransactionActive(false) {}

    int get(const std::string& key) {
        if (isTransactionActive && transactionDB.count(key) > 0) {
            return transactionDB[key];
        }
        if (mainDB.count(key) > 0) {
            return mainDB[key];
        }
        return -1; // Indicate that the key doesn't exist
    }

    void put(const std::string& key, int value) {
        if (!isTransactionActive) {
            throw std::runtime_error("Transaction not in progress");
        }
        transactionDB[key] = value;
    }

    void begin_transaction() {
        if (isTransactionActive) {
            throw std::runtime_error("Transaction already in progress");
        }
        isTransactionActive = true;
        transactionDB.clear();
    }

    void commit() {
        if (!isTransactionActive) {
            throw std::runtime_error("No transaction in progress");
        }
        for (const auto& pair : transactionDB) {
            mainDB[pair.first] = pair.second;
        }
        transactionDB.clear();
        isTransactionActive = false;
    }

    void rollback() {
        if (!isTransactionActive) {
            throw std::runtime_error("No transaction in progress");
        }
        transactionDB.clear();
        isTransactionActive = false;
    }
};

int main() {
    InMemoryDB db;

    try {
        // Should throw error - no transaction
        db.put("A", 5);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    int value = db.get("A");
    if (value == -1) {
        std::cout << "Key A not found" << std::endl;
    } else {
        std::cout << "Value of A: " << value << std::endl;
    }

    db.begin_transaction();
    db.put("A", 5);
    
    value = db.get("A");
    if (value == -1) {
        std::cout << "Key A not found" << std::endl;
    } else {
        std::cout << "Value of A: " << value << std::endl;
    }

    db.put("A", 6);
    db.commit();

    value = db.get("A");
    if (value == -1) {
        std::cout << "Key A not found" << std::endl;
    } else {
        std::cout << "Value of A: " << value << std::endl;
    }

    return 0;
}