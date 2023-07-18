#include <stdio.h>
#include "util.h"
int main(){

	int num1, num2,num3;
	/*taking two integer number from user for part1,part2 and part3 function.*/
	printf("Please enter 2 integer number for following functions\npart1: Calculating the GCD of these 2 numbers\npart2: Summing these 2 numbers\npart3: Multiplicating these 2 numbers\n");
	printf("first number: ");
	scanf("%d", &num1);
	printf("second number: ");
	scanf("%d", &num2);
	/*printing the GCD of these two numbers.*/
	printf("\nGCD(%d,%d) : %d\n",num1,num2, part1(num1, num2));
	/*part2 function takes these two numbers.*/
	part2(num1, num2);
	/*part3 function takes these two numbers.*/
	part3(num1, num2);
	/*taking a integer number from user for part4 function.*/
	printf("\nPlease enter a integer number between 1-10\n");
	scanf("%d", &num3);
	/*part4 function takes this number.*/
	part4(num3);
}
