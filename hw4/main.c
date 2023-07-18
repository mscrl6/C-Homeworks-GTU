#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*defining the functions for creating a receipt*/
void receipt(FILE* file, char student, float total);
void print_menu();
void print_above();
void print_bottom(char student, float total);
void order();

/*
defining the function for the Stone Paper Scissors game
*/
void game();

/*
printing the menu to let the user choose a product.
*/
void print_menu() {
	FILE *menu;
	menu=fopen("menu.txt","r+");
	char c;
	int line=0;
	int print = 0;
	printf("Yemek Listesi:");
	while((c = fgetc(menu)) != EOF){
		if(c == '\n'){
			line++;
			print = 0;
		}
		
		if (line >= 1) {
			if (!print && (c != '\n' && c != ' ')) {
				print = 1;
				printf("\n");
				printf("%d. ", line);
			}
			if (print && (c!='\n') && (c<48 || c>57) && (c!='.')) {
				putchar(c);
			}
			
		}
	}
	printf("\n");
	fclose(menu);
}
/*
printing the above part of the receipt.
*/
void print_above(){
	time_t t = time(NULL);
	printf("\n-------------------------------------------\n");
	printf("210104004014       %s", ctime(&t)); //using ctime function to print the current date.
	printf("-------------------------------------------\n");
	printf("Product 			  Price(TL)\n");
	printf("-------------------------------------------\n");
}

/*
printing the bottom part of the receipt.
*/
void print_bottom(char student, float total) {
	printf("Total %37.2f\n", total);
	float discount = 0;
	float price = 0;
	float VAT;

	/*
	Checking whether the user is student or not
	*/
	if (student == 'Y') {
		discount = total * 0.125; //If the user is student we will offer a %12.5 discount.
		printf("Student Discount %26.2f\n", discount);
		printf("-------------------------------------------\n");
	}
	else if (student == 'N' && total >= 150) {
		discount = total * 0.1; //If the user is not student but the total price is greater than 150TL we will offer a %10 discount.
		printf("Total discount %40.2f\n", discount);
		printf("-------------------------------------------\n");
	}
	else if (student == 'N' && total < 150) {
		price = total; //If the user is not student and the total price is less than 150TL there is no discount.
		printf("-------------------------------------------\n");
	}
	price = total - discount;
	printf("Price %37.2f\n", price);
	VAT = price * 0.18; //Calculating the VAT.
	printf("Price + VAT %31.2f\n", price + VAT);
}

/*
printing the receipt to console and the txt file.
*/
void receipt(FILE *file,char student,float total) {
	print_above(); //Printing the above part of the receipt.
	char c;
	file = fopen("receipt.txt", "a+"); //Opening the receipt.txt file for saving the receipt to file.
	while ((c = fgetc(file)) != EOF) {
		printf("%c", c);
	}
	fprintf(file, "Total price: %.2f", total); //Saving the total price to the receipt.txt file.
	print_bottom(student, total); //Printing the bottom part of the receipt.
	fclose(file);
}

