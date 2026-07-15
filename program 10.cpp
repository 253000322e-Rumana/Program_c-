#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
private:
    int id;
    string name;
    string department;
    double cgpa;
    vector<int> courseIDs;

public:
    Student() : id(0), name(""), department(""), cgpa(0.0) {}

    Student(int i, string n, string d, double c) {
        id = i;
        name = n;
        department = d;
        cgpa = c;
    }

    void displayStudent() {
        cout << "\n============================\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
        cout << "Courses: ";
        for (size_t i = 0; i < courseIDs.size(); i++) {
            cout << courseIDs[i] << " ";
        }
        cout << endl;
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    string getDepartment() { return department; }
    double getCGPA() { return cgpa; }
    vector<int> getCourseIDs() { return courseIDs; }

    void setName(string n) { name = n; }
    void setDepartment(string d) { department = d; }
    void setCGPA(double c) { cgpa = c; }

    void addCourse(int courseID) {
        courseIDs.push_back(courseID);
    }

    void saveToFile(ofstream& file) {
        file << id << endl;
        file << name << endl;
        file << department << endl;
        file << cgpa << endl;
        file << courseIDs.size() << endl;
        for (size_t i = 0; i < courseIDs.size(); i++) {
            file << courseIDs[i] << endl;
        }
    }

    void loadFromFile(ifstream& file) {
        int size;
        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, department);
        file >> cgpa;
        file >> size;
        for (int i = 0; i < size; i++) {
            int cid;
            file >> cid;
            courseIDs.push_back(cid);
        }
    }
};

class Teacher {
private:
    int id;
    string name;
    string department;
    string designation;

public:
    Teacher() : id(0), name(""), department(""), designation("") {}

    Teacher(int i, string n, string d, string des) {
        id = i;
        name = n;
        department = d;
        designation = des;
    }

    void displayTeacher() {
        cout << "\n============================\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Designation: " << designation << endl;
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    string getDepartment() { return department; }

    void setName(string n) { name = n; }
    void setDepartment(string d) { department = d; }
    void setDesignation(string d) { designation = d; }

    void saveToFile(ofstream& file) {
        file << id << endl;
        file << name << endl;
        file << department << endl;
        file << designation << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, department);
        getline(file, designation);
    }
};

class Course {
private:
    int id;
    string name;
    int credits;
    int teacherID;

public:
    Course() : id(0), name(""), credits(0), teacherID(0) {}

    Course(int i, string n, int c, int t) {
        id = i;
        name = n;
        credits = c;
        teacherID = t;
    }

    void displayCourse() {
        cout << "\n============================\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Credits: " << credits << endl;
        cout << "Teacher ID: " << teacherID << endl;
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    int getCredits() { return credits; }
    int getTeacherID() { return teacherID; }

    void setName(string n) { name = n; }
    void setCredits(int c) { credits = c; }
    void setTeacherID(int t) { teacherID = t; }

    void saveToFile(ofstream& file) {
        file << id << endl;
        file << name << endl;
        file << credits << endl;
        file << teacherID << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> id;
        file.ignore();
        getline(file, name);
        file >> credits;
        file >> teacherID;
    }
};

class Department {
private:
    int id;
    string name;
    string head;

public:
    Department() : id(0), name(""), head("") {}

    Department(int i, string n, string h) {
        id = i;
        name = n;
        head = h;
    }

    void displayDepartment() {
        cout << "\n============================\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Head: " << head << endl;
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    string getHead() { return head; }

    void setName(string n) { name = n; }
    void setHead(string h) { head = h; }

    void saveToFile(ofstream& file) {
        file << id << endl;
        file << name << endl;
        file << head << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, head);
    }
};

class University {
private:
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;
    vector<Department> departments;
    string filename;

public:
    University(string fname) {
        filename = fname;
        loadFromFile();
    }

    void loadFromFile() {
        students.clear();
        teachers.clear();
        courses.clear();
        departments.clear();

        ifstream file(filename);
        if (!file) {
            cout << "No existing data found. New database created.\n";
            return;
        }

        int studentCount, teacherCount, courseCount, deptCount;

        file >> studentCount;
        for (int i = 0; i < studentCount; i++) {
            Student s;
            s.loadFromFile(file);
            students.push_back(s);
        }

        file >> teacherCount;
        for (int i = 0; i < teacherCount; i++) {
            Teacher t;
            t.loadFromFile(file);
            teachers.push_back(t);
        }

        file >> courseCount;
        for (int i = 0; i < courseCount; i++) {
            Course c;
            c.loadFromFile(file);
            courses.push_back(c);
        }

        file >> deptCount;
        for (int i = 0; i < deptCount; i++) {
            Department d;
            d.loadFromFile(file);
            departments.push_back(d);
        }

        file.close();
        cout << "Data loaded successfully!\n";
    }

