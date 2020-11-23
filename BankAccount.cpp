//Imports
#include "BankAccount.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

//THE NAMESPACE
using namespace std;

//********************************************************************************************************************\\
//************************************* WRITTEN AND PROGRAMMED BY JONATHAN KIPPER*************************************\\
//********ALL OF THE DIFFERENT CLASS METHODS, CONSTRUCTORS, DESTRUCTORS, ETC. IMPLEMENTATIONS ARE IN THIS FILE********\\
//********************************************************************************************************************\\

//*********************************************IN .CPP FUNCTION PROTOTYPES*********************************************\\

void emptyID(string &);

//*********************************************START OF BANK ACCOUNT CLASS********************************************\\
//****************************************************CONSTRUCTORS****************************************************\\
//Default:
BankAccount::BankAccount()
{
    accountID = "0";
    accountBalance = 0;
    monthlyInterestRate = 0;
    numberOfDeposits = 0;
    numberOfWithdrawls = 0;
    yearlyFee = 0;
    month = 1; //1 = january, 2 = february, 12 = december
    accountType = "Default";
}
//secondary:
BankAccount::BankAccount(string id, double bal)
{
    //calls the emptyID function to check if id is empty or not (passed by reference)
    emptyID(id);
    accountID = id;

    //sets up defaults
    accountBalance = bal;
    monthlyInterestRate = 0;
    numberOfWithdrawls = 0;
    numberOfDeposits = 0;
    yearlyFee = 0;
    month = 1; //1 = january, 2 = february, 12 = december
    accountType = "Default";
}

//***************************************************RETURN METHODS***************************************************\\
//returns the accounts current balance
double BankAccount::getBalance()
{
    return accountBalance;
}

//returns the account's ID value
string BankAccount::getID()
{
    return accountID;
}

//returns the month as a string
string BankAccount::returnMonthAsString()
{
    if (month == 1)
    {
        return "January";
    }
    else if (month == 2)
    {
        return "February";
    }
    else if (month == 3)
    {
        return "March";
    }
    else if (month == 4)
    {
        return "April";
    }
    else if (month == 5)
    {
        return "May";
    }
    else if (month == 6)
    {
        return "June";
    }
    else if (month == 7)
    {
        return "July";
    }
    else if (month == 8)
    {
        return "August";
    }
    else if (month == 9)
    {
        return "September";
    }
    else if (month == 10)
    {
        return "October";
    }
    else if (month == 11)
    {
        return "November";
    }
    else if (month == 12)
    {
        return "December";
    }
    else
    {
        //shouldn't run if everything is working properly
        return "ERROR WITH THE MONTH CALCULATION";
    }
}

//****************************************************VOID METHODS****************************************************\\
//deposits money into the account
void BankAccount::deposit(double depositAmount)
{
    if (depositAmount > 0)
    {
        accountBalance += depositAmount;
        numberOfDeposits++;
    }
    else if (depositAmount < 0)
    {
        cout << "Hey dummy, you can't deposit a negative amount of money!" << endl;
    }
    else
    {
        cout << "Dude, you can't deposit zero" << endl;
    }
}
//withdrawl method
void BankAccount::withdraw(double withdrawAmount)
{
    //ensures there isn't somehow a negative account balance to begin with
    if (accountBalance > 0)
    {
        double tmp = accountBalance - withdrawAmount;
        if (withdrawAmount < 0)
        {
            withdrawAmount *= -1;
        }
        else if ((withdrawAmount > 0) && (tmp < 0))
        {
            cout << "You can't withdraw that much money, you're going to be in the negative if you do!" << endl;
        }
        else if (withdrawAmount == 0)
        {
            cout << "You can't withdraw nothing!" << endl;
        }
        else if ((withdrawAmount > 0) && (tmp > 0))
        {
            accountBalance -= withdrawAmount;
            numberOfWithdrawls++;
        }
    }
    else
    {
        cout << "Unable to make the withdraw because your account balance is negative. " << endl;
    }
}
//does the monthly calculation for the bank account
void BankAccount::monthlyCalc()
{
    double monthlyInterest = accountBalance * monthlyInterestRate;
    accountBalance = accountBalance + monthlyInterest;
    month++;

    if (month > 12)
    {
        endOfYear();
    }
}
//runs the end of year for the bank account
void BankAccount::endOfYear()
{
    numberOfDeposits = 0;
    numberOfWithdrawls = 0;
    accountBalance -= yearlyFee;
    month=1;
}
//prints out the status of the account and it's all super neat and organized and nice and stuff
void BankAccount::printStatus()
{
    string theMonth = returnMonthAsString();
    cout << "***************************************************************" << endl;
    cout << "*The account ID is: " << accountID << setprecision(2) << fixed << right <<setw(63-(20+accountID.length()))  << "*" << endl;
    cout << "*The account type is: " << accountType << right <<setw(63-(22+accountType.length()))  << "*" << endl;
    cout << "*The number of deposits this year so far is: " << numberOfDeposits << right <<setw(63-(45+to_string(numberOfDeposits).length()))  << "*" << endl;
    cout << "*The number of withdrawls this year so far is: " << numberOfWithdrawls << right <<setw(63-(47+to_string(numberOfWithdrawls).length()))  << "*" << endl;
    cout << "*The monthly interest rate is " << monthlyInterestRate << "%." << right <<setw(63-(28+to_string(monthlyInterestRate).length()))  << "*" << endl;
    cout << "*The yearly fee is: $" << yearlyFee << right <<setw(63-(17+to_string(yearlyFee).length()))  << "*" << endl;
    cout << "*The current balance is: $" << accountBalance << right <<setw(63-(22+to_string(accountBalance).length()))  << "*" << endl;
    cout << "*The current month is: " << theMonth << right <<setw(63-(23+theMonth.length()))  << "*" << endl;
    cout << "***************************************************************" << endl << endl;
}