/*
receiving the order.
*/
void order() {
	int product;
	int servings;
	char student;
	int line = 0; //This is for finding the products from menu.txt file.

	float price;
	float total = 0;
	char c;

	int keb = 0, lah = 0, pid = 0, don = 0, kol = 0, su = 0, kun = 0, sut = 0, cor = 0, sal = 0;
	float tkeb = 0, tlah = 0, tpid = 0, tdon = 0, tkol = 0, tsu = 0, tkun = 0, tsut = 0, tcor = 0, tsal = 0;

	FILE* menu; //File pointer for the menu.txt file.
	FILE* rcp;	//File pointer for the receipt.txt file.
	rcp = fopen("receipt.txt", "w+"); //Opening the receipt.txt

	/*
	Starting an infinite while loop. It will break when user enter "0".
	*/
	while (1) {
		menu = fopen("menu.txt", "r"); //Opening the menu.txt
		line = 0;	
		/*
		Starting an infinite while loop. It will break if user enter a value between 1 and 10. 
		If user enter a invalid input it will warn the user.
		*/
		while (1) {
			printf("Please choose a product(1 - 10) : ");
			scanf("%d", &product);
			if (product < 0 || product>10) {
				printf("Invalid input. Please choose again.\n");
			}
			else {
				break;
			}
		}

		/*
		If product selection is finished (product=0) the program asks the user if he/she is student or not.
		*/
		if (product == 0) {
			printf("Are you student? (Y/N): ");
			scanf(" %c", &student);
			break;
		}

		/*
		If product is not 0 the program will keep asking for the servings.
		*/
		while (1) {
			printf("How many servings do you want? ");
			scanf("%d", &servings);
			if (servings <= 0) {
				printf("Please enter a number greater than 0.\n");
			}
			else {
				break;
			}
		}


		/*
		Taking the product name and price from the menu.txt
		*/
		if (menu == NULL) {
			printf("Error!. \n");
		}
		while ((c = fgetc(menu)) != EOF) {

			if (c == '\n') {
				line++; //when c='n' the line is line + 1. Line will continue to increase until line equals the product.
			}

			/*
			If line=product we can read the price of the product from the file.
			For example if user choose product 2 (Which is 3th line in the txt file) 
			line counter will start from 0 and continue to increase until it equals 2.
			When it equals to 2 (which is 3th in the txt file) the program will read price of the product.
			*/
			if (line == product) {
				fscanf(menu, "%*s	%f", &price); //Reading the price of the given product from menu.txt.

				/*
				Starting a switch-case to print the servings*name and servings*price of the product to receipt.txt file.
				Also in this switch-case, the program calculates the total price. Which is 0 at the beginning.
				*/
				switch (line) {
					case 1: {
						keb = servings;
						tkeb = price * servings;
						total += tkeb;
						fprintf(rcp, "%d* %-30s %9.2f\n", keb,"Kebap", tkeb);
						break;
					}
					case 2: {
						lah = servings;
						tlah = price * servings;
						total += tlah;
						fprintf(rcp, "%d* %-30s %9.2f\n", lah,"Lahmacun", tlah);
						break;
					}
					case 3: {
						pid = servings;
						tpid = price * servings;
						total += tpid;
						fprintf(rcp, "%d* %-30s %9.2f\n", pid,"Pide", tpid);
						break;
					}
					case 4: {
						don = servings;
						tdon = price * servings;
						total += tdon;
						fprintf(rcp, "%d* %-30s %9.2f\n", don,"Doner", tdon);
						break;
					}
					case 5: {
						kol = servings;
						tkol = price * servings;
						total += tkol;
						fprintf(rcp, "%d* %-30s %9.2f\n", kol,"Kola", tkol);
						break;
					}
					case 6: {
						su = servings;
						tsu = price * servings;
						total += tsu;
						fprintf(rcp, "%d* %-30s %9.2f\n", su,"Su", tsu);
						break;
					}
					case 7: {
						kun = servings;
						tkun = price * servings;
						total += tkun;
						fprintf(rcp, "%d* %-30s %9.2f\n", kun,"Kunefe", tkun);
						break;
					}
					case 8: {
						sut = servings;
						tsut = price * servings;
						total += tsut;
						fprintf(rcp, "%d* %-30s %9.2f\n", sut,"Sutlac", tsut);
						break;
					}
					case 9: {
						cor = servings;
						tcor = price * servings;
						total += tcor;
						fprintf(rcp, "%d* %-30s %9.2f\n", cor,"Corba", tcor);
						break;
					}
					case 10: {
						sal = servings;
						tsal = price * servings;
						total += tsal;
						fprintf(rcp, "%d* %-30s %9.2f\n", sal,"Salata", tsal);
						break;
					}
					default: {
						break;
					}
				}
			}
		}
	}
	fclose(rcp); //Closing the receipt.txt
	receipt(rcp, student, total); //Sending the rcp pointer, whether the user is student or not and the total price.
	fclose(menu); //Closing the menu.txt
}
/*--------------------------------------------------------------------------------------------------------------------*/

