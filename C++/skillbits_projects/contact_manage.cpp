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
    "country code TEXT, "
    "phone TEXT);";

char* errMsg = nullptr;
result = sqlite3_exec(DB, createTableSQL, nullptr, nullptr, &errMsg);
if (result != SQLITE_OK) {
    std::cerr << "Error creating table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
}
    sqlite3_close(DB);


    return 0;
}