//******************************************************OPERATORS******************************************************\\
//the less than operator for the bank account class to compare account ID's (to order them)
bool BankAccount::operator<(const BankAccount &mainAccount) const
{
    int mainID = stoi(mainAccount.accountID);
    int secondaryID = stoi(this->accountID);

    //returns true of the this is greater than the first, otherwise returns false
    return secondaryID < mainID;
}

//***********************************************END BANK ACCOUNT CLASS***********************************************\\

//********************************************START OF SIMPLE SAVINGS CLASS*******************************************\\
//****************************************************CONSTRUCTORS****************************************************\\
//default constructor
SimpleSavings::SimpleSavings() : BankAccount()
{
    BankAccount::accountType = "Simple Account";
    BankAccount::monthlyInterestRate = 0.005;
    BankAccount::yearlyFee = 5;
}

//simple savings main constructor
SimpleSavings::SimpleSavings(string &ID, double balance) : BankAccount()
{
    emptyID(ID); //checks for emptiness
    BankAccount::accountID = ID;
    BankAccount::accountType = "Simple Account";
    BankAccount::monthlyInterestRate = 0.005;
    BankAccount::accountBalance = balance;
    BankAccount::yearlyFee = 5;
}

//**********************************************END SIMPLE SAVINGS CLASS**********************************************\\

//*******************************************START OF ADVANCED SAVINGS CLASS*******************************************\\
//****************************************************CONSTRUCTORS****************************************************\\
//default
AdvancedSavings::AdvancedSavings() : BankAccount()
{
    BankAccount::accountType = "Advanced Savings";
    BankAccount::yearlyFee = 100;

    //sets the monthly interest rate
    if (BankAccount::accountBalance > 10000)
    {
        BankAccount::monthlyInterestRate = 0.02;
    }
    else
    {
        BankAccount::monthlyInterestRate = 0.01;
    }
}
//main constructor
AdvancedSavings::AdvancedSavings(string &ID, double balance) : BankAccount()
{
    emptyID(ID);
    BankAccount::accountID = ID;
    BankAccount::accountType = "Advanced Savings";
    BankAccount::yearlyFee = 100;
    BankAccount::accountBalance = balance;
    //sets the monthly interest rate
    if (BankAccount::accountBalance > 10000)
    {
        BankAccount::monthlyInterestRate = 0.02;
    }
    else
    {
        BankAccount::monthlyInterestRate = 0.01;
    }

}

//*************************************************REDEFINED FUNCTIONS*************************************************\\

void AdvancedSavings::withdraw(double withdrawAmount)
{
    //ensures there isn't somehow a negative account balance to begin with
    if (accountBalance > 0)
    {
        //number of withdrawls is equal to the withdrawl fee
        double tmp = accountBalance - withdrawAmount - BankAccount::numberOfWithdrawls; 
        if (withdrawAmount < 0)
        {
            withdrawAmount *= -1;
        }
        else if ((withdrawAmount > 0) && (tmp < 0))
        {
            cout << "You can't withdraw that much money, you're going to be in the negative if you do!" << endl;
        }
        else if (withdrawAmount == 0)
        {
            cout << "You can't withdraw nothing!" << endl;
        }
        else if ((withdrawAmount > 0) && (tmp > 0))
        {
            accountBalance -= (withdrawAmount + BankAccount::numberOfWithdrawls);
            BankAccount::numberOfWithdrawls++;
        }
    }
    else
    {
        cout << "Unable to make the withdraw because your account balance is negative. " << endl;
    }
}

