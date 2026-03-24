#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <sqlite3.h>

int main(void){
    // Enable UTF-8 output on Windows
    //this is to get hindi text in terminal
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF-8");
    //adding database
    sqlite3 *db = NULL;
    char *err = NULL;
    
    //opening DataBase FIRST
    if (sqlite3_open("atmdata.db", &db) != SQLITE_OK) {
        fprintf(stderr, "DB open error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    //checking if table exist
    const char *sql_create =
    "CREATE TABLE IF NOT EXISTS users ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "card_number INTEGER UNIQUE NOT NULL,"
    "pin TEXT NOT NULL,"
    "balance INTEGER DEFAULT 0);";
    if (sqlite3_exec(db, sql_create, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "Create table error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return 1;
    }
    
    //defining variables
    int user = 0;
    char choice1;
    char choice2;
    char choice3;
    char choice4;
    char choice5;
    char choice6;
    char choice7;
    char choice8;
    char choice9;
    char choice10;
    char choice11;
    char choice12;
    int  checkpin = 0;
    int  newPIN  = 0;
    int  OTP  = 0 ;
    int  mobile = 0;
    int  managepin =0;
    int  atmlimit = 0;
    int  POSlimit = 0;
    int  COMMlimit =0;
    int  LIMpin = 0;
    int  checkcard = 0;
    int  checkpinn = 0;
    int  newpinn  = 0;
    int pinn = 0;
    int cash = 0;
    int GenOtp = 0 ;
    // promting -> insert card details (6 digit int number)
    do{
        printf("Enter card details(last 6 digits):");
        // Check if scanf successfully read an integer
        if(scanf("%d",&user) != 1) {
            // Clear the input buffer by reading and discarding invalid characters
            while(getchar() != '\n');
            printf("Invalid input! Please enter card details\n");
            user = 0; // Reset user to invalid value to continue loop
            continue;
        }
    }
    while (user > 999999 || user < 100000);
    
    // Check if card exists in database
    sqlite3_stmt *stmt;
    int card_exists = 0;
    int user_id = 0;
    
    sqlite3_prepare_v2(db, "SELECT id FROM users WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, user);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        card_exists = 1;
        user_id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    
    // If card doesn't exist, reprompt
    while (!card_exists) {
        printf("Card not found in database. Please enter valid card details(last 6 digits):");
        if(scanf(" %d",&user) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter card details\n");
            user = 0;
            continue;
        }
        if (user > 999999 || user < 100000) {
            printf("Card must be 6 digits. Please try again.\n");
            continue;
        }
        
        // Check database again
        sqlite3_prepare_v2(db, "SELECT id FROM users WHERE card_number = ?;", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, user);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            card_exists = 1;
            user_id = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    // promt -> select language (hindi , english)
    printf("Select a language \n");
    printf("a: HINDI         b: ENGLISH ,\n");
    scanf(" %c",&choice1);
    // printf("आपने हिंदी चुना है");

    // promt -> a; manage debit card (will work on already existing database) b; enter atm pin c;set/generate ATM pin (can do random number generator)
    printf("  a: manage debit card  \n  b: enter atm pin \n  c: set/generate ATM pin \n");
    scanf(" %c", &choice2);

    //after selecting manage debit card
    if(choice2 == 'a'){
        printf("a: Manage channels \n b: Set card limits\n");
        scanf(" %c",&choice5);
        
        //manage channels
        if(choice5 == 'a'){
            printf("Enable or disable channels:\n");
            printf("a: ATM TRANSACTIONS\n");
            printf("b: POS (merchant machine)\n");
            printf("c: E-COMM (ONLINE/WEB)\n");
            printf("d: CONTACTLESS (NFC Tap)\n");
            scanf(" %c", &choice6);
            if(choice6 == 'a'){
                printf("ATM TRANSACTIONS\n");
                printf("A) ENABLE B)DESABLE \n");
                scanf(" %c",&choice7);
            }
            else if(choice6 == 'b'){
                printf("POS (merchant machine)\n");
                printf("A) ENABLE B)DESABLE \n");
                scanf(" %c",&choice8);
            }
            else if(choice6 == 'c'){
                printf("E-COMM (ONLINE/WEB)\n");
                printf("A) ENABLE B)DESABLE \n");
                scanf(" %c",&choice9);
            }
            else if(choice6 == 'd'){
                printf("CONTACTLESS (NFC Tap)\n");
                printf("A) ENABLE B)DESABLE \n");
                scanf(" %c",&choice10);
            }
            //ask for the pin
            printf("Please enter your ATM pin\n");
            scanf(" %d",&managepin);
            //compare with original pin
           // Validate PIN against database
            sqlite3_prepare_v2(db, "SELECT pin FROM users WHERE card_number = ?;", -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, user);  // user is the card number

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char *stored_pin = (const char*)sqlite3_column_text(stmt, 0);
                char entered_pin_str[10];
                sprintf(entered_pin_str, "%d", managepin);  // Convert int to string
                
                if (strcmp(entered_pin_str, stored_pin) != 0) {
                    printf("Invalid PIN! \n");
                    sqlite3_finalize(stmt);
                    sqlite3_close(db);
                    exit(1);
                }
            } else {
                printf("Card not found in database.\n");
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                exit(1);
            }
            sqlite3_finalize(stmt);

            // If PIN is correct, continue with the success message
            printf("please wait\n");
            sleep(10); 
            printf("your request has been processed successfully\n");
            exit(0);
        }
            
        //set card limits
        else if (choice5 == 'b'){
            //a) ATM  b)pos/ecom
            printf("a: ATM \n b: POS  \n  c: E-COMM \n");
            scanf(" %c",&choice11);
            if(choice11 == 'a'){
                printf("ATM Withdrawal\n");
                printf("Enter the desired Limit\n");
                scanf(" %d",&atmlimit);
            }
            else if(choice11 == 'b'){
                printf("POS\n");
                printf("Enter the desired Limit\n");
                scanf(" %d",&POSlimit);
                
            }
            else if(choice11 == 'c'){
                printf("E-COMM\n");
                printf("Enter the desired Limit\n");
                scanf(" %d",&COMMlimit);
                
            }
            printf("enter ATM pin\n");
            scanf(" %d",&LIMpin);
            //compare with original pin
            sqlite3_prepare_v2(db, "SELECT pin FROM users WHERE card_number = ?;", -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, user);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char *stored_pin = (const char*)sqlite3_column_text(stmt, 0);
                char entered_pin_str[10];
                sprintf(entered_pin_str, "%d", LIMpin);  // Convert int to string

                if (strcmp(entered_pin_str, stored_pin) != 0) {
                    printf("Invalid PIN!\n");
                    sqlite3_finalize(stmt);
                    sqlite3_close(db);
                    return 1;
                }
            } else {
                printf("Card not found in database.\n");
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }
            sqlite3_finalize(stmt);

            printf("Please wait\n");
            sleep(10);
            //if both pins are equal then this
            //prompt ->  your request has been processed successfully
            printf("your request has been processed successfully\n");
            // remove immediate exit to keep app context, or use menu loop
             exit(0);
        }
            

        
    }
    // after selecting enter atm pin
    else if(choice2 == 'b')
    // promt -> enter atm pin;
        {printf("Enter 4 digit pin :");
        scanf("%d",&pinn);
        // checking if the pin is correct
        sqlite3_prepare_v2(db, "SELECT pin FROM users WHERE card_number = ?;", -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, user);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char *stored_pin = (const char*)sqlite3_column_text(stmt, 0);
                char entered_pin_str[10];
                sprintf(entered_pin_str, "%d", pinn);  // Convert int to string

                if (strcmp(entered_pin_str, stored_pin) != 0) {
                    printf("Invalid PIN!\n");
                    sqlite3_finalize(stmt);
                    sqlite3_close(db);
                    return 1;
                }
            } else {
                printf("Card not found in database.\n");
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }
            sqlite3_finalize(stmt);

    // after entering correct pin 
    // a; change pin      b; fast cash
    // c; fund transfer   d; withdrawal
    // e; Mobile banking  f; balance enquiry
    //              g; exit
        printf("a: change pin           b: fast cash\n");
        printf("c: fund transfer        d: withdrawal\n");
        printf("e: Mobile banking       f: balance enquiry\n");
        printf("g: exit\n");
        scanf(" %c",&choice3);
        
        if (choice3 == 'b' || choice3 == 'd') {
            // promt -> select account type
            printf("Select account type :\n");
        
            printf(" a; savings  \n b; current  \n c; credit card \n");
            scanf(" %c", &choice4);
            // promt -> enter amount (in the multiple of 100)
            if (choice4 == 'a' || choice4 == 'b' || choice4 == 'c') {
                do {
                    printf("Enter amount : \n (* PLEASE ENTER IN MULTIPLE OF 100s):\n");
                    scanf("%d", &cash);
                    if (cash <= 0 || cash > 99999 || cash % 100 != 0) {
                        printf("Invalid amount! \n");
                    }
                } while (cash <= 0 || cash > 99999 || cash % 100 != 0);
            }
            // prompt -> please wait while your transaction is being processed 
            printf("please wait while your transaction is being processed\n");
            sleep(30);
            printf("please collect your cash\n");
            //update the balance after withdrawal in the database
            sqlite3_stmt *update_stmt;
            sqlite3_prepare_v2(db, "UPDATE users SET balance = balance - ? WHERE card_number = ?;", -1, &update_stmt, NULL);
            sqlite3_bind_int(update_stmt, 1, cash);
            sqlite3_bind_int(update_stmt, 2, user);
            if (sqlite3_step(update_stmt) != SQLITE_DONE) {
                printf("Error updating balance.\n");
            } else {
                printf("Transaction successful. Amount debited: Rs. %d\n", cash);
            }
            sqlite3_finalize(update_stmt);
        }
        else if(choice3 == 'a'){
            //ask for card and current pin
            printf("Enter last 6 digit of your card");
            scanf(" %d",&checkcard);
            printf("Enter 4 DIGIT ATM pin");
            scanf(" %d",&checkpinn);
            // validate both details
            sqlite3_prepare_v2(db,
                "SELECT pin FROM users WHERE card_number = ?;",-1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, checkcard);
            
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char *stored_pin = (const char*)sqlite3_column_text(stmt, 0);
                char entered_pin_str[10];
                sprintf(entered_pin_str, "%d", checkpinn);
                
                if (strcmp(entered_pin_str, stored_pin) != 0) {
                    printf("Card and PIN do not match.\n");
                    sqlite3_finalize(stmt);
                    // go back to menu or exit, your choice
                    return 1;
                }
            } else {
                printf("Card not found in database.\n");
                sqlite3_finalize(stmt);
                return 1;
            }
            sqlite3_finalize(stmt);
            
            printf("Card+PIN validated successfully.\n");
            //ask for new pin 
            printf("Enter new ATM pin");
            scanf(" %d",&newpinn);
            //update this new pin in the place of old pin in database
            sqlite3_stmt *update_stmt;
            sqlite3_prepare_v2(db, "UPDATE users SET pin = ? WHERE card_number = ?;", -1, &update_stmt, NULL);
            char new_pin_str[10];
            sprintf(new_pin_str, "%d", newpinn);
            sqlite3_bind_text(update_stmt, 1, new_pin_str, -1, SQLITE_STATIC);
            sqlite3_bind_int(update_stmt, 2, checkcard);
            if (sqlite3_step(update_stmt) != SQLITE_DONE) {
                printf("Error updating PIN.\n");
            } else {
                printf("PIN updated successfully.\n");
            }
            sqlite3_finalize(update_stmt);


        }
        else if( choice3 == 'c' || choice3 == 'e'){
            printf("these features is coming soon");
            exit(1);
        }
        else if(choice3 == 'f'){
            //display the amount from the database user section
            
                sqlite3_prepare_v2(db, "SELECT balance FROM users WHERE card_number = ?;", -1, &stmt, NULL);
                sqlite3_bind_int(stmt, 1, user);
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    int balance = sqlite3_column_int(stmt, 0);
                    printf("Your current balance is: Rs. %d\n", balance);
                } 
                sqlite3_finalize(stmt);
            
        }
        else if(choice3 == 'g'){
            exit(1);
        }
}           

else if(choice2 == 'c'){
    printf( "generate ATM pin\n");

    //for this we will use the random number generator to get a 4 digit number and save it to new card number
        printf("enter a valid mobile number\n");
        scanf(" %d",&mobile);
        //no real otp is send this is just a dummy
        printf("Enter OTP send to the mobile number\n");
        scanf(" %d",&OTP);

        //use random number generator to get a 4 digit pin and store it in the database
        printf("Please Wait\n");
        sleep(10);
        srand(time(0));
        int GenOtp = (rand() % 9000 + 1000);
        printf("This is your new PIN \n");
        printf(" %d" ,GenOtp );
        printf("\n");
        // update generated pin in database
        sqlite3_stmt *update_stmt;
        sqlite3_prepare_v2(db, "UPDATE users SET pin = ? WHERE card_number = ?;", -1, &update_stmt, NULL);
        char gen_pin_str[10];
        sprintf(gen_pin_str, "%d", GenOtp);
        sqlite3_bind_text(update_stmt, 1, gen_pin_str, -1, SQLITE_STATIC);
        sqlite3_bind_int(update_stmt, 2, user);
        if (sqlite3_step(update_stmt) != SQLITE_DONE) {
            printf("Error updating PIN.\n");
        } else {
            printf("PIN updated successfully.\n");
        }
        sqlite3_finalize(update_stmt);
    
}
    sqlite3_close(db);
    return 0;   
}