#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'


/*Defining the functions*/
void menu();
void GamePlay(int size, int character_location, int door_location);
void DrawingTheRoom(int size, int character_location, int door_location);
int ControlOfStatus(int current_character_location, int door_location);


/*START MENU FUNCTION*/
void menu() {
	int option;
	int size;
	int character_location;
	int door_location;
	printf("Welcome to the 2D puzzle game!\n");
	printf("1. New Game\n2. Help\n3. Exit\n");
	scanf("%d", &option);
	while (1) {
		switch (option) {
		case 1: {
			while (1) {
				printf("Please enter the size (5-10) for room (NxN): "); //Getting the room size from user.
				scanf("%d", &size);
				if (size >= 5 && size <= 10) {
					break;
				}
				else {
					printf("Please enter a number between 5-10\n"); //Sending a warning message if number is not between 5-10.
				}
			}
			srand(time(0));
			while (1) {
				character_location = 1 + rand() % (size * size); //Selecting the characater's location between 1 and square of size randomly.
				door_location = 1 + rand() % (size * size); //Selecting the door's location between 1 and square of size randomly.
				if (character_location != door_location) {
					break; //The locations should be different. So when they are different while loop ends.
				}
			}
			DrawingTheRoom(size, character_location, door_location); //Sending the size and locations to the function for drawing the room.
			GamePlay(size, character_location, door_location); //Sending the size and locations to the function for starting the game. 
			break;
		}
		case 2: {
			//Help
			printf("\nThe character is able to move one space in any of the four cardinal directions: up, down, left, and right. ");
			printf("Diagonal moves are not allowed. ");
			printf("The user will\ninput their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down.\n\n");
			menu();
			break;
		}
		case 3: {
			//Exiting the game.
			printf("Thanks for playing.\n");
			exit(0);
		}
		default: {
			//If the user entered a valid input.
			printf("You entered a wrong option. Please enter 1, 2 or 3.\n");
			break;
		}
		}
	}
}
/*END MENU FUNCTION*/


/*START DRAWINGTHEROOM FUNCTION*/
void DrawingTheRoom(int size, int character_location, int door_location) {
	int i = 1, j = 1, k; //defining i,j,k for the for loops.
	char Door = 'D'; //defining the Door as 'D'
	char Character = 'C'; //defining the Character as 'C'

	//Printing the above wall
	for (k = 1; k <= (size * 2) + 1; k++) {
		printf("-");
	}
	printf("\n");

	//Printing the room
	//THE ALGORITHM
		/*Let's assume that size=5.
		i equals 1 at first. And it prints the first wall of first line which represents the first (1.) space.
		Then j=2 and i equals 6. It represents the first wall and the first space of the second line.
		Also this space is 7. space in all room.*/
	for (j = 1; j <= size; j++) {
		for (i = size * j - size + 1; i <= size * j; i++) {

			printf("|");
			if (i == character_location) {
				printf("%c", Character);
			}
			else if (i == door_location) {
				printf("%c", Door);
			}
			else {
				printf(" ");
			}
		}
		printf("|"); //Printing the rightmost wall
		printf("\n");
	}
	//Printing the below wall
	for (k = 1; k <= (size * 2) + 1; k++) {
		printf("-");
	}
	printf("\n");
}
/*END DRAWINGTHEROOM FUNCTION*/


