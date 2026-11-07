# CodeAlpha CGPA/GPA Calculator (C++ only)

## Compile and run (MSYS2 UCRT64 / PowerShell)
```powershell
g++ -std=c++17 -Wall -Wextra main.cpp -o app.exe
.\app.exe
```
## Menu
1 calculates a credit-weighted GPA and appends a record to `gpa_records.txt`.
2 displays saved records.
0 exits.

Formula: GPA = sum(grade points * credit hours) / sum(credit hours).
This simple version calculates GPA for the courses entered in one run; it does not combine semesters into cumulative CGPA.
