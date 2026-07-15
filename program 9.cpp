#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    string department;
    double cgpa;

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
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    string getDepartment() { return department; }
    double getCGPA() { return cgpa; }

    void setName(string n) { name = n; }
    void setDepartment(string d) { department = d; }
    void setCGPA(double c) { cgpa = c; }

    void saveToFile(ofstream& file) {
        file << id << endl;
        file << name << endl;
        file << department << endl;
        file << cgpa << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, department);
        file >> cgpa;
    }
};

class Database {
private:
    vector<Student> students;
    string filename;

public:
    Database(string fname) {
        filename = fname;
        loadFromFile();
    }

    void loadFromFile() {
        students.clear();
        ifstream file(filename);

        if (!file) {
            cout << "No existing database found. New database created.\n";
            return;
        }

        while (!file.eof()) {
            Student s;
            s.loadFromFile(file);
            if (file) {
                students.push_back(s);
            }
        }
        file.close();
        cout << "Loaded " << students.size() << " records from file.\n";
    }

    void saveToFile() {
        ofstream file(filename);
        for (size_t i = 0; i < students.size(); i++) {
            students[i].saveToFile(file);
        }
        file.close();
        cout << "Data saved to file successfully!\n";
    }

    void addStudent() {
        int id;
        string name, department;
        double cgpa;

        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter CGPA: ";
        cin >> cgpa;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                cout << "Student ID already exists!\n";
                return;
            }
        }

        Student newStudent(id, name, department, cgpa);
        students.push_back(newStudent);
        saveToFile();
        cout << "Student added successfully!\n";
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students in database!\n";
            return;
        }

        cout << "\n========= ALL STUDENTS =========\n";
        for (size_t i = 0; i < students.size(); i++) {
            students[i].displayStudent();
        }
    }

    void searchStudent() {
        int id;
        cout << "Enter Student ID to search: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                students[i].displayStudent();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void updateStudent() {
        int id;
        string name, department;
        double cgpa;

        cout << "Enter Student ID to update: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Department: ";
                getline(cin, department);
                cout << "Enter New CGPA: ";
                cin >> cgpa;

                students[i].setName(name);
                students[i].setDepartment(department);
                students[i].setCGPA(cgpa);

                saveToFile();
                cout << "Student updated successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                students.erase(students.begin() + i);
                saveToFile();
                cout << "Student deleted successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }
};

int main() {
    Database db("students.txt");
    int choice;

    do {
        cout << "\n===== STUDENT DATABASE =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.displayAllStudents();
                break;
            case 3:
                db.searchStudent();
                break;
            case 4:
                db.updateStudent();
                break;
            case 5:
                db.deleteStudent();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
