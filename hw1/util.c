#include <stdio.h>
#include "util.h"
int part1(int x, int y){
	/*checking if one of the number is equals to 0.*/
	if (y == 0) {
		return x;
	}
	if (x == 0) {
		return y;
	}/*end checking*/
	/*starting a while loop to calculate the GCD.*/
	while (x != 0 || y != 0) {
		int b, z;
		b = x / y;
		z = x - y * (b);
		x = y;
		y = z;
		if (x == 0) {
			return y;
		}
		if (y == 0) {
			return x;
		}
	}/*end calculating the GCD*/
}
/*end part1*/

void part2(int x, int y){
	/*part 2 function starts summing these 2 numbers.*/
	printf("\nFirst number: %d\nSecond number: %d\n", x, y);
	printf("%5d\n%5d\n+\n-----\n%5d", x, y, x + y);
	printf("\n");
}
/*end part2*/

void part3(int x, int y){
	/*part3 function starts multiplying these 2 numbers.*/
	int units,tens,hundreds;
	/*checking if y number is 3 digits number.*/
	if(100<=y&&y<=999||-100>=y&&y>=-999){
	units = (y % 100)%10;
	tens = (y % 100)/10;
	hundreds = y / 100;
	printf("\nFirst number: %d\nSecond number: %d\n", x, y);
	printf("%7d\n%7d\n*\n-------\n%7d\n%6d\n%5d\n*\n-------\n%7d",x,y,units*x,tens*x,hundreds*x,x*y);
	printf("\n");
	}
	/*checking if y number is 2 digits number.*/
	if (10 <= y && y <= 99 || -10>=y&&y>=-99 ){
		units = (y % 100) % 10;
		tens = (y % 100) / 10;
		printf("\nFirst number: %d\nSecond number: %d\n", x, y);
		printf("%7d\n%7d\n*\n-------\n%7d\n%6d\n*\n-------\n%7d", x, y, units * x, tens * x, x * y);
		printf("\n");
	}
	/*checking if y number is 1 digit number.*/
	if(y>-10&&y<=0||y>0&&y<10){
		printf("\nFirst number: %d\nSecond number: %d\n", x, y);
		printf("%7d\n%7d\n*\n-------\n%7d", x, y, x * y);
		printf("\n");
	}		
}
/*end part3*/

void part4(int x){
	if (5 < x && x <= 10) {
		printf("The integer you entered is greater than 5.\n");
	}
	else if (1 <= x && x <= 5) {
		printf("The integer you entered is less than or equal to 5.\n"); 
	}
	else {
		printf("Invalid input.\n");
	}
}
/*end part4*/
