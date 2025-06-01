#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Student {
private:
    string name;
    string rollNumber;
    double cgpa;
    vector<string> enrolledCourses;

public:
    // Constructors
    Student() : name(""), rollNumber(""), cgpa(0.0) {}
    Student(string n, string r, double c) : name(n), rollNumber(r), cgpa(c) {}
    Student(const Student &other) : name(other.name), rollNumber(other.rollNumber), cgpa(other.cgpa), enrolledCourses(other.enrolledCourses) {}

    // Destructor
    ~Student() {
        enrolledCourses.clear();
    }

    void addCourse(const string &course) {
        if (find(enrolledCourses.begin(), enrolledCourses.end(), course) == enrolledCourses.end()) {
            enrolledCourses.push_back(course);
            cout << "Course added successfully!\n";
        } else {
            cout << "Error: Course already exists for this student!\n";
        }
    }

    // Update student CGPA with validation
    void updateCGPA(double newCGPA) {
        if (newCGPA >= 0.0 && newCGPA <= 4.0) {
            cgpa = newCGPA;
            cout << "CGPA updated successfully!\n";
        } else {
            cout << "Error: Invalid CGPA! Must be between 0.0 and 4.0.\n";
        }
    }

    // Display complete student information
    void display() const {
        cout << "\nStudent Details:\n";
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "CGPA: " << cgpa << endl;
        cout << "Enrolled Courses:\n";
        for (const string &course : enrolledCourses) {
            cout << "  - " << course << endl;
        }
        cout << endl;
    }

    // Getters
    string getRollNumber() const { return rollNumber; }
};

class StudentManagementSystem {
private:
    vector<Student> students;

    
    int findStudentIndex(const string &roll) {
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].getRollNumber() == roll) {
                return i;
            }
        }
        return -1;
    }

public:
    // Add new student to the system 
    void addStudent() {
        string name, roll;
        double cgpa;
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter roll number: ";
        getline(cin, roll);

       
        if (findStudentIndex(roll) != -1) {
            cout << "Error: Student with this roll number already exists!\n";
            return;
        }

        cout << "Enter CGPA: ";
        while (!(cin >> cgpa) || cgpa < 0.0 || cgpa > 4.0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter CGPA (0.0-4.0): ";
        }
        cin.ignore(); 
        students.emplace_back(name, roll, cgpa);
        cout << "Student added successfully!\n";
    }

    // Add course to a student with validation
    void addCourseToStudent() {
        string roll, course;
        cout << "Enter roll number: ";
        getline(cin, roll);
        int idx = findStudentIndex(roll);
        if (idx != -1) {
            cout << "Enter course name: ";
            getline(cin, course);
            students[idx].addCourse(course);
        } else {
            cout << "Error: Student not found!\n";
        }
    }

    // Update student CGPA with validation
    void updateStudentCGPA() {
        string roll;
        double newCGPA;
        cout << "Enter roll number: ";
        getline(cin, roll);
        int idx = findStudentIndex(roll);
        if (idx != -1) {
            cout << "Enter new CGPA: ";
            while (!(cin >> newCGPA) || newCGPA < 0.0 || newCGPA > 4.0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter CGPA (0.0-4.0): ";
            }
            cin.ignore(); // Clear the input buffer
            students[idx].updateCGPA(newCGPA);
        } else {
            cout << "Error: Student not found!\n";
        }
    }

    // Display all student records
    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students in the system!\n";
            return;
        }
        cout << "\n=== All Students ===\n";
        for (const Student &s : students) {
            s.display();
        }
    }

    // Search student 
    void searchStudent() {
        string roll;
        cout << "Enter roll number: ";
        getline(cin, roll);
        int idx = findStudentIndex(roll);
        if (idx != -1) {
            students[idx].display();
        } else {
            cout << "Error: Student not found!\n";
        }
    }
};

void showMenu() {
    cout << "\n===== Student Management System =====\n";
    cout << "1. Add New Student\n";
    cout << "2. Add Course to Student\n";
    cout << "3. Update Student CGPA\n";
    cout << "4. Display All Students\n";
    cout << "5. Search Student\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManagementSystem sms;
    int choice;
    do {
        showMenu();
        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Enter a number between 1 and 6: ";
        }
        cin.ignore(); 

        switch (choice) {
            case 1: sms.addStudent(); break;
            case 2: sms.addCourseToStudent(); break;
            case 3: sms.updateStudentCGPA(); break;
            case 4: sms.displayAllStudents(); break;
            case 5: sms.searchStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
