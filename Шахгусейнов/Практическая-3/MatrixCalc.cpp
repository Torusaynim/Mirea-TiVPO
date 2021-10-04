#include <iostream>

using namespace std;

class Matrix {
public:
    int** matrix = NULL;
    int n, m;
    void fillMatrix();
};

void Matrix::fillMatrix() {
    if (n <= 0 || m <= 0)
        return;
    int number;
    for (int i = 0; i < this->n; i++)
    {
        this->matrix[i] = new int[this->m];
        for (int j = 0; j < this->m; j++)
        {
            cin >> number;
            this->matrix[i][j] = number;
        }
    }
}

class MatrixCalc {
public:
    Matrix* object = new Matrix();
    MatrixCalc(int n, int m);
    MatrixCalc(int n, int m, int** matrix);
    MatrixCalc* addMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2);
    MatrixCalc* subMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2);
    MatrixCalc* numberMultMatrix(MatrixCalc* matrix, int num);
    MatrixCalc* numberDivMatrix(MatrixCalc* matrix, int num);
    MatrixCalc* multMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2);
    MatrixCalc* transMatrix(MatrixCalc* matrix);
    void printMatrix();
};

MatrixCalc::MatrixCalc(int n, int m) {
    if (n <= 0 || m <= 0)
        return;
    object->n = n;
    object->m = m;
    object->matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        object->matrix[i] = new int[m];
        for (int j = 0; j < m; j++)
            object->matrix[i][j] = 0;
    }
}

MatrixCalc::MatrixCalc(int n, int m, int** matrix) {
    if (n <= 0 || m <= 0)
        return;
    if (matrix == NULL)
        return;
    object->n = n;
    object->m = m;
    object->matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        object->matrix[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            object->matrix[i][j] = matrix[i][j];
        }
    }
}

MatrixCalc* MatrixCalc::addMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2) {
    if (matrix1->object->n <= 0 || matrix2->object->n <= 0 || matrix1->object->m <= 0 || matrix2->object->m <= 0)
        return NULL;
    if ((matrix1->object->n != matrix2->object->n) || (matrix1->object->m != matrix2->object->m))
        return NULL;
    MatrixCalc* result = new MatrixCalc(matrix1->object->n, matrix1->object->m);
    for (int i = 0; i < this->object->n; i++)
    {
        for (int j = 0; j < this->object->m; j++)
        {
            result->object->matrix[i][j] = matrix1->object->matrix[i][j] + matrix2->object->matrix[i][j];
        }
    }
    return result;
}

MatrixCalc* MatrixCalc::subMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2) {
    if (matrix1->object->n <= 0 || matrix2->object->n <= 0 || matrix1->object->m <= 0 || matrix2->object->m <= 0)
        return NULL;
    if ((matrix1->object->n != matrix2->object->n) || (matrix1->object->m != matrix2->object->m))
        return NULL;
    MatrixCalc* result = new MatrixCalc(matrix1->object->n, matrix1->object->m);
    for (int i = 0; i < this->object->n; i++)
    {
        for (int j = 0; j < this->object->m; j++)
        {
            result->object->matrix[i][j] = matrix1->object->matrix[i][j] - matrix2->object->matrix[i][j];
        }
    }
    return result;
}

MatrixCalc* MatrixCalc::numberMultMatrix(MatrixCalc* matrix, int num)
{
    if (matrix->object->n <= 0 || matrix->object->m <= 0)
        return NULL;
    for (int i = 0; i < matrix->object->n; i++)
    {
        for (int j = 0; j < matrix->object->m; j++)
        {
            matrix->object->matrix[i][j] *= num;
        }
    }
    return matrix;
}

MatrixCalc* MatrixCalc::numberDivMatrix(MatrixCalc* matrix, int num)
{
    if (matrix->object->n <= 0 || matrix->object->m <= 0)
        return NULL;
    for (int i = 0; i < matrix->object->n; i++)
    {
        for (int j = 0; j < matrix->object->m; j++)
        {
            matrix->object->matrix[i][j] /= num;
        }
    }
    return matrix;
}

