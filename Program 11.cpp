#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Student
{
private:
    int id;
    string name, department;
    int semester;
    float marks[5];
    float total, average, gpa;
    char grade;

public:
    void input()
    {
        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Department: ";
        getline(cin, department);

        cout << "Enter Semester: ";
        cin >> semester;

        total = 0;

        cout << "Enter Marks of 5 Subjects:\n";
        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
            total += marks[i];
        }

        average = total / 5;

        if (average >= 80)
        {
            gpa = 4.00;
            grade = 'A';
        }
        else if (average >= 70)
        {
            gpa = 3.50;
            grade = 'B';
        }
        else if (average >= 60)
        {
            gpa = 3.00;
            grade = 'C';
        }
        else if (average >= 50)
        {
            gpa = 2.50;
            grade = 'D';
        }
        else
        {
            gpa = 0.00;
            grade = 'F';
        }
    }

    void display()
    {
        cout << "\n---------------------------------------\n";
        cout << "Student ID : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Department : " << department << endl;
        cout << "Semester   : " << semester << endl;
        cout << "Total Marks: " << total << endl;
        cout << "Average    : " << average << endl;
        cout << "GPA        : " << fixed << setprecision(2) << gpa << endl;
        cout << "Grade      : " << grade << endl;
    }

    int getID()
    {
        return id;
    }

    float getGPA()
    {
        return gpa;
    }

    string getDepartment()
    {
        return department;
    }
};
int main()
{
    Student s[20];
    int n;

    cout << "Enter Number of Students (Max 20): ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Information for Student " << i + 1 << endl;
        s[i].input();
    }

    cout << "\n========== STUDENT MARKSHEET ==========\n";
    for (int i = 0; i < n; i++)
    {
        s[i].display();
    }

    int searchID;
    cout << "\nEnter Student ID to Search: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        if (s[i].getID() == searchID)
        {
            cout << "\nStudent Found:\n";
            s[i].display();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student Not Found.\n";
    }

    // Sort by GPA (Descending)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (s[i].getGPA() < s[j].getGPA())
            {
                Student temp;
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    cout << "\n===== Students Sorted by GPA =====\n";

    for (int i = 0; i < n; i++)
    {
        s[i].display();
    }

    cout << "\n===== Topper =====\n";
    s[0].display();

    return 0;
}
