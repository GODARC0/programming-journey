#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <sqlite3.h>

/* ─────────────────────────────────────────────
   HELPER FUNCTIONS
   ───────────────────────────────────────────── */

/* Validates PIN for a given card number against the DB.
   Returns 1 if valid, 0 otherwise. */
int validate_pin(sqlite3 *db, int card, int pin) {
    sqlite3_stmt *stmt;
    int valid = 0;

    sqlite3_prepare_v2(db, "SELECT pin FROM users WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, card);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *stored_pin = (const char *)sqlite3_column_text(stmt, 0);
        char entered_str[10];
        sprintf(entered_str, "%d", pin);
        valid = (strcmp(entered_str, stored_pin) == 0);
    }
    sqlite3_finalize(stmt);
    return valid;
}

/* Returns 1 if a row exists in `table` for `card_number`, else 0. */
int row_exists(sqlite3 *db, const char *table, int card) {
    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "SELECT card_number FROM %s WHERE card_number = ?;", table);

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, card);

    int exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

/* Inserts a default row into `table` for `card_number`. */
void insert_default_row(sqlite3 *db, const char *table, int card) {
    sqlite3_stmt *stmt;
    char sql[100];
    sprintf(sql, "INSERT INTO %s (card_number) VALUES (?);", table);

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, card);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

/* Simulates processing delay then prints success. */
void process_and_confirm(int delay_secs) {
    printf("Please wait...\n");
    sleep(delay_secs);
    printf("Your request has been processed successfully.\n");
}

/* ─────────────────────────────────────────────
   FEATURE FUNCTIONS
   ───────────────────────────────────────────── */

/* Handles channel enable/disable under "Manage Debit Card > Manage Channels" */
void manage_channels(sqlite3 *db, int card) {
    char choice, enable_choice;

    printf("Enable or disable channels:\n");
    printf("a: ATM TRANSACTIONS\n");
    printf("b: POS (merchant machine)\n");
    printf("c: E-COMM (ONLINE/WEB)\n");
    printf("d: CONTACTLESS (NFC Tap)\n");
    scanf(" %c", &choice);

    const char *channel_names[] = {
        "ATM TRANSACTIONS", "POS (merchant machine)",
        "E-COMM (ONLINE/WEB)", "CONTACTLESS (NFC Tap)"
    };
    const char *columns[] = {"ATM_transc", "POS", "E_COMM", "NFC"};

    int idx = -1;
    if      (choice == 'a') idx = 0;
    else if (choice == 'b') idx = 1;
    else if (choice == 'c') idx = 2;
    else if (choice == 'd') idx = 3;
    else { printf("Invalid choice!\n"); return; }

    printf("%s\nA) ENABLE  B) DISABLE\n", channel_names[idx]);
    scanf(" %c", &enable_choice);

    printf("Please enter your ATM pin: ");
    int pin;
    scanf(" %d", &pin);

    if (!validate_pin(db, card, pin)) {
        printf("Invalid PIN!\n");
        return;
    }

    if (!row_exists(db, "channels", card))
        insert_default_row(db, "channels", card);

    int status = (enable_choice == 'A' || enable_choice == 'a') ? 1 : 0;

    char update_sql[100];
    sprintf(update_sql, "UPDATE channels SET %s = ? WHERE card_number = ?;", columns[idx]);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, update_sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, status);
    sqlite3_bind_int(stmt, 2, card);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error updating channel.\n");
    else
        process_and_confirm(10);

    sqlite3_finalize(stmt);
}

