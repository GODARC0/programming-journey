// Build a program to manage student grades. Allow users
// to input student information ,including names and scores for
// multiple subjects, and calculate the average score of each student

#include <iostream>
#include <string>
#include <vector>
#include  <limits>
#include <iomanip>
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

char choice;
int main(){
    //need a storage to maintain students grades
    //get various user inputs 
    vector<Student> students;
    int idCounter = 0;
    bool isFirstStudent = true;
do{
    Student s1;
    std::cout << "Enter students full name: ";
    if (!isFirstStudent) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    isFirstStudent = false;
    std::getline(cin, s1.fullName);
    cout << "Note : if the student had not opted that subject please fill N/A in place of marks\n";
    
    
    s1.uid = ++idCounter;
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

    
    // calculate and display average score of students
    s1.avg =  static_cast<float>(total)/count;
    s1.percent = (static_cast<float>(total)/(count*80))*100;
    //store everything in a clean table like formate with unique id's for easy retrieval
    
    cout<<"Name :"<<s1.fullName<<"\n";
    cout<<"Avg marks :"<<s1.avg<<"\n";
    cout<<"percentage :"<<s1.percent<<"%\n";
    students.push_back(s1);
    
    
    cout<<"Add another student? (y/n): "<<"\n";
    cin>>choice;
    
}
while(choice == 'y');
    cout << setw(5) << "uid" << setw(15) << "fullName" << setw(10) << "physics" <<setw(10)<< "chemistry" <<setw(10)<< "biology" <<setw(10)<< "maths" <<setw(10)<< "compSci" <<setw(10)<< "english" <<setw(10)<< "avg" << setw(10)<< "%" <<setw(10)<< "\n";
for (Student s : students) {
    cout << setw(5) << s.uid << setw(15) << s.fullName << setw(10) << s.physics <<setw(10)<< s.chemistry <<setw(10)<< s.biology <<setw(10)<< s.maths <<setw(10)<< s.compSci <<setw(10)<< s.english <<setw(10)<< s.avg << setw(10)<< s.percent <<setw(10)<< "\n";
}



    return 0;
}