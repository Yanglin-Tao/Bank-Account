/*
  Bank Accounts.cpp
 */
// Created by Yanglin Tao
// Program to simulate bank account activities

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 3
// Define an Account and Transaction classes

// transaction class
class transaction{
    friend ostream& operator << (ostream& os, const transaction& some_transaction);
public:
    transaction(const string& command, int amount): command(command), amount(amount){
    }
private:
    //indicate whether this is a deposit or a withdrawal
    string command;
    //how much is being deposited or withdrawn
    int amount;
};

//output operator for transaction class
ostream& operator << (ostream& os, const transaction& some_transaction){
    os << some_transaction.command << "   " << some_transaction.amount << endl;;
    return os;
}

// history of transaction class, with deposit and transaction functions
class history{
    friend ostream& operator << (ostream& os, const history& some_history);
public:
    history(const string& name, int number) : account_name(name), account_number(number){
    }
    // necessary for task 3
    const string& get_account_name() const{
        return account_name;
    }
    void deposit(int amount){
        balance += amount;
        transaction_history.emplace_back("deposit", amount);
    }
    void withdrawal(int amount){
        if(balance < amount){
            cout << "Account# " << account_number << " has only " << balance << ". ";
            cout << "Insufficient for withdrawal of " << amount << ". " << endl;
        }
        else{
            balance -= amount;
            transaction_history.emplace_back("withdrawal", amount);
        }
    }
private:
    string account_name;
    int account_number;
    vector<transaction> transaction_history;
    int balance = 0;
};

// output operator for history class
ostream& operator << (ostream& os, const history& some_history){
    //loop over
    os << some_history.account_name << "   " << some_history.account_number << ":" << endl;
    for(const transaction& transaction : some_history.transaction_history){
        cout << transaction;
    }
    return os;
}

// Task 2
// Define an Account class
class account_class{
friend ostream& operator << (ostream& os, const account_class& some_account);
public:
    account_class(const string& name, int number) : account_name(name), account_number(number){
    }
    const string& get_account_name() const{
        return account_name;
    }
    int get_account_number() const{
        return account_number;
    }

    
private:
    string account_name;
    int account_number;
};

// output operator for account class
ostream& operator << (ostream& os, const account_class& some_account){
    os <<  some_account.account_name << "   ";
    os <<  some_account.account_number;
    return os;
}



// Task 1
// Define an Account struct
struct Account{
    string account_name;
    int account_number;
};


 int main() {
     // open accounts.txt
     ifstream accounts("accounts.txt");
     if(!accounts){
         cout << "Could not open file.\n";
         exit(1);
     }
     
     // Task 1: account as struct
     //      1a
     cout << "Task1a:\n";
     vector<Account> vector_accounts;
     string name;
     int number;
     while(accounts >> name >> number){
         Account new_account;
         new_account.account_name = name;
         new_account.account_number = number;
         vector_accounts.push_back(new_account);
     }
     accounts.close();
     for (size_t i = 0; i < vector_accounts.size(); ++i) {
         cout << vector_accounts[i].account_name << "   " << vector_accounts[i].account_number << endl;
     }
     //      1b
     cout << "Task1b:\n";
     cout << "Filling vector of struct objects, using {} initialization:\n";
     vector_accounts.clear();
     accounts.open("accounts.txt");
     string init_name;
     int init_number;
     while(accounts >> init_name >> init_number){
         Account new_account{init_name,init_number};
         vector_accounts.push_back(new_account);
     };
     accounts.close();
     for (size_t i = 0; i < vector_accounts.size(); ++i) {
         cout << vector_accounts[i].account_name << "   " << vector_accounts[i].account_number << endl;
     }

    //==================================
    // Task 2: account as class

    //      2a
    //
     cout << "==============\n";
     cout << "\nTask2a:";
     cout << "\nFilling vector of class objects, using local class object:\n";
     vector<account_class> vector_account_class;
     for (size_t i = 0; i < vector_accounts.size(); ++i) {
         account_class new_acc(vector_accounts[i].account_name, vector_accounts[i].account_number);
         vector_account_class.push_back(new_acc);
     }
     
     for (size_t i = 0; i < vector_account_class.size(); ++i){
         cout << vector_account_class[i].get_account_name() << "   " << vector_account_class[i].get_account_number() << endl;
     }

     cout << "\nTask2b:\n";
     cout << "output using output operator with getters\n";
     for (size_t i = 0; i < vector_account_class.size(); ++i){
         cout << vector_account_class[i] << endl;
     }
     
     cout << "\nTask2c:\n";
     cout << "output using output operator as friend without getters\n";
     for (size_t i = 0; i < vector_account_class.size(); ++i){
         cout << vector_account_class[i] << endl;
     }
     
     cout << "\nTask2d:\n";
     cout << "Filling vector of class objects, using temporary class object:\n";
     vector<account_class> vector_account_class_temp;
     for (size_t i = 0; i < vector_accounts.size(); ++i) {
         vector_account_class_temp.push_back(account_class(vector_accounts[i].account_name, vector_accounts[i].account_number));
     }
     for (size_t i = 0; i < vector_account_class.size(); ++i){
         cout << vector_account_class_temp[i] << endl;
     }
     
     cout << "\nTask2e:\n";
     cout << "Filling vector of class objects, using emplace_back:\n";
     vector<account_class> vector_account_class_emplace;
     for (size_t i = 0; i < vector_accounts.size(); ++i) {
         vector_account_class_emplace.emplace_back(vector_accounts[i].account_name, vector_accounts[i].account_number);
     }
     for (size_t i = 0; i < vector_account_class_emplace.size(); ++i){
         cout << vector_account_class_emplace[i] << endl;
     }

     cout << "==============\n";
     cout << "\nTask 3:\nAccounts and Transaction:\n";

     // open file transactions.txt
     ifstream transactions("transactions.txt");
     if(!transactions){
         cout << "Could not open file.\n";
         exit(1);
     }
     
     vector<history> account_history;
     string acc_name;
     int acc_number;
     string command;
     int transaction_amount;
     string account = "Account";
     string deposit = "Deposit";
     string withdrawal = "Withdraw";
     
     // read in and execute commands from transactions.txt
     while(transactions >> command){
         if(command == account){
             transactions >> acc_name;
             transactions >> acc_number;
             account_history.emplace_back(acc_name, acc_number);
         }
         else if(command == deposit){
             transactions >> acc_number;
             for(history& some_history : account_history){
                 // locate the account in a collection of accounts
                 if(some_history.get_account_name() == acc_name){
                     transactions >> transaction_amount;
                     some_history.deposit(transaction_amount);
                 }
             }
         }
         else if(command == withdrawal){
             transactions >> acc_number;
             for(history& some_history : account_history){
                 // locate the account in a collection of accounts
                 if(some_history.get_account_name() == acc_name){
                     transactions >> transaction_amount;
                     some_history.withdrawal(transaction_amount);
                 }
         }
     }
     
     }
     transactions.close();
     
     // output account history
     for(const history& some_history : account_history){
         cout << some_history << endl;
     }
}