    void saveToFile() {
        ofstream file(filename);

        file << students.size() << endl;
        for (size_t i = 0; i < students.size(); i++) {
            students[i].saveToFile(file);
        }

        file << teachers.size() << endl;
        for (size_t i = 0; i < teachers.size(); i++) {
            teachers[i].saveToFile(file);
        }

        file << courses.size() << endl;
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i].saveToFile(file);
        }

        file << departments.size() << endl;
        for (size_t i = 0; i < departments.size(); i++) {
            departments[i].saveToFile(file);
        }

        file.close();
        cout << "Data saved successfully!\n";
    }

    void addStudent() {
        int id;
        string name, dept;
        double cgpa;

        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, dept);
        cout << "Enter CGPA: ";
        cin >> cgpa;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                cout << "Student ID already exists!\n";
                return;
            }
        }

        Student newStudent(id, name, dept, cgpa);
        students.push_back(newStudent);
        saveToFile();
        cout << "Student admitted successfully!\n";
    }

    void addTeacher() {
        int id;
        string name, dept, des;

        cout << "Enter Teacher ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, dept);
        cout << "Enter Designation: ";
        getline(cin, des);

        for (size_t i = 0; i < teachers.size(); i++) {
            if (teachers[i].getID() == id) {
                cout << "Teacher ID already exists!\n";
                return;
            }
        }

        Teacher newTeacher(id, name, dept, des);
        teachers.push_back(newTeacher);
        saveToFile();
        cout << "Teacher added successfully!\n";
    }

    void addCourse() {
        int id, credits, teacherID;
        string name;

        cout << "Enter Course ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Course Name: ";
        getline(cin, name);
        cout << "Enter Credits: ";
        cin >> credits;
        cout << "Enter Teacher ID: ";
        cin >> teacherID;

        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].getID() == id) {
                cout << "Course ID already exists!\n";
                return;
            }
        }

        Course newCourse(id, name, credits, teacherID);
        courses.push_back(newCourse);
        saveToFile();
        cout << "Course added successfully!\n";
    }

    void addDepartment() {
        int id;
        string name, head;

        cout << "Enter Department ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Department Name: ";
        getline(cin, name);
        cout << "Enter Head of Department: ";
        getline(cin, head);

        for (size_t i = 0; i < departments.size(); i++) {
            if (departments[i].getID() == id) {
                cout << "Department ID already exists!\n";
                return;
            }
        }

        Department newDept(id, name, head);
        departments.push_back(newDept);
        saveToFile();
        cout << "Department added successfully!\n";
    }

    void registerCourse() {
        int studentID, courseID;

        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Course ID: ";
        cin >> courseID;

        Student* student = NULL;
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == studentID) {
                student = &students[i];
                break;
            }
        }

        Course* course = NULL;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].getID() == courseID) {
                course = &courses[i];
                break;
            }
        }

        if (!student) {
            cout << "Student not found!\n";
            return;
        }
        if (!course) {
            cout << "Course not found!\n";
            return;
        }

        student->addCourse(courseID);
        saveToFile();
        cout << "Course registered successfully!\n";
    }

    void assignTeacher() {
        int teacherID, courseID;

        cout << "Enter Teacher ID: ";
        cin >> teacherID;
        cout << "Enter Course ID: ";
        cin >> courseID;

        Teacher* teacher = NULL;
        for (size_t i = 0; i < teachers.size(); i++) {
            if (teachers[i].getID() == teacherID) {
                teacher = &teachers[i];
                break;
            }
        }

        Course* course = NULL;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].getID() == courseID) {
                course = &courses[i];
                break;
            }
        }

        if (!teacher) {
            cout << "Teacher not found!\n";
            return;
        }
        if (!course) {
            cout << "Course not found!\n";
            return;
        }

        course->setTeacherID(teacherID);
        saveToFile();
        cout << "Teacher assigned to course successfully!\n";
    }

    void calculateGPA() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                double totalPoints = 0;
                int totalCredits = 0;
                vector<int> courseIDs = students[i].getCourseIDs();

                for (size_t j = 0; j < courseIDs.size(); j++) {
                    for (size_t k = 0; k < courses.size(); k++) {
                        if (courses[k].getID() == courseIDs[j]) {
                            totalPoints += students[i].getCGPA() * courses[k].getCredits();
                            totalCredits += courses[k].getCredits();
                            break;
                        }
                    }
                }

                if (totalCredits > 0) {
                    double gpa = totalPoints / totalCredits;
                    cout << "Student " << students[i].getName() << " GPA: "
                         << fixed << setprecision(2) << gpa << endl;
                } else {
                    cout << "No courses registered!\n";
                }
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void generateTranscript() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                cout << "\n========= TRANSCRIPT =========\n";
                cout << "Student ID: " << students[i].getID() << endl;
                cout << "Name: " << students[i].getName() << endl;
                cout << "Department: " << students[i].getDepartment() << endl;
                cout << "CGPA: " << fixed << setprecision(2) << students[i].getCGPA() << endl;
                cout << "\nCourses Taken:\n";
                vector<int> courseIDs = students[i].getCourseIDs();
                for (size_t j = 0; j < courseIDs.size(); j++) {
                    for (size_t k = 0; k < courses.size(); k++) {
                        if (courses[k].getID() == courseIDs[j]) {
                            cout << "- " << courses[k].getName()
                                 << " (Credits: " << courses[k].getCredits() << ")" << endl;
                            break;
                        }
                    }
                }
                cout << "==============================\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void searchStudent() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                students[i].displayStudent();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void searchTeacher() {
        int id;
        cout << "Enter Teacher ID: ";
        cin >> id;

        for (size_t i = 0; i < teachers.size(); i++) {
            if (teachers[i].getID() == id) {
                teachers[i].displayTeacher();
                return;
            }
        }
        cout << "Teacher not found!\n";
    }

    void searchCourse() {
        int id;
        cout << "Enter Course ID: ";
        cin >> id;

        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].getID() == id) {
                courses[i].displayCourse();
                return;
            }
        }
        cout << "Course not found!\n";
    }

    void searchDepartment() {
        int id;
        cout << "Enter Department ID: ";
        cin >> id;

        for (size_t i = 0; i < departments.size(); i++) {
            if (departments[i].getID() == id) {
                departments[i].displayDepartment();
                return;
            }
        }
        cout << "Department not found!\n";
    }

    void sortStudentsByCGPA() {
        if (students.empty()) {
            cout << "No students to sort!\n";
            return;
        }

        for (size_t i = 0; i < students.size() - 1; i++) {
            for (size_t j = 0; j < students.size() - i - 1; j++) {
                if (students[j].getCGPA() < students[j + 1].getCGPA()) {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        cout << "\nStudents sorted by CGPA (Descending):\n";
        for (size_t i = 0; i < students.size(); i++) {
            students[i].displayStudent();
        }
        saveToFile();
    }

    void departmentStatistics() {
        cout << "\n===== DEPARTMENT STATISTICS =====\n";
        for (size_t i = 0; i < departments.size(); i++) {
            int studentCount = 0;
            double totalCGPA = 0;

            for (size_t j = 0; j < students.size(); j++) {
                if (students[j].getDepartment() == departments[i].getName()) {
                    studentCount++;
                    totalCGPA += students[j].getCGPA();
                }
            }

            cout << "\nDepartment: " << departments[i].getName() << endl;
            cout << "Head: " << departments[i].getHead() << endl;
            cout << "Total Students: " << studentCount << endl;
            if (studentCount > 0) {
                cout << "Average CGPA: " << fixed << setprecision(2)
                     << totalCGPA / studentCount << endl;
            } else {
                cout << "Average CGPA: N/A" << endl;
            }
        }
    }

    void displayAll() {
        cout << "\n========= ALL STUDENTS =========\n";
        for (size_t i = 0; i < students.size(); i++) {
            students[i].displayStudent();
        }

        cout << "\n========= ALL TEACHERS =========\n";
        for (size_t i = 0; i < teachers.size(); i++) {
            teachers[i].displayTeacher();
        }

        cout << "\n========= ALL COURSES =========\n";
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i].displayCourse();
        }

        cout << "\n========= ALL DEPARTMENTS =========\n";
        for (size_t i = 0; i < departments.size(); i++) {
            departments[i].displayDepartment();
        }
    }
};

