// Build a program to manage student grades. Allow users
// to input student information ,including names and scores for
// multiple subjects, and calculate the average score of each student

#include <iostream>
#include <string>
using namespace std;
    
struct Student {
    int uid;jj
    float physics;
    float chemistry;
    float maths;
    float biology;
    float compSci;
    float english;
    std::string fullName;
    float avg;
};
int main(){
    //need a storage to maintain students grades
    //get various user inputs 
    Student s1;
    std::cout << "Enter students full name: ";
    
    cin >> s1.fullName ;
    cout << "Note : if the student had not opted that subject please fill N/A in place of marks\n";
    cout << "type ok to proceed\n";
    cin >>  agree;
    
    int total = 0;
    int count = 0;

    cout << "physics marks :";
    cin >> s1.physics;
    if (physics != -1 ) {
    total += physics ;  // stoi() converts "85" → 85
    count++;
    }

//     cout << "chemistry marks :";
//     cin >> s1.chemistry;
//     if (chemistry != "N/A") {
//     total += stoi(chemistry);  // stoi() converts "85" → 85
//     count++;
//     }

//     cout << "maths marks :";
//     cin >> s1.maths ;
//     if (maths != "N/A") {
//     total += stoi(maths);  // stoi() converts "85" → 85
//     count++;
// }

//     cout << "biology marks :";
//     cin  >> s1.biology;
//     if (biology != "N/A") {
//     total += stoi(biology);  // stoi() converts "85" → 85
//     count++;
// }

//     cout << "Computer Science marks :";
//     cin >> s1.compSci;
//     if (compSci != "N/A") {
//     total += stoi(compSci);  // stoi() converts "85" → 85
//     count++;
// }

//     cout << "English marks :";
//     cin  >> s1.english;
//     if (english != "N/A") {
//     total += stoi(english);  // stoi() converts "85" → 85
//     count++;
// }


    // calculate and display average score of students
    float avg =  static_cast<float>(total)/count
    //store everything in a clean table like formate with unique id's for easy retrieval
    

    return 0;
}