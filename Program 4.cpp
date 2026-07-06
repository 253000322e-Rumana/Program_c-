#include <iostream>
#include <string>
using namespace std;

class Product
{
public:
    int id, stock, sold;
    string name;
    double price;

    void input()
    {
        cout << "Enter Product ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Product Name: ";
        getline(cin, name);

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Stock: ";
        cin >> stock;

        sold = 0;
    }

    void display()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Stock: " << stock << endl;
        cout << "Sold: " << sold << endl;
        cout << "------------------------" << endl;
    }
};

class Inventory
{
private:
    Product p[100];
    int count = 0;
    double totalSales = 0;

public:

    void addProduct()
    {
        p[count].input();
        count++;
    }

    void updateStock()
    {
        int id, qty;

        cout << "Enter Product ID: ";
        cin >> id;

        cout << "Enter New Stock Quantity: ";
        cin >> qty;

        for(int i=0;i<count;i++)
        {
            if(p[i].id==id)
            {
                p[i].stock=qty;
                cout<<"Stock Updated Successfully.\n";
                return;
            }
        }

        cout<<"Product Not Found.\n";
    }

    void sellProduct()
    {
        int id, qty;

        cout<<"Enter Product ID: ";
        cin>>id;

        cout<<"Enter Quantity: ";
        cin>>qty;

        for(int i=0;i<count;i++)
        {
            if(p[i].id==id)
            {
                if(qty<=p[i].stock)
                {
                    p[i].stock-=qty;
                    p[i].sold+=qty;

                    double bill=qty*p[i].price;
                    totalSales+=bill;

                    cout<<"Bill = "<<bill<<endl;
                }
                else
                {
                    cout<<"Insufficient Stock.\n";
                }

                return;
            }
        }

        cout<<"Product Not Found.\n";
    }

    void showProducts()
    {
        for(int i=0;i<count;i++)
            p[i].display();
    }

    void showTotalSales()
    {
        cout<<"Total Sales = "<<totalSales<<endl;
    }

    void bestSellingProduct()
    {
        if(count==0)
        {
            cout<<"No Products.\n";
            return;
        }

        int index=0;

        for(int i=1;i<count;i++)
        {
            if(p[i].sold>p[index].sold)
                index=i;
        }

        cout<<"Best Selling Product\n";
        p[index].display();
    }
};

int main()
{
    Inventory shop;
    int choice;

    do
    {
        cout<<"\n===== Inventory & Billing System =====\n";
        cout<<"1. Add Product\n";
        cout<<"2. Update Stock\n";
        cout<<"3. Sell Product\n";
        cout<<"4. Show Products\n";
        cout<<"5. Total Sales\n";
        cout<<"6. Best Selling Product\n";
        cout<<"0. Exit\n";

        cout<<"Enter Choice: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            shop.addProduct();
            break;

        case 2:
            shop.updateStock();
            break;

        case 3:
            shop.sellProduct();
            break;

        case 4:
            shop.showProducts();
            break;

        case 5:
            shop.showTotalSales();
            break;

        case 6:
            shop.bestSellingProduct();
            break;

        case 0:
            cout<<"Thank You.\n";
            break;

        default:
            cout<<"Invalid Choice.\n";
        }

    }while(choice!=0);

    return 0;
}
