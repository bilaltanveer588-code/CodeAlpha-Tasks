#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void calculateGPA() {
    string studentName;
    int courseCount;
    double grade, credits;
    double totalPoints = 0;
    double totalCredits = 0;

    cout << "Student name: ";
    getline(cin, studentName);

    cout << "Number of courses (1-10): ";
    cin >> courseCount;

    if (courseCount < 1 || courseCount > 10) {
        cout << "Please enter between 1 and 10 courses.\n";
        return;
    }

    for (int i = 1; i <= courseCount; i++) {
        cout << "\nCourse " << i << " grade points (0-4): ";
        cin >> grade;
        cout << "Course " << i << " credit hours: ";
        cin >> credits;

        if (grade < 0 || grade > 4 || credits <= 0) {
            cout << "Invalid grade or credit hours. Calculation cancelled.\n";
            cin.ignore(10000, '\n');
            return;
        }

        totalPoints = totalPoints + (grade * credits);
        totalCredits = totalCredits + credits;
    }

    double gpa = totalPoints / totalCredits;
    cout << fixed << setprecision(2);
    cout << "\nStudent: " << studentName << "\nGPA: " << gpa << "\n";

    ofstream file("gpa_records.txt", ios::app);
    if (file.is_open()) {
        file << studentName << " | GPA: " << fixed << setprecision(2) << gpa << "\n";
        file.close();
        cout << "Result saved to gpa_records.txt\n";
    } else {
        cout << "Could not save the result.\n";
    }
    cin.ignore(10000, '\n');
}

void showRecords() {
    ifstream file("gpa_records.txt");
    string line;
    if (!file.is_open()) {
        cout << "No saved records yet.\n";
        return;
    }
    cout << "\n--- SAVED GPA RECORDS ---\n";
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n=== CGPA / GPA CALCULATOR ===\n";
        cout << "1. Calculate GPA and save\n";
        cout << "2. View saved records\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice == 1) {
            calculateGPA();
        } else if (choice == 2) {
            showRecords();
        } else if (choice == 0) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
