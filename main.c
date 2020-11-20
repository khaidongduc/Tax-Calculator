#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define BUFFSIZE 32

/**
 * @brief Get the tax that correspond to income (in thousand VND)
 *
 * @param income the income in thousand VND
 * @return double the tax
 */
double getTax(double income) {
    if (income <= 5000) return 0.05;
    if (income <= 10000) return 0.1;
    if (income <= 18000) return 0.15;
    if (income <= 32000) return 0.2;
    if (income <= 52000) return 0.25;
    if (income <= 80000) return 0.3;
    return 0.35;
}

#define RATE_PENSION 0.05
#define RATE_HEALTH 0.01
#define DEPENDANT_COST 1600.0
#define ALLOWANCE 4000.0

void input(double *income, char *pensionContribution, char *healthInsurance,
           int *numDependant, double *charity) {
    printf("Enter personal information <in thousand VND>\n");
    *income = atof(getInput(validateDouble, "Income for the current month:",
                            "Invalid input, try again."));

    *pensionContribution =
        getInput(validateYN, "Pension contributions (5%) y/n?",
                 "You must press 'y' or 'n' only, try again")[0];

    *healthInsurance = getInput(validateYN, "Pension contributions (5%) y/n?",
                                "You must press 'y' or 'n' only, try again")[0];

    *numDependant = atoi(getInput(
        validateInt,
        "Number of Dependants < 18 years old:", "Invalid input, try again."));

    *charity = atof(getInput(validateDouble,
                             "Gift of Charity:", "Invalid input, try again."));
}

double calc_tax(double income, char pensionContribution, char healthInsurance,
                int numDependant, double charity) {
    /*
    printf("%f %c %c %d %f", income, pension_contribution, health_insurance,
           num_dependant, charity);
    */
    double allowance = ALLOWANCE;
    double pensionDeduct =
        (pensionContribution == 'y') ? income * RATE_PENSION : 0;
    double healthDeduct = (healthInsurance == 'y') ? income * RATE_HEALTH : 0;
    double dependantDeduct = numDependant * DEPENDANT_COST;
    double charityDeduct = charity;

    double taxDeduct = allowance + pensionDeduct + healthDeduct +
                       dependantDeduct + charityDeduct;
    double taxableIncome = income - taxDeduct;
    if (taxableIncome < 0) taxableIncome = 0;
    double taxAmount = taxableIncome * getTax(taxableIncome);
    double netIncome = income - taxAmount;

    printf("\n");
    printf("Gross Income:             %10.2f\n", income);
    printf("Deduction\n");
    printf("  Personal Allowance:     %10.2f\n", allowance);
    printf("  Pension Contributions:  %10.2f\n", pensionDeduct);
    printf("  Health Insurance:       %10.2f\n", healthDeduct);
    printf("  Dependant:              %10.2f\n", dependantDeduct);
    printf("  Charity:                %10.2f\n", charityDeduct);
    printf("--------------------------------------------\n");
    printf("Total Deduction:          %10.2f\n", taxDeduct);
    printf("Taxable Income:           %10.2f\n", taxableIncome);
    printf("Tax:                      %10.2f\n", taxAmount);
    printf("Net Income:               %10.2f\n", netIncome);
}

int main() {
    printf("Income tax Calculator\n");
    printf("======================\n");
    double income, charity;
    int numDependant;
    char pensionContribution, healthInsurance;

    setBufferSize(BUFFSIZE);
    while (true) {
        input(&income, &pensionContribution, &healthInsurance, &numDependant,
              &charity);
        calc_tax(income, pensionContribution, healthInsurance, numDependant,
                 charity);
        if (getInput(validateYN, "Another run (y/n)? ",
                     "You must press 'n' or 'y' only, try again")[0] == 'n')
            break;
    }
}