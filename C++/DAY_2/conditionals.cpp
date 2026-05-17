#include <iostream>
using namespace std;

int main () {
    //first condition code

    int n = -34;
    if (n >= 0){
        cout << "n is positive"<<"\n";
    }
    else{
        cout<< "n is negative"<<"\n";
    }


    //can you vote??
    
    int age;
        cout<<"enter your age:";
        cin>> age;

        if (age>>18){
            cout<<"yes you can vote "<<"\n";
        }
        else{
            cout<<"no you can not vote"<<"\n";
        }



        //3 conditions, marks batao
        int num;
        cout<<"kitne number ayein hai? ";
        cin>>num;
        
        if (num >=90){
            cout<<"shabbash.";
        }
        else if (num >=80 && num < 90){
            cout<<"aur mehnat karo .";
        }
        else{
            cout<<"aaj khana nahi milega.";
        }

        
        //identify upper and lower case
        char ch;
        cout<<"enter a character: ";
        cin>>ch;

        if(ch>='a'  && ch<='z' ){ // we can also use ascaii value of  these jise implicit type conversion kahenge
            cout<<"character is in lowercase"<<"\n";

        }
        else{
            cout<<"character is in uppercase"<<"\n";
        }
    return 0;

}