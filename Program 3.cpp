#include <iostream>
#include <string>
using namespace std;

class Book
{
public:
    string title, isbn;
    double price;
    bool available;

    Book()
    {
        title = "";
        isbn = "";
        price = 0;
        available = true;
    }

    void input()
    {
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter ISBN: ";
        getline(cin, isbn);

        cout << "Enter Price: ";
        cin >> price;

        available = true;
    }

    void display()
    {
        cout << "Title: " << title << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Price: " << price << endl;
        cout << "Status: " << (available ? "Available" : "Borrowed") << endl;
        cout << "------------------------" << endl;
    }
};

class Library
{
private:
    Book books[100];
    int count = 0;

public:
    void addBook()
    {
        books[count].input();
        count++;
    }

    void borrowBook()
    {
        string id;
        cout << "Enter ISBN: ";
        cin >> id;

        for(int i=0;i<count;i++)
        {
            if(books[i].isbn==id)
            {
                if(books[i].available)
                {
                    books[i].available=false;
                    cout<<"Book Borrowed Successfully.\n";
                }
                else
                    cout<<"Book Already Borrowed.\n";
                return;
            }
        }
        cout<<"Book Not Found.\n";
    }

    void returnBook()
    {
        string id;
        cout<<"Enter ISBN: ";
        cin>>id;

        for(int i=0;i<count;i++)
        {
            if(books[i].isbn==id)
            {
                books[i].available=true;
                cout<<"Book Returned Successfully.\n";
                return;
            }
        }
        cout<<"Book Not Found.\n";
    }

    void searchBook()
    {
        string key;
        cout<<"Enter ISBN: ";
        cin>>key;

        for(int i=0;i<count;i++)
        {
            if(books[i].isbn==key)
            {
                books[i].display();
                return;
            }
        }
        cout<<"Book Not Found.\n";
    }

    void displayAvailableBooks()
    {
        cout<<"\nAvailable Books:\n";

        for(int i=0;i<count;i++)
        {
            if(books[i].available)
                books[i].display();
        }
    }

    void totalValue()
    {
        double sum=0;

        for(int i=0;i<count;i++)
            sum+=books[i].price;

        cout<<"Total Library Value = "<<sum<<endl;
    }
};

int main()
{
    Library lib;
    int choice;

    do
    {
        cout<<"\n===== Library Management System =====\n";
        cout<<"1. Add Book\n";
        cout<<"2. Borrow Book\n";
        cout<<"3. Return Book\n";
        cout<<"4. Search Book\n";
        cout<<"5. Display Available Books\n";
        cout<<"6. Total Library Value\n";
        cout<<"0. Exit\n";

        cout<<"Enter Choice: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.borrowBook();
            break;
        case 3:
            lib.returnBook();
            break;
        case 4:
            lib.searchBook();
            break;
        case 5:
            lib.displayAvailableBooks();
            break;
        case 6:
            lib.totalValue();
            break;
        case 0:
            cout<<"Thank You!\n";
            break;
        default:
            cout<<"Invalid Choice.\n";
        }

    }while(choice!=0);

    return 0;
}
