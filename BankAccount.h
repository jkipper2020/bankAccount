//
// Created by Jonathan Kipper on 5/13/2019.
//

#ifndef ASSIGNMENT5_BANKACCOUNT_H
#define ASSIGNMENT5_BANKACCOUNT_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BankAccount
{
//protected variables
protected:
    double accountBalance;
    int numberOfDeposits;
    int numberOfWithdrawls;
    int month;
    double monthlyInterestRate;
    double yearlyFee;
    string accountType;
    string accountID;

public:
    //constructors
    BankAccount();
    BankAccount(string, double);
    //methods
    double getBalance(); //it's never actually used but might be handy someday.
    virtual void deposit(double);
    virtual void withdraw(double);
    virtual void monthlyCalc();
    virtual void endOfYear();
    virtual void printStatus();
    bool operator<(const BankAccount &) const;
    string getID();
    virtual ~BankAccount();
    string returnMonthAsString();
};

//simple savings class
class SimpleSavings:public BankAccount
{
public:
    //constructors
    SimpleSavings();
    SimpleSavings(string &ID, double balance);

    //destructor
    ~SimpleSavings() override;
};

//AdvancedSavings savings class
class AdvancedSavings:public BankAccount
{
public:
    //constructors
    AdvancedSavings();
    AdvancedSavings(string &ID, double balance);

    //methods that replace the virtual functions from the base class, marked as override for annotation
    void withdraw(double) override;
    void endOfYear() override;

    //destructor
    ~AdvancedSavings() override;
};

//checking account class
class CheckingAccount:public BankAccount
{
public:
    //constructors
    CheckingAccount();
    CheckingAccount(string &ID, double balance);

    //methods
    void withdraw(double) override;
    void endOfYear() override;

    ~CheckingAccount() override;
};

//credit account class
class CreditAccount:public BankAccount
{
protected:
    int monthsLate;
    double monthlyChargeRate;
    //keeps track of the monthly payments in this vector
    vector<double> monthlyDepositAmount;
    bool isClosed;

public:
    //constructors
    CreditAccount();
    CreditAccount(string &ID, double balance);

    //methods
    void deposit(double) override;
    void withdraw(double) override;
    void monthlyCalc() override;
    void printStatus() override;
    void endOfYear() override;

    ~CreditAccount() override;
};

#endif //ASSIGNMENT5_BANKACCOUNT_H