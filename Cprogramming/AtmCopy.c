#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void){
    //defining variables
    int user = 0;
    char choice1;
    char choice2;
    char choice3;
    char choice4;
    int pin = 0;
    int cash = 0;
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
    if(choice2 == 'b')
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
}


    // prompt -> please wait while your transaction is being processed 
    printf("please wait while your transaction is being processed\n");
    // after 1 min 
    sleep(30);
    // prompt  -> please collect your cash 
    printf("please collect your cash\n");
    return 0;   
}