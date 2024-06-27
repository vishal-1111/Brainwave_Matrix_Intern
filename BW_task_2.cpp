#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include<fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

class bank {
    private:
    float balance;
    int pin;
    string pass, id,name,fname,address,phone;
public:
    void menu();
    void bank_management();
    void New_User();
    void Already_User();
    void Deposit();
    void Withdraw();
    void Transfer();
};


char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void bank::menu() {
    p:
    system("clear");
    int choice;
    string pin, pass, email;
    cout << "\n\n\t\tControl Panel";
    cout << "\n\n1. Bank Management";
    cout << "\n2. Exit";
    cout << "\n\n Enter Your Choice : ";
    cin >> choice;
    switch (choice) {
        case 1:
            system("clear");
            cout << "\n\n\n\t\t\tLogin Account";
            
            cout<<"\n\nEnter your details one by one->\nEmail\nPin\nPassword\n";
            cout << "\n\n E-mail : ";
            cin >> email;
            cout << "\n\n Pin Code : ";
            for (int i = 0; i < 5; i++) {
                char ch = getch();
                pin += ch;
                cout << "*";
            }
            cout << "\n\n Password : ";
            for (int i = 0; i < 5; i++) {
                char ch = getch();
                pass += ch;
                cout << "*";
            }
            if (email == "bikecar@gmail.com" && pin == "12345" && pass == "54321") {
                bank_management();
            } else {
                cout << "\nInvalid User\nXXXXXXXXXXXXXXXXXXXXXXXX\n";
            }
            break;
     
        case 2:
            exit(0);
        default:
            cout << "\n\n Invalid Value...Please Try Again";
    }
    getch();
    goto p;
}

void bank::bank_management() {

    p:
    int choice;
    system("clear");
    cout<<"\n\nBank Management System";
    cout<<"\n\n1. New User";
    cout<<"\n2. Already User";
    cout<<"\n3. Deposit Option";
    cout<<"\n4. Withdraw Option";
    cout<<"\n5. Transfer Option";
    cout<<"\n6. Go Back";
    cout<<"\n Enter Your Choice : ";
    cin>>choice;
    switch(choice){

        case 1:
            New_User();
            break;
        case 2:
            Already_User();
            break;
        case 3:
            Deposit();
            break;
        case 4:
            Withdraw();
            break;
        case 5:
            Transfer();
            break;
        case 6:
            menu();
            break;
        default:
        cout<<"\nInvalid Choice\nXXXXXXXXXXXXXXXXXXXX";

        
    }
    getch();
    goto p;

  
}


void bank::New_User(){
    p:

    system("clear");
    fstream file;
    int p;
    float b;
    string n,f,pa,a,ph,i;

    cout<<"\n\n\t\tAdd New User";
    cout<<"\nUser ID : ";
    cin>>id;
    cout<<"\nName : ";
    cin>>name;
    cout<<"\nFather's Name : ";
    cin>>fname;
    cout<<"\nAddress : ";
    cin>>address;
    cout<<"\nPin Code : ";
    cin>>pin;
    cout<<"\nPasword : ";
    cin>>pass;
    cout<<"\nPhone No. : ";
    cin>>phone;
    cout<<"\nBalance : ";
    cin>>balance;
    file.open("bank.txt",ios::in);
    if(!file){
        file.open("bank.txt",ios::app | ios::out);
        file<<" "<<id<<" "<<name<<" "<<fname<<" "<<address<<" "<<pin<<" "<<
        pass<<" "<<phone<<" "<<balance<<"\n";
        file.close();
    }
    else{
        file>>i>>n>>f>>a>>p>>pa>>ph>>b;
        while(!file.eof()){
            if(i==id){
                cout<<"\n\nUser ID Already Exists...";
                getch();
                goto p;
            }
            file>>i>>n>>f>>a>>p>>pa>>ph>>b;

        }
        file.close();
        file.open("bank.txt",ios::app | ios::out);
        file<<" "<<id<<" "<<name<<" "<<fname<<" "<<address<<" "<<pin<<" "<<
        pass<<" "<<phone<<" "<<balance<<"\n";
        file.close();

    }
    cout<<"\n\nNew User Registered Successfully.....\n\n";

}

void bank::Already_User(){
    system("clear");
    fstream file;
    string U_id;
    int found=0;
    cout<<"\n\nAlready User Account";
    file.open("bank.txt",ios::in);
    if(!file){
        cout<<"\nFile Opening Error";
    }
    else{
        cout<<"\nUser ID : ";
        cin>>U_id;
        file>>id>>name>>fname>>address>>pin>>pass>>phone>>balance;
        while(!file.eof()){
            if(U_id==id){
                system("clear");
                cout<<"\nAlready Registered User Account";
                cout<<"\nUser ID : "<<id<<"\nPin Code : "<<pin<<"\nPassword : "<<pass<<"\n";
                found++;
            }
             file>>id>>name>>fname>>address>>pin>>pass>>phone>>balance;
        }
        file.close();
        if(found==0)
            cout<<"\n\nCannot Find User ID.....";
        
    }

}

