# CodeAlpha C++ Internship Projects

A collection of four C++ console-based projects developed as part of the **CodeAlpha C++ Programming Internship**. These projects demonstrate fundamental programming concepts, problem-solving techniques, file handling, data validation, and algorithm implementation using standard C++.

## 📌 Projects Overview

| Task | Project | Key Concepts |
|---|---|---|
| Task 1 | CGPA Calculator | GPA calculation, weighted averages, file handling |
| Task 2 | Login and Registration System | Authentication, file handling, input validation |
| Task 3 | Sudoku Solver | 2D arrays, recursion, backtracking |
| Task 4 | Banking System | Structures, functions, transactions, file handling |

---

## 📂 Repository Structure

```text
CodeAlpha_CPP_Projects/
│
├── CodeAlpha_CGPA_Calculator/
│   ├── main.cpp
│   └── ...
│
├── CodeAlpha_LoginRegistrationSystem/
│   ├── main.cpp
│   ├── users.txt
│   └── ...
│
├── CodeAlpha_SudokuSolver/
│   ├── main.cpp
│   ├── sudoku_solution.txt
│   └── ...
│
├── CodeAlpha_BankingSystem/
│   ├── main.cpp
│   └── ...
│
└── README.md
```

*Note: The actual folder and file names may vary according to your project structure.*

---

# 🧮 Task 1: CGPA Calculator

## Overview

The CGPA Calculator is a console-based C++ application designed to calculate a student's Grade Point Average (GPA) and Cumulative Grade Point Average (CGPA).

It helps students calculate academic performance using course grades and credit hours.

## Features

- Enter course information and academic grades.
- Calculate GPA using credit hours.
- Calculate CGPA across multiple semesters.
- Display calculated academic results.
- Store academic records using file handling.

## Calculation

The GPA is calculated using the weighted average of grade points and credit hours.

\[
GPA = \frac{\sum(\text{Grade Points} \times \text{Credit Hours})}{\sum \text{Credit Hours}}
\]

For multiple semesters, CGPA is calculated using the total grade points and total credit hours across all included courses.

## CodeAlpha Task Requirements

- Develop a CGPA calculator using C++.
- Accept academic information from the user.
- Calculate GPA/CGPA accurately.
- Display the calculated results.
- Use appropriate programming logic and data handling.

## Concepts Used

- Variables and data types
- Conditional statements
- Loops
- Functions
- Arithmetic operations
- File handling

---

# 🔐 Task 2: Login and Registration System

## Overview

The Login and Registration System is a console-based application that allows users to register an account and log in using their username and password.

The system stores user credentials in a text file and checks the entered information during login.

## Features

- User registration.
- Username availability checking.
- Duplicate username prevention.
- Password input.
- Login authentication.
- Validation of username and password.
- Persistent user records using file handling.
- Menu-driven interface.

## How It Works

1. The user selects the registration option.
2. The system checks whether the username already exists.
3. If the username is available, the user enters a password.
4. The credentials are stored in `users.txt`.
5. During login, the system compares the entered credentials with the stored records.
6. The application displays a success or error message.

## CodeAlpha Task Requirements

- Create a registration system.
- Create a login system.
- Store user information.
- Verify login credentials.
- Handle invalid login attempts.

## Concepts Used

- Functions
- Strings
- Conditional statements
- Loops
- File handling
- Input validation

> **Security Note:** This project is intended for educational purposes. The current implementation stores passwords as plain text. Real-world authentication systems should use secure password hashing and appropriate security controls.

---

# 🧩 Task 3: Sudoku Solver

## Overview

The Sudoku Solver is a C++ application that solves a standard 9×9 Sudoku puzzle using a recursive backtracking algorithm.

The Sudoku grid is represented using a two-dimensional array. The program checks Sudoku constraints before placing a number in an empty cell.

## Features

- Represent the Sudoku grid using a 9×9 two-dimensional array.
- Accept Sudoku puzzle input row by row.
- Use `0` to represent empty cells.
- Validate rows, columns, and 3×3 subgrids.
- Detect invalid Sudoku puzzles.
- Solve incomplete puzzles using backtracking.
- Detect puzzles with no solution.
- Recognize already completed valid Sudoku puzzles.
- Display the solved Sudoku grid.
- Save the solution to `sudoku_solution.txt`.

