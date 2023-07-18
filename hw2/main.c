#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Starting leapYear function to perform the calculation based on the year
void leapYear(int year) 
{
	if (year%4 == 0) {
		if (year % 100 == 0 && year%400!=0){
			printf("%d is not a leap year.\n", year);
		}
		else if (year % 4000 == 0) {
			printf("%d is not a leap year.\n", year);
		}
		else {
			printf("%d is a leap year.\n", year);
		}
	}

	else {
		printf("%d is not a leap year.\n", year);
	}
		printf("************************************\n");
}// END leapYear

// Starting printScientific function to print the result if output format is 'S'
void printScientific(double result, int m, int n) {
	// Rounding the result to n decimal places
	double rounded_result = round(result * pow(10, n)) / pow(10, n);
	// Calculating the exponent
	int exponent = floor(log10(rounded_result));
	// Calculating the coefficient
	double coefficient = rounded_result / pow(10, exponent);
	// Printint the result in scientific notation format
	printf("%0*.*fe%d\n", m + 1, n, coefficient, exponent);
}

// Starting enhancedCalculator function to perform the calculation based on the output format
void enhancedCalculator(char outputformat)
{		double Snum1, Snum2;
		double Inum1,Inum2;
		int factnum;
		int m, n;
		char op;
		double result;
		// If output format is "S"
		if (outputformat == 'S')
		{	
			// Taking m and n values from user
			while(1){
			printf("Enter m and n values (m should be bigger than n): \n");	
			printf("m: ");
			scanf("%d", &m);
			printf("n: ");
			scanf("%d", &n);
			if(n>m){
			printf("m should be bigger than n.\n");
			}
			else{
			break;
			}

			}
			// Taking the operation from user
			printf("Enter the operation (+, -, *, /,!,^,%%): ");
			scanf(" %c", &op);

			// Checking if operation is "!". Because if the operation is '!' we just need one operand.
			if (op == '!')
			{
				printf("Enter the operand: ");
				scanf("%d", &factnum);
			}

			// If operation is not '!' we need 2 operand.
			else if (op == '+' || '-' || '*' || '/' || '^' || '%')
			{
				printf("Enter the first operand: ");
				scanf("%lf", &Snum1);
				printf("Enter the second operand: ");
				scanf("%lf", &Snum2);
			}

			// Checking if operand is invalid
			else
			{
				printf("You entered a wrong operation.");
			}
		// Starting switch-case for the calculations based on the operand.
		switch (op)
		{
			// Checking if operand is '+'
			case '+':
			{	
				result = Snum1 + Snum2;
				printScientific(result,  m,  n); // Sending the result, m and n values to printScientific function to print.
				break;
			}

			// Checking if operand is '-'
			case '-':
			{
				result = Snum1 - Snum2;
				printScientific(result, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}
			
			// Checking if operand is '*'
			case '*':
			{
				result = Snum1 * Snum2;
				printScientific(result, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}

			// Checking if operand is '/'
			case '/':
			{
				result = Snum1 / Snum2;
				printScientific(result, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}

			// Checking if operand is '!'
			case '!':
			{
				int i;
				double fact = 1;

				// Calculating the factorial of factnum with using for loop.
				for (i = 1; i <= factnum; i++)
				{
					fact = fact * i;
				}
				printScientific(fact, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}

			// Checking if operand is ^
			case '^':
			{
				int i = 0;
				double sum = 1;

				// Calculating the num1^num2 with using while loop
				while (i < Snum2)
				{
					sum = sum * Snum1;
					i++;
				}
				printScientific(sum, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}
			case '%':
			{
				result=(double)((int)Snum1 % (int)Snum2);
				printScientific(result, m, n); // Sending the result, m and n values to printScientific function to print.
				break;
			}
			// Checking if operand is invalid
			default:
			{
				printf("You entered a wrong operand.");
				break;
			}
		}
		}

		// Checking if the format is I
		if (outputformat == 'I')
		{
			// Taking the operation from user
			printf("Enter the operation (+, -, *, /,!,^,%%): ");
			scanf(" %c", &op);

			// Checking if operation is "!". Because if the operation is "!" we just need one operand.
			if (op == '!')
			{
				printf("Enter the operand: ");
				scanf("%d", &factnum);
			}

			// If operation is not "!" we need 2 operand.
			else if (op == '+' || '-' || '*' || '/' || '^' || '%')
			{
				printf("Enter the first operand: ");
				scanf("%lf", &Inum1);
				printf("Enter the second operand: ");
				scanf("%lf", &Inum2);
			}
			else {
				printf("You entered a wrong operation.");
			}

			// Checking switch case
		switch (op)
		{
			// Checking if operand is +
			case '+':
			{
				printf("%d + %d = %d", (int)Inum1, (int)Inum2, (int)Inum1 + (int)Inum2);
				break;
			}

			// Checking if operand is -
			case '-':
			{
				printf("%d - %d = %d", (int)Inum1, (int)Inum2, (int)Inum1 - (int)Inum2);
				break;
			}

			// Checking if operand is *
			case '*':
			{
				printf("%d * %d = %d", (int)Inum1, (int)Inum2, (int)Inum1 * (int)Inum2);
				break;
			}

			// Checking if operand is /
			case '/':
			{
				printf("%d / %d = %d", (int)Inum1, (int)Inum2, (int)Inum1 / (int)Inum2);
				break;
			}

			// Checking if operand is !
			case '!':
			{
				int i;
				int fact = 1;

				// Calculating the factnum! with using for loop
				for (i = 1; i <= factnum; i++)
				{
					fact = fact * i;
				}
				printf("%d!= %d", factnum, fact);
				break;
			}

			// Checking if operand is ^
			case '^':
			{
				int i = 0;
				int sum = 1;

				// Calculating the num1^num2 with using while loop
				while (i < Inum2)
				{
					sum = sum * (int)Inum1;
					i++;
				}
				printf("%d ^ %d = %d", (int)Inum1, (int)Inum2, sum);
				break;
			}

			// Checking if operand is %
			case '%':
			{
				printf("%d", (int)Inum1 % (int)Inum2);
				break;
			}
			// Checking if operand is invalid
			default:
			{
				printf("You entered a wrong operand.");
				break;
			}
		}
		}
			printf("\n************************************\n");

}
// END enhancedCalculator

// Starting gradeCalculator function to perform the calculation based on the grades
void gradeCalculator(double exam1, double exam2, double exam3, double assignment1, double assignment2)
{
		double finalgrade;
		// Calculating the final grade
		finalgrade = ((exam1 + exam2 + exam3) * 0.6 / 3) + ((assignment1 + assignment2) * 0.4 / 2);

		// Checking whether student passed or failed the exam
		if (finalgrade >= 60)
		{
			printf("Final Grade: %.2lf Passed!", finalgrade);
		}
		if (finalgrade < 60) 
		{
			printf("Final Grade: %.2lf Failed!", finalgrade);
		}
		printf("\n************************************");
}// END gradeCalculator

int main()
{		
		// Getting year information from user for leapYear function.
		int year;
		printf("Please enter a year: ");
		scanf("%d", &year);
		leapYear(year);// Sending the year to the function.


		// Getting the format of output from user for enhancedCalculator function.
		char outputformat;
		printf("Enter the format of output (S or I): ");
		scanf(" %c", &outputformat);
		enhancedCalculator(outputformat);// Sending format of output to the function.

		// Getting the exam grades from user for gradeCalculator function.
		double exam1, exam2, exam3, assignment1, assignment2;
		while(1){
		printf("Enter 3 exam grades of student: ");
		scanf("%lf %lf %lf", &exam1, &exam2, &exam3);
		if(exam1>100||exam2>100||exam3>100){
		printf("The grades should be smaller than 100 or equals 100. Enter again.\n");		
		}
		else {
		break;
		}
		}
		// Getting the assignmnet grades
		while(1){
		printf("\nEnter 2 assignment grades of student: ");
		scanf("%lf %lf", &assignment1, &assignment2);
		if(assignment1>100||assignment2>100){
		printf("The grades should be smaller than 100 or equals 100. Enter again.\n");		
		}
		else{
		break;
		}
}
		gradeCalculator(exam1, exam2, exam3, assignment1, assignment2);// Sending exam and assignment grades to the function.
}