/* Handles transaction limit setting under "Manage Debit Card > Set Card Limits" */
void set_card_limits(sqlite3 *db, int card) {
    char choice;

    printf("a: ATM\nb: POS\nc: E-COMM\n");
    scanf(" %c", &choice);

    const char *columns[] = {"ATMlim", "POSlim", "E_COMMlim"};
    const char *labels[]  = {"ATM Withdrawal", "POS", "E-COMM"};

    int idx = -1;
    if      (choice == 'a') idx = 0;
    else if (choice == 'b') idx = 1;
    else if (choice == 'c') idx = 2;
    else { printf("Invalid choice!\n"); return; }

    printf("%s\nEnter the desired limit: ", labels[idx]);
    int limit;
    scanf(" %d", &limit);

    printf("Enter ATM pin: ");
    int pin;
    scanf(" %d", &pin);

    if (!validate_pin(db, card, pin)) {
        printf("Invalid PIN!\n");
        return;
    }

    if (!row_exists(db, "limits", card))
        insert_default_row(db, "limits", card);

    char update_sql[100];
    sprintf(update_sql, "UPDATE limits SET %s = ? WHERE card_number = ?;", columns[idx]);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, update_sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, limit);
    sqlite3_bind_int(stmt, 2, card);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error updating limit.\n");
    else
        process_and_confirm(10);

    sqlite3_finalize(stmt);
}

/* Handles cash withdrawal (fast cash and regular withdrawal share same logic) */
void handle_withdrawal(sqlite3 *db, int card) {
    char acct_choice;
    printf("Select account type:\na: Savings\nb: Current\nc: Credit Card\n");
    scanf(" %c", &acct_choice);

    if (acct_choice != 'a' && acct_choice != 'b' && acct_choice != 'c') {
        printf("Invalid choice!\n");
        return;
    }

    int cash;
    do {
        printf("Enter amount (* PLEASE ENTER IN MULTIPLES OF 100):\n");
        scanf(" %d", &cash);
        if (cash <= 0 || cash > 9999999 || cash % 100 != 0)
            printf("Invalid amount!\n");
    } while (cash <= 0 || cash > 9999999 || cash % 100 != 0);

    /* Check balance */
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT balance FROM users WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, card);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int balance = sqlite3_column_int(stmt, 0);
        if (cash > balance) {
            printf("Insufficient balance! Available balance: Rs. %d\n", balance);
            sqlite3_finalize(stmt);
            return;
        }
    } else {
        printf("Could not retrieve balance.\n");
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    printf("Please wait while your transaction is being processed...\n");
    sleep(30);
    printf("Please collect your cash.\n");

    /* Deduct balance */
    sqlite3_prepare_v2(db,
        "UPDATE users SET balance = balance - ? WHERE card_number = ?;",
        -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, cash);
    sqlite3_bind_int(stmt, 2, card);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error updating balance.\n");
    else
        printf("Transaction successful. Amount debited: Rs. %d\n", cash);

    sqlite3_finalize(stmt);
}

/* Handles PIN change */
void change_pin(sqlite3 *db) {
    printf("Enter last 6 digits of your card: ");
    int card;
    scanf(" %d", &card);

    printf("Enter current 4-digit ATM pin: ");
    int old_pin;
    scanf(" %d", &old_pin);

    if (!validate_pin(db, card, old_pin)) {
        printf("Card and PIN do not match.\n");
        return;
    }
    printf("Card + PIN validated successfully.\n");

    printf("Enter new 4-digit ATM pin: ");
    int new_pin;
    scanf(" %d", &new_pin);

    if (new_pin < 1000 || new_pin > 9999) {
        printf("PIN must be exactly 4 digits!\n");
        return;
    }

    char new_pin_str[10];
    sprintf(new_pin_str, "%d", new_pin);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "UPDATE users SET pin = ? WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, new_pin_str, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, card);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error updating PIN.\n");
    else
        printf("PIN updated successfully.\n");

    sqlite3_finalize(stmt);
}

/* Handles balance enquiry */
void balance_enquiry(sqlite3 *db, int card) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT balance FROM users WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, card);

    if (sqlite3_step(stmt) == SQLITE_ROW)
        printf("Your current balance is: Rs. %d\n", sqlite3_column_int(stmt, 0));

    sqlite3_finalize(stmt);
}