## Sudoku Rules

A valid Sudoku solution must satisfy the following conditions:

1. Each row contains digits 1–9 without repetition.
2. Each column contains digits 1–9 without repetition.
3. Each 3×3 subgrid contains digits 1–9 without repetition.

## Backtracking Algorithm

The solver follows these steps:

1. Find an empty cell.
2. Try numbers from 1 to 9.
3. Check whether the selected number is valid.
4. If valid, place the number in the cell.
5. Recursively attempt to solve the remaining puzzle.
6. If the selected number leads to a dead end, reset the cell to `0`.
7. Try another number.
8. Continue until the puzzle is solved or no valid solution exists.

## CodeAlpha Task Requirements

- Represent Sudoku using a 2D array.
- Implement a backtracking algorithm.
- Check row, column, and 3×3 subgrid constraints.
- Recursively try possible numbers.
- Solve the puzzle and display the result.

## Concepts Used

- Two-dimensional arrays
- Functions
- Recursion
- Backtracking
- Conditional statements
- Loops
- File handling

---

# 🏦 Task 4: Banking System

## Overview

The Banking System is a menu-driven C++ console application that simulates basic banking operations.

It allows users to create and manage bank accounts, perform transactions, and maintain account information.

## Features

- Create a new bank account.
- Store account information.
- Display account details.
- List available accounts.
- Deposit money.
- Withdraw money.
- Transfer funds between accounts.
- Maintain transaction history.
- Store account and transaction records using file handling.
- Validate account information and transaction amounts.

## Banking Operations

### Account Creation

The user enters account information to create a new bank account.

### Deposit

The system adds the entered amount to the selected account balance.

### Withdrawal

The system checks the account balance before processing a withdrawal.

### Fund Transfer

The system transfers money from one account to another, subject to account and balance validation.

### Transaction History

The system maintains records of financial transactions for review.

## CodeAlpha Task Requirements

- Create a banking application using C++.
- Implement basic banking operations.
- Manage account information.
- Support deposits and withdrawals.
- Use appropriate data structures and programming logic.

## Concepts Used

- Structures (`struct`)
- Arrays
- Functions
- Conditional statements
- Loops
- File handling
- Input validation

---

# 🛠️ Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC / G++
- **IDE:** Visual Studio Code
- **Libraries:** Standard C++ libraries
- **Data Storage:** Text files

## Requirements

To compile and run these projects, you need:

- A C++ compiler such as GCC/G++.
- Visual Studio Code or another C++ editor.
- A terminal or command prompt.

## How to Compile and Run

### Using GCC / G++

Open the project folder in your terminal and compile the source file:

```bash
g++ main.cpp -o main
```

Run the compiled program:

**Windows PowerShell:**

```powershell
.\main
```

**Linux / macOS:**

```bash
./main
```

For projects stored in separate folders, navigate to the relevant project directory before compiling.

---

# 🎯 Learning Outcomes

Through these projects, I practiced and improved my understanding of:

- C++ programming fundamentals.
- Functions and modular programming.
- Arrays and two-dimensional arrays.
- Structures and data organization.
- File handling and persistent data storage.
- Input validation and error handling.
- Recursive problem-solving.
- Backtracking algorithms.
- Basic authentication and transaction logic.
- Writing organized and maintainable code.

---

# 🚀 Future Improvements

Potential improvements for these projects include:

- Improved user interfaces.
- Stronger input validation.
- More robust file handling.
- Secure password hashing for authentication.
- Database integration.
- Additional test cases.
- GUI-based interfaces.

---

# 👨‍💻 Author

**Muhammad Bilal Tanveer**

C++ Programming | Software Engineering Student

## Acknowledgment

These projects were developed as part of the **CodeAlpha C++ Programming Internship** to practice programming fundamentals and implement practical C++ applications.

---

⭐ If you find this repository useful, feel free to explore the projects and provide feedback.

