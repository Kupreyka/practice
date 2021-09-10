#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <string>
using namespace std;

/// <summary>
/// Считывает элемент с клавиатуры
/// </summary>
/// <returns>Введенный элемент</returns>
double GetElementFromKeyboard()
{
    cout << "Введите число: ";
    double input;
    cin >> input;
    return input;
}

/// <summary>
/// Заполняет массив значениями, введенными с клавиатуры
/// </summary>
/// <param name="source">Массив для заполнения</param>
void FillByKeyboard(vector<double>& source)
{
    if (source.empty())
    {
        while (true)
        {
            source.push_back(GetElementFromKeyboard());

            cout << "continue? y\\n ";
            char choice;
            cin >> choice;
            if (choice == 'n')
                break;
        }
        return;
    }

    for (auto& item : source)
    {
        item = GetElementFromKeyboard();
    }
}

/// <summary>
/// Меню выбора заполнения массива данными
/// </summary>
/// <returns>Пункт меню (1 либо 2)</returns>
int InputFillType()
{
    cout << "Выберите тип ввода массива (1, 2):\n";
    cout << "1. Заполнение случайными числами\n";
    cout << "2. Ручной ввод\n";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cerr << "Ошибка! Нет " << choice << " пункта меню\n";
        exit(1);
    }

    return choice;
}

/// <summary>
/// Меню выбора размера массива
/// </summary>
/// <returns>Размер массива если выбран "статический"</returns>
size_t InputSize()
{
    cout << "Выберите размер массива (1, 2):\n";
    cout << "1. Динамический\n";
    cout << "2. Статический\n";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        return 0;

    case 2:
        cout << "Введите размер массива: ";
        int inputSize;
        cin >> inputSize;
        return inputSize;

    default:
        cerr << "Ошибка! Нет " << choice << " пункта меню\n";
        exit(1);
    }
}

/// <summary>
/// Возвращает рандомное число в заданном диапазоне (распределение равномерное)
/// </summary>
/// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
/// <param name="rightBound">Верхняя граница диапазона случайных чисел</param>
/// <returns>Случайное число в заданном диапазоне</returns>
double GetRandomNumber(int leftBound, int rightBound)
{
    assert(leftBound <= rightBound);

    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> distribution(leftBound, rightBound);
    return distribution(rng);
}

/// <summary>
/// Заполняет массив случайными значениями (по умолчанию [-100, 100]
/// </summary>
/// <param name="source">Массив для заполнения</param>
/// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
/// <param name="rightBoard">Верхняя граница диапазона случайных чисел</param>
void FillRandomly(vector<double>& source, int leftBound = -100, int rightBoard = 100)
{
    if (source.empty())
    {
        while (true)
        {
            source.push_back(GetRandomNumber(leftBound, rightBoard));
            cout << "Добавлен " << source.back() << "\n";
            cout << "continue? y\\n ";
            char choice;
            cin >> choice;
            if (choice == 'n')
                break;
        }
    }
    for (double& i : source)
    {
        i = GetRandomNumber(leftBound, rightBoard);
    }
}

/// <summary>
/// Обеспечивает создание массива с помощью меню выбора размера массива
///  и меню выбора способа заполнения его данными
/// </summary>
/// <returns>Массив с учетом выбранных условий</returns>
vector<double> CreateArrayWithType()
{
    size_t inputSize = InputSize();
    int fillType = InputFillType();
    vector<double> source(inputSize);

    switch (fillType)
    {
    case 1: // Случайными числами
        FillRandomly(source);
        break;
    case 2: // Ручной ввод
        FillByKeyboard(source);
        break;
    default:
        cerr << "Ошибка! Нет " << fillType << " пункта меню\n";
        exit(1);
    }

    return source;
}

/// <summary>
/// Создает объект массива с заданным типом
/// </summary>
/// <returns>Массив с элементами введенного типа</returns>
//auto InputTypeOfArray()
//{
    //TODO 1
//}

/// <summary>
/// Создает вектор заданного типа
/// </summary>
/// <returns></returns>
vector<double> InputSequence()
{
    //InputTypeOfArray();
    return CreateArrayWithType();
}

/// <summary>
/// Вычисляет сумму цифр числа
/// </summary>
/// <param name="value">Исходное число</param>
/// <returns>Сумма цифр</returns>
int SumOfDigits(double value)
{
    const string source = to_string(value);

    int sum = 0;
    for (auto item : source)
    {
        if (isdigit(item))
        {
            sum += item - '0';
        }
    }

    return sum;
}

size_t GetMinIndex(const vector<double>& sequence)
{
    double min = sequence[0];
    size_t minIndex = 0;
    for (size_t i = 1; i < sequence.size(); ++i)
    {
        if (sequence[i] < min)
        {
            min = sequence[i];
            minIndex = i;
        }
    }

    return minIndex;
}

size_t GetLastMaxIndex(const vector<double>& sequence, size_t start)
{
    double max = sequence[0];
    size_t maxIndex = 0;
    for (size_t i = 1; i < sequence.size(); ++i)
    {
        if (sequence[i] >= max)
        {
            max = sequence[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

/*
 Из массива А(N) удалить все элементы, сумма цифр которых чётная,стоящие между
 первым минимальным и последним максимальным элементами (или последним элементом массива).
 */
void EditSequence(vector<double>& sequence)
{
    size_t minIndex = GetMinIndex(sequence);
    size_t maxIndex = GetLastMaxIndex(sequence, minIndex);

    if (maxIndex - minIndex == 1)
    {
        return;
    }

    for (int i = minIndex + 1; i < maxIndex;)
    {
        if (SumOfDigits(sequence[i]) % 2 == 0)
        {
            sequence.erase(sequence.begin() + i);
            maxIndex--;
        }
        else
        {
            minIndex++;
        }
    }

}

/// <summary>
/// Выводит вектор на экран
/// </summary>
/// <param name="source">Исходный вектор</param>
void PrintVector(vector<double> source)
{
    for (double* ptr = &source[0]; ptr < &source[0] + source.size(); ++ptr)
    {
        cout << *ptr << " ";
    }
    cout << "\n";
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector<double> sequence = InputSequence();
    PrintVector(sequence);
    EditSequence(sequence);
    cout << "\nПосле изменений:" << "\n";
    PrintVector(sequence);
    cout << "\n";
    return 0;
}