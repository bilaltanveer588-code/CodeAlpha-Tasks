#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string CUSTOMERS_FILE = "customers.txt";
const string ACCOUNTS_FILE = "accounts.txt";
const string TRANSACTIONS_FILE = "transactions.txt";
const int RECENT_TRANSACTION_LIMIT = 10;

class Customer {
public:
    int id;
    string name;

    Customer(int customerId = 0, const string& customerName = "")
        : id(customerId), name(customerName) {}
};

class Account {
public:
    int id;
    int customerId;
    double balance;

    Account(int accountId = 0, int ownerId = 0, double openingBalance = 0.0)
        : id(accountId), customerId(ownerId), balance(openingBalance) {}
};

class Transaction {
public:
    string type;
    int sourceAccountId;
    int destinationAccountId;
    double amount;
    long long timestamp;
    string legacyText;

    Transaction(const string& transactionType = "", int sourceId = 0,
                int destinationId = 0, double transactionAmount = 0.0,
                long long transactionTime = 0, const string& oldText = "")
        : type(transactionType), sourceAccountId(sourceId),
          destinationAccountId(destinationId), amount(transactionAmount),
          timestamp(transactionTime), legacyText(oldText) {}

    bool involvesAccount(int accountId) const {
        return sourceAccountId == accountId || destinationAccountId == accountId;
    }

    void display(int accountId) const {
        if (!legacyText.empty()) {
            cout << legacyText << "\n";
            return;
        }

        cout << formatTimestamp(timestamp) << "  " << type << "  "
             << fixed << setprecision(2) << amount;
        if (type == "TRANSFER") {
            cout << "  From account " << sourceAccountId
                 << " to account " << destinationAccountId;
        } else if (type == "DEPOSIT") {
            cout << "  Deposited into account " << destinationAccountId;
        } else if (type == "WITHDRAWAL") {
            cout << "  Withdrawn from account " << sourceAccountId;
        } else if (type == "OPEN") {
            cout << "  Opening balance for account " << destinationAccountId;
        }
        cout << "  (Account " << accountId << ")\n";
    }

    static string formatTimestamp(long long value) {
        if (value <= 0) return "Unknown date";
        const time_t rawTime = static_cast<time_t>(value);
        const tm* localTime = localtime(&rawTime);
        if (localTime == nullptr) return "Unknown date";

        ostringstream output;
        output << put_time(localTime, "%Y-%m-%d %H:%M:%S");
        return output.str();
    }
};

vector<Customer> customers;
vector<Account> accounts;

string trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

vector<string> split(const string& value, char delimiter) {
    vector<string> parts;
    string part;
    istringstream input(value);
    while (getline(input, part, delimiter)) parts.push_back(part);
    return parts;
}

int findCustomer(int id) {
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].id == id) return static_cast<int>(i);
    }
    return -1;
}

int findAccount(int id) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].id == id) return static_cast<int>(i);
    }
    return -1;
}

int nextCustomerId() {
    int nextId = 1001;
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].id >= nextId) nextId = customers[i].id + 1;
    }
    return nextId;
}

int nextAccountId() {
    int nextId = 1001;
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].id >= nextId) nextId = accounts[i].id + 1;
    }
    return nextId;
}

void loadCustomers() {
    ifstream file(CUSTOMERS_FILE.c_str());
    string line;
    while (getline(file, line)) {
        const vector<string> fields = split(line, '|');
        if (fields.size() < 2) continue;

        istringstream idInput(fields[0]);
        int id;
        if (!(idInput >> id)) continue;
        const string name = trim(fields[1]);
        if (name.empty()) continue;

        const int existing = findCustomer(id);
        if (existing == -1) customers.push_back(Customer(id, name));
        else customers[existing].name = name;
    }
}

