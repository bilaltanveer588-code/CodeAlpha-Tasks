# CodeAlpha Sudoku Solver (C++ only)

## Compile and run
```powershell
g++ -std=c++17 -Wall -Wextra main.cpp -o app.exe
.\app.exe
```
Enter 9 rows, each exactly 9 digits; `0` means an empty cell. A solved grid is saved to `sudoku_solution.txt`.
Uses recursion and backtracking.
