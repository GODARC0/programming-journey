#include <stdio.h>
#include <string.h>


int main(void){
    //defining variables
    int user = 0;
    char choice1;
    char choice2;
    // promting -> insert card details (6 digit int number)
    do{
        printf("Enter card details(last 6 digits):");
        scanf("%d",&user);
    }
    while (user>999999 || user<99999);
    // promt -> select language (hindi , english)

    printf("Select a language \n");
    printf("a: HINDI         b: ENGLISH ,\n");

    scanf(" %c",&choice1);

    // promt -> a; manage debit card (will work on already existing database) b; enter atm pin c;set/generate ATM pin (can do random number generator)
    printf("  a: manage debit card  \n  b: enter atm pin \n  c: set/generate ATM pin \n");
    scanf(" %c", &choice2);

    
    // after selecting enter atm pin 
    // promt -> enter atm pin;
    // after entering correct pin 
    // a; change pin      b; fast cash
    // c; fund transfer   d; withdrawal
    // e; Mobile banking  f; balance enquiry
    //              g; exit
    // promt -> select account type
    // a; savings 
    // b; current 
    // c; credit card

    // promt -> enter amount (in the multiple of 100)
    // allow upto 5 digit in amount in int format
    // enter

    // prompt -> please wait while your transaction is being processed 
    // after 1 min 
    // prompt  -> please collect your cash 
    return 0;   
}