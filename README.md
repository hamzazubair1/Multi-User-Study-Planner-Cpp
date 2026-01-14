# Multi-User Study Planner (C++)

A console-based Study Planner application developed in C++ that allows multiple users to manage their study tasks securely using a login and registration system. Each user has their own task file stored separately.

## Features
- User registration and login system
- Change password functionality
- Add new study tasks
- View all tasks with full details
- View pending tasks only
- Mark tasks as completed
- Suggest next pending task
- Save and load tasks using file handling
- Separate task files for each user

## Concepts Used
- Arrays
- Functions
- Conditional statements
- Loops
- File handling (`fstream`)
- Input validation
- Basic authentication system

## How It Works
- User accounts are stored in `users.txt`
- Each user has a separate task file:  
  `tasks_username.txt`
- Tasks are automatically loaded on login and saved on exit

## How to Run
1. Open the project in any C++ compiler (Dev C++, Code::Blocks, Visual Studio, etc.)
2. Compile and run the program
3. Register a new user or log in with existing credentials
4. Use the menu to manage study tasks

## File Structure
- `users.txt` → Stores user IDs and passwords
- `tasks_<username>.txt` → Stores tasks of each user

## Limitations
- Console-based only
- Uses arrays (maximum 100 tasks per user)
- Passwords are stored in plain text (for learning purposes)

## Author
Hamza
