#include <bits/stdc++.h>
#include <iostream>
#include <fstream>   // for file handling.
#include <sstream>   // stringstream-(datatype),
#include <windows.h> // Sleep()-funct,
using namespace std;

class Bill
{
private:
        string item;
        int rate, quantity;

public:
        Bill() : item(""), rate(0), quantity(0) {}

        void setItem(string itm)
        {
                item = itm;
        }
        void setRate(int rt)
        {
                rate = rt;
        }
        void setQuantity(int qnt)
        {
                quantity = qnt;
        }

        string getItem()
        {
                return item;
        }
        int getRate()
        {
                return rate;
        }
        int getQuantity()
        {
                return quantity;
        }
};

void addItem(Bill b);
void BillCounting();
void searchItem();

int main()
{
        Bill b;

        bool exit = false;
        while (!exit)
        {
                system("cls");
                int val;

                cout << "\tWelcome To \"Super Market Billing System\"" << endl;
                cout << "\t***************************************" << endl;
                cout << "\t\t1. Add Item." << endl;
                cout << "\t\t2. Purchase Item." << endl;
                cout << "\t\t3. Search Item." << endl;
                cout << "\t\t4. Exit." << endl;
                cout << "Enter Choice: ";
                cin >> val;

                if (val == 1)
                {
                        system("cls");
                        Sleep(1000);
                        addItem(b);
                }
                else if (val == 2)
                {
                        system("cls");
                        BillCounting();
                }
                else if (val == 3)
                {
                        system("cls");
                        searchItem();
                }
                else if (val == 4)
                {
                        system("cls");
                        exit = true;

                        cout << endl
                             << endl
                             << endl;
                        cout << "\t-------------Good Luck!------------" << endl;
                        cout << endl
                             << endl
                             << endl;
                }
        }

        return 0;
}

void addItem(Bill b)
{
        bool close = false;
        while (!close)
        {
                int choice;
                cout << "\t\t1. Add Item." << endl;
                cout << "\t\t2. Close." << endl;
                cout << "Enter Choice: ";
                cin >> choice;

                if (choice == 1)
                {
                        system("cls");
                        string item;
                        int rate, quant;

                        cout << "\tEnter Item Name: ";
                        cin >> item;
                        b.setItem(item);

                        cout << "\tEnter Rate of Item: ";
                        cin >> rate;
                        b.setRate(rate);

                        cout << "\tEnter Quantity of Item: ";
                        cin >> quant;
                        b.setQuantity(quant);

                        ofstream out("E:\\Bill.txt", ios::app);
                        if (!out)
                        {
                                cout << "/tError: File can't Open!" << endl;
                        }
                        else
                        {
                                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl
                                    << endl;
                                Sleep(1000);
                                cout << "\n\t\t-----Item Added Successfully-----\n"
                                     << endl;
                        }

                        out.close();
                }

                else if (choice == 2)
                {
                        system("cls");
                        close = true;
                        cout << "\tBack to Main Manue!" << endl;
                }
        }
}

void BillCounting()
{
        int count = 0;
        bool close = false;
        while (!close)
        {
                int choice;
                cout << "\t\t1. Purchase Item." << endl;
                cout << "\t\t2. Close Purchase." << endl;
                cout << "Enter Choice: ";
                cin >> choice;

                if (choice == 1)
                {
                        string item;
                        int quant;
                        cout << "\tEnter Item: ";
                        cin >> item;

                        cout << "\tEnter Quantity: ";
                        cin >> quant;

                        ifstream in("E:\\Bill.txt");
                        if (!in)
                        {
                                cout << "File not found.........." << endl;
                                return;
                        }
                        ofstream out("E:\\Bill_temp.txt");

                        string line;
                        bool found = false;
                        while (getline(in, line))
                        {
                                stringstream ss;
                                ss << line;
                                string itemName;
                                int itemRate, itemQuant;
                                char delimiter;
                                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                                if (item == itemName && found == false)
                                {
                                        found = true;
                                        if (quant <= itemQuant)
                                        {
                                                int amount = itemRate * quant;
                                                cout << "\t Item | Rate | Quantity | Amount" << endl;
                                                cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
                                                int newQuant = itemQuant - quant;
                                                itemQuant = newQuant;
                                                count += amount;

                                                out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl;
                                        }
                                        else
                                        {
                                                // if quantity is less
                                                cout << "\tSorry,  \"" << item << "\"  Ended!" << endl;

                                                int amount = itemRate * itemQuant;
                                                count += amount;
                                                cout << "\t Item | Rate | Quantity | Amount" << endl;
                                                cout << "\t" << itemName << "\t " << itemRate << "\t " << itemQuant << "\t " << amount << endl;
                                        }
                                }
                                else
                                {
                                        // if item not found
                                        out << line << endl;
                                }
                        }

                        if (!found)
                        {
                                cout << "\tSorry! Item Not Available......................." << endl;
                        }

                        out.close();
                        in.close();

                        remove("E:\\Bill.txt");
                        rename("E:\\Bill_temp.txt", "E:\\Bill.txt");
                }

                else if (choice == 2)
                {
                        close = true;
                        cout << "\tCounting Total Bill........" << endl;
                }

                Sleep(1000);
        }

        // system("cls");
        cout << endl
             << endl;
        cout << "\tTotal Bill -------------- : " << count << endl
             << endl;
        cout << "\tThanks For Shopping!" << endl;
        Sleep(10000);
}

void searchItem()
{
        string temp;
        cout << "Enter Item Name: ";
        cin >> temp;

        ifstream in("E:\\Bill.txt");
        if (!in)
        {
                cout << "File not found.........." << endl;
                return;
        }

        string line;
        bool fl = false;
        while (getline(in, line))
        {
                stringstream ss;
                ss << line;

                string itemName;
                int itemRate, itemQuant;
                char delimiter;

                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (itemName == temp)
                {
                        fl = true;
                        cout << "YES!!! " << temp << " is availabel." << endl;
                        cout << "\t Item | Rate | Quantity " << endl;
                        cout << "\t" << itemName << "\t " << itemRate << "\t " << itemQuant << endl;
                        Sleep(10000);
                        break;
                }
        }

        if (!fl)
        {
                cout << endl;
                cout << "----------------SORRY!!! " << temp << " is not available right now---------------" << endl;
                Sleep(5000);
        }
}
