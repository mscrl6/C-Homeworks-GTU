#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
	This function prints the letters that are counted.
*/
void print_letter(int letter[]){
	int i;
	for (i = 0; i < 26; i++) {
		printf("%c: %d", ('A'+i), letter[i]);
		printf("\n");
		 //J was 'A' at first. At  end of the each for loop this letter increases: B, C, D....Z;
	}
}

/*
	This function converts the lowercase letters to uppercase.
*/
char letter_conversion(char c) {
		if (c >= 'a' && c <= 'z') {
			return c-32;
		}	
		else{
			return c;
		}
 //If the letter is lower case letter this function makes it uppercase latter using ASCII table. 
}

void part1() {

	int letter[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //each index corresponds to a letter
	char enteredFile[50];
	char c;
	FILE* text;	
	while(1){
		printf("Enter a file name: ");
		scanf("%s",enteredFile);
		text = fopen(enteredFile, "r");	
		if(text == NULL) {
			printf("Error! Enter again.\n");
		}
		else{
			break;
		}
	}
	while ((c = fgetc(text)) != EOF) {
		/*
		if the letters are lowercase we send the letter to conversion function.
		and increasing the index of the letter.
		*/
		if (c >= 'a' && c <= 'z') {
			letter[letter_conversion(c) - 'A']++;
		
		}
		else if (c >= 'A' && c <= 'Z') {
			letter[c - 'A']++;
		}
	}
	fclose(text);
	print_letter(letter);
}
//END OF THE PART1 FUNCTION
/*------------------------------------------------------------------------------------------------------------------*/

/*
	Enumerating the colors
*/
typedef enum {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	ORANGE
}Color;

/*
	ColorMixer function takes two color and one function pointer.
*/
Color colorMixer(Color c1, Color c2, Color(*Mixer)(Color, Color)) {
	return (*Mixer)(c1, c2);
}

/*
	Mixer function mixes the colors.
*/
Color Mixer(Color x, Color y) {
							/*RED*/	  /*GREEN*/   /*BLUE*/   /*YELLOW*/	   /*ORANGE*/
	double color[5][3] = { {1.0,0,0}, {0,1.0,0}, {0,0,1.0}, {0.5,0.5,0}, {0.5,0.4,0.2} };
	int i;
	double mixed[3]; //Its an length-3 vector array to calculate the closest color.
	mixed[0] = (color[x][0] + color[y][0]) / 2.0;
	mixed[1] = (color[x][1] + color[y][1]) / 2.0;
	mixed[2] = (color[x][2] + color[y][2]) / 2.0;

	Color closest;
	int closestColor;
	double minDistance = 100.0; //Defining a random big distance. It will change in the for loop.

	/*
		RED=0, ORANGE=4
	*/
	for (i = RED; i <= ORANGE; i++) {
		/*
			 Calculating the Euclidean distance.
		*/
		double distance = sqrt(pow(mixed[0] - color[i][0], 2)
						      + pow(mixed[1] - color[i][1], 2)
					          + pow(mixed[2] - color[i][2], 2));
		if (distance < minDistance) {
			minDistance = distance; //Updating the minimum distance if calculated distance is smaller than minDistance.
			closestColor = i; //Updating the index of the closest color.
		}
	}
	switch (closestColor) {
		case RED: {
			closest = RED;
			break; 
		}
		case GREEN: {
			closest = GREEN;
			break;
		} 
		case BLUE: {
			closest = BLUE;
			break;
		} 
		case YELLOW: {
			closest = YELLOW;
			break;
		} 
		case ORANGE: {
			closest = ORANGE;
			break;
		}	   
	}
	return closest;
}
void part2() {
	char color1,color2;
	Color clr1,clr2;
	printf("Welcome to the Color Mixer Program!\n");
	while (1) {
		/*
			Taking inputs for color1 and color2.
		*/
		printf("Enter Color 1 (r,g,b,y,o): ");
		scanf(" %c", &color1);
		if (color1 != 'r' && color1 != 'g' && color1 != 'b' && color1 != 'y' && color1 != 'o') {
			printf("Invalid input.\n"); //If the color is not r,g,b,y or o program prompts an error message.
		}
		else {
			printf("Enter Color 2 (r,g,b,y,o): ");
			scanf(" %c", &color2);
			if(color2 != 'r' && color2 != 'g' && color2 != 'b' && color2 != 'y' && color2 != 'o'){
				printf("Invalid input.\n");
			}
			else {
				break;
			}
		}

	}

	switch (color1) {
		case 'r': {
			clr1 = RED;
			break;
		}
		case 'g': {
			clr1 = GREEN;
			break;
		}
		case 'b': {
			clr1 = BLUE;
			break;
		}
		case 'y': {
			clr1 = YELLOW;
			break;
		}
		case 'o': {
			clr1 = ORANGE;
			break;
		}
	}
	switch (color2)
	{
		case 'r': {
			clr2 = RED;
			break;
		}
		case 'g': {
			clr2 = GREEN;
			break;
		}
		case 'b': {
			clr2 = BLUE;
			break;
		}
		case 'y': {
			clr2 = YELLOW;
			break;
		}
		case 'o': {
			clr2 = ORANGE;
			break;
		}
	}

	Color mixed = colorMixer(clr1, clr2, Mixer); //Sending the colors and Mixer function to ColorMixer function.
	printf("Mixed color: ");
	switch (mixed) {
		case RED: {
			printf("RED: [1, 0, 0]  \n");
			break;
		}
		case GREEN: {
			printf("GREEN: [0, 1, 0] \n");
			break;
		}
		case BLUE: {
			printf("BLUE: [0, 0, 1] \n");
			break;
		}
		case YELLOW: {
			printf("YELLOW: [0, 0, 1] \n");
			break;
		}
		case ORANGE: {
			printf("ORANGE: [0.5, 0.4, 0.2] \n");
			break;
		}
	}
}




/*------------------------------------------------------------------------------------------------------------------*/
/*
	Checking whether the game is end or continue.
*/
int check_game_status(char tictactoe[3][3]) {
	int i=0, j=0;
	//row checker
	for (i = 0; i < 3; i++) {
		if (tictactoe[i][0]!='_'
			&& tictactoe[i][0] == tictactoe[i][1]
			&& tictactoe[i][1] == tictactoe[i][2]) {
			return 1;
		}

	}
	//column checker
	for (i = 0; i < 3; i++) {
		if (tictactoe[0][i] != '_'
			&& tictactoe[0][i] == tictactoe[1][i]
			&& tictactoe[1][i] == tictactoe[2][i]) {
			return 1;
		}
	}
	//Cross checker
	if (tictactoe[0][0] != '_'
		&& tictactoe[0][0] == tictactoe[1][1]
		&& tictactoe[1][1] == tictactoe[2][2]) {
		return 1;
	}
	else if (tictactoe[0][2] != '_'
		&& tictactoe[0][2] == tictactoe[1][1]
		&& tictactoe[0][2] == tictactoe[2][0]) {
		return 1;
	}

	//Is the board full checker
	int counter=0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (tictactoe[i][j] == 'O' || tictactoe[i][j] == 'X') {
				counter++;
			}
		}
	}
	if (counter == 9) {
		return 2; //The board is full, it's tie
	}	
	return 0; //Continue 
}

