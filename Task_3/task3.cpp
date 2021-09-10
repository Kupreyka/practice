#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Matrix
{
    int rows;
    int cols;
    int* array;

    Matrix(int rows, int cols);

    int GetSize() const;
    void Print() const;
};

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), array(new int[rows * cols]) {}

int Matrix::GetSize() const {
    return rows * cols;
};

void Matrix::Print() const
{
    for (int i = 0; i < GetSize(); ++i)
    {
        if (i % cols == 0)
        {
            cout << "\n";
        }
        cout << array[i] << " ";
    }
}

string ReadAllTextFromFile(fstream& file)
{
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return text;
}

vector<int> split(const string& s, char delim)
{
    vector<int> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(stoi(item));
    }

    return result;
}

//Заполняет массив значениями, прочитанными из файла в source
void FillMatrix(Matrix& maxtrix, const string source, char delimiter = ' ')
{
    vector<int> sourceSplited = split(source, delimiter);
    if (maxtrix.GetSize() != sourceSplited.size())
    {
        cerr << "Введенное количество столбцов и строк невозможно разместить в указанном массиве.\n";
        exit(1);
    }

    for (int i = 0; i < sourceSplited.size(); ++i)
    {
        maxtrix.array[i] = sourceSplited[i];
    }
}

//Считывает Matrix из указанного файла. Привязано к разделителю
Matrix InputMatrix(const string& filename)
{
    fstream file(filename);
    if (!file.is_open())
    {
        cerr << "Невозможно открыть " << filename << " в текущей директории\n";
        exit(1);
    }

    string text = ReadAllTextFromFile(file);

    const int defaultRowsPosition = 0;
    const int defaultColsPosition = 3;
    const int defaultArrayPosition = 6;

    Matrix input(text[defaultRowsPosition] - '0', text[defaultColsPosition] - '0');

    text.erase(0, defaultArrayPosition);

    FillMatrix(input, text);

    return input;
}

//Считает количество знакочередующихся элементов
int CountSigns(Matrix matrix, int start, int end)
{
    int count = 0;
    for (int i = start; i < end - 1; ++i)
    {
        if (
            (matrix.array[i] > 0 && matrix.array[i + 1] < 0) ||
            (matrix.array[i] < 0 && matrix.array[i + 1] > 0))
        {
            count++;
        }
    }

    return count;
}

//Находит номер строки с максимальным количеством знакочередующихся элементов
int FindRow(Matrix matrix)
{
    int response = 1;
    int max = CountSigns(matrix, 0, matrix.cols);
    for (int i = matrix.cols, row = 1; i < matrix.GetSize(); i += matrix.cols)
    {
        int currentSigns = CountSigns(matrix, i, i + matrix.cols);
        row++;

        if (currentSigns > max)
        {
            max = currentSigns;
            response = row;
        }
    }

    return response;
}

void Swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

//Меняет последнюю строку с заданной
void SwitchRows(Matrix& matrix, int row)
{
    if (row == matrix.rows)
    {
        return;
    }

    const int firstLastRowElementIndex = matrix.GetSize() - matrix.cols;
    for (int i = firstLastRowElementIndex, firstIndex = 0; i < matrix.GetSize(); ++i)
    {
        Swap(matrix.array[i], matrix.array[row * matrix.cols - matrix.cols + firstIndex++]);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    Matrix A = InputMatrix("maxtrix.txt");
    A.Print();
    SwitchRows(A, FindRow(A));
    cout << "\n";
    A.Print();
    return 0;
}