#include <iostream>
#include <vector>
using namespace std;
typedef unsigned side;

struct Triangle
{
	side first;
	side second;
	side third;

	unsigned perimeter;

	string type;

	/// <summary>
	/// Создает треугольник по введенным сторонам, если треугольник с заданными сторонами существует и определяет его тип
	/// </summary>
	/// <param name="x">Первая сторона</param>
	/// <param name="y">Вторая сторона</param>
	/// <param name="z">Третяя сторона</param>
	Triangle(side x, side y, side z)
	{
		if (!isExist(x, y, z))
		{
			cerr << "Error. Triangle with " << x << " " << y << " " << z << " sides is not exist\n";
			exit(1);
		}

		first = x;
		second = y;
		third = z;
		perimeter = first + second + third;
		type = GetTriangleType();
	};

	/// <summary>
	/// Сравнивает текущий объект с введенным
	/// </summary>
	/// <param name="value">Введенный объект</param>
	/// <returns>true если равны и false если не равны</returns>
	const bool Equals(const Triangle& value) const
	{
		return first == value.first && second == value.second && third == value.third;
	}

private:

	/// <summary>
	/// Проверяет существование треугольника с заданными сторонами
	/// </summary>
	/// <param name="x">Первая сторона</param>
	/// <param name="y">Вторая сторона</param>
	/// <param name="z">Третяя сторона</param>
	/// <returns></returns>
	const bool isExist(side x, side y, side z) const
	{
		if (x > y + z || y > x + z || z > x + y)
		{
			return false;
		}

		return true;
	}

	/// <summary>
	/// Определяет тип треугольника
	/// </summary>
	/// <returns>'Isosceles' - если две стороны равны, 'Equilateral' если все стороны равны, 'Plane' во всех других случаях</returns>
	const string GetTriangleType() const
	{
		if (first == second || first == third || second == third)
		{
			return "Isosceles";
		}

		if (first == second == third)
		{
			return "Equilateral";
		}

		return "Plane";
	}
};

/// <summary>
/// Находит индекс треугольника с максимальным периметром
/// </summary>
/// <param name="source">Исходный массив для поиска</param>
/// <returns>Индекс треугольника с максимальным периметром</returns>
const Triangle Max(const vector<Triangle>& source)
{
	Triangle max = source[0];
	for (size_t i = 1; i < source.size(); ++i)
	{
		if (source[i].perimeter > max.perimeter)
		{
			max = source[i];
		}
	}

	return max;
}

/// <summary>
/// Находит индекс искомого объекта в исходном массиве
/// </summary>
/// <param name="source">Объект для поиска</param>
/// <param name="value">Массив для поиск</param>
/// <returns>Индекс элемента в массиве либо -1, если такового нет</returns>
const size_t find(const vector<Triangle>& source, const Triangle& value)
{
	for (size_t i = 0; i < source.size(); ++i)
	{
		if (source[i].Equals(value))
		{
			return i;
		}
	}

	return -1;
}

/// <summary>
/// Сортировка массива элементов Triangle по убыванию периметров
/// </summary>
/// <param name="source">Исходный массив</param>
const void SortDescending(vector<Triangle>& source)
{
	vector<Triangle> temp = source;
	vector<Triangle> sorted;
	while (temp.size() > 0)
	{
		Triangle max = Max(temp);
		sorted.push_back(max);
		temp.erase(temp.begin() + find(temp, max));
	}
	source = sorted;
}

/// <summary>
/// Выводит элементы исходного вектора на экран
/// </summary>
/// <param name="source">Исходный вектор</param>
const void PrintVector(const vector<Triangle>& source)
{
	for (size_t i = 0; i < source.size(); ++i)
	{
		cout << source[i].perimeter << " ";
	}

	cout << "\n";
}

/// <summary>
/// Обеспечивает ввод Triangle с клавиатуры
/// </summary>
/// <returns>Объект типа Triangle</returns>
const Triangle GetTriangleFromKeyboard()
{
	unsigned x;
	unsigned y;
	unsigned z;

	cout << "Enter sides of triangle:\n";
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "z: ";
	cin >> z;

	return Triangle(x, y, z);
}

/// <summary>
/// Создает массив элементов типа Triangle, полученных с клавиатуры
/// </summary>
/// <returns>Массив элементов типа Triangle</returns>
const vector<Triangle> InputTriangles()
{
	vector<Triangle> input;
	while (true)
	{
		input.push_back(GetTriangleFromKeyboard());

		cout << "continue? y\\n ";
		char choice;
		cin >> choice;
		if (choice == 'n')
		{
			break;
		}
	}

	return input;
}

int main()
{
	vector<Triangle> input = InputTriangles();
	PrintVector(input);
	cout << "Index of triangle with max perimeter = " << find(input, Max(input)) << "\n";
	SortDescending(input);
	PrintVector(input);

}