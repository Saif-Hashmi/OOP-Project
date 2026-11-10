# 🏦 Bank Account Management System (C++ OOP Final Project)

A console-based banking simulation written in **C++** that demonstrates the core pillars of Object-Oriented Programming: abstraction, encapsulation, inheritance and polymorphism. It models two kinds of bank accounts (Savings and Checking), each with its own business rules, and supports deposits, withdrawals, transfers, interest and account comparison.

---

## 📑 Table of Contents

- [Features](#-features)
- [OOP Concepts Demonstrated](#-oop-concepts-demonstrated)
- [Class Design](#-class-design)
- [Business Rules](#-business-rules)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Future Improvements](#-future-improvements)
- [Author](#-author)

---

## ✨ Features

- Create **Savings** and **Checking** accounts using default or parameterized constructors
- **Deposit** money, with an optional **bonus** deposit (overloaded `deposit`)
- **Withdraw** money with account-specific rules
- **Transfer** funds between any two accounts
- **Apply interest** to Savings accounts (also resets the monthly withdrawal counter)
- **Compare** accounts by balance using `>`, `<` and `==`
- Read an account from the keyboard and print it with the standard stream operators (`>>` and `<<`)
- Use accounts polymorphically through a base-class pointer

---

## 🧠 OOP Concepts Demonstrated

| Concept | Where it is used |
|---|---|
| **Abstraction** | `Account` is an abstract class with pure virtual functions (`deposit`, `withdraw`, `display`) |
| **Encapsulation** | Data members are `protected`/`private` and exposed through getters |
| **Inheritance** | `SavingsAccount` and `CheckingAccount` derive publicly from `Account` |
| **Polymorphism (runtime)** | An `Account*` pointer calls the correct derived-class `deposit`/`withdraw`/`display` through virtual functions |
| **Function overloading** | `deposit(amount)` and `deposit(amount, bonus)` |
| **Operator overloading** | `+` (deposit), `-` (withdraw), `>`, `<`, `==` (balance comparison), `<<` and `>>` (stream I/O) |
| **Friend functions** | `transfer()` and the stream operators access protected members of `Account` |
| **Static members** | `SavingsAccount::withdrawalLimit` and `SavingsAccount::interestRate` are shared by all savings accounts |
| **Constructors** | Default, parameterized (with default arguments) and copy constructors |
| **Destructors** | Defined for the base and derived classes |
| **Const-correctness** | Comparison operators and `getOverdraftLimit()` are `const` |

---

## 🧩 Class Design

```
                 ┌───────────────────────────┐
                 │     Account (abstract)    │
                 │───────────────────────────│
                 │ # AccountNumber : int     │
                 │ # HolderName    : string  │
                 │ # Balance       : double  │
                 │───────────────────────────│
                 │ + deposit(amount)     = 0 │
                 │ + deposit(amount,bonus)=0 │
                 │ + withdraw(amount)    = 0 │
                 │ + display()           = 0 │
                 │ + operator + , - , > , <, ==│
                 │ friend transfer(), >>, << │
                 └─────────────┬─────────────┘
                               │
              ┌────────────────┴────────────────┐
              │                                 │
┌─────────────┴─────────────┐     ┌─────────────┴─────────────┐
│       SavingsAccount      │     │      CheckingAccount      │
│───────────────────────────│     │───────────────────────────│
│ - withdrawalCount : int   │     │ - overdraftLimit : double │
│ - withdrawalLimit : static│     │───────────────────────────│
│ - interestRate    : static│     │ + withdraw() (overdraft)  │
│───────────────────────────│     │ + deposit() / bonus       │
│ + withdraw() (monthly cap)│     │ + display()               │
│ + deposit() / bonus       │     └───────────────────────────┘
│ + applyInterest()         │
│ + display()               │
└───────────────────────────┘
```

---

## 📋 Business Rules

### Savings Account
- Maximum **3 withdrawals per month** (`withdrawalLimit = 3`)
- Interest rate of **11%** (`interestRate = 0.11`)
- `applyInterest()` adds interest to the balance and **resets** the withdrawal counter to 0
- Withdrawals are rejected if the amount is negative or exceeds the balance

### Checking Account
- Default **overdraft limit of $500** (customizable per account)
- A withdrawal is allowed as long as `Balance + overdraftLimit >= amount`

### Transfers
- A transfer succeeds only if the amount is positive and the sender's balance covers it
- Internally it calls `withdraw()` on the sender and `deposit()` on the receiver, so each account type's own rules still apply

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler with C++11 support or newer (e.g. **g++**, **clang++**, or **MSVC**)

### Compile and run

```bash
# Clone the repository
git clone https://github.com/<your-username>/<your-repo-name>.git
cd <your-repo-name>

# Compile
g++ -std=c++11 OOP_Final_Project.cpp -o bank

# Run (Linux / macOS)
./bank

# Run (Windows)
bank.exe
```

You can also open the `.cpp` file in **Dev-C++**, **Code::Blocks** or **Visual Studio** and press *Build & Run*.

---

## 💻 Usage

When the program starts it:

1. Creates a Savings account for **Jacob** (#1001, balance $500).
2. Asks you to enter the details of a second Savings account from the keyboard (account number, holder name, balance).
3. Creates two Checking accounts, **Arthur** (#1003) and **Mark** (#1004, overdraft limit $600).
4. Displays all four accounts using the overloaded `<<` operator.
5. Runs a demo of the operations:
   - `deposit(100)` and `deposit(100, 100)` through a base-class pointer
   - a deposit using the `+` operator and a withdrawal using the `-` operator
   - a withdrawal with an invalid (negative) amount
   - a transfer from Savings to Checking
   - another withdrawal to demonstrate the monthly withdrawal counter
6. Applies interest to the Savings account and displays the final state.

### Sample input

```
Enter Account Number: 1002
Enter Account Holder Name: Benjamin
Enter Balance: 1000
```

---

## 📁 Project Structure

```
.
├── OOP_Final_Project.cpp   # Complete source code
└── README.md               # Project documentation
```

---

## 🔮 Future Improvements

- Menu-driven interface for interactive banking operations
- Store accounts in a container (e.g. `vector<Account*>`) and manage them dynamically
- File handling to save and load account data
- Transaction history for every account
- Exception handling instead of printed error messages
- Additional account types (e.g. Fixed Deposit, Student Account)

---

## 👤 Author

**Your Name**
- GitHub: [@your-username](https://github.com/your-username)

Developed as the Final Project for the **Object-Oriented Programming** course.

---

## 📄 License

This project is for educational purposes. Feel free to use and modify it with attribution.