/*
Function for the Stone Paper Scissors game.
*/
void game() {
	int user_choice;
	int computer_choice;
	char play_again;
	/*
	Starting an infinite while loop. It will break when user enter 'N'.
	*/
	while (1) {
		printf("Please make a choice!\n");
		printf("1: Stone, 2: Paper, 3: Scissors\n");
		scanf("%d", &user_choice); //Taking the choice input from user.

		/*
		Defining the computer's choice against user randomly.
		*/
		srand(time(0));
		computer_choice = 1 + rand() % 3;
		
		switch (user_choice) {
			case 1: {
				if (computer_choice == 1) {
					printf("You chose Stone. I chose Stone. It's a tie!\n\n");
				}
				else if (computer_choice == 2) {
					printf("You chose Stone. I chose Paper. I won!\n\n");
				}
				else if (computer_choice == 3) {
					printf("You chose Stone. I chose Scissors. You won!\n\n");
				}

				/*
				Asking the user whether he/she wants to play again or not.
				*/
				while (1) {
					printf("Do you want to play again? (Y/N): ");
					scanf(" %c", &play_again);
					if (play_again == 'N' || play_again == 'Y') {
						if (play_again == 'N') {
							printf("Well played! Goodbye...\n"); //If the user selects 'N' the program will be finished.
							exit(0);
						}
						else {
							break;
						}
					}
					else {
						printf("Invalid input.\n");
					}
				}
				break;
			}
			case 2: {
				if (computer_choice == 1) {
					printf("You chose Paper. I chose Stone. You won!\n\n");
				}
				else if (computer_choice == 2) {
					printf("You chose Paper. I chose Paper. It's a tie!\n\n");
				}
				else if (computer_choice == 3) {
					printf("You chose Paper. I chose Scissors. I won!\n\n");
				}
				while (1) {
					printf("Do you want to play again? (Y/N): ");
					scanf(" %c", &play_again);
					if (play_again == 'N' || play_again == 'Y') {
						if (play_again == 'N') {
							printf("Well played! Goodbye...\n"); //If the user selects 'N' the program will be finished.
							exit(0);
						}
						else {
							break;
						}
					}
					else {
						printf("Invalid input.\n");
					}
				}
				break;
			}
			case 3: {
				if (computer_choice == 1) {
					printf("You chose Scissors. I chose Stone. I won!\n\n");
				}
				else if (computer_choice == 2) {
					printf("You chose Scissors. I chose Paper. You won!\n\n");
				}
				else if (computer_choice == 3) {
					printf("You chose Scissors. I chose Scissors. It's a tie!\n\n");
				}
				while (1) {
					printf("Do you want to play again? (Y/N): ");
					scanf(" %c", &play_again);
					if (play_again == 'N' || play_again == 'Y') {
						if (play_again == 'N') {
							printf("Well played! Goodbye...\n"); //If the user selects 'N' the program will be finished.
							exit(0);
						}
						else {
							break;
						}
					}
					else {
						printf("Invalid input.\n");
					}
				}
				break;
			}
			default: {
				printf("You entered a invalid option.\n");
				while (1) {
					printf("Do you want to play again? (Y/N): ");
					scanf(" %c", &play_again);
					if (play_again == 'N' || play_again == 'Y') {
						if (play_again == 'N') {
							printf("Well played! Goodbye...\n"); //If the user selects 'N' the program will be finished.
							exit(0);
						}
						else {
							break;
						}
					}
					else {
						printf("Invalid input.\n");
					}
				}
				break;
			}

		}
	}
}
int main() {

	/*
	Calling the print_menu and order function for the menu task.
	*/
	print_menu();
	order();
	printf("\n----------------------------------------------------------\n");
	/*
	Calling the game function for the game task.
	*/	
	printf("Welcome to the Stone Paper Scissors Game!\n");
	game();

}