/*START GAMEPLAY FUNCTION*/
void GamePlay(int size, int character_location, int door_location) {
	char move;
	int current_character_location = 0;
	int move_counter = 0;
	int check;
	while(1){
		printf("Please enter the move(w,a,s,d): \n");
		getchar();
		scanf(" %c",&move);
		switch (move) {
			//If user wants to move to UP
			case UP: {
				//Checking if after pressing 'w' the character's location will be in between 1 and square of size. This checking is for above wall. 
				if (character_location - size >= 1 && character_location - size <= size * size) {
					current_character_location = character_location - size;
					/*If character didn't hit the wall its new location will be its location minus size.
					for example, if size is 7 and character is in 17. space, after pressing w the new location will be 10. space.
					that is the space above the character's current space.*/

					check = ControlOfStatus(current_character_location, door_location); //Checking whether the game is ended or not.
					move_counter++; //Counting the number of moves

					//After checking the game's status.
					if (check == 1) {
					//If game is over.
					printf("Congratulations! You have successfully completed the game with a total of %d moves.\n\n", move_counter);
					menu();
					}
					else {
					//If game is not over printing the room with using current location.
					DrawingTheRoom(size, current_character_location, door_location);
					character_location = current_character_location; //After printing the room character's new location is the main location.
					}
				}

				//If character hits the wall
				else {
					//Character's location didn't change.
					printf("\nOops! There is a wall.\n\n");
					move_counter++;
					DrawingTheRoom(size, character_location, door_location); //Printing the room  
				}
					break;
			}

			//If user wants to move to DOWN
			case DOWN: {
				//Checking if after pressing 's' the character's location will be in between 1 and square of size. This checking is for below wall. 
				if (character_location + size >= 1 && character_location + size <= size * size) {
					current_character_location = character_location + size;

					/*If character didn't hit the wall its new location will be its location plus size.
					for example, if size is 7 and character is in 17. space, after pressing w the new location will be 24. space.
					that is the space below the character's current space.*/

					check = ControlOfStatus(current_character_location, door_location); //Checking whether the game is ended or not.
					move_counter++;//Counting the number of moves

					//After checking the game's status.
					if (check == 1) {
						//If game is over.
						printf("Congratulations! You have successfully completed the game with a total of %d moves.\n\n", move_counter);
						menu();
					}

					else if (check == 0) {
						//If game is not over printing the room with using current location.
						DrawingTheRoom(size, current_character_location, door_location); //After printing the room character's new location is the main location.
						character_location = current_character_location; //Going to begining of the switch-case so that user can enter a another move.
					}
				}
				else {
					current_character_location = character_location;
					printf("\nOops! There is a wall.\n\n");
					move_counter++;
					DrawingTheRoom(size, current_character_location, door_location);
				}
					break;
				}

			//If user wants to move to LEFT
			case LEFT: {
				if ((character_location - 1) % size != 0) {
					current_character_location = character_location - 1;
					/*
					if character didn't hit the wall its new location will be its location minus 1.
					but it's only applies if the character is next to the wall. to check if the character
					for example if size is 5 the spaces will be like this for our algorithm
					1 2 3 4 5
					6 7 8 9 10
					11 12 13 14 15
					...         20
					..          25
					if the character is next to the one of left walls its location-1 will be multiples of size.
					*/
					check = ControlOfStatus(current_character_location, door_location);
					move_counter++;
					if (check == 1) {
						printf("Congratulations! You have successfully completed the game with a total of %d moves.\n\n", move_counter);
						menu();
					}
					else if (check == 0) {
						DrawingTheRoom(size, current_character_location, door_location);
						character_location = current_character_location;
					}
				}
				else {
					current_character_location = character_location;
					printf("\nOops! There is a wall.\n\n");
					move_counter++;
					DrawingTheRoom(size, current_character_location, door_location);
				}
				break;
			}

			//If user wants to move to RIGHT
			case RIGHT: {
				if (character_location % size != 0) {
					current_character_location = character_location + 1;
					/*
					if character didn't hit the wall its new location will be its location plus 1.
					but it's only applies if the character is next to the wall. to check if the character
					for example if size is 5 the spaces will be like this for our algorithm
					1 2 3 4 5
					6 7 8 9 10
					11 12 13 14 15
					...         20
					..          25
					if the character is next to the one of right walls its location will be multiples of size.
					*/
					check = ControlOfStatus(current_character_location, door_location);
					move_counter++;
					if (check == 1) {
						printf("Congratulations! You have successfully completed the game with a total of %d moves.\n\n", move_counter);
						menu();
					}
					else if (check == 0) {
						DrawingTheRoom(size, current_character_location, door_location);
						character_location = current_character_location;
					}
				}
				else {
					current_character_location = character_location;
					printf("\nOops! There is a wall.\n\n");
					move_counter++;
					DrawingTheRoom(size, current_character_location, door_location);
				}
				break;
			}
			default: {
				printf("You entered a invalid input.\n\n");
				DrawingTheRoom(size, character_location, door_location);
				break;
			}
		}
		
	}
}
/*END GAMEPLAY FUNCTION*/


/*START CONTROLOFSTATUS FUNCTION*/
int ControlOfStatus(int current_character_location, int door_location) {
	int checker;
	//Checking if the locations are the same. 
	if (current_character_location == door_location) {
		checker = 1; //If they are the same checker is 1.
	}
	else {
		checker = 0; //If they are not the same checker is 0.

	}
	return checker; //Returning the checker.
}
/*END CONTROLOFSTATUS FUNCTION*/


/*MAIN FUNCTION*/
int main()
{
	menu();
}