void loadAccounts() {
    ifstream file(ACCOUNTS_FILE.c_str());
    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        const vector<string> fields = split(line, '|');
        int accountId;
        int customerId;
        double balance;
        string customerName;
        bool valid = false;

        if (fields.size() == 3) {
            istringstream accountInput(fields[0]);
            istringstream customerInput(fields[1]);
            istringstream balanceInput(fields[2]);
            valid = (accountInput >> accountId) &&
                    (customerInput >> customerId) &&
                    (balanceInput >> balance) &&
                    isfinite(balance) && balance >= 0.0;
        } else {
            istringstream legacyInput(line);
            if (legacyInput >> accountId) {
                string remainder;
                getline(legacyInput, remainder);
                remainder = trim(remainder);
                const size_t lastSpace = remainder.find_last_of(" \t");
                const string balanceText = lastSpace == string::npos
                    ? remainder : remainder.substr(lastSpace + 1);
                istringstream balanceInput(balanceText);
                if (balanceInput >> balance && isfinite(balance) && balance >= 0.0) {
                    customerName = lastSpace == string::npos
                        ? "" : trim(remainder.substr(0, lastSpace));
                    if (customerName.empty()) customerName = "Unknown Customer";
                    customerId = accountId;
                    valid = true;
                }
            }
        }

        if (!valid || findAccount(accountId) != -1) continue;
        accounts.push_back(Account(accountId, customerId, balance));
        if (findCustomer(customerId) == -1) {
            if (customerName.empty()) customerName = "Customer " + to_string(customerId);
            customers.push_back(Customer(customerId, customerName));
        }
    }
}

bool saveCustomers() {
    ofstream file(CUSTOMERS_FILE.c_str());
    if (!file) {
        cerr << "Error: could not save customer data to " << CUSTOMERS_FILE << ".\n";
        return false;
    }
    for (size_t i = 0; i < customers.size(); ++i) {
        file << customers[i].id << "|" << customers[i].name << "\n";
    }
    if (!file) {
        cerr << "Error: failed while writing " << CUSTOMERS_FILE << ".\n";
        return false;
    }
    return true;
}

bool saveAccounts() {
    ofstream file(ACCOUNTS_FILE.c_str());
    if (!file) {
        cerr << "Error: could not save account data to " << ACCOUNTS_FILE << ".\n";
        return false;
    }
    for (size_t i = 0; i < accounts.size(); ++i) {
        file << accounts[i].id << "|" << accounts[i].customerId << "|"
             << fixed << setprecision(2) << accounts[i].balance << "\n";
    }
    if (!file) {
        cerr << "Error: failed while writing " << ACCOUNTS_FILE << ".\n";
        return false;
    }
    return true;
}

bool saveTransaction(const Transaction& transaction) {
    ofstream file(TRANSACTIONS_FILE.c_str(), ios::app);
    if (!file) {
        cerr << "Error: could not save transaction history to "
             << TRANSACTIONS_FILE << ".\n";
        return false;
    }
    file << transaction.type << "|" << transaction.sourceAccountId << "|"
         << transaction.destinationAccountId << "|" << fixed << setprecision(2)
         << transaction.amount << "|" << transaction.timestamp << "\n";
    if (!file) {
        cerr << "Error: failed while writing " << TRANSACTIONS_FILE << ".\n";
        return false;
    }
    return true;
}

bool readInt(const string& prompt, int& value) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) return false;
    istringstream input(line);
    char trailing;
    if (!(input >> value) || (input >> trailing)) {
        cout << "Please enter a valid whole number.\n";
        return false;
    }
    return true;
}

bool readAmount(const string& prompt, double& amount) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) return false;
    istringstream input(line);
    char trailing;
    if (!(input >> amount) || (input >> trailing) ||
        !isfinite(amount) || amount <= 0.0) {
        cout << "Enter a valid amount greater than zero.\n";
        return false;
    }
    return true;
}

bool readCustomerName(string& name) {
    cout << "Customer name: ";
    if (!getline(cin, name)) return false;
    name = trim(name);
    if (name.empty() || name.find('|') != string::npos) {
        cout << "Name cannot be empty or contain the | character.\n";
        return false;
    }
    return true;
}

void createCustomer() {
    string name;
    if (!readCustomerName(name)) return;

    customers.push_back(Customer(nextCustomerId(), name));
    if (!saveCustomers()) {
        customers.pop_back();
        return;
    }
    cout << "Customer created. Customer ID: " << customers.back().id << "\n";
}

void listCustomers() {
    if (customers.empty()) {
        cout << "No customers found.\n";
        return;
    }

    cout << "\nCUSTOMERS\n";
    cout << left << setw(14) << "Customer ID" << "Name\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << left << setw(14) << customers[i].id << customers[i].name << "\n";
    }
}

