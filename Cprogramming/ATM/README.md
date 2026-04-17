#  ATM Simulation (C + SQLite)

A terminal-based ATM simulation written in C, backed by an SQLite database. Built incrementally as a personal project — covers the core flows you'd expect from a real ATM: card validation, PIN management, withdrawals, and card settings.

---

##  Project Structure

```
.
├── AtmCopy.c        # Original build — written feature by feature, everything in main()
├── CleanAtm.c      # Refactored version — same logic, split into helper/feature functions
└── atmdata.db       # SQLite database (auto-created on first run)
```

Both files do **exactly the same thing**. `AtmCopy.c` is the original, grown organically over time. `CleanAtm.c` is a cleaner rewrite using functions — same brain, better structure.

---

##  Features

### Currently Working
- **Card Validation** — Accepts last 6 digits of card number; checks against DB
- **Language Selection** — English supported; Hindi placeholder (coming soon)
- **Enter ATM PIN** — Validates against hashed/stored PIN in database
  - **Balance Enquiry** — Displays current account balance
  - **Withdrawal / Fast Cash** — Amount in multiples of ₹100; balance check before debit
  - **Change PIN** — Validates old card + PIN before allowing update
- **Manage Debit Card**
  - **Manage Channels** — Enable/Disable: ATM, POS, E-COMM, NFC/Contactless
  - **Set Card Limits** — Set transaction limits for ATM, POS, E-COMM
- **Generate/Set PIN** — Random 4-digit PIN generator via dummy OTP flow

### Coming Soon
-  Hindi language support
-  Mobile Banking
-  Fund Transfer
-  Real OTP verification (currently a dummy flow)
-  Transaction history / mini statement

---

##  Database Schema

The program auto-creates `atmdata.db` with the following tables:

**`users`** — Core account data
| Column | Type | Notes |
|---|---|---|
| id | INTEGER | Primary key, auto-increment |
| card_number | INTEGER | Last 6 digits, unique |
| pin | TEXT | Stored as string |
| balance | INTEGER | Default 0 |

**`channels`** — Channel on/off flags per card
| Column | Notes |
|---|---|
| card_number | Foreign reference to users |
| ATM_transc, POS, E_COMM, NFC | 1 = enabled, 0 = disabled |

**`limits`** — Transaction limits per card
| Column | Notes |
|---|---|
| card_number | Foreign reference to users |
| ATMlim, POSlim, E_COMMlim | Integer limits in ₹ |

> You'll need to manually insert test users into `users` before running — no registration flow yet.

---

##  Build & Run

**Dependencies:** GCC, SQLite3

```bash
# Install SQLite dev library (if not already)
sudo apt install libsqlite3-dev   # Linux
# or link manually on Windows with sqlite3.h + sqlite3.c

# Compile (raw version)
gcc AtmCopy.c -o atm_raw -lsqlite3

# Compile (clean version)
gcc CleanAtm.c -o atm_clean -lsqlite3

# Run
./AtmCopy
```

> **Windows note:** The code uses `SetConsoleCP(65001)` for UTF-8/Hindi terminal support. Compile with MinGW and link against `sqlite3.dll`.

---

##  Why Two Files?

`AtmCopy.c` is the real project — every feature was added one at a time as it was learned and built. It's messy in places, but it works and it's honest.

`CleanAtm.c` came after, as a refactoring exercise. Same logic, but helper functions like `validate_pin()`, `row_exists()`, and `process_and_confirm()` reduce repetition and make the code easier to read and extend.

Both are kept here intentionally — the raw version shows the process, the clean version shows the result.

---

##  Notes

- Sleep delays (`sleep(10)`, `sleep(30)`) are intentional — simulating real ATM processing time
- OTP generation is **not real** — a random number is generated locally, no SMS sent
- No encryption on PINs currently — planned improvement

---

*Built as a personal C project. Feedback welcome.*
