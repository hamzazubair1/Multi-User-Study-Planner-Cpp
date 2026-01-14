#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ================= GLOBAL =================
string currentUser;
string taskFileName;

const int MAX_TASKS = 100;
string taskTitle[MAX_TASKS];
string subjectName[MAX_TASKS];
int dayDue[MAX_TASKS];
int monthDue[MAX_TASKS];
int priorityLevel[MAX_TASKS];
int completed[MAX_TASKS];
int taskCount = 0;

// ================= FUNCTION DECLARATIONS =================
bool loginOrRegister();
bool login();
void registerUser();
bool userExists(string id);
void changePassword();

void addTask();
void viewAllTasks();
void viewPendingTasks();
void markTaskCompleted();
void suggestTask();
void saveToFile(bool msg = true);
void loadFromFile(bool msg = false);

// ================= MAIN =================
int main() {

    if (!loginOrRegister()) {
        cout << "Exiting program...\n";
        return 0;
    }

    taskFileName = "tasks_" + currentUser + ".txt";
    loadFromFile(false);

    int choice;
    do {
        cout << "\n===== STUDY PLANNER (" << currentUser << ") =====\n";
        cout << "1. Add Task\n";
        cout << "2. View All Tasks (Full Details)\n";
        cout << "3. View Pending Tasks (Full Details)\n";
        cout << "4. Mark Task Completed\n";
        cout << "5. Suggest Next Task\n";
        cout << "6. Change Password\n";
        cout << "7. Save Tasks\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice) {
        case 1: addTask(); break;
        case 2: viewAllTasks(); break;
        case 3: viewPendingTasks(); break;
        case 4: markTaskCompleted(); break;
        case 5: suggestTask(); break;
        case 6: changePassword(); break;
        case 7: saveToFile(true); break;
        case 8: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    saveToFile(false);
    return 0;
}

// ================= LOGIN / REGISTER =================
bool loginOrRegister() {
    int choice;
    cout << "1. Login\n2. Register\nChoose: ";
    cin >> choice;

    if (choice == 1)
        return login();
    else if (choice == 2) {
        registerUser();
        return true;
    }
    return false;
}

bool login() {
    ifstream in("users.txt");
    if (!in) {
        cout << "No users found. Please register first.\n";
        registerUser();
        return true;
    }

    string id, pass, fileID, filePass;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    while (in >> fileID >> filePass) {
        if (id == fileID) {
            if (pass == filePass) {
                currentUser = id;
                cout << "Login successful!\n";
                return true;
            }
            else {
                cout << "Wrong password!\n";
                return false;
            }
        }
    }

    cout << "ID not found. Please register first.\n";
    registerUser();
    return true;
}

bool userExists(string id) {
    ifstream in("users.txt");
    string fileID, filePass;
    while (in >> fileID >> filePass) {
        if (fileID == id) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

void registerUser() {
    string id, pass;
    cout << "Create ID: ";
    cin >> id;

    if (userExists(id)) {
        cout << "Account already exists! Redirecting to login...\n";
        login();
        return;
    }

    cout << "Create Password: ";
    cin >> pass;

    ofstream out("users.txt", ios::app);
    out << id << " " << pass << endl;
    out.close();

    currentUser = id;
    cout << "Registration successful!\n";
}

void changePassword() {
    ifstream in("users.txt");
    ofstream out("temp.txt");

    string id, pass, newPass;
    cout << "Enter new password: ";
    cin >> newPass;

    while (in >> id >> pass) {
        if (id == currentUser)
            out << id << " " << newPass << endl;
        else
            out << id << " " << pass << endl;
    }

    in.close();
    out.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");

    cout << "Password changed successfully!\n";
}

// ================= TASK FUNCTIONS =================
void addTask() {
    if (taskCount >= MAX_TASKS) {
        cout << "Task limit reached!\n";
        return;
    }

    cin.ignore();
    cout << "Task Title: ";
    getline(cin, taskTitle[taskCount]);
    cout << "Subject: ";
    getline(cin, subjectName[taskCount]);
    cout << "Due Day: ";
    cin >> dayDue[taskCount];
    cout << "Due Month: ";
    cin >> monthDue[taskCount];
    cout << "Priority (1=High, 2=Medium, 3=Low): ";
    cin >> priorityLevel[taskCount];

    completed[taskCount++] = 0;
}

// FULL DETAILS – ALL TASKS
void viewAllTasks() {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        cout << "\nTask No: " << i + 1 << endl;
        cout << "Title   : " << taskTitle[i] << endl;
        cout << "Subject : " << subjectName[i] << endl;
        cout << "Due Date: " << dayDue[i] << "/" << monthDue[i] << endl;

        cout << "Priority: ";
        if (priorityLevel[i] == 1) cout << "High\n";
        else if (priorityLevel[i] == 2) cout << "Medium\n";
        else cout << "Low\n";

        cout << "Status  : "
            << (completed[i] ? "Completed" : "Pending") << endl;
    }
}

// FULL DETAILS – PENDING TASKS ONLY
void viewPendingTasks() {
    bool found = false;

    for (int i = 0; i < taskCount; i++) {
        if (!completed[i]) {
            found = true;
            cout << "\nTask No: " << i + 1 << endl;
            cout << "Title   : " << taskTitle[i] << endl;
            cout << "Subject : " << subjectName[i] << endl;
            cout << "Due Date: " << dayDue[i] << "/" << monthDue[i] << endl;

            cout << "Priority: ";
            if (priorityLevel[i] == 1) cout << "High\n";
            else if (priorityLevel[i] == 2) cout << "Medium\n";
            else cout << "Low\n";
        }
    }

    if (!found)
        cout << "No pending tasks. Well done!\n";
}

// OPTION 4 – SHOW ALL TASKS FIRST, THEN MARK
void markTaskCompleted() {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    // Show all tasks with full details
    viewAllTasks();

    int n;
    cout << "\nEnter task number to mark completed: ";
    cin >> n;

    if (n < 1 || n > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    completed[n - 1] = 1;
    cout << "Task marked as completed.\n";
}

void suggestTask() {
    for (int i = 0; i < taskCount; i++) {
        if (!completed[i]) {
            cout << "Next Task: " << taskTitle[i] << endl;
            return;
        }
    }
    cout << "No pending tasks!\n";
}

// ================= FILE HANDLING =================
void saveToFile(bool msg) {
    ofstream out(taskFileName);
    out << taskCount << endl;

    for (int i = 0; i < taskCount; i++) {
        out << taskTitle[i] << endl;
        out << subjectName[i] << endl;
        out << dayDue[i] << " "
            << monthDue[i] << " "
            << priorityLevel[i] << " "
            << completed[i] << endl;
    }

    out.close();
    if (msg) cout << "Tasks saved successfully.\n";
}

void loadFromFile(bool msg) {
    ifstream in(taskFileName);
    if (!in) return;

    in >> taskCount;
    in.ignore();

    for (int i = 0; i < taskCount; i++) {
        getline(in, taskTitle[i]);
        getline(in, subjectName[i]);
        in >> dayDue[i]
            >> monthDue[i]
            >> priorityLevel[i]
            >> completed[i];
        in.ignore();
    }

    in.close();
    if (msg) cout << "Tasks loaded successfully.\n";
}