void createAccount() {
    if (customers.empty()) {
        cout << "Create a customer before opening an account.\n";
        return;
    }

    int customerId;
    if (!readInt("Customer ID: ", customerId)) return;
    const int customerIndex = findCustomer(customerId);
    if (customerIndex == -1) {
        cout << "Customer not found.\n";
        return;
    }

    double openingBalance = 0.0;
    cout << "Opening balance (enter 0 for none): ";
    string line;
    if (!getline(cin, line)) return;
    istringstream input(line);
    char trailing;
    if (!(input >> openingBalance) || (input >> trailing) ||
        !isfinite(openingBalance) || openingBalance < 0.0) {
        cout << "Enter a valid balance that is zero or greater.\n";
        return;
    }

    accounts.push_back(Account(nextAccountId(), customerId, openingBalance));
    if (!saveAccounts()) {
        accounts.pop_back();
        return;
    }
    const Account& account = accounts.back();
    if (!saveTransaction(Transaction("OPEN", 0, account.id, openingBalance,
                                    static_cast<long long>(time(nullptr))))) {
        cout << "Account was created, but its opening transaction could not be recorded.\n";
    }
    cout << "Account created. Account ID: " << account.id
         << " (Customer: " << customers[customerIndex].name << ")\n";
}

void listAccounts() {
    if (accounts.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    cout << "\nACCOUNTS\n";
    cout << left << setw(14) << "Account ID" << setw(14) << "Customer ID"
         << setw(24) << "Customer" << "Balance\n";
    for (size_t i = 0; i < accounts.size(); ++i) {
        const int customerIndex = findCustomer(accounts[i].customerId);
        const string name = customerIndex == -1
            ? "Unknown Customer" : customers[customerIndex].name;
        cout << left << setw(14) << accounts[i].id
             << setw(14) << accounts[i].customerId
             << setw(24) << name << fixed << setprecision(2)
             << accounts[i].balance << "\n";
    }
}

void showRecentTransactions(int accountId) {
    ifstream file(TRANSACTIONS_FILE.c_str());
    vector<Transaction> matching;
    string line;

    while (getline(file, line)) {
        const vector<string> fields = split(line, '|');
        if (fields.size() == 5) {
            istringstream sourceInput(fields[1]);
            istringstream destinationInput(fields[2]);
            istringstream amountInput(fields[3]);
            istringstream timestampInput(fields[4]);
            int sourceId;
            int destinationId;
            double amount;
            long long timestamp;
            if ((sourceInput >> sourceId) && (destinationInput >> destinationId) &&
                (amountInput >> amount) && (timestampInput >> timestamp)) {
                Transaction transaction(fields[0], sourceId, destinationId, amount, timestamp);
                if (transaction.involvesAccount(accountId)) matching.push_back(transaction);
            }
        } else {
            const string marker = "Account: ";
            const size_t position = line.find(marker);
            if (position != string::npos) {
                istringstream idInput(line.substr(position + marker.size()));
                int legacyAccountId;
                if (idInput >> legacyAccountId && legacyAccountId == accountId) {
                    matching.push_back(Transaction("", accountId, 0, 0.0, 0, line));
                }
            }
        }
    }

    cout << "\nRECENT TRANSACTIONS (up to " << RECENT_TRANSACTION_LIMIT << ")\n";
    const size_t start = matching.size() > RECENT_TRANSACTION_LIMIT
        ? matching.size() - RECENT_TRANSACTION_LIMIT : 0;
    if (start == matching.size()) {
        cout << "No transactions found for this account.\n";
        return;
    }
    for (size_t i = start; i < matching.size(); ++i) {
        matching[i].display(accountId);
    }
}

void showAccountDetails() {
    int id;
    if (!readInt("Account ID: ", id)) return;
    const int accountIndex = findAccount(id);
    if (accountIndex == -1) {
        cout << "Account not found.\n";
        return;
    }

    const Account& account = accounts[accountIndex];
    const int customerIndex = findCustomer(account.customerId);
    cout << "\nACCOUNT DETAILS\n"
         << "Account ID: " << account.id << "\n"
         << "Customer ID: " << account.customerId << "\n"
         << "Customer name: "
         << (customerIndex == -1 ? "Unknown Customer" : customers[customerIndex].name)
         << "\nBalance: " << fixed << setprecision(2) << account.balance << "\n";
    showRecentTransactions(id);
}

void updateBalance(int accountIndex, double newBalance, const Transaction& transaction) {
    const double oldBalance = accounts[accountIndex].balance;
    accounts[accountIndex].balance = newBalance;
    if (!saveAccounts()) {
        accounts[accountIndex].balance = oldBalance;
        return;
    }
    if (saveTransaction(transaction)) {
        cout << "Transaction successful. New balance: " << fixed
             << setprecision(2) << accounts[accountIndex].balance << "\n";
    } else {
        cout << "Balance was updated, but the transaction could not be recorded.\n";
    }
}

void deposit() {
    int id;
    if (!readInt("Account ID: ", id)) return;
    const int index = findAccount(id);
    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount;
    if (!readAmount("Deposit amount: ", amount)) return;
    updateBalance(index, accounts[index].balance + amount,
                  Transaction("DEPOSIT", 0, id, amount,
                              static_cast<long long>(time(nullptr))));
}

void withdraw() {
    int id;
    if (!readInt("Account ID: ", id)) return;
    const int index = findAccount(id);
    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount;
    if (!readAmount("Withdrawal amount: ", amount)) return;
    if (amount > accounts[index].balance) {
        cout << "Insufficient funds.\n";
        return;
    }
    updateBalance(index, accounts[index].balance - amount,
                  Transaction("WITHDRAWAL", id, 0, amount,
                              static_cast<long long>(time(nullptr))));
}

void transfer() {
    int fromId;
    int toId;
    if (!readInt("From account ID: ", fromId) ||
        !readInt("To account ID: ", toId)) return;

    const int fromIndex = findAccount(fromId);
    const int toIndex = findAccount(toId);
    if (fromIndex == -1 || toIndex == -1) {
        cout << "One or both accounts were not found.\n";
        return;
    }
    if (fromId == toId) {
        cout << "Source and destination accounts must be different.\n";
        return;
    }

    double amount;
    if (!readAmount("Transfer amount: ", amount)) return;
    if (amount > accounts[fromIndex].balance) {
        cout << "Insufficient funds.\n";
        return;
    }

    const double oldSourceBalance = accounts[fromIndex].balance;
    const double oldDestinationBalance = accounts[toIndex].balance;
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    if (!saveAccounts()) {
        accounts[fromIndex].balance = oldSourceBalance;
        accounts[toIndex].balance = oldDestinationBalance;
        return;
    }
    if (!saveTransaction(Transaction("TRANSFER", fromId, toId, amount,
                                     static_cast<long long>(time(nullptr))))) {
        cout << "Transfer balances were updated, but the transaction could not be recorded.\n";
        return;
    }
    cout << "Transfer successful.\n"
         << "Account " << fromId << " balance: " << fixed << setprecision(2)
         << accounts[fromIndex].balance << "\n"
         << "Account " << toId << " balance: "
         << accounts[toIndex].balance << "\n";
}

int main() {
    loadCustomers();
    loadAccounts();

    int choice = -1;
    do {
        cout << "\n=== BANKING SYSTEM ===\n"
             << "1. Create customer\n"
             << "2. List customers\n"
             << "3. Create account\n"
             << "4. List accounts\n"
             << "5. Deposit\n"
             << "6. Withdraw\n"
             << "7. Transfer funds\n"
             << "8. Account details and recent transactions\n"
             << "0. Exit\n"
             << "Choice: ";

        string line;
        if (!getline(cin, line)) break;
        istringstream input(line);
        char trailing;
        if (!(input >> choice) || (input >> trailing)) {
            cout << "Please enter a valid menu number.\n";
            continue;
        }

        switch (choice) {
        case 1: createCustomer(); break;
        case 2: listCustomers(); break;
        case 3: createAccount(); break;
        case 4: listAccounts(); break;
        case 5: deposit(); break;
        case 6: withdraw(); break;
        case 7: transfer(); break;
        case 8: showAccountDetails(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
