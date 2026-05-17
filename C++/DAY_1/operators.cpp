#include <iostream>
using namespace std;

int main()  {

    //arithmetic operators
    int a = 12 ;
    int b = 87;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << "a % b = " << a % b << endl;

    cout << 5/(float)2 << "\n";

    //relational operators
    int c = 45;
    int d = 67;
    cout << (c == d) << endl;
    cout << (c != d) << endl;
    cout << (c > d) << endl;
    cout << (c < d) << endl;
    cout << (c >= d) << endl;
    cout << (c <= d) << endl;

    //logical operators
    cout << ((c < d) && (c != d)) << endl;
    cout << ((c < d) || (c == d)) << endl;
    cout << !(c < d) << endl;
    cout << !((c < d) || (c == d)) << endl;

    //unary operators
    int e = 45;
    int f = e++; //post increment  kaam -> update
    int g = ++e; //pre increment   update -> kaam
    cout << f << endl; //45
    cout << g << endl; //47
    cout << e-- << endl; //47
    cout << --e << endl; //45
    return 0;
}