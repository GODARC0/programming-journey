#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
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
    int  managepin =0;
    int  atmlimit = 0;
    int  POSlimit = 0;
    int  COMMlimit =0;
    int  ATMpin = 0;
    int  POSpin = 0;
    int  COMMpin = 0;
    int pin = 0;
    int cash = 0;
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
    // promt -> select language (hindi , english)

    printf("Select a language \n");
    printf("a: HINDI         b: ENGLISH ,\n");

    scanf(" %c",&choice1);

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
            printf("please wait\n");
            sleep(10); 
            // if both pins are same then this
            //prompt ->  your request has been processed successfully
            printf("your request has been processed successfully\n");
            // if both pins are not same then prompt error
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
                printf("enter ATM pin\n");
                scanf(" %d",&ATMpin);
            }
            else if(choice11 == 'b'){
                printf("POS\n");
                printf("Enter the desired Limit\n");
                scanf(" %d",&POSlimit);
                printf("enter ATM pin\n");
                scanf(" %d",&POSpin);
            }
            else if(choice11 == 'c'){
                printf("E-COMM\n");
                printf("Enter the desired Limit\n");
                scanf(" %d",&COMMlimit);
                printf("enter ATM pin\n");
                scanf(" %d",&COMMpin);
                
            }
             //compare with original pin
             printf("Please wait\n");
            sleep(10); 
            //if both pins are equal then this
            //prompt ->  your request has been processed successfully
            printf("your request has been processed successfully");
            //if both pins are not same the show error
            exit(0);   
        }
            

        
    }
    // after selecting enter atm pin
    else if(choice2 == 'b')
    // promt -> enter atm pin;
        {printf("Enter 4 digit pin :");
        scanf("%d",&pin);
        // printf("%d",pin);
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
        // promt -> select account type
        printf("Select account type :\n");

        printf(" a; savings  \n b; current  \n c; credit card \n");
        scanf(" %c",&choice4);
         // promt -> enter amount (in the multiple of 100)
        if(choice4 == 'a' || choice4 == 'b' || choice4 == 'c' ){
            do {
                printf("Enter amount : \n (* PLEASE ENTER IN MULTIPLE OF 100s):\n");
                // allow upto 5 digit in amount in int format
                scanf("%d",&cash);
                // allow upto 5 digit in amount in int format
                // enter
                if (cash <= 0 || cash > 99999 || cash % 100 != 0) {
                    printf("Invalid amount! \n");
                }
            } while (cash <= 0 || cash > 99999 || cash % 100 != 0);

    };
    // prompt -> please wait while your transaction is being processed 
    printf("please wait while your transaction is being processed\n");
    // after 1 min 
    sleep(30);
    // prompt  -> please collect your cash 
    printf("please collect your cash\n");
}

if(choice2 == 'c'){
    printf("a: update ATM pin \n  b:  generate ATM pin")
    // for option A pin will be updated in the database
    //for option B we will use the random number generator to get a 4 digit number and save it to new card number
}
    
    return 0;   
}