void bank::Deposit(){
      system("clear");
    fstream file, file1;
    float dep;
    string U_id;
    int found = 0;

    cout << "\n\nDeposit Amount Option\n";
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\nFile Opening Error\n";
        return;
    }

    cout << "User ID: ";
    cin >> U_id;
    file1.open("bank1.txt", ios::app | ios::out);
    if (!file1) {
        cout << "\nTemporary File Opening Error\n";
        file.close();
        return;
    }

    file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
    while (!file.eof()) {
        if (U_id == id) {
            cout << "Amount To Be Deposited: ";
            cin >> dep;
            balance += dep;
            file1 << id << " " << name << " " << fname << " " << address << " " << pin << " "
                  << pass << " " << phone << " " << balance << "\n";
            found++;
            cout << "\n\t\t\tYour Amount " << dep << " Successfully Deposited....\n";
        } else {
            file1 << id << " " << name << " " << fname << " " << address << " " << pin << " "
                  << pass << " " << phone << " " << balance << "\n";
        }
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
    }

    file.close();
    file1.close();
    remove("bank.txt");
    rename("bank1.txt", "bank.txt");

    if (found == 0) {
        cout << "\n\nCannot Find User ID.....\n";
    }



}


void bank::Withdraw(){

 system("clear");
    fstream file, file1;
    float withd;
    string U_id;
    int found = 0;

    cout << "\n\nWithdraw Amount Option\n";
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\nFile Opening Error\n";
        return;
    }

    cout << "User ID: ";
    cin >> U_id;
    file1.open("bank1.txt", ios::app | ios::out);
    if (!file1) {
        cout << "\nTemporary File Opening Error\n";
        file.close();
        return;
    }

    file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
    while (!file.eof()) {
        if (U_id == id) {
            cout << "Amount To Be Withdraw: ";
            cin >> withd;
            if (withd <= balance) {
                balance -= withd;
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " "
                      << pass << " " << phone << " " << balance << "\n";
                found++;
                cout << "\n\n\t\tYour Amount Rs " << withd << " Successfully Withdrawn....\n";
            } else {
                cout << "\n\nYou have Only Rs " << balance << " In Your Account\n";
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " "
                      << pass << " " << phone << " " << balance << "\n";
                found++;
            }
        } else {
            file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " "
                  << pass << " " << phone << " " << balance << "\n";
        }
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
    }

    file.close();
    file1.close();
    remove("bank.txt");
    rename("bank1.txt", "bank.txt");

    if (found == 0) {
        cout << "\n\nCannot Find User ID.....\n";
    }

}

void bank::Transfer() {
    fstream file, file1;
    string S_id, R_id;
    float amount;
    bool sender_found = false, receiver_found = false;

    system("clear");
    cout << "\n\nPayment Transfer Option" << endl;

    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\n\nFile Opening Error...." << endl;
        return;
    }

    cout << "\n\nSender's User Id: ";
    cin >> S_id;
    cout << "\n\nReceiver's User Id: ";
    cin >> R_id;
    cout << "\nEnter The Amount To Be Transferred: ";
    cin >> amount;

   
    vector<string> lines;
    string line;
    float sender_balance = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, fname, address, pin, pass, phone;
        float balance;
        iss >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;

        if (id == S_id) {
            sender_found = true;
            if (amount <= balance) {
                sender_balance = balance;
            } else {
                cout << "\nInsufficient balance for sender." << endl;
                file.close();
                usleep(2000000); 
                return;
            }
        }
        if (id == R_id) {
            receiver_found = true;
        }

        lines.push_back(line);
    }
    file.close();

    if (!sender_found) {
        cout << "\nSender ID not found." << endl;
        usleep(2000000); 
        return;
    }
    if (!receiver_found) {
        cout << "\nReceiver ID not found." << endl;
        usleep(2000000); 
        return;
    }

   
    file1.open("bank1.txt", ios::out);
    for (const string& line : lines) {
        istringstream iss(line);
        string id, name, fname, address, pin, pass, phone;
        float balance;
        iss >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;

        if (id == S_id) {
            balance -= amount;
            file1 << id << " " << name << " " << fname << " " << address << " " << pin << " "
                  << pass << " " << phone << " " << balance << "\n";
        } else if (id == R_id) {
            balance += amount;
            file1 << id << " " << name << " " << fname << " " << address << " " << pin << " "
                  << pass << " " << phone << " " << balance << "\n";
        } else {
            file1 << line << "\n";
        }
    }
    file1.close();

   
    remove("bank.txt");
    rename("bank1.txt", "bank.txt");

    cout << "\n\nTransaction successful. Amount " << amount << " transferred from " << S_id << " to " << R_id << "." << endl;
    usleep(2000000); 
}



int main() {
    bank obj;
    obj.menu();
    return 0;
}
