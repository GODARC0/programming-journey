#include <iostream>
using namespace std;
//Create a command-line calculator program that can perform
//arithmetic operations like add sub multiply and divide.
//  Allow the user to input 
//two number and desired operation 

int main() {
    //basic arithmetic calculator
    double num1;
    double num2;
    int oper;
    cout << "Enter a numbers: ";
    cin >> num1 ;
    cout << "Enter another number: ";
    cin >> num2 ;
    cout << "Select operation to perform \n" ;
    cout << " 1. Addition \n 2. Subtraction \n 3. Multiplication \n 4. Division \n";
    cin >> oper;
    if (oper == 1){
            cout << "Sum of " << num1 << " and " << num2 << " is: " << num1 + num2 << endl;
        }
        else if (oper == 2){
            cout << "Difference of " << num1 << " and " << num2 << " is: " << num1 - num2 << endl;
        }
        else if (oper == 3){
            cout << "Product of " << num1 << " and " << num2 << " is: " << num1 * num2 << endl;
        }
        else if (oper == 4){
            cout << "Division of " << num1 << " and " << num2 << " is: " << num1 / num2 << endl;

        }
        else {
            return 0;
        }

      //objective is fullfilled but now i will try  to make it bug proof   
    
    return 0;    
}

    
