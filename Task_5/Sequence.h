#pragma once
#include <vector>
using namespace std;
class Sequence
{
    /// <summary>
    /// Создает объект массива с заданным типом
    /// </summary>
    /// <returns>Массив с элементами введенного типа</returns>
    //auto InputTypeOfArray()

public:

    /// <summary>
    /// Создает вектор заданного типа
    /// </summary>
    const void InputSequence();

    /// <summary>
    /// Выводит вектор на экран
    /// </summary>
    const void Print();

    double& operator[] (const size_t index);

    /*
    Из массива А(N) удалить все элементы, сумма цифр которых чётная,стоящие между
    первым минимальным и последним максимальным элементами (или последним элементом массива).
    */
    const void EditSequence();

private:
    vector<double> source;

    /// <summary>
    /// Обеспечивает создание массива с помощью меню выбора размера массива
    ///  и меню выбора способа заполнения его данными
    /// </summary>
    /// <returns>Массив с учетом выбранных условий</returns>
    const vector<double> CreateArrayWithType();

    /// <summary>
    /// Меню выбора размера массива
    /// </summary>
    /// <returns>Размер массива если выбран "статический"</returns>
    const size_t InputSize();

    /// <summary>
    /// Меню выбора заполнения массива данными
    /// </summary>
    /// <returns>Пункт меню (1 либо 2)</returns>
    const int InputFillType();

    /// <summary>
    /// Заполняет массив случайными значениями (по умолчанию [-100, 100]
    /// </summary>
    /// <param name="source">Массив для заполнения</param>
    /// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
    /// <param name="rightBoard">Верхняя граница диапазона случайных чисел</param>
    const void FillRandomly(vector<double>&, int leftBound = -100, int rightBoard = 100);

    /// <summary>
    /// Заполняет массив значениями, введенными с клавиатуры
    /// </summary>
    /// <param name="source">Массив для заполнения</param>
    const void FillByKeyboard(vector<double>&);

    /// <summary>
    /// Возвращает рандомное число в заданном диапазоне (распределение равномерное)
    /// </summary>
    /// <param name="leftBound">Нижняя граница диапазона случайных чисел</param>
    /// <param name="rightBound">Верхняя граница диапазона случайных чисел</param>
    /// <returns>Случайное число в заданном диапазоне</returns>
    const double GetRandomNumber(int, int);

    /// <summary>
    /// Считывает элемент с клавиатуры
    /// </summary>
    /// <returns>Введенный элемент</returns>
    const double GetElementFromKeyboard();

    /// <summary>
    /// Вычисляет сумму цифр числа
    /// </summary>
    /// <param name="value">Исходное число</param>
    /// <returns>Сумма цифр</returns>
    const int SumOfDigits(double) const;

    /// <summary>
    /// Вычисляет индекс первого минимального элемента последовательности
    /// </summary>
    /// <returns>Индекс первого минимального элемента последовательности</returns>
    const size_t GetMinIndex() const;

    /// <summary>
    /// Вычисляет индекс последнего максимального элемента последовательности
    /// </summary>
    /// <returns>Индекс последнего максимального элемента последовательности</returns>
    const size_t GetLastMaxIndex() const;
};