int main() {
    University uni("university_data.txt");
    int choice;

    do {
        cout << "\n===== MINI UNIVERSITY ERP SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Teacher\n";
        cout << "3. Add Course\n";
        cout << "4. Add Department\n";
        cout << "5. Register Course for Student\n";
        cout << "6. Assign Teacher to Course\n";
        cout << "7. Calculate GPA\n";
        cout << "8. Generate Transcript\n";
        cout << "9. Search Student\n";
        cout << "10. Search Teacher\n";
        cout << "11. Search Course\n";
        cout << "12. Search Department\n";
        cout << "13. Sort Students by CGPA\n";
        cout << "14. Department Statistics\n";
        cout << "15. Display All\n";
        cout << "16. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: uni.addStudent(); break;
            case 2: uni.addTeacher(); break;
            case 3: uni.addCourse(); break;
            case 4: uni.addDepartment(); break;
            case 5: uni.registerCourse(); break;
            case 6: uni.assignTeacher(); break;
            case 7: uni.calculateGPA(); break;
            case 8: uni.generateTranscript(); break;
            case 9: uni.searchStudent(); break;
            case 10: uni.searchTeacher(); break;
            case 11: uni.searchCourse(); break;
            case 12: uni.searchDepartment(); break;
            case 13: uni.sortStudentsByCGPA(); break;
            case 14: uni.departmentStatistics(); break;
            case 15: uni.displayAll(); break;
            case 16:
                cout << "Exiting...\n";
                uni.saveToFile();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 16);

    return 0;
}
