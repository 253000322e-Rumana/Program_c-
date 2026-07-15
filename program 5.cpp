#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

class Employee {
private:
    int id;
    string name;
    string designation;
    double basicSalary;
    double houseRent;
    double medicalAllowance;
    double tax;
    double netSalary;

public:
    Employee() : id(0), name(""), designation(""), basicSalary(0.0) {}

    Employee(int i, string n, string d, double salary) {
        id = i;
        name = n;
        designation = d;
        basicSalary = salary;
        calculateSalary();
    }

    void calculateSalary() {
        houseRent = basicSalary * 0.30;
        medicalAllowance = basicSalary * 0.15;

        if (basicSalary <= 25000) {
            tax = 0;
        } else if (basicSalary <= 50000) {
            tax = (basicSalary - 25000) * 0.05;
        } else if (basicSalary <= 100000) {
            tax = 25000 * 0.05 + (basicSalary - 50000) * 0.10;
        } else {
            tax = 25000 * 0.05 + 50000 * 0.10 + (basicSalary - 100000) * 0.15;
        }

        netSalary = basicSalary + houseRent + medicalAllowance - tax;
    }

    void displayEmployee() {
        cout << "\n============================\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Designation: " << designation << endl;
        cout << "Basic Salary: " << fixed << setprecision(2) << basicSalary << endl;
        cout << "House Rent: " << houseRent << endl;
        cout << "Medical Allowance: " << medicalAllowance << endl;
        cout << "Tax: " << tax << endl;
        cout << "Net Salary: " << netSalary << endl;
        cout << "============================\n";
    }

    int getID() { return id; }
    string getName() { return name; }
    double getNetSalary() { return netSalary; }

    void setData(int i, string n, string d, double salary) {
        id = i;
        name = n;
        designation = d;
        basicSalary = salary;
        calculateSalary();
    }
};

class Payroll {
private:
    vector<Employee> employees;

public:
    void addEmployee() {
        int id;
        string name, designation;
        double salary;

        cout << "Enter Employee ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Basic Salary: ";
        cin >> salary;

        for (size_t i = 0; i < employees.size(); i++) {
            if (employees[i].getID() == id) {
                cout << "Employee ID already exists!\n";
                return;
            }
        }

        Employee newEmployee(id, name, designation, salary);
        employees.push_back(newEmployee);
        cout << "Employee added successfully!\n";
    }

    void displayAllEmployees() {
        if (employees.empty()) {
            cout << "No employees in the system!\n";
            return;
        }

        cout << "\n========= ALL EMPLOYEES =========\n";
        for (size_t i = 0; i < employees.size(); i++) {
            employees[i].displayEmployee();
        }
    }

    void sortByNetSalary() {
        if (employees.empty()) {
            cout << "No employees to sort!\n";
            return;
        }

        for (size_t i = 0; i < employees.size() - 1; i++) {
            for (size_t j = 0; j < employees.size() - i - 1; j++) {
                if (employees[j].getNetSalary() < employees[j + 1].getNetSalary()) {
                    Employee temp = employees[j];
                    employees[j] = employees[j + 1];
                    employees[j + 1] = temp;
                }
            }
        }

        cout << "\nEmployees sorted by Net Salary (Descending):\n";
        for (size_t i = 0; i < employees.size(); i++) {
            employees[i].displayEmployee();
        }
    }

    void searchEmployee() {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;

        for (size_t i = 0; i < employees.size(); i++) {
            if (employees[i].getID() == id) {
                employees[i].displayEmployee();
                return;
            }
        }
        cout << "Employee not found!\n";
    }

    void deleteEmployee() {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        for (size_t i = 0; i < employees.size(); i++) {
            if (employees[i].getID() == id) {
                employees.erase(employees.begin() + i);
                cout << "Employee deleted successfully!\n";
                return;
            }
        }
        cout << "Employee not found!\n";
    }

    void updateEmployee() {
        int id;
        string name, designation;
        double salary;

        cout << "Enter Employee ID to update: ";
        cin >> id;

        for (size_t i = 0; i < employees.size(); i++) {
            if (employees[i].getID() == id) {
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Designation: ";
                getline(cin, designation);
                cout << "Enter New Basic Salary: ";
                cin >> salary;

                employees[i].setData(id, name, designation, salary);
                cout << "Employee updated successfully!\n";
                return;
            }
        }
        cout << "Employee not found!\n";
    }
};

int main() {
    Payroll payroll;
    int choice;

    do {
        cout << "\n===== EMPLOYEE PAYROLL SYSTEM =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Sort Employees by Net Salary (Descending)\n";
        cout << "4. Search Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Update Employee\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                payroll.addEmployee();
                break;
            case 2:
                payroll.displayAllEmployees();
                break;
            case 3:
                payroll.sortByNetSalary();
                break;
            case 4:
                payroll.searchEmployee();
                break;
            case 5:
                payroll.deleteEmployee();
                break;
            case 6:
                payroll.updateEmployee();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
