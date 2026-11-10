#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Account
{
	// Protected for access in derived classes
	protected:
		int AccountNumber;
		string HolderName;
		double Balance;

	public:

		// Default & Parameterized Constructor
		Account(int accNo = 0, string name = "", double bal = 0.0):
			AccountNumber(accNo), HolderName(name), Balance(bal) {}

		// Copy Constructor
		Account(const Account& obj):
			AccountNumber(obj.AccountNumber), HolderName(obj.HolderName), Balance(obj.Balance) {}

		// Virtual destructor (needed for safe polymorphic deletion)
		virtual ~Account() {}

		// Getters
		int getAccountNumber() const { return AccountNumber; }
		string getHolderName() const { return HolderName; }
		double getBalance() const { return Balance; }

		// Pure Virtual Functions
		virtual void deposit(double amount) = 0;
		virtual void deposit(double amount, double bonus) = 0;
		virtual bool withdraw(double amount) = 0;   // returns true if withdrawal succeeded
		virtual void display() = 0;

		// Friend Functions
		friend void transfer(Account& sender, Account& receiver, double amount);
		friend istream& operator >> (istream& i, Account& obj);
		friend ostream& operator << (ostream& o, Account& obj);

		// Operator Overloading
		Account& operator + (double amount) {
			deposit(amount);
			return *this;
		}
		Account& operator - (double amount) {
			withdraw(amount);
			return *this;
		}
		bool operator > (const Account& obj) const {
			return Balance > obj.Balance;
		}
		bool operator < (const Account& obj) const {
			return Balance < obj.Balance;
		}
		bool operator == (const Account& obj) const {
			return Balance == obj.Balance;
		}
};

// Overloaded Input Operator
istream& operator >> (istream& i, Account& obj) {
	cout << "\nEnter Account Number: ";
	i >> obj.AccountNumber;
	cout << "Enter Account Holder Name: ";
	i.ignore();
	getline(i, obj.HolderName);
	cout << "Enter Balance: ";
	i >> obj.Balance;
	return i;
}

// Overloaded Output Operator
ostream& operator << (ostream& o, Account& obj) {
	obj.display();
	return o;
}

// Friend Function For Transferring Funds
void transfer(Account& sender, Account& receiver, double amount) {
	if (amount > 0 && sender.Balance >= amount) {
		// Only deposit if the withdrawal really happened
		if (sender.withdraw(amount)) {
			receiver.deposit(amount);
			cout << "\nAmount $" << amount << " transferred from Account #" << sender.AccountNumber
			     << " to Account #" << receiver.AccountNumber;
		}
		else
			cout << "\nTransaction Failed! Withdrawal was not allowed for Account #" << sender.AccountNumber;
	}
	else
		cout << "\nTransaction Failed! No sufficient funds in account #" << sender.AccountNumber;
}

class SavingsAccount: public Account
{
	int withdrawalCount;
	static int withdrawalLimit;
	static double interestRate;

	public:

		// Constructor
		SavingsAccount(int accNo = 0, string n = "", double bal = 0.0, int count = 0):
			Account(accNo, n, bal), withdrawalCount(count) {}

		// Copy Constructor
		SavingsAccount(const SavingsAccount& obj):
			Account(obj), withdrawalCount(obj.withdrawalCount) {}

		int getWithdrawalCount() const { return withdrawalCount; }

		void deposit(double amount) {
			if (amount > 0) {
				Balance += amount;
				cout << "\nDeposited amount $" << amount << " to Savings Account #" << AccountNumber;
			}
		}

		void deposit(double amount, double bonus) {
			if (amount > 0 && bonus > 0) {
				Balance += (amount + bonus);
				cout << "\nDeposited Amount $" << amount << " and Bonus $" << bonus << " to Savings Account #" << AccountNumber;
			}
		}

		bool withdraw(double amount) {
			if (amount <= 0) {
				cout << "\nNot Possible because Amount must be greater than 0";
				return false;
			}
			if (withdrawalCount >= withdrawalLimit) {
				cout << "\nWithdrawal Limit reached for Savings Account #" << AccountNumber;
				return false;
			}
			if (amount <= Balance) {
				Balance -= amount;
				withdrawalCount++;
				cout << "\nWithdrew Amount $" << amount << " from Savings Account #" << AccountNumber;
				return true;
			}
			cout << "\nWithdrawal failed! No sufficient funds in the Savings Account #" << AccountNumber;
			return false;
		}

