#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    double** data;

public:
    Matrix() : rows(0), cols(0), data(NULL) {}

    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new double*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }

    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = new double*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ~Matrix() {
        if (data) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    void inputMatrix() {
        cout << "Enter elements of matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    void displayMatrix() {
        cout << "\nMatrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << fixed << setprecision(2) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getRows() { return rows; }
    int getCols() { return cols; }

    void setElement(int i, int j, double value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            data[i][j] = value;
        }
    }

    double getElement(int i, int j) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            return data[i][j];
        }
        return 0;
    }

    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrix dimensions must match for addition!\n";
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrix dimensions must match for subtraction!\n";
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) {
            cout << "Invalid dimensions for multiplication!\n";
            return Matrix(0, 0);
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix transpose() {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    bool isSymmetric() {
        if (rows != cols) {
            return false;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] != data[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    double determinant3x3() {
        if (rows != 3 || cols != 3) {
            cout << "Determinant only available for 3x3 matrices!\n";
            return 0;
        }

        double det = 0;
        det = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
              - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
              + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        return det;
    }

    double determinant2x2() {
        if (rows != 2 || cols != 2) {
            cout << "Determinant only available for 2x2 matrices!\n";
            return 0;
        }

        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
};

int main() {
    int choice;

    do {
        cout << "\n===== MATRIX CALCULATOR =====\n";
        cout << "1. Matrix Addition\n";
        cout << "2. Matrix Subtraction\n";
        cout << "3. Matrix Multiplication\n";
        cout << "4. Matrix Transpose\n";
        cout << "5. Check Symmetry\n";
        cout << "6. Determinant (2x2 or 3x3)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }

        if (choice >= 1 && choice <= 3) {
            int r1, c1, r2, c2;

            cout << "Enter dimensions of first matrix (rows cols): ";
            cin >> r1 >> c1;
            Matrix m1(r1, c1);
            m1.inputMatrix();
            m1.displayMatrix();

            cout << "Enter dimensions of second matrix (rows cols): ";
            cin >> r2 >> c2;
            Matrix m2(r2, c2);
            m2.inputMatrix();
            m2.displayMatrix();

            Matrix result;

            if (choice == 1) {
                result = m1 + m2;
                if (result.getRows() > 0) {
                    cout << "\nAddition Result:";
                    result.displayMatrix();
                }
            } else if (choice == 2) {
                result = m1 - m2;
                if (result.getRows() > 0) {
            cout << "\nSubtraction Result:";
                    result.displayMatrix();
                }
            } else if (choice == 3) {
                result = m1 * m2;
                if (result.getRows() > 0) {
                    cout << "\nMultiplication Result:";
                    result.displayMatrix();
                }
            }

        } else if (choice == 4) {
            int r, c;
            cout << "Enter dimensions of matrix (rows cols): ";
            cin >> r >> c;
            Matrix m(r, c);
            m.inputMatrix();
            m.displayMatrix();

            Matrix result = m.transpose();
            cout << "\nTranspose Result:";
            result.displayMatrix();

        } else if (choice == 5) {
            int r, c;
            cout << "Enter dimensions of matrix (rows cols): ";
            cin >> r >> c;

            if (r != c) {
                cout << "Matrix must be square to check symmetry!\n";
                continue;
            }

            Matrix m(r, c);
            m.inputMatrix();
            m.displayMatrix();

            if (m.isSymmetric()) {
                cout << "The matrix is symmetric!\n";
            } else {
                cout << "The matrix is not symmetric!\n";
            }

        } else if (choice == 6) {
            int r, c;
            cout << "Enter dimensions of matrix (2x2 or 3x3): ";
            cin >> r >> c;

            if ((r != 2 || c != 2) && (r != 3 || c != 3)) {
                cout << "Only 2x2 and 3x3 matrices are supported!\n";
                continue;
            }

            Matrix m(r, c);
            m.inputMatrix();
            m.displayMatrix();

            if (r == 2 && c == 2) {
                double det = m.determinant2x2();
                cout << "Determinant: " << fixed << setprecision(2) << det << endl;
            } else if (r == 3 && c == 3) {
                double det = m.determinant3x3();
                cout << "Determinant: " << fixed << setprecision(2) << det << endl;
            }

        } else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}
