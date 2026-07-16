// Build a program to manage student grades. Allow users
// to input student information ,including names and scores for
// multiple subjects, and calculate the average score of each student

#include <iostream>
#include <string>
#include <vector>
#include  <limits>
using namespace std;
    
struct Student {
    int uid;
    float physics;
    float chemistry;
    float maths;
    float biology;
    float compSci;
    float english;
    std::string fullName;
    float avg;
    float percent;
};
int main(){
    //need a storage to maintain students grades
    //get various user inputs 
    vector<Student> students;
do{
    Student s1;
    std::cout << "Enter students full name: ";
    
    std::getline(cin, s1.fullName);
    cout << "Note : if the student had not opted that subject please fill N/A in place of marks\n";
    
    int total = 0;
    int count = 0;
    std::string temp;
    cout << "physics marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.physics = stoi(temp);
        total += s1.physics ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.physics = -1;
    }
    cout << "chemistry marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.chemistry = stoi(temp);
        total += s1.chemistry ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.chemistry = -1;
    }

    cout << "maths marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.maths = stoi(temp);
        total += s1.maths ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.maths = -1;
    }

    cout << "biology marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.biology = stoi(temp);
        total += s1.biology ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.biology = -1;
    }
    cout << "computer science marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.compSci = stoi(temp);
        total += s1.compSci ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.compSci = -1;
    }

    cout << "english marks :";
    cin >> temp;
    if (temp != "N/A" ) {
        s1.english = stoi(temp);
        total += s1.english ;  // stoi() converts "85" → 85
        count++;
    }
    else{
        s1.english = -1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // calculate and display average score of students
    s1.avg =  static_cast<float>(total)/count;
    s1.percent = (static_cast<float>(total)/(count*80))*100;
    //store everything in a clean table like formate with unique id's for easy retrieval
    
    cout<<"Name :"<<s1.fullName<<"\n";
    cout<<"Avg marks :"<<s1.avg<<"\n";
    cout<<"percentage :"<<s1.percent<<"%\n";
    students.push_back(s1);
    
    continue ;
}
while(//ask after every loop "add student and continue if the input is Y and exit if input is N")
    return 0;
}