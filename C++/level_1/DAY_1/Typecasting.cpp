#include <iostream>
using namespace std;

int main() {
     char grade = 'Z';
     int value = grade; // Implicit typecasting big to small

     cout << value << endl;

    double marks = 97.5;
    int newMarks = (int)marks; // Explicit typecasting  small to big
    cout << newMarks << endl;
    return 0;
}