/*
	Checking if the inputs entered by user 1 are valid or not.
*/
int is_it_valid_user1(int user1x, int user1y, char tictactoe[3][3]) {
	int valid1;
	if (tictactoe[user1x-1][user1y-1] == 'O' || tictactoe[user1x-1][user1y-1] == 'X') {
		valid1 = 0; //If the index is not empty it is an invalid input.
	}
	else {
		valid1 = 1; //Continue
	}
	return valid1;
}

/*
	Checking if the inputs entered by user 2 are valid or not.
*/
int is_it_valid_user2(int user2x, int user2y, char tictactoe[3][3]) {
	int valid2;
	if (tictactoe[user2x-1][user2y-1] == 'O' || tictactoe[user2x-1][user2y-1] == 'X') {
		valid2 = 0; //If the index is not empty it is an invalid input.
	}
	else {
		valid2 = 1; //Continue
	}
	return valid2;
}

/*
	This function prints the game board after each move.
*/
void print_board(char tictactoe[3][3]) {
	int i, j;
	for (i = 0; i <= 2; i++) {
		for (j = 0; j <= 2; j++) {
			if (tictactoe[i][j] != 'O' && tictactoe[i][j] != 'X') {
				tictactoe[i][j] = '_'; //If in the index of array is empty, not equals to X or O, the index is equals to "_".
			}
			printf("%c ", tictactoe[i][j]); //printing the array.
		}
		printf("\n"); //New line after each row.
	}
}

