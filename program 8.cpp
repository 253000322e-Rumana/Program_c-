#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class String {
private:
    char* str;
    int length;

public:
    String() {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }

    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    ~String() {
        delete[] str;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    String operator+(const String& other) {
        String result;
        result.length = length + other.length;
        delete[] result.str;
        result.str = new char[result.length + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    bool operator==(const String& other) {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) {
        return strcmp(str, other.str) != 0;
    }

    bool operator<(const String& other) {
        return strcmp(str, other.str) < 0;
    }

    bool operator>(const String& other) {
        return strcmp(str, other.str) > 0;
    }

    String reverse() {
        String result;
        delete[] result.str;
        result.str = new char[length + 1];
        result.length = length;

        for (int i = 0; i < length; i++) {
            result.str[i] = str[length - 1 - i];
        }
        result.str[length] = '\0';
        return result;
    }

    int countVowels() {
        int count = 0;
        for (int i = 0; i < length; i++) {
            char ch = tolower(str[i]);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                count++;
            }
        }
        return count;
    }

    String toUpperCase() {
        String result;
        delete[] result.str;
        result.str = new char[length + 1];
        result.length = length;

        for (int i = 0; i < length; i++) {
            result.str[i] = toupper(str[i]);
        }
        result.str[length] = '\0';
        return result;
    }

    void display() {
        cout << str << endl;
    }

    int getLength() {
        return length;
    }

    const char* getString() {
        return str;
    }
};

int main() {
    String s1, s2, s3;
    int choice;

    do {
        cout << "\n===== DYNAMIC STRING CLASS =====\n";
        cout << "1. Create String 1\n";
        cout << "2. Create String 2\n";
        cout << "3. Concatenate Strings\n";
        cout << "4. Compare Strings\n";
        cout << "5. Reverse String\n";
        cout << "6. Count Vowels\n";
        cout << "7. Convert to Uppercase\n";
        cout << "8. Display Strings\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            char input[100];
            cout << "Enter String 1: ";
            cin.getline(input, 100);
            s1 = String(input);
            cout << "String 1 created!\n";

        } else if (choice == 2) {
            char input[100];
            cout << "Enter String 2: ";
            cin.getline(input, 100);
            s2 = String(input);
            cout << "String 2 created!\n";

        } else if (choice == 3) {
            s3 = s1 + s2;
            cout << "Concatenated String: ";
            s3.display();

        } else if (choice == 4) {
            cout << "String 1: ";
            s1.display();
            cout << "String 2: ";
            s2.display();

            if (s1 == s2) {
                cout << "Strings are equal!\n";
            } else if (s1 < s2) {
                cout << "String 1 is less than String 2\n";
            } else if (s1 > s2) {
                cout << "String 1 is greater than String 2\n";
            }

        } else if (choice == 5) {
            String reversed = s1.reverse();
            cout << "Original: ";
            s1.display();
            cout << "Reversed: ";
            reversed.display();

        } else if (choice == 6) {
            cout << "String: ";
            s1.display();
            cout << "Number of vowels: " << s1.countVowels() << endl;

        } else if (choice == 7) {
            String upper = s1.toUpperCase();
            cout << "Original: ";
            s1.display();
            cout << "Uppercase: ";
            upper.display();

        } else if (choice == 8) {
            cout << "\nString 1: ";
            s1.display();
            cout << "String 2: ";
            s2.display();
            cout << "String 3: ";
            s3.display();

        } else if (choice == 9) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}