/* Generates and saves a new random PIN */
void generate_pin(sqlite3 *db, int card) {
    long long mobile;
    int otp;

    printf("Enter a valid mobile number: ");
    scanf(" %lld", &mobile);
    printf("Enter OTP sent to the mobile number: ");
    scanf(" %d", &otp);

    /* OTP is a dummy — no real verification */
    printf("Please wait...\n");
    sleep(10);

    srand(time(0));
    int new_pin = rand() % 9000 + 1000;
    printf("This is your new PIN: %d\n", new_pin);

    char pin_str[10];
    sprintf(pin_str, "%d", new_pin);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "UPDATE users SET pin = ? WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pin_str, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, card);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        printf("Error updating PIN.\n");
    else
        printf("PIN updated successfully.\n");

    sqlite3_finalize(stmt);
}

/* 
   MAIN
 */

int main(void) {
    /* Enable UTF-8 output on Windows (for Hindi text in terminal) */
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF-8");

    /* Open database */
    sqlite3 *db = NULL;
    char *err = NULL;

    if (sqlite3_open("atmdata.db", &db) != SQLITE_OK) {
        fprintf(stderr, "DB open error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /* Create tables if they don't exist */
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

    /* ── Card Entry ── */
    int user = 0;
    do {
        printf("Enter card details (last 6 digits): ");
        if (scanf("%d", &user) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter card details.\n");
            user = 0;
            continue;
        }
    } while (user > 999999 || user < 100000);

    /* Validate card against DB */
    sqlite3_stmt *stmt;
    int card_exists = 0;

    sqlite3_prepare_v2(db, "SELECT id FROM users WHERE card_number = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, user);
    card_exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    while (!card_exists) {
        printf("Card not found. Please enter valid card details (last 6 digits): ");
        if (scanf(" %d", &user) != 1) {
            while (getchar() != '\n');
            printf("Invalid input!\n");
            user = 0;
            continue;
        }
        if (user > 999999 || user < 100000) {
            printf("Card must be 6 digits. Try again.\n");
            continue;
        }
        sqlite3_prepare_v2(db, "SELECT id FROM users WHERE card_number = ?;", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, user);
        card_exists = (sqlite3_step(stmt) == SQLITE_ROW);
        sqlite3_finalize(stmt);
    }

    /* ── Language Selection ── */
    char choice;
    printf("Select a language:\na: HINDI   b: ENGLISH\n");
    scanf(" %c", &choice);

    if (choice == 'a') {
        printf("This section will be introduced in the future.\n");
        sqlite3_close(db);
        return 0;
    }

    /* ── Main Menu ── */
    printf("\na: Manage Debit Card\nb: Enter ATM Pin\nc: Set/Generate ATM Pin\n");
    scanf(" %c", &choice);

    if (choice == 'a') {
        /* ── Manage Debit Card ── */
        char sub;
        printf("a: Manage Channels\nb: Set Card Limits\n");
        scanf(" %c", &sub);

        if      (sub == 'a') manage_channels(db, user);
        else if (sub == 'b') set_card_limits(db, user);
        else                 printf("Invalid choice!\n");
    }
    else if (choice == 'b') {
        /* ── Enter ATM Pin ── */
        printf("Enter 4-digit PIN: ");
        int pin;
        scanf("%d", &pin);

        if (!validate_pin(db, user, pin)) {
            printf("Invalid PIN!\n");
            sqlite3_close(db);
            return 1;
        }

        /* ── Post-login Menu ── */
        printf("\na: Change PIN           b: Fast Cash\n");
        printf("c: Fund Transfer        d: Withdrawal\n");
        printf("e: Mobile Banking       f: Balance Enquiry\n");
        printf("g: Exit\n");
        scanf(" %c", &choice);

        if      (choice == 'b' || choice == 'd') handle_withdrawal(db, user);
        else if (choice == 'a')                  change_pin(db);
        else if (choice == 'f')                  balance_enquiry(db, user);
        else if (choice == 'c' || choice == 'e') printf("This feature is coming soon.\n");
        else if (choice == 'g')                  printf("Goodbye!\n");
        else                                     printf("Invalid choice!\n");
    }
    else if (choice == 'c') {
        /* ── Generate PIN ── */
        generate_pin(db, user);
    }
    else {
        printf("Invalid choice!\n");
    }

    sqlite3_close(db);
    return 0;
}