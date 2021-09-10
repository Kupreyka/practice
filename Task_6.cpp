#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// Проверка, является ли символ буквой
/// </summary>
/// <param name="c">Исходный символ</param>
/// <returns>true если является, false если нет</returns>
const bool isLetter(char c)
{
	c = toupper(c);
	return (c >= 'A' && c <= 'Z');
}

/// <summary>
/// Считает длину слова начиная с позиции start
/// </summary>
/// <param name="source">Указатель на начало строки</param>
/// <param name="start">Порядковый номер элемента, с которого начнется расчёт длины</param>
/// <param name="length">Количество символов в исходной строке</param>
/// <returns>Длину слова</returns>
const int NextWordLength(const char* source, const size_t start, const size_t length)
{
	if (start >= length)
	{
		return -1;
	}

	int count = 0;
	for (size_t i = start; isLetter(source[i]); ++i)
	{
		count++;
	}

	return count;
}

/// <summary>
/// Считает количество слов с максимальной длиной
/// </summary>
/// <param name="source">Указатель на первый элемент строки</param>
/// <returns>Количество слов с максимальной длиной</returns>
const unsigned CountOfWordsWithMaxLength(const char* source, const size_t length)
{
	int currentIndex = 0;
	unsigned max = 0;
	unsigned wordLength = 0;
	unsigned count = 0;
	for (size_t i = 0; i <= length; ++i)
	{
		if (isLetter(source[i]))
		{
			wordLength++;
		}
		else
		{
			if (wordLength > max)
			{
				max = wordLength;
				count = 1;
			}
			else if (wordLength == max)
			{
				count++;
			}

			wordLength = 0;
		}
	}

	return count;
}

/// <summary>
/// Считает количество слов с максимальной длиной
/// </summary>
/// <param name="source">Исходная строка</param>
/// <returns>Количество слов с максимальной длиной</returns>
const unsigned GetCountOfWordsWithMaxLength(const string source)
{
	return CountOfWordsWithMaxLength(source.c_str(), source.size());
}

int main()
{
	cout << "Enter source string:\n";
	string source;
	getline(cin, source); //считывает строку до Enter
	cout << GetCountOfWordsWithMaxLength(source) << "\n";
	return 0;
}
