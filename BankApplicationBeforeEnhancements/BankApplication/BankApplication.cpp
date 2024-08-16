// BankApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//
#include <iomanip> 
#include <iostream> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h>
#include <string> 
using namespace std;

class BankApplication
{
public:
    float getInitialDeposit()
    {

        return initialDeposit;
    }
    float getmonthlyDeposit()
    {
        return monthlyDeposit;
    }
    float getAnnualInterest()
    {
        return annualInterest;
    }
    int getNumberYears()
    {
        return numberYears;
    }
    float getInterestRate()
    {
        return interestRate;
    }
    int getNumMonth()
    {
        return numMonth;
    }
    float getOpeningAmount()
    {
        return openingAmount;
    }
    float getDepositedAmount()
    {
        return depositedAmount;
    }
    float getTotal()
    {
        return total;
    }
    void setInitialDeposit(float initialDeposit_a)
    {
        initialDeposit = initialDeposit_a;
    }
    void setMonthlyDeposit(float monthlyDeposit_a)
    {
        monthlyDeposit = monthlyDeposit_a;
    }
    void setAnnualInterest(float annualInterest_a)
    {
        annualInterest = annualInterest_a;
    }
    void setInterestRate(float InterestRate_a)
    {
        interestRate = InterestRate_a;
    }
    void setNumMonth(int NumMonth_a)
    {
        numMonth = NumMonth_a;
    }
    void setOpeningAmount(float OpeningAmount_a)
    {

        openingAmount = OpeningAmount_a;
    }
    float calculateOpeningAmount()
    {

        //openingAmount = OpeningAmount_a;
    }
    void setDepositedAmount(float DepositedAmount_a)
    {
        depositedAmount = DepositedAmount_a;
    }
    void setTotal(float total_a)
    {
        total = total_a;
    }
    void setNumberYears(int numberYears_a)
    {
        numberYears = numberYears_a;
    }

    float calculateInterest()
    {
        interest = (openingAmount + monthlyDeposit) * ((interestRate / 100) / 12);
        return roundFloat(interest);
    }
    float roundFloat(float num)
    {
        /*
        char st[20];
        sprintf(st, "%.2f", num);
        sscanf(st, "%f", &num);
        */
        float value = (int)(num * 100 + .5);

        return( (float)value / 100);

    }
private:
    float initialDeposit; // Starting Investing Ammount 
    float monthlyDeposit;
    float annualInterest;
    int numberYears;
    float interestRate;
    float interest;
    int numMonth;
    float openingAmount;
    float depositedAmount;
    float total;
};





int main()
{
    while (1)
    {
        BankApplication bankApplication;
        string initialInvestmentAmount;
        string monthlyDeposit;
        string interestRate;
        int numberYears;
        float tmp;

        cout << "Initial Investment Amount:  ";
        cin >> initialInvestmentAmount;
        if (initialInvestmentAmount.at(0) == '$')
            initialInvestmentAmount.erase(0);
        bankApplication.setOpeningAmount(bankApplication.roundFloat(std::stof(initialInvestmentAmount)));

        cout << "Monthly Deposit:  ";
        cin >> monthlyDeposit;
        if(monthlyDeposit.at(0) == '$')
            monthlyDeposit.erase(0);
        bankApplication.setMonthlyDeposit(std::stof(monthlyDeposit));

        cout << "Annual interest:  ";
        cin >> interestRate;
        if (interestRate.back() == '%')
            interestRate.pop_back();
         bankApplication.setInterestRate(std::stof(interestRate)); // Interest Rate
        cout << "Number of years:  ";
        cin >> numberYears;
        bankApplication.setNumberYears(numberYears);
        cout << "Press any key to continue..." << endl;
        cin >> tmp;
        bankApplication.calculateInterest();
        float newBalance = 0.0;
        float initialOpeningAmount = bankApplication.getOpeningAmount();
        cout << "Balance and Interest without Monthly deposit" << endl;
        for (int i = 0; i < numberYears * 12; i++)
        {
            cout << "Month  OpeningAmout  $Total     $interest   Closing Balance" << endl;
            cout << i + 1 << "           " << bankApplication.getOpeningAmount() << "          "
                << bankApplication.getOpeningAmount() << "    "
                << bankApplication.calculateInterest() << "          "
                << bankApplication.getOpeningAmount() + bankApplication.calculateInterest() << endl;
            bankApplication.setOpeningAmount(bankApplication.getOpeningAmount() + bankApplication.calculateInterest());
        }
        cout << endl << endl << endl;
        bankApplication.setOpeningAmount(initialOpeningAmount);
        cout << "Balance and Interest with Monthly deposit" << endl;
        for (int i = 0; i < numberYears * 12; i++)
        {
            cout << "Month  OpeningAmout   Deposited Amount   $Total     $interest   Closing Balance" << endl;
            cout << i+1 << "           " << bankApplication.getOpeningAmount() << "          " 
                << bankApplication.getmonthlyDeposit() << "                 " 
                << bankApplication.getmonthlyDeposit()+ bankApplication.getOpeningAmount() << "          "
                << bankApplication.calculateInterest() << "          "
                << bankApplication.getOpeningAmount() + bankApplication.calculateInterest() + bankApplication.getmonthlyDeposit() << endl << endl;
            bankApplication.setOpeningAmount(bankApplication.getOpeningAmount() + bankApplication.calculateInterest() + bankApplication.getmonthlyDeposit());

        }
        cout << "Press any key to continue..." << endl;
        cin >> tmp;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
