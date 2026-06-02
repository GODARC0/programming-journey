// Build a program to manage student grades. Allow users
// to input student information ,including names and scores for
// multiple subjects, and calculate the average score of each student

#include <iostream>
#include <string>
using namespace std;
int main(){
    //need a storage to maintain students grades
    //get various user inputs 
    std::string physics;
    std::string chemistry;
    std::string maths;
    std::string biology;
    std::string compSci;
    std::string english;
    std::string agree;
    std::string fullName;
    std::cout << "Enter students full name: ";
    
    cin >> fullName ;
    cout << "Note : if the student had not opted that subject please fill N/A in place of marks\n";
    cout << "type ok to proceed\n";
    cin >>  agree;
    
    int total = 0;
    int count = 0;

    cout << "physics marks :";
    cin >> physics;
    if (physics != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
    }

    cout << "chemistry marks :";
    cin >> chemistry;
    if (chemistry != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
    }

    cout << "maths marks :";
    cin >> maths ;
    if (maths != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
}

    cout << "biology marks :";
    cin  >> biology;
    if (biology != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
}

    cout << "Computer Science marks :";
    cin >> compSci;
    if (compSci != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
}

    cout << "English marks :";
    cin  >> english;
    if (english != "N/A") {
    total += stoi(physics_input);  // stoi() converts "85" → 85
    count++;
}


    // calculate and display average score of students 
    //store everything in a clean table like formate with unique id's for easy retrieval

    return 0;
}