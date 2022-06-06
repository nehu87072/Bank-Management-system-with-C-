/*********************
                   HEADER FILE USED IN PROJECT
**********************/
#include<bits/stdc++.h>
using namespace std;

/*********************
                  CLASS USED IN PROJECT
**********************/


class pnb_account
{
	int pnb_account_no;
	char user_name[50];
	int deposit;
	char acc_type;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return pnb_account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return acc_type of pnb_account
};         //class ends here

void pnb_account::create_account()
{
	cout<<"\nEnter The PNB account No. :";
	cin>>pnb_account_no;
	cout<<"\n\nEnter The Name of The PNB account Holder : ";
	cin.ignore();
	cin.getline(user_name,50);
	cout<<"\nEnter Type of The PNB account (C/S) : ";
	cin>>acc_type;
	acc_type=toupper(acc_type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void pnb_account::show_account() const
{
	cout<<"\n PNB Account No. : "<<pnb_account_no;
	cout<<"\nPNB Account Holder Name : ";
	cout<<user_name;
	cout<<"\nType of PNB  Account : "<<acc_type;
	cout<<"\nBalance amount : "<<deposit;
}


void pnb_account::modify()
{
	cout<<"\nAccount No. : "<<pnb_account_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(user_name,50);
	cout<<"\nModify Type of Account : ";
	cin>>acc_type;
	acc_type=toupper(acc_type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void pnb_account::dep(int x)
{
	deposit+=x;
}
	
void pnb_account::draw(int x)
{
	deposit-=x;
}
	
void pnb_account::report() const
{
	cout<<pnb_account_no<<setw(10)<<" "<<user_name<<setw(10)<<" "<<acc_type<<setw(6)<<deposit<<endl;
}

	
int pnb_account::retacno() const
{
	return pnb_account_no;
}

int pnb_account::retdeposit() const
{
	return deposit;
}

char pnb_account::rettype() const
{
	return acc_type;
}


//*********************
//    	function declaration
//**********************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display pnb_account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all pnb_account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given pnb_account
void intro();	//introductory screen function

//*********************
//    	THE MAIN FUNCTION OF PROGRAM
//**********************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The pnb_account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The PNB account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The PNB account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The PNB account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The PNB account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//*********************
//    	function to write in file
//**********************

void write_account()
{
	pnb_account ac;
	ofstream outFile;
	outFile.open("pnb_account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
	outFile.close();
}

//*********************
//    	function to read specific record from file
//**********************

void display_sp(int n)
{
	pnb_account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("pnb_account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(pnb_account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//*********************
//    	function to modify record of file
//**********************

void modify_account(int n)
{
	bool found=false;
	pnb_account ac;
	fstream File;
	File.open("pnb_account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of pnb_account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(pnb_account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//*********************
//    	function to delete record of file
//**********************


void delete_account(int n)
{
	pnb_account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("pnb_account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(pnb_account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
		}
	}
	inFile.close();
	outFile.close();
	remove("pnb_account.dat");
	rename("Temp.dat","pnb_account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//*********************
//    	function to display all accounts deposit list
//**********************

void display_all()
{
	pnb_account ac;
	ifstream inFile;
	inFile.open("pnb_account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type    Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(pnb_account)))
	{
		ac.report();
	}
	inFile.close();
}

/*********************
    	function to deposit and withdraw amounts
**********************/

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	pnb_account ac;
	fstream File;
	File.open("pnb_account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(pnb_account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//*********************
//    	INTRODUCTION FUNCTION
//**********************


void intro()
{   cout<<"\n\n\n\t Punjab National Bank";
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n Press enter:";
	cin.get();
}

//*********************
//    			END OF PROJECT
//*********************
