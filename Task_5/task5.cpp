#include <iostream>
#include "Sequence.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    Sequence sequence;
    sequence.InputSequence();
    sequence.Print();
    sequence.EditSequence();
    cout << "\nПосле изменений:" << "\n";
    sequence.Print();
    cout << "\n";
    return 0;
}