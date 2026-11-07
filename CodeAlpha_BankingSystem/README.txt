# C++ Banking System

## Compile and run
```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app.exe
.\app.exe
```

Create a customer before opening an account. Customers may own multiple accounts.
Account details show the current balance and up to 10 recent transactions for that
account. Deposits, withdrawals, opening balances, and transfers are recorded; a
transfer appears in the history of both accounts.

Data is stored in `customers.txt`, `accounts.txt`, and `transactions.txt` in the
current working directory. Existing account files in the original
`accountId name balance` format are loaded and migrated to the current format
when account data is next saved. Existing transaction text entries remain
readable in account history when they identify an account.

**Educational demo only:** this is not secure or suitable for real financial
transactions.
