
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

const filesystem::path FILE_NAME = filesystem::current_path() / "users.txt";

bool usernameExists(string username) {
    ifstream file(FILE_NAME);

    if (!file.is_open()) {
        cout << "Error: Cannot open users.txt for reading!\n";
        return false;
    }

    string line, savedUsername, savedPassword;

    while (getline(file, line)) {
        istringstream record(line);
        if (record >> quoted(savedUsername) >> quoted(savedPassword) &&
            savedUsername == username) {
            return true;
        }
    }

    return false;
}

void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";
    cout << "Enter username (spaces allowed): ";
    getline(cin, username);
    if (username.empty()) {
        cout << "Error: Username cannot be empty!\n";
        return;
    }

    if (usernameExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password (letters, numbers, and symbols allowed): ";
    getline(cin, password);
    if (password.empty()) {
        cout << "Error: Password cannot be empty!\n";
        return;
    }

    ofstream file(FILE_NAME, ios::app);

    if (!file.is_open()) {
        cout << "Error: Cannot open users.txt for writing!\n";
        return;
    }

    file << quoted(username) << " " << quoted(password) << "\n";
    file.close();

    if (file.fail()) {
        cout << "Error: Could not save user data!\n";
        return;
    }

    cout << "Registration successful!\n";
}

void loginUser() {
    string username, password;
    string savedUsername, savedPassword, line;
    bool found = false;

    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ifstream file(FILE_NAME);

    if (!file.is_open()) {
        cout << "Error: Cannot open users.txt for login!\n";
        return;
    }

    while (getline(file, line)) {
        istringstream record(line);
        if (record >> quoted(savedUsername) >> quoted(savedPassword) &&
            savedUsername == username &&
            savedPassword == password) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Login successful! Welcome, "
             << username << "!\n";
    } else {
        cout << "Invalid username or password!\n";
        cout << "Check the username and password saved in users.txt.\n";
    }
}

int main() {
    cout << "Using data file:\n" << FILE_NAME.string() << "\n";

    int choice;

    do {
        cout << "\n===== Login and Registration System =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Restart the program.\n";
            return 1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 0:
                cout << "Program closed. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
