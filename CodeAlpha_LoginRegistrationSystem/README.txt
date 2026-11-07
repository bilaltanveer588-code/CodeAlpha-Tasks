# C++ Login and Registration System

## Compile and run
Run these commands from this project folder:
```powershell
g++ -std=c++17 -Wall -Wextra main.cpp -o main
.\main
```

The program reads and writes `users.txt` in the current working directory.
Usernames may contain spaces. Passwords may contain letters, numbers, symbols,
and spaces. New records are quoted so spaces and special characters are saved
correctly; existing unquoted `username password` records remain readable.
Passwords are stored in plain text for this beginner project; do not use real
passwords.