/*
	Gameplay function.
*/
void part3() {
	char tictactoe[3][3]; //Defining an array for printing the board.
	char play_again;
	printf("\nWelcome to the Tic Tac Toe game!\n");

	while (1) {

		//USER1
		while(1) {
			int user1x = 0, user1y = 0; 
			/*
				Taking the movement inputs from user1
			*/
			printf("Player 1 (X), enter your move. (row, col): ");
			scanf("%d %d", &user1x, &user1y);
				
				/*
					Checking if the input is valid (it should be between 1-4).
				*/
				if (user1x > 0 && user1y > 0 && user1x < 4 && user1y < 4) {
					/*
						Checking if the input is valid. The index of the array should be empty. 
					*/
					if (is_it_valid_user1(user1x, user1y, tictactoe) == 1) {
						tictactoe[user1x - 1][user1y - 1] = 'X'; //If it is empty the index is equals to X now.
						print_board(tictactoe); //Printing the board.

						/*
							Checking whether game is over or continue.
						*/
						if (check_game_status(tictactoe) == 1 || check_game_status(tictactoe) == 2) {
							if (check_game_status(tictactoe) == 1) {
								printf("Player 1 (X) wins!");
							}
							else if (check_game_status(tictactoe) == 2) {
								printf("Its's a tie!. Game over...");
							}

							/*
								Asking the user if he/she wants to play again.
							*/
							do {
								printf("\nDo you want to play again?(Y/N): ");
								scanf(" %c", &play_again);
								if (play_again == 'Y') {
									printf("\nNew game...\n");
									part3();
								}
								else if (play_again=='N'){
									printf("Thanks for playing.\n");
									exit(0);
								}
								else {
									printf("Invalid input. Please enter Y or N.\n");
								}
							} while (play_again != 'Y' && play_again != 'N');

						}
						break;
					}

					/*
						If the index of the array is not empty, program prompts an error message.
					*/
					else if (is_it_valid_user1(user1x, user1y, tictactoe) == 0) {
						printf("Invalid input. You can't enter a value that had been entered.\n");
					}
				}
				/*
					If the inputs are not between 1-3 the program prompts an error message.
				*/
				else{
					printf("Please enter a value between 1 and 3.\n");
				}
		} 


		//USER2
		while(1) {
			int user2x = 0, user2y = 0;
			/*
				Taking the movement inputs from user1
			*/
			printf("Player 2 (O), enter your move. (row, col): ");
			scanf("%d %d", &user2x, &user2y);

			/*
				Checking if the input is valid (it should be between 1-3).
			*/
				if (user2x > 0 && user2y > 0 && user2x < 4 && user2y < 4) {
					/*
						Checking if the input is valid. The index of the array should be empty.
					*/	
					if (is_it_valid_user2(user2x, user2y, tictactoe) == 1) {
						tictactoe[user2x - 1][user2y - 1] = 'O';//If it is empty the index is equals to O now.
						print_board(tictactoe); //Printing the board.

						/*
							Checking whether game is over or continue.
						*/
						if (check_game_status(tictactoe) == 1 || check_game_status(tictactoe) == 2) {
							if (check_game_status(tictactoe) == 1) {
								printf("Player 2 (O) wins!");
							}
							else if (check_game_status(tictactoe) == 2) {
								printf("Its's a tie!.");
							}

							/*
								Asking the user if he/she wants to play again.
							*/
							do {
								printf("\nDo you want to play again?(Y/N): ");
								scanf(" %c", &play_again);
								if (play_again == 'Y') {
									printf("\nNew game...\n");
									part3();
								}
								else if (play_again=='N'){
									printf("Thanks for playing.\n");
									exit(0);
								}
								else {
									printf("Invalid input. Please enter Y or N.\n");
								}
							} while (play_again != 'Y' && play_again != 'N');
						}
						break;
					}
					/*
						If the index of the array is not empty, program prompts an error message.
					*/
					else if (is_it_valid_user2(user2x, user2y, tictactoe) == 0) {
						printf("Invalid input. You can't enter a value that had been entered.\n");
					}
				}
				/*
					If the inputs are not between 1-3 the program prompts an error message.
				*/
				else{
					printf("Please enter a value between 1 and 3.\n");
				}
		}
			
	}

}

int main()
{	//Part1, letter counter program.
	part1();

	//Part2, color mixer program.
	part2();

	//Part3, Tic Tac Toe game.
	part3();
}