MatrixCalc* MatrixCalc::multMatrix(MatrixCalc* matrix1, MatrixCalc* matrix2)
{
    if (matrix1->object->n <= 0 || matrix2->object->n <= 0 || matrix1->object->m <= 0 || matrix2->object->m <= 0)
        return NULL;
    if (matrix1->object->m != matrix2->object->n)
        return NULL;
    MatrixCalc* result = new MatrixCalc(matrix1->object->n, matrix2->object->m);
    for (int i = 0; i < matrix1->object->n; i++)
    {
        for (int j = 0; j < matrix2->object->m; j++)
        {
            result->object->matrix[i][j] = 0;
            for (int k = 0; k < matrix1->object->m; k++)
            {
                result->object->matrix[i][j] += matrix1->object->matrix[i][k] * matrix2->object->matrix[k][j];
            }
        }
    }
    return result;
}

MatrixCalc* MatrixCalc::transMatrix(MatrixCalc* matrix)
{
    if (matrix->object->n <= 0 || matrix->object->m <= 0)
        return NULL;
    MatrixCalc* result = new MatrixCalc(matrix->object->m, matrix->object->n);
    for (int i = 0; i < matrix->object->m; i++)
    {
        for (int j = 0; j < matrix->object->n; j++)
        {
            result->object->matrix[i][j] = matrix->object->matrix[j][i];
        }
    }
    return result;
}

void MatrixCalc::printMatrix()
{
    if (object->n <= 0 || object->m <= 0)
        return;
    for (int i = 0; i < object->n; i++)
    {
        for (int j = 0; j < object->m; j++)
            cout << object->matrix[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}

class CLI {
    int command = -1;
    int n, m, number;
    void command1();
    void command2();
    void command3();
    void command4();
    void command5();
    void command6();
    int command0();
public:
    CLI();
};

CLI::CLI() {
    while (command != 0)
    {
        cout << "Выберите команду:\n1.Сложить две матрицы\n2.Вычесть из одной матрицы другую\n3.Умножить матрицу на число\n4.Разделить матрицу на число\n5.Перемножить две матрицы\n6.Транспонировать матрицу\n0. Выход из программы\n";
        cin >> command;
        switch (command)
        {
        case 1:
        {
            command1();
            break;
        }
        case 2:
        {
            command2();
            break;
        }
        case 3:
        {
            command3();
            break;
        }
        case 4:
        {
            command4();
            break;
        }
        case 5:
        {
            command5();
            break;
        }
        case 6:
        {
            command6();
            break;
        }
        case 0:
        {
            if (command0() == 0)
                return;
            break;
        }
        default:
        {
            cout << "Некорректное значение- попробуйте снова\n";
            break;
        }
        }
    }
}

void CLI::command1() {
    cout << "Введите размерность и значения первой матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();
    cout << "Введите размерность и значения второй матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix2 = new MatrixCalc(n, m);
    matrix2->object->fillMatrix();

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->addMatrix(matrix1, matrix2);
    result->printMatrix();
}

void CLI::command2() {
    cout << "Введите размерность и значения первой матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();
    cout << "Введите размерность и значения второй матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix2 = new MatrixCalc(n, m);
    matrix2->object->fillMatrix();

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->subMatrix(matrix1, matrix2);
    result->printMatrix();
}

void CLI::command3() {
    cout << "Введите размерность и значения матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();
    cout << "Введите число:\n";
    cin >> n;

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->numberMultMatrix(matrix1, n);
    result->printMatrix();
}

void CLI::command4() {
    cout << "Введите размерность и значения матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();
    cout << "Введите число:\n";
    cin >> n;

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->numberDivMatrix(matrix1, n);
    result->printMatrix();
}

void CLI::command5() {
    cout << "Введите размерность и значения первой матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();
    cout << "Введите размерность и значения второй матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix2 = new MatrixCalc(n, m);
    matrix2->object->fillMatrix();

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->multMatrix(matrix1, matrix2);
    result->printMatrix();
}

void CLI::command6() {
    cout << "Введите размерность и значения матрицы:\n";
    cin >> n >> m;
    MatrixCalc* matrix1 = new MatrixCalc(n, m);
    matrix1->object->fillMatrix();

    cout << "Результат:\n";
    MatrixCalc* result = matrix1->transMatrix(matrix1);
    result->printMatrix();
}

int CLI::command0() {
    cout << "Введите ноль снова, если хотите закончить программу\n";
    cin >> command;
    if (command == 0)
    {
        cout << "Спасибо за внимание! Работа программы завершена";
        return 0;
    }
    else return 1;
}


int main()
{
    setlocale(LC_CTYPE, "rus");

    CLI* cli = new CLI();
}