#include <iostream>
using namespace std;

int main() {
    //basic arithmetic calculator
    double num1;
    double num2;
    cout << "Enter a numbers: ";
    cin >> num1 ;
    cout << "Enter another number: ";
    cin >> num2 ;
    cout << "Sum of " << num1 << " and " << num2 << " is: " << num1 + num2 << endl;
    cout << "Difference of " << num1 << " and " << num2 << " is: " << num1 - num2 << endl;
    cout << "Product of " << num1 << " and " << num2 << " is: " << num1 * num2 << endl;
    cout << "Quotient of " << num1 << " and " << num2 << " is: " << num1 / num2 << endl;
    //now i will add the option so the user will be able to select from above 4 what he want to do 
    return 0;    
}

    
