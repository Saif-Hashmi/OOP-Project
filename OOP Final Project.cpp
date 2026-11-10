#include <iostream>
#include <iomanip>
using namespace std;

class Account
{
	//Protected for access in derived classes
	protected:    
	int AccountNumber;
	string HolderName;
	double Balance;
	
	public:
		
		//Default & Parameterized Constructor
		Account(int accNo=0, string name="" ,double bal=0.0):
			AccountNumber(accNo), HolderName(name),Balance(bal) {}
		
		//Copy Constructor
		Account(const Account& obj):
			AccountNumber(obj.AccountNumber), HolderName(obj.HolderName), Balance(obj.Balance){}
		
		~Account(){}
		
		//Getters
		int getAccountNumber(){ return AccountNumber; }
		string getHolderName(){ return HolderName; }
		double getBalance(){ return Balance; }
		
		//Pure Virtual Functions
		virtual void deposit(double amount)=0;
		virtual void deposit(double amount, double bonus)=0;
		virtual void withdraw(double amount)=0;
		virtual void display()=0;
		
		//Friend Functions
		friend void transfer(Account& sender, Account& receiver, double amount);
		friend istream& cin  (istream& i, Account& obj);
		friend ostream& cout << (ostream& i, Account& obj);
		
		//Operator Overloading
		Account& operator + (double amount){
			deposit(amount);
			return *this;
		}
		Account& operator - (double amount){
			withdraw(amount);
			return *this;
		}
		bool operator > (const Account& obj) const {
			return Balance>obj.Balance;
		}
		bool operator < (const Account& obj) const {
			return Balance<obj.Balance;
		}
		bool operator == (const Account& obj) const {
			return Balance==obj.Balance;
		}
};

istream& operator  (istream& i, Account& obj){
	cout<<"\nEnter Account Number: ";
	i>>obj.AccountNumber;
	cout<<"Enter Account Holder Name: ";
	cin.ignore();
	getline(i,obj.HolderName);
	cout<<"Enter Balance: ";
	i>>obj.Balance;
	return i;
}

ostream& operator << (ostream& i, Account& obj){
	obj.display();
	return i;
}

//Friend Function For Transferring Funds
void transfer(Account& sender, Account& receiver, double amount){
	if(amount>0 && sender.Balance>=amount){
		sender.withdraw(amount);
		receiver.deposit(amount);
		cout<<"\nAmount $"<<amount<<" transferred from Account #"<<sender.AccountNumber<<" to Account #"<<receiver.AccountNumber;
	}
	else
		cout<<"\nTransaction Failed! No sufficient funds in account #"<<sender.HolderName;
}

class SavingsAccount: public Account
{
	int withdrawalCount;
	static int withdrawalLimit;
	static double interestRate;
	
	public:
		
		//Constructor
		SavingsAccount(int accNo=0, string n="", double bal=0.0, int count=0):
			Account(accNo, n, bal), withdrawalCount(count) {}
		
		//Copy Constructor
		SavingsAccount(const SavingsAccount& obj):
			Account(obj), withdrawalCount(obj.withdrawalCount) {}
		
		int getWithdrawalCount() { return withdrawalCount; }
		
		void deposit(double amount){
			if(amount>0){
				Balance += amount;
				cout<<"\nDeposited amount $"<<amount<<" to Savings Account #"<<AccountNumber;
			}
		}
		
		void deposit(double amount, double bonus){
			if(amount>0 && bonus>0){
				Balance += (amount+bonus);
				cout<<"\nDeposited Amount $"<<amount<<" and Bonus $"<<bonus<<" to Savings Account #"<<AccountNumber;
			}
		}
		
		void withdraw(double amount){
			if(amount<0){
				cout<<endl;
				cout<<"Not Possible because Amount is less than 0"<<endl;}
			else {
		
			
			if( withdrawalCount >= withdrawalLimit ){
				cout<<"\nWithdrawal Limit reached for Savings Account #"<<AccountNumber;
				return;
			}
			if( amount<=Balance ){
				Balance -= amount;
				cout<<"\nWithdrew Amount $"<<amount<<" from Savings Account #"<<AccountNumber;
				withdrawalCount++;
			}
			else{
				cout<<"\nWithdrawal failed! No sufficient funds in the Savings Account #"<<AccountNumber;
			}
		}
	}
		void display(){
			cout<<"\nSavings Account: #"<<AccountNumber<<"\nAccount Holder Name: "<<HolderName;
			cout<<"\nBalance: $"<<fixed<<setprecision(2)<<Balance<<"\nWithdrawal Count this month: "<<withdrawalCount;
		}
		
