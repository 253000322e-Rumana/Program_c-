#include<iostream>
#include<string>
using namespace std;

class Account
{
private:
    int accountNo;
    string customerName;
    float balance;

public:

    void openAccount()
    {
        cout<<"Enter Account Number: ";
        cin>>accountNo;
        cin.ignore();

        cout<<"Enter Customer Name: ";
        getline(cin, customerName);

        cout<<"Enter Initial Balance: ";
        cin>>balance;
    }

    void deposit()
    {
        float amount;
        cout<<"Enter Deposit Amount: ";
        cin>>amount;

        balance += amount;

        cout<<"Deposit Successful.\n";
    }

    void withdraw()
    {
        float amount;

        cout<<"Enter Withdraw Amount: ";
        cin>>amount;

        if(amount<=balance)
        {
            balance -= amount;
            cout<<"Withdraw Successful.\n";
        }
        else
        {
            cout<<"Insufficient Balance.\n";
        }
    }

    void transfer(Account &receiver)
    {
        float amount;

        cout<<"Enter Transfer Amount: ";
        cin>>amount;

        if(amount<=balance)
        {
            balance -= amount;
            receiver.balance += amount;
            cout<<"Money Transfer Successful.\n";
        }
        else
        {
            cout<<"Insufficient Balance.\n";
        }
    }

    void display()
    {
        cout<<"\nAccount Number : "<<accountNo<<endl;
        cout<<"Customer Name  : "<<customerName<<endl;
        cout<<"Balance        : "<<balance<<endl;
    }

    float getBalance()
    {
        return balance;
    }
};

int main()
{
    Account a1, a2;
    int choice;

    cout<<"Open First Account\n";
    a1.openAccount();

    cout<<"\nOpen Second Account\n";
    a2.openAccount();

    do
    {
        cout<<"\n===== Banking Management System =====\n";
        cout<<"1. Deposit\n";
        cout<<"2. Withdraw\n";
        cout<<"3. Money Transfer\n";
        cout<<"4. Show Accounts\n";
        cout<<"5. Richest Customer\n";
        cout<<"0. Exit\n";

        cout<<"Enter Your Choice: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            a1.deposit();
            break;

        case 2:
            a1.withdraw();
            break;

        case 3:
            a1.transfer(a2);
            break;

        case 4:
            cout<<"\nFirst Account";
            a1.display();

            cout<<"\nSecond Account";
            a2.display();
            break;

        case 5:
            if(a1.getBalance()>a2.getBalance())
            {
                cout<<"\nRichest Customer:\n";
                a1.display();
            }
            else
            {
                cout<<"\nRichest Customer:\n";
                a2.display();
            }
            break;

        case 0:
            cout<<"\nThank You!\n";
            break;

        default:
            cout<<"\nInvalid Choice!\n";
        }

    }while(choice!=0);

    return 0;
}