void AdvancedSavings::endOfYear()
{
    if (numberOfWithdrawls == 0)
    {
        cout << "Congragulations, you made zero withdrawls throughout the year so your yearly fee is only $15.00!" << endl;
        yearlyFee = 15;
    }
    numberOfDeposits = 0;
    numberOfWithdrawls = 0;
    accountBalance -= yearlyFee;
    month=1;
    yearlyFee=100;
}



//********************************************END OF ADVANCED SAVINGS CLASS********************************************\\

//*******************************************START OF CHECKING ACCOUNT CLASS*******************************************\\
//****************************************************CONSTRUCTORS****************************************************\\
//default constructor
CheckingAccount::CheckingAccount() : BankAccount()
{
    BankAccount::accountType = "Checking";
    BankAccount::yearlyFee = 5;
}

//main constructor
CheckingAccount::CheckingAccount(string &ID, double balance) : BankAccount()
{
    emptyID(ID);
    BankAccount::accountID = ID;
    BankAccount::accountType = "Checking";
    BankAccount::accountBalance = balance;
    BankAccount::yearlyFee = 5;
}

//*************************************************REDEFINED FUNCTIONS*************************************************\\

void CheckingAccount::withdraw(double withdrawlAmount)
{
    double tmp = BankAccount::accountBalance - withdrawlAmount;

    //if they try to withdraw a negative amount of money
    if (withdrawlAmount < 0)
    {
        withdrawlAmount *= -1;
    }

    if (tmp < 0)
    {
        withdrawlAmount += 15;
    }

    BankAccount::accountBalance -= withdrawlAmount;
    BankAccount::numberOfWithdrawls++;
}

void CheckingAccount::endOfYear()
{
    BankAccount::yearlyFee = (0.1 * numberOfWithdrawls) + 5;
    BankAccount::accountBalance -= BankAccount::yearlyFee;

    if (BankAccount::accountBalance < 0)
    {
        double tmp = (-1)*(BankAccount::accountBalance * 0.1);
        BankAccount::accountBalance -= tmp;
    }
    numberOfDeposits = 0;
    numberOfWithdrawls = 0;
    BankAccount::yearlyFee=5;
    month=1;
}

//********************************************END OF CHECKING ACCOUNT CLASS********************************************\\

//********************************************START OF CREDIT ACCOUNT CLASS********************************************\\
//****************************************************CONSTRUCTORS****************************************************\\
//default
CreditAccount::CreditAccount()
{
    BankAccount::accountType = "Credit";
    CreditAccount::monthsLate = 1;
    BankAccount::yearlyFee = 25;
    CreditAccount::isClosed = false;
    CreditAccount::monthlyChargeRate=0;

}
//main constructor
CreditAccount::CreditAccount(string &ID, double balance)
{
    emptyID(ID);
    BankAccount::accountID = ID;
    BankAccount::accountBalance = balance;
    BankAccount::accountType = "Credit";
    CreditAccount::monthsLate = 1;
    BankAccount::yearlyFee = 25;
    CreditAccount::isClosed = false;
    CreditAccount::monthlyChargeRate=0;
}
//*************************************************REDEFINED FUNCTIONS*************************************************\\

void CreditAccount::deposit(double depositAmount)
{
    if (depositAmount < 0)
    {
        depositAmount *= -1;
    }

    if (BankAccount::accountBalance<0)
    {
        BankAccount::accountBalance += depositAmount;
        CreditAccount::monthlyDepositAmount.emplace_back(depositAmount);
        BankAccount::numberOfDeposits++;
    }
}

void CreditAccount::withdraw(double withdrawlAmount)
{
    if (CreditAccount::isClosed)
    {
        cout << "Account is closed, unable to make withdrawl." << endl;
    }
    else
    {
        if (withdrawlAmount < 0)
        {
            withdrawlAmount *= -1;
        }

        if (CreditAccount::monthsLate > 0 && !CreditAccount::isClosed)
        {
            double tmp = 0.01 * withdrawlAmount;
            withdrawlAmount += tmp;
            BankAccount::accountBalance -= withdrawlAmount;
        }
        else
        {
            BankAccount::accountBalance -= withdrawlAmount;
        }
    }
}

