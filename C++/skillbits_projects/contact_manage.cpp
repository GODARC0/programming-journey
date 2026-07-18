// create a program that manages a list of contacts. users
// should be able to add, update, delete and view contact information.
#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
using namespace std;

int main(){
    //for storing contacts i had 2 options one with stings of json code and other was sqlite
    //im going to use sqlite because im more familiar with that 
    sqlite3* DB;

    int result = sqlite3_open("my_database.db", &DB);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database!" << std::endl;
        return 1; 
    }
    std::cout << "Database opened/created successfully!" << std::endl;
    const char* createTableSQL = 
    "CREATE TABLE IF NOT EXISTS contacts ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "name TEXT NOT NULL, "
    "country_code TEXT, "
    "phone TEXT);";


while(input != 5){
    char* errMsg = nullptr;
result = sqlite3_exec(DB, createTableSQL, nullptr, nullptr, &errMsg);
if (result != SQLITE_OK) {
    std::cerr << "Error creating table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
}

cout<<"\n=== Contact Manager ===\n"
         << "1. Add contact\n"
         << "2. View contacts\n"
         << "3. Update contact\n"
         << "4. Delete contact\n"
         << "5. Exit\n"
         << "Choose an option: ";
    
    
cin>> input >> "\n";

int input = 1;

switch (light){
    case 1 :
        cout<<"Add contact";
        break;

    case 2 :
        cout <<"View contacts";
        break;

    case 3:
        cout << "Update contact";
        break;

    case 4 :
        cout << "Delete contacts";
        break;
}
         sqlite3_close(DB);



}


    return 0;
}