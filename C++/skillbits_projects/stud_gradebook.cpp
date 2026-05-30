// Build a program to manage student grades. Allow users
// to input student information ,including names and scores for
// multiple subjects, and calculate the average score of each student

#include <iostream>
#include <string>
using namespace std;
int main(){
    //need a storage to maintain students grades
    //get various user inputs 
    int physics;
    int chemistry;
    int maths;
    int biology;
    int compSci;
    int english;
    std::string agree;
    std::string fullName;
    std::cout << "Enter students full name: ";
    
    cin >> fullName ;
    cout << "hello " << fullName << endl;
    cout << "Note : if the student had not opted that subject please fill N/A in place of marks";
    cout << "type ok to proceed";
    cin >>  agree;

    cout << "physics marks";
    cin >> physics;
    cout << "chemistry marks";
    cin >> chemistry;
    cout << "maths marks";
    cin >> maths ;
    cout << "biology marks"
    cin  >> biology;
    cout << "Computer Science marks";
    cin >> compSci;
    cout << "English marks";
    cin  >> english;

    // calculate and display average score of students 
    //store everything in a clean table like formate with unique id's for easy retrieval

    return 0;
}