//does the monthly calculation for the credit account
void CreditAccount::monthlyCalc()
{
    if (BankAccount::accountBalance < 0)
    {
        CreditAccount::monthlyChargeRate = 0.05;
    }
    else
    {
        CreditAccount::isClosed=false;
        CreditAccount::monthsLate=1;
        CreditAccount::monthlyChargeRate = 0;
    }

    if (BankAccount::month < 12)
    {
        if (BankAccount::accountBalance < 0)
        {
            //keeps track of the monthly payments in this vector
            double amountPaid = 0;
            for (double i : CreditAccount::monthlyDepositAmount)
            {
                amountPaid += i;
            }

            if (amountPaid < 100)
            {
                CreditAccount::monthsLate++;
            }
            else
            {
                CreditAccount::monthsLate=1; //resets the months late counter
            }
        }
        else if (CreditAccount::monthsLate >= 6)
        {
            CreditAccount::monthsLate++;
            CreditAccount::isClosed = true;
        }

        //clears the vector for storing the monthly payments in
        CreditAccount::monthlyDepositAmount.clear();

        double monthlyPayment = CreditAccount::monthlyChargeRate * BankAccount::accountBalance;
        accountBalance = accountBalance + monthlyPayment;
        month++;
    }
    else
    {
        CreditAccount::endOfYear();
    }
}
//this just prints out the account status and information for the credit account class.
void CreditAccount::printStatus()
{
    string theMonth = BankAccount::returnMonthAsString();
    cout << "***************************************************************" << endl;
    cout << "*The account ID is: " << accountID << setprecision(2) << fixed << right <<setw(63-(20+accountID.length()))  << "*" << endl;
    cout << "*The account type is: " << accountType << right <<setw(63-(22+accountType.length()))  << "*" << endl;
    cout << "*The number of deposits this year so far is: " << numberOfDeposits << right <<setw(63-(45+to_string(numberOfDeposits).length()))  << "*" << endl;
    cout << "*The number of withdrawls this year so far is: " << numberOfWithdrawls << right <<setw(63-(47+to_string(numberOfWithdrawls).length()))  << "*" << endl;
    cout << "*The monthly interest rate is " << monthlyInterestRate << "%." << right <<setw(63-(28+to_string(monthlyInterestRate).length()))  << "*" << endl;
    cout << "*The yearly fee is: " << yearlyFee << right <<setw(63-(16+to_string(yearlyFee).length()))  << "*" << endl;
    cout << "*The current balance is: $" << accountBalance << right <<setw(63-(22+to_string(accountBalance).length()))  << "*" << endl;
    cout << "*The current month is: " << theMonth << right <<setw(63-(23+theMonth.length()))  << "*" << endl;
    if (CreditAccount::monthsLate > 1)
    {
        cout << "*The account is late by: " << CreditAccount::monthsLate-1 << " months." << right <<setw(63-(33+to_string(CreditAccount::monthsLate).length()))  << "*" << endl;
    }
    if (CreditAccount::isClosed)
    {
        cout << "*The account is closed and owes $" << (-1*BankAccount::accountBalance) << right <<setw(63-(28+to_string(BankAccount::accountBalance).length()))  << "*" << endl;
    }
    if (BankAccount::accountBalance > 0)
    {
        cout << "*The account is overpaid by $" << (BankAccount::accountBalance) << right <<setw(63-(25+to_string(BankAccount::accountBalance).length()))  << "*" << endl;
    }
    if (!CreditAccount::monthlyDepositAmount.empty())
    {
        double amountPaid = 0;
        for (double d:monthlyDepositAmount)
        {
            amountPaid += d;
        }
        cout << "*This month there has been $" << (amountPaid) << " deposited." << right <<setw(63-(35+to_string(amountPaid).length()))  << "*" << endl;
    }
    else
    {
        cout << "*This month there has been $" << (0.00) << " deposited." << right <<setw(63-(43))  << "*" << endl;
    }
    cout << "***************************************************************" << endl << endl;
}

void CreditAccount::endOfYear()
{
    numberOfDeposits = 0;
    numberOfWithdrawls = 0;
    accountBalance -= yearlyFee;
    month=1;
}

//*********************************************END OF CREDIT ACCOUNT CLASS********************************************\\

//*****************************************************DESTRUCTORS*****************************************************\\
//default bank account constructor
BankAccount::~BankAccount()
= default;

//default simpleSavings constructor
SimpleSavings::~SimpleSavings()
= default;

//AdvancedSavings Savings Destructor
AdvancedSavings::~AdvancedSavings()
= default;

//checking account destructor
CheckingAccount::~CheckingAccount()
= default;

//credit account destructor
CreditAccount::~CreditAccount()
= default;

//*************************************************END OF DESTRUCTORS*************************************************\\

//************************************************IN .CPP FILE METHODS************************************************\\

//passes the ID string by reference, then if it's empty will set it to a default zero value. otherwise, leaves it alone
void emptyID(string &ID)
{
    if (ID.empty())
    {
        cout << "Error, the ID was blank! Setting it to zero" << endl;
        ID = "0";
    }
}
//*********************************************END OF IN .CPP FILE METHODS*********************************************\\