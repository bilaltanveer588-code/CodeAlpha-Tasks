
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int SIZE = 9;

int grid[SIZE][SIZE];

// Display Sudoku grid
void printGrid() {

    for (int row = 0; row < SIZE; row++) {

        if (row % 3 == 0) {
            cout << "+-------+-------+-------+\n";
        }

        for (int col = 0; col < SIZE; col++) {

            if (col % 3 == 0) {
                cout << "| ";
            }

            if (grid[row][col] == 0) {
                cout << ". ";
            }
            else {
                cout << grid[row][col] << " ";
            }
        }

        cout << "|\n";
    }

    cout << "+-------+-------+-------+\n";
}

// Check row, column and 3x3 box
bool isSafe(int row, int col, int number) {

    // Check row and column
    for (int i = 0; i < SIZE; i++) {

        if (grid[row][i] == number) {
            return false;
        }

        if (grid[i][col] == number) {
            return false;
        }
    }

    // Find starting position of 3x3 box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;

    // Check 3x3 subgrid
    for (int r = boxRow; r < boxRow + 3; r++) {

        for (int c = boxCol; c < boxCol + 3; c++) {

            if (grid[r][c] == number) {
                return false;
            }
        }
    }

    return true;
}

// Validate the original Sudoku puzzle
bool isValidPuzzle() {

    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            int number = grid[row][col];

            if (number != 0) {

                // Temporarily remove current number
                grid[row][col] = 0;

                // Check whether number is valid
                if (!isSafe(row, col, number)) {

                    grid[row][col] = number;

                    return false;
                }

                // Restore original number
                grid[row][col] = number;
            }
        }
    }

    return true;
}

// Check whether Sudoku is completely filled
bool isComplete() {

    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            if (grid[row][col] == 0) {
                return false;
            }
        }
    }

    return true;
}

// Solve Sudoku using Backtracking
bool solveSudoku() {

    // Find an empty cell
    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            if (grid[row][col] == 0) {

                // Try numbers from 1 to 9
                for (int number = 1; number <= 9; number++) {

                    if (isSafe(row, col, number)) {

                        // Place number
                        grid[row][col] = number;

                        // Recursive call
                        if (solveSudoku()) {
                            return true;
                        }

                        // Backtracking
                        grid[row][col] = 0;
                    }
                }

                // No valid number found
                return false;
            }
        }
    }

    // All cells are filled
    return true;
}

// Save solution in text file
void saveSolution() {

    ofstream file("sudoku_solution.txt");

    if (!file.is_open()) {

        cout << "\nError: Could not save solution.\n";

        return;
    }

    for (int row = 0; row < SIZE; row++) {

        for (int col = 0; col < SIZE; col++) {

            file << grid[row][col] << " ";
        }

        file << "\n";
    }

    file.close();

    if (file.fail()) {
        cout << "\nError: Could not finish saving solution.\n";
    }
    else {
        cout << "\nSolution saved to sudoku_solution.txt\n";
    }
}

// Main function
int main() {

    cout << "====================================\n";
    cout << "          SUDOKU SOLVER\n";
    cout << "====================================\n";

    cout << "\nINSTRUCTIONS:\n";
    cout << "1. Enter exactly 9 rows.\n";
    cout << "2. Each row must contain 9 digits.\n";
    cout << "3. Use digits 1-9 for filled cells.\n";
    cout << "4. Use 0 for empty cells.\n";
    cout << "5. Duplicate numbers are not allowed\n";
    cout << "   in any row, column or 3x3 box.\n";

    cout << "\nExample Sudoku puzzle:\n";

    cout << "530070000\n";
    cout << "600195000\n";
    cout << "098000060\n";
    cout << "800060003\n";
    cout << "400803001\n";
    cout << "700020006\n";
    cout << "060000280\n";
    cout << "000419005\n";
    cout << "000080079\n";

    cout << "\nEnter your Sudoku puzzle row by row.\n\n";

    // Take input from user
    for (int row = 0; row < SIZE; row++) {

        string line;

        cout << "Row " << row + 1 << ": ";
        cin >> line;

        // Check row length
        if (line.length() != 9) {

            cout << "\nError: Each row must contain exactly 9 digits.\n";

            return 1;
        }

        // Check input characters
        for (int col = 0; col < SIZE; col++) {

            if (line[col] < '0' || line[col] > '9') {

                cout << "\nError: Only digits 0-9 are allowed.\n";

                return 1;
            }

            grid[row][col] = line[col] - '0';
        }
    }

    // Display original puzzle
    cout << "\n--- INPUT PUZZLE ---\n";

    printGrid();

    // Validate Sudoku
    if (!isValidPuzzle()) {

        cout << "\nError: Invalid Sudoku puzzle!\n";

        cout << "Duplicate numbers found in a row, column or 3x3 box.\n";

        return 1;
    }

    // Check already solved Sudoku
    if (isComplete()) {

        cout << "\nSudoku is already completely solved!\n";

        cout << "All Sudoku rules are satisfied.\n";

        cout << "\n--- SOLVED PUZZLE ---\n";

        printGrid();

        saveSolution();

        return 0;
    }

    // Solve incomplete Sudoku
    cout << "\nSolving Sudoku using Backtracking...\n";

    if (solveSudoku()) {

        cout << "\n--- SOLVED PUZZLE ---\n";

        printGrid();

        cout << "\nSudoku solved successfully!\n";

        saveSolution();
    }

    else {

        cout << "\nNo solution exists for this puzzle.\n";
    }

    return 0;
}
