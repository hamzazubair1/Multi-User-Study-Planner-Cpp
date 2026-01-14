#include <iostream>   // For input/output
#include <fstream>    // For file handling
#include <string>     // For string data type

using namespace std;

// Maximum number of tasks allowed
const int MAX_TASKS = 100;

// Arrays to store task information
string taskTitle[MAX_TASKS];
string subjectName[MAX_TASKS];
int dayDue[MAX_TASKS];
int monthDue[MAX_TASKS];
int priorityLevel[MAX_TASKS];
int completed[MAX_TASKS];   // 0 = Pending, 1 = Completed

int taskCount = 0;          // Total number of tasks

// Function declarations
void addTask();
void viewAllTasks();
void viewPendingTasks();
void markTaskCompleted();
void suggestTask();
void saveToFile(bool showMessage = true);
void loadFromFile(bool showMessage = false);

int main() {
    int choice;

    // Load tasks from file when program starts (without message)
    loadFromFile(false);

    do {
        // Main menu
        cout << "\n=========================\n";
        cout << "   Simple Study Planner  \n";
        cout << "=========================\n";
        cout << "1. Add new task\n";
        cout << "2. View all tasks\n";
        cout << "3. View pending tasks\n";
        cout << "4. Mark task as completed\n";
        cout << "5. Suggest next task\n";
        cout << "6. Save tasks to file\n";
        cout << "7. Load tasks from file\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        // Menu selection
        switch (choice) {
        case 1: addTask(); break;
        case 2: viewAllTasks(); break;
        case 3: viewPendingTasks(); break;
        case 4: markTaskCompleted(); break;
        case 5: suggestTask(); break;
        case 6: saveToFile(true); break;
        case 7: loadFromFile(true); break;
        case 8: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    // Save tasks automatically before exiting
    saveToFile(false);

    return 0;
}

// Function to add a new task
void addTask() {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full.\n";
        return;
    }

    cin.ignore(1000, '\n');

    cout << "Enter task title: ";
    getline(cin, taskTitle[taskCount]);

    cout << "Enter subject name: ";
    getline(cin, subjectName[taskCount]);

    cout << "Enter due day (1-31): ";
    cin >> dayDue[taskCount];

    cout << "Enter due month (1-12): ";
    cin >> monthDue[taskCount];

    cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
    cin >> priorityLevel[taskCount];

    completed[taskCount] = 0;   // Task is pending by default
    taskCount++;

    cout << "Task added successfully.\n";
}

// Function to display all tasks
void viewAllTasks() {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        cout << "\nTask No: " << i + 1 << endl;
        cout << "Title    : " << taskTitle[i] << endl;
        cout << "Subject  : " << subjectName[i] << endl;
        cout << "Due Date : " << dayDue[i] << "/" << monthDue[i] << endl;
        cout << "Priority : " << priorityLevel[i] << endl;
        cout << "Status   : "
            << (completed[i] ? "Completed" : "Pending") << endl;
    }
}

// Function to display only pending tasks
void viewPendingTasks() {
    bool found = false;

    for (int i = 0; i < taskCount; i++) {
        if (completed[i] == 0) {
            found = true;
            cout << "\nTask No: " << i + 1 << endl;
            cout << "Title   : " << taskTitle[i] << endl;
            cout << "Subject : " << subjectName[i] << endl;
            cout << "Due     : " << dayDue[i] << "/" << monthDue[i] << endl;
        }
    }

    if (!found)
        cout << "No pending tasks. Well done!\n";
}

// Function to mark a task as completed
void markTaskCompleted() {
    int num;

    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    viewAllTasks();

    cout << "\nEnter task number to mark completed: ";
    cin >> num;

    if (num < 1 || num > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    completed[num - 1] = 1;
    cout << "Task marked as completed.\n";
}

// Function to suggest the next task based on priority and due date
void suggestTask() {
    int best = -1;

    for (int i = 0; i < taskCount; i++) {
        if (completed[i] == 0) {
            if (best == -1 ||
                priorityLevel[i] < priorityLevel[best] ||
                (priorityLevel[i] == priorityLevel[best] &&
                    monthDue[i] < monthDue[best]) ||
                (priorityLevel[i] == priorityLevel[best] &&
                    monthDue[i] == monthDue[best] &&
                    dayDue[i] < dayDue[best])) {
                best = i;
            }
        }
    }

    if (best == -1) {
        cout << "No pending tasks.\n";
    }
    else {
        cout << "\nNext Suggested Task:\n";
        cout << "Title   : " << taskTitle[best] << endl;
        cout << "Subject : " << subjectName[best] << endl;
        cout << "Due     : " << dayDue[best] << "/" << monthDue[best] << endl;
        cout << "Priority: " << priorityLevel[best] << endl;
    }
}

// Function to save tasks to a file
void saveToFile(bool showMessage) {
    ofstream out("tasks.txt");

    if (!out) {
        if (showMessage) cout << "Error saving file.\n";
        return;
    }

    out << taskCount << endl;

    for (int i = 0; i < taskCount; i++) {
        out << taskTitle[i] << endl;
        out << subjectName[i] << endl;
        out << dayDue[i] << " " << monthDue[i] << " "
            << priorityLevel[i] << " " << completed[i] << endl;
    }

    out.close();
    if (showMessage) cout << "Tasks saved successfully.\n";
}

// Function to load tasks from a file
void loadFromFile(bool showMessage) {
    ifstream in("tasks.txt");

    if (!in) {
        return;
    }

    in >> taskCount;
    in.ignore(1000, '\n');

    for (int i = 0; i < taskCount; i++) {
        getline(in, taskTitle[i]);
        getline(in, subjectName[i]);
        in >> dayDue[i] >> monthDue[i]
            >> priorityLevel[i] >> completed[i];
        in.ignore(1000, '\n');
    }

    in.close();
}
