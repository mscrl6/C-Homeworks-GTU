#include <stdio.h>
#include "util.h"
int main() {

int num1,num2,den1,den2;
/* An unitilized fractional number */
  int num3, den3;
/*getting 2 frictional number from user*/
printf("Please enter 2 frictional number's numerator and denominator:\n");
printf("first number's numerator:");
	scanf("%d",&num1);
printf("\nfirst number's denominator:");
	scanf("%d",&den1);
printf("\nsecond number's numerator:");
	scanf("%d",&num2);
printf("\nsecond number's denominator:");
	scanf("%d",&den2);
        printf("\n");
/*printing the numbers*/
    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");
/*end of printing the numbers*/

/*adding the numbers*/
    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
/*subtracting the numbers*/
    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
/*multiplying the numbers*/
    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
/*dividing the numbers*/
    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    return(0);
}
