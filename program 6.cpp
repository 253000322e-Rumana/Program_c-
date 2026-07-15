#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

class Course {
private:
    int courseCode;
    string courseName;
    int creditHours;
    double grade;

public:
    Course() : courseCode(0), courseName(""), creditHours(0), grade(0.0) {}

    Course(int code, string name, int credits) {
        courseCode = code;
        courseName = name;
        creditHours = credits;
        grade = 0.0;
    }

    void setGrade(double g) {
        if (g >= 0 && g <= 4.0) {
            grade = g;
        } else {
            cout << "Invalid grade! Must be between 0 and 4.0\n";
        }
    }

    void displayCourse() {
        cout << "Course Code: " << courseCode << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credit Hours: " << creditHours << endl;
        cout << "Grade: " << fixed << setprecision(2) << grade << endl;
    }

    int getCourseCode() { return courseCode; }
    string getCourseName() { return courseName; }
    int getCreditHours() { return creditHours; }
    double getGrade() { return grade; }
};

class Student {
private:
    int studentID;
    string name;
    string department;
    vector<Course> registeredCourses;

public:
    Student() : studentID(0), name(""), department("") {}

    Student(int id, string n, string dept) {
        studentID = id;
        name = n;
        department = dept;
    }

    void displayStudent() {
        cout << "\n============================\n";
        cout << "Student ID: " << studentID << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Registered Courses: " << registeredCourses.size() << endl;
        cout << "Total Credit Hours: " << calculateTotalCreditHours() << endl;
        cout << "Semester GPA: " << fixed << setprecision(2) << calculateGPA() << endl;
        cout << "============================\n";
    }

    void displayCourses() {
        if (registeredCourses.empty()) {
            cout << "No courses registered!\n";
            return;
        }

        cout << "\n===== REGISTERED COURSES =====\n";
        for (size_t i = 0; i < registeredCourses.size(); i++) {
            cout << "\nCourse " << i + 1 << ":\n";
            registeredCourses[i].displayCourse();
        }
    }

    bool registerCourse(Course course) {
        if (registeredCourses.size() >= 6) {
            cout << "Cannot register more than 6 courses!\n";
            return false;
        }

        for (size_t i = 0; i < registeredCourses.size(); i++) {
            if (registeredCourses[i].getCourseCode() == course.getCourseCode()) {
                cout << "Course already registered!\n";
                return false;
            }
        }

        registeredCourses.push_back(course);
        cout << "Course registered successfully!\n";
        return true;
    }

    bool dropCourse(int courseCode) {
        for (size_t i = 0; i < registeredCourses.size(); i++) {
            if (registeredCourses[i].getCourseCode() == courseCode) {
                registeredCourses.erase(registeredCourses.begin() + i);
                cout << "Course dropped successfully!\n";
                return true;
            }
        }
        cout << "Course not found!\n";
        return false;
    }

    int calculateTotalCreditHours() {
        int total = 0;
        for (size_t i = 0; i < registeredCourses.size(); i++) {
            total += registeredCourses[i].getCreditHours();
        }
        return total;
    }

    double calculateGPA() {
        if (registeredCourses.empty()) {
            return 0.0;
        }

        double totalPoints = 0;
        int totalCredits = 0;

        for (size_t i = 0; i < registeredCourses.size(); i++) {
            totalPoints += registeredCourses[i].getGrade() * registeredCourses[i].getCreditHours();
            totalCredits += registeredCourses[i].getCreditHours();
        }

        if (totalCredits == 0) return 0.0;
        return totalPoints / totalCredits;
    }

    int getStudentID() { return studentID; }
    string getName() { return name; }
};

class University {
private:
    vector<Student> students;
    vector<Course> availableCourses;

public:
    void addStudent() {
        int id;
        string name, department;

        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getStudentID() == id) {
                cout << "Student ID already exists!\n";
                return;
            }
        }

        Student newStudent(id, name, department);
        students.push_back(newStudent);
        cout << "Student added successfully!\n";
    }

    void addCourse() {
        int code, credits;
        string name;

        cout << "Enter Course Code: ";
        cin >> code;
        cin.ignore();
        cout << "Enter Course Name: ";
        getline(cin, name);
        cout << "Enter Credit Hours: ";
        cin >> credits;

        for (size_t i = 0; i < availableCourses.size(); i++) {
            if (availableCourses[i].getCourseCode() == code) {
                cout << "Course Code already exists!\n";
                return;
            }
        }

        Course newCourse(code, name, credits);
        availableCourses.push_back(newCourse);
        cout << "Course added successfully!\n";
    }

    Student* findStudent(int id) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getStudentID() == id) {
                return &students[i];
            }
        }
        return NULL;
    }

    Course* findCourse(int code) {
        for (size_t i = 0; i < availableCourses.size(); i++) {
            if (availableCourses[i].getCourseCode() == code) {
                return &availableCourses[i];
            }
        }
        return NULL;
    }

    void registerCourseForStudent() {
        int studentID, courseCode;
        double grade;

        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Course Code: ";
        cin >> courseCode;

        Student* student = findStudent(studentID);
        Course* course = findCourse(courseCode);

        if (!student) {
            cout << "Student not found!\n";
            return;
        }
        if (!course) {
            cout << "Course not found!\n";
            return;
        }

        cout << "Enter Grade (0-4.0): ";
        cin >> grade;

        Course courseCopy = *course;
        courseCopy.setGrade(grade);

        if (student->registerCourse(courseCopy)) {
            cout << "Course registered with grade " << grade << endl;
        }
    }

    void dropCourseForStudent() {
        int studentID, courseCode;

        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Course Code to drop: ";
        cin >> courseCode;

        Student* student = findStudent(studentID);
        if (!student) {
            cout << "Student not found!\n";
            return;
        }

        student->dropCourse(courseCode);
    }

    void displayStudentInfo() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        Student* student = findStudent(id);
        if (student) {
            student->displayStudent();
            student->displayCourses();
        } else {
            cout << "Student not found!\n";
        }
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students in the system!\n";
            return;
        }

        cout << "\n========= ALL STUDENTS =========\n";
        for (size_t i = 0; i < students.size(); i++) {
            students[i].displayStudent();
        }
    }

    void displayAllCourses() {
        if (availableCourses.empty()) {
            cout << "No courses available!\n";
            return;
        }

        cout << "\n========= AVAILABLE COURSES =========\n";
        for (size_t i = 0; i < availableCourses.size(); i++) {
            cout << "\nCourse " << i + 1 << ":\n";
            availableCourses[i].displayCourse();
        }
    }
};

int main() {
    University uni;
    int choice;

    do {
        cout << "\n===== UNIVERSITY COURSE REGISTRATION =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Course\n";
        cout << "3. Register Course for Student\n";
        cout << "4. Drop Course for Student\n";
        cout << "5. Display Student Info\n";
        cout << "6. Display All Students\n";
        cout << "7. Display All Courses\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                uni.addStudent();
                break;
            case 2:
                uni.addCourse();
                break;
            case 3:
                uni.registerCourseForStudent();
                break;
            case 4:
                uni.dropCourseForStudent();
                break;
            case 5:
                uni.displayStudentInfo();
                break;
            case 6:
                uni.displayAllStudents();
                break;
            case 7:
                uni.displayAllCourses();
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
