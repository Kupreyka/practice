#include <iostream>
#include <string>
using namespace std;

/// <summary>
/// Обеспечивает ввод числа с клавиатуры
/// </summary>
/// <returns></returns>
int InputNumber()
{
	cout << "Enter number: ";
	int number;
	cin >> number;
	return number;
}

/// <summary>
/// Находит индекс самой большой цифры числа
/// </summary>
/// <param name="number"></param>
/// <returns>Индекс наибольшей цифры числа</returns>
int MaxIndex(int number)
{
	int max = 0;
	int maxIndex = to_string(number).length();
	int currentIndex = maxIndex;

	while (number > 0)
	{
		int base = number % 10;
		if (base > max)
		{
			max = base;
			maxIndex = currentIndex;
		}

		number /= 10;
		currentIndex--;
	}

	return maxIndex;
}

int main()
{
	while (true)
	{
		int number = InputNumber();
		cout << "maxIndex = " << MaxIndex(number) << "\n";
		cout << "continue? y\\n ";
		char choice;
		cin >> choice;
		if (choice == 'n')
			break;
	}

	return 0;
}