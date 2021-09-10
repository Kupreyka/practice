#pragma once
#include "Sequence.h"
#include <iostream>
#include <random>
#include <cassert>
#include <string>

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
const void Sequence::InputSequence()
{
    //InputTypeOfArray();
    source =  CreateArrayWithType();
}

/// <summary>
/// Обеспечивает создание массива с помощью меню выбора размера массива
///  и меню выбора способа заполнения его данными
/// </summary>
/// <returns>Массив с учетом выбранных условий</returns>
const vector<double> Sequence::CreateArrayWithType()
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
/// Меню выбора размера массива
/// </summary>
/// <returns>Размер массива если выбран "статический"</returns>
const size_t Sequence::InputSize()
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
/// Меню выбора заполнения массива данными
/// </summary>
/// <returns>Пункт меню (1 либо 2)</returns>
const int Sequence::InputFillType()
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
/// Заполняет массив случайными значениями (по умолчанию [-100, 100]
/// </summary>
/// <param name="source">Массив для заполнения</param>
/// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
/// <param name="rightBoard">Верхняя граница диапазона случайных чисел</param>
const void Sequence::FillRandomly(vector<double>& source, int leftBound, int rightBoard)
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
/// Возвращает рандомное число в заданном диапазоне (распределение равномерное)
/// </summary>
/// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
/// <param name="rightBound">Верхняя граница диапазона случайных чисел</param>
/// <returns>Случайное число в заданном диапазоне</returns>
const double Sequence::GetRandomNumber(int leftBound, int rightBound)
{
    assert(leftBound <= rightBound);

    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> distribution(leftBound, rightBound);
    return distribution(rng);
}

/// <summary>
/// Заполняет массив значениями, введенными с клавиатуры
/// </summary>
/// <param name="source">Массив для заполнения</param>
const void Sequence::FillByKeyboard(vector<double>& source)
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
/// Считывает элемент с клавиатуры
/// </summary>
/// <returns>Введенный элемент</returns>
const double Sequence::GetElementFromKeyboard()
{
    cout << "Введите число: ";
    double input;
    cin >> input;
    return input;
}

/// <summary>
/// Выводит вектор на экран
/// </summary>
/// <param name="source">Исходный вектор</param>
const void Sequence::Print()
{
    for (double* ptr = &source[0]; ptr < &source[0] + source.size(); ++ptr)
    {
        cout << *ptr << " ";
    }
    cout << "\n";
}

double& Sequence::operator[] (const size_t index)
{
    return source[index];
}

/*
 Из массива А(N) удалить все элементы, сумма цифр которых чётная,стоящие между
 первым минимальным и последним максимальным элементами (или последним элементом массива).
 */
const void Sequence::EditSequence()
{
    size_t minIndex = GetMinIndex();
    size_t maxIndex = GetLastMaxIndex();

    if (maxIndex - minIndex == 1)
    {
        return;
    }

    for (size_t i = minIndex + 1; i < maxIndex;)
    {
        if (SumOfDigits(source[i]) % 2 == 0)
        {
            source.erase(source.begin() + i);
            maxIndex--;
        }
        else
        {
            i++;
        }
    }

}

/// <summary>
/// Вычисляет сумму цифр числа
/// </summary>
/// <param name="value">Исходное число</param>
/// <returns>Сумма цифр</returns>
const int Sequence::SumOfDigits(double value) const
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

/// <summary>
/// Вычисляет индекс первого минимального элемента последовательности
/// </summary>
/// <returns>Индекс первого минимального элемента последовательности</returns>
const size_t Sequence::GetMinIndex() const
{
    double min = source[0];
    size_t minIndex = 0;
    for (size_t i = 1; i < source.size(); ++i)
    {
        if (source[i] < min)
        {
            min = source[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/// <summary>
/// Вычисляет индекс последнего максимального элемента последовательности
/// </summary>
/// <returns>Индекс последнего максимального элемента последовательности</returns>
const size_t Sequence::GetLastMaxIndex() const
{
    double max = source[0];
    size_t maxIndex = 0;
    for (size_t i = 1; i < source.size(); ++i)
    {
        if (source[i] >= max)
        {
            max = source[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}