		void display() {
			cout << "\nSavings Account: #" << AccountNumber << "\nAccount Holder Name: " << HolderName;
			cout << "\nBalance: $" << fixed << setprecision(2) << Balance
			     << "\nWithdrawal Count this month: " << withdrawalCount;
		}

		void applyInterest() {
			double interest = Balance * interestRate;
			Balance += interest;
			cout << "\nInterest of $" << fixed << setprecision(2) << interest
			     << " applied to Savings Account #" << AccountNumber;
			withdrawalCount = 0;
		}

		~SavingsAccount() {}
};

// Static Members Initialization
int SavingsAccount::withdrawalLimit = 3;
double SavingsAccount::interestRate = 0.11;

class CheckingAccount: public Account
{
	double overdraftLimit;

	public:

		// Default & Parameterized Constructor
		CheckingAccount(int accNo = 0, string n = "", double bal = 0.0, double limit = 500.0):
			Account(accNo, n, bal), overdraftLimit(limit) {}

		// Copy Constructor
		CheckingAccount(const CheckingAccount& obj):
			Account(obj), overdraftLimit(obj.overdraftLimit) {}

		double getOverdraftLimit() const { return overdraftLimit; }

		void display() {
			cout << "\nChecking Account: #" << AccountNumber << "\nName: " << HolderName
			     << "\nBalance: $" << fixed << setprecision(2) << Balance;
			cout << "\nOverdraft Limit: $" << overdraftLimit;
		}

		bool withdraw(double amount) {
			if (amount > 0 && (Balance + overdraftLimit) >= amount) {
				Balance -= amount;
				cout << "\nWithdrew Amount $" << amount << " from Checking Account #" << AccountNumber;
				return true;
			}
			cout << "\nOverdraft Limit exceeded for Checking Account #" << AccountNumber;
			return false;
		}

		void deposit(double amount) {
			if (amount > 0) {
				Balance += amount;
				cout << "\nDeposited Amount $" << amount << " to Checking Account #" << AccountNumber;
			}
		}

		void deposit(double amount, double bonus) {
			if (amount > 0 && bonus > 0) {
				Balance += (amount + bonus);
				cout << "\nDeposited Amount $" << amount << " + Bonus $" << bonus << " to Checking Account #" << AccountNumber;
			}
		}

		~CheckingAccount() {}
};

int main()
{
	SavingsAccount S1(1001, "Jacob", 500);
//	SavingsAccount S2(1002, "Benjamin", 1000);
//	SavingsAccount S3 = S2;                // Copy Constructor used

	SavingsAccount S2;
	cin >> S2;                             // Used Overloaded Cin Operator

	CheckingAccount C1(1003, "Arthur", 500), C2(1004, "Mark", 1000, 600);

	Account* A1;
	A1 = &S1;

//	cout << "\nChecking Account Number: " << C1.getAccountNumber() << "\nAccount Holder Name: ";
//	cout << C1.getHolderName() << "\nBalance: " << C1.getBalance();

	cout << S1 << endl << S2 << endl << C1 << endl << C2 << endl;   // Overloaded Cout is Used

	A1->deposit(100);                      // Calling derived methods using base class pointers
	A1->deposit(100, 100);                 // Deposit with Bonus
	*A1 + 100;                             // Deposit using + operator

	A1->withdraw(-100);                    // Invalid amount (not counted)
	S1 - 30;                               // Withdraw 1 using - operator
	transfer(S1, C1, 300);                 // Withdraw 2 (through transfer)

	S1.withdraw(40);                       // Withdraw 3 (limit now reached)
	S1.withdraw(20);                       // Rejected: withdrawal limit reached
	cout << endl;

	S1.display();
	cout << endl;

	C1.display();
	cout << endl;

	// Overloaded Operators

	if (C1 > C2) {
		cout << "\n#" << C1.getAccountNumber() << " has more balance than Account #" << C2.getAccountNumber();
	}
	if (C1 < C2) {
		cout << "\n#" << C1.getAccountNumber() << " has less balance than Account #" << C2.getAccountNumber();
	}
	if (C1 == C2) {
		cout << "\n#" << C1.getAccountNumber() << " has equal balance to Account #" << C2.getAccountNumber();
	}

	S1.applyInterest();                    // Applying Interest Rate

	cout << endl << S1 << "\n\n";          // Display

	// No delete: A1 points to a stack object (S1), which is destroyed automatically.

	return 0;
}