		void applyInterest(){
			double interest = Balance*interestRate;
			Balance += interest;
			cout<<"\nInterest of $"<< fixed << setprecision(2) <<interest<<" applied to Savings Account #"<<AccountNumber;
			withdrawalCount = 0;
		}
		
		~SavingsAccount(){}
};

//Static Members Initialization
int SavingsAccount::withdrawalLimit = 3;
double SavingsAccount::interestRate = 0.11;

class CheckingAccount: public Account
{
	double overdraftLimit;
	
	public:
		
		//Default & Parameterized Constrctor
		CheckingAccount(int accNo=0, string n="", double bal=0.0, double limit=500.0):
			Account(accNo,n,bal), overdraftLimit(limit) {}
			
		//Copy Constructor
		CheckingAccount(CheckingAccount& obj):
			Account(obj), overdraftLimit(obj.overdraftLimit) {}
		
		double getOverdraftLimit() const { return overdraftLimit; }
		
		void display(){
			cout<<"\nChecking Account: #"<<AccountNumber<<"\nName: "<<HolderName<<"\nBalance: $"<<fixed<<setprecision(2)<<Balance;
			cout<<"\nOverdraft Limit: $"<<overdraftLimit;
		}
		
		void withdraw(double amount){
			if(amount>0&&(Balance+overdraftLimit)>=amount){
				Balance-=amount;
				cout<<"\nWithdrew Amount $"<<amount<<" from Checking Account #"<<AccountNumber;
			}
			else
				cout<<"\nOverdraft Limit exceeded for Checking Account #"<<AccountNumber;
		}
		
		void deposit(double amount){
			if(amount>0){
				Balance += amount;
				cout<<"\nDeposited Amount $"<<amount<<" to Checking Account #"<<AccountNumber;
			}
		}
		
		void deposit(double amount, double bonus){
			if(amount>0 && bonus>0){
				Balance += (amount+bonus);
				cout<<"\nDeposited Amount $"<<amount<<" + Bonus $"<<bonus<<" to Checking Account #"<<AccountNumber;
			}
		}
		
		~CheckingAccount(){}
};

int main()
{
	SavingsAccount S1(1001,"Jacob",500);
//	SavingsAccount S2(1002,"Benjamin",1000);
//	SavingsAccount S3 = S2;                // Copy Constructor used  
	
	SavingsAccount S2;
	cin S2;                              // Used Overloaded Cin Operator

	CheckingAccount C1(1003,"Arthur",500),C2(1004,"Mark",1000,600);
	
	Account* A1;
	A1 = &S1;
	
//	cout<<"\nChecking Account Number: "<<C1.getAccountNumber()<<"\nAccount Holder Name: ";
//	cout<<C1.getHolderName()<<"\nBalance: "<<C1.getBalance();
	
	cout<<S1<<endl<<S2<<endl<<C1<<endl<<C2<<endl;       // Overloaded Cout is Used
	
	A1->deposit(100);                     //Calling derived methods using base class pointers
	A1->deposit(100,100);                 //Deposit with Bonus  
	A1+100;                               //Deposit using + operator 
	
	A1->withdraw(-100);                     //Withdraw 1
	S1-30;                                //Withdraw 2 Withdrawal using - operator
	transfer(S1,C1,300);                  //Withdraw 3
	
	S1.withdraw(40);                      //Withdrawal Count Full
	cout<<endl;
	
	S1.display();
	cout<<endl;
	
	C1.display();
	cout<<endl;
	
	// Overloaded Operators
	
//	if(C1>C2){
//		cout<<"\n#"<<C1.getAccountNumber()<<" has more balance than Account #"<<C2.getAccountNumber();
//	}
//	if(C1<C2){
//		cout<<"\n#"<<C1.getAccountNumber()<<" has lesser balance than Account #"<<C2.getAccountNumber();
//	}
//	if(C1==C2){
//		cout<<"\n#"<<C1.getAccountNumber()<<" has equal balance to the Account #"<<C2.getAccountNumber();
//	}
	
	S1.applyInterest();                   //Applying Interest Rate
	
	cout<<endl<<S1<<"\n\n";               //Display
	
	delete A1;
	
	return 0;
}




