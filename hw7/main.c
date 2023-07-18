#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    struct data structure to represent the puzzle board
*/
typedef struct {
    int board[3][3];
} Puzzle;

/*
    functions for playing the game as user
*/
void generate_puzzle(Puzzle* puzzle);
int is_solvable(Puzzle* puzzle);
void display_puzzle(Puzzle* puzzle);
void save_state(Puzzle* puzzle, const char* filename, int counter);
int move(Puzzle* puzzle, int number, char direction);
void play_game();
int is_complete(Puzzle* puzzle);

/*
    functions for the score
*/
int calculate_score(int moves);
void save_best_score(int score);
int get_best_score();
void show_best_score();

/*
    functions for auto finish
*/
void finish_with_pc();
void auto_finish(Puzzle* computer_puzzle,int*previous_number);
Puzzle computer_play_game(Puzzle* computer_puzzle, int* previous_number);
/*
*/
void exit_game();

/*
    generating the puzzle
*/
void generate_puzzle(Puzzle* puzzle) {

    int nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int i, j;
    int temp;

    // using fisher–yates algorithm
    for (i = 8; i > 0; i--) {
        j = rand() % (i + 1); //generating random numbers
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    int index = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            puzzle->board[i][j] = nums[index++]; //filling the board with the numbers
        }
    }

    /* checking if the puzzle is solvable */
    if (!is_solvable(puzzle)) {
        generate_puzzle(puzzle); //if the puzzle is not solvable we call the generate_puzzle function again. 
    }
}

// checking if the generated puzzle is solvable
int is_solvable(Puzzle* puzzle) {

    // I watched this video to understand the algortihm: https://www.youtube.com/watch?v=bhmCmbj9VAg

    int inversion_counter = 0;
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {

            int row_i = i / 3;
            int col_i = i % 3;

            int row_j = j / 3;
            int col_j = j % 3;

            if (puzzle->board[row_i][col_i] && puzzle->board[row_j][col_j] && puzzle->board[row_i][col_i] > puzzle->board[row_j][col_j]) {
                inversion_counter++;
            }
        }
    }
    return inversion_counter % 2 == 0; //if inversion counter is odd number->returns 0, if it is even number->returns 1
}

// displaying the puzzle board
void display_puzzle(Puzzle* puzzle) {

    printf("\n");
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (puzzle->board[i][j] == 0) {
                printf("_ "); // in the pdf file there is '_' to represent the "0".
            }
            else {
                printf("%d ", puzzle->board[i][j]);
            }
        }
        printf("\n");
    }
}

// saving the state of the puzzle board to a txt file
void save_state(Puzzle* puzzle, const char* filename, int counter) {

    //counter=1 means we open the file with w mode. it means it is a new game and the program should erase the boards in txt file.
    if (counter == 1) {
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (puzzle->board[i][j] == 0) {
                    fprintf(file, "_ ");
                }
                else {
                    fprintf(file, "%d ", puzzle->board[i][j]);
                }
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n\n");
        fclose(file);
    }

    //if counter is not 1 we can add the new board after previous board.
    else {

        FILE* file = fopen(filename, "a");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }

        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (puzzle->board[i][j] == 0) {
                    fprintf(file, "_ ");
                }
                else {
                    fprintf(file, "%d ", puzzle->board[i][j]);
                }
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n\n");
        fclose(file);
    }
}

// calculating the score based on the number of moves
int calculate_score(int moves) {
    return 1000 - 10 * moves;
}

// checking if the puzzle is complete
int is_complete(Puzzle* puzzle) {

    int correct_board[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} }; //it is the final board.

    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (puzzle->board[i][j] != correct_board[i][j])
                return 0;
        }
    }
    return 1;
}

// this function makes the moves and checks if the move is legal
int move(Puzzle* puzzle, int number, char direction) {

    int row = -1, col, newRow, newCol;
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            //finding the given number
            if (puzzle->board[i][j] == number) {
                row = i;
                col = j;
                break;
            }
        }
        //if the given number couldn't find in the board for loop breaks.
        if (row != -1) {
            break;
        }
    }

    //if the given number couldn't find in the board
    if (row == -1) {
        printf("Number couldn't find in the board!\n");
    }

    //switch-case to the new move of given number.
    switch (direction) {
    case 'U':
    case 'u':
        newRow = row - 1;
        newCol = col;
        break;
    case 'D':
    case 'd':
        newRow = row + 1;
        newCol = col;
        break;
    case 'L':
    case 'l':
        newRow = row;
        newCol = col - 1;
        break;
    case 'R':
    case 'r':
        newRow = row;
        newCol = col + 1;
        break;
    default:
        return 0;
    }

    //if the move is invalid.
    if (newRow < 0 || newRow >= 3 || newCol < 0 || newCol >= 3 || puzzle->board[newRow][newCol] != 0) {
        return -1;
    }

    //switching the given number and 0
    puzzle->board[newRow][newCol] = number;
    puzzle->board[row][col] = 0;

    //if the move is legal
    return 1;
}

// function to play the game as a user
void play_game() {

    Puzzle puzzle;

    //generating the puzzle.
    generate_puzzle(&puzzle);

    //it is the counter that determine whether it is a new game or the game is continue
    int file_counter = 0;

    //displaying the puzzle
    display_puzzle(&puzzle);

    int moves = 0;

    //infinite loop that ends if the puzzle is completed
    while (!is_complete(&puzzle)) {

        int number;
        char direction;

        printf("Enter your move (number-direction, e.g., 2-R): ");
        scanf("%d-%c", &number, &direction);

        if (move(&puzzle, number, direction) == 1) {
            moves++;
            file_counter++;
            save_state(&puzzle, "game.txt", file_counter);
            display_puzzle(&puzzle);
        }
        else if (move(&puzzle, number, direction) == 0) {
            printf("Invalid direction. Use U (up), D (down), L (left), or R (right).\n");
        }
        else if (move(&puzzle, number, direction) == -1) {
            printf("Illegal move. Try again.\n");
        }
    }
    //if is_complete(&puzzle)=1
    printf("Congratulations! You completed the puzzle.\n");

    int score = calculate_score(moves); //calculating the score

    //printing the number of moves and score
    printf("Total number of moves: %d\nYour Score: %d\n", moves, score);

    //getting the best score in the txt file
    int best_score = get_best_score();

    //if the score is greater than the previous best score
    if (best_score == -1 || score > best_score) {
        save_best_score(score);
        printf("New best score!\n");
    }
}

/*------------------------------------------------------------------------------------------*/

/*
    finishing with computer
*/

int computer_moves = 0;

void finish_with_pc() {
    Puzzle computer_puzzle;
    generate_puzzle(&computer_puzzle);
    display_puzzle(&computer_puzzle);
    int previous_number = -1;
    auto_finish(&computer_puzzle,&previous_number);
    printf("Total number of computer moves: %d\n", computer_moves);
}


Puzzle computer_play_game(Puzzle* computer_puzzle, int* previous_number) {

    //direction array to generate a random move
    char directions[4] = { 'U','D','L','R' };

    //if the 0 is in the center,corner or side of the puzzle
    int center_computer_number[4];
    int corner_computer_number[2];
    int side_computer_number[3];

    int number_index;
    int random_computer_number = -1;

    int flag;
    int i, j;

    int direction_index;
    char computer_direction;

    //it is defined so that the computer does not generate the same number 2 times in a row
 
    //if the computer complete the puzzle
     //generating a number direction
    direction_index = rand() % 4;
    computer_direction = directions[direction_index];

    /*
      in this for loop the program determines the numbers next to 0 and fills the arrays
      it makes more easier to finish the program with computer
    */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (computer_puzzle->board[i][j] == 0) {
                if (i == 1 && j == 1) {
                    flag = 1;
                    center_computer_number[0] = computer_puzzle->board[0][1];
                    center_computer_number[1] = computer_puzzle->board[1][0];
                    center_computer_number[2] = computer_puzzle->board[2][1];
                    center_computer_number[3] = computer_puzzle->board[1][2];
                }
                else if (i == 0 && j == 0 || i == 0 && j == 2 || i == 2 && j == 0 || i == 2 && j == 2) {
                    flag = 2;
                    if (i == 0 && j == 0) {
                        corner_computer_number[0] = computer_puzzle->board[0][1];
                        corner_computer_number[1] = computer_puzzle->board[1][0];
                    }
                    else if (i == 0 && j == 2) {
                        corner_computer_number[0] = computer_puzzle->board[0][1];
                        corner_computer_number[1] = computer_puzzle->board[1][2];
                    }
                    else if (i == 2 && j == 0) {
                        corner_computer_number[0] = computer_puzzle->board[1][0];
                        corner_computer_number[1] = computer_puzzle->board[2][1];
                    }
                    else if (i == 2 && j == 2) {
                        corner_computer_number[0] = computer_puzzle->board[1][2];
                        corner_computer_number[1] = computer_puzzle->board[2][1];
                    }
                }
                else if (i == 1 && j == 0 || i == 0 && j == 1 || i == 1 && j == 2 || i == 2 && j == 1) {
                    flag = 3;
                    if (i == 1 && j == 0) {
                        side_computer_number[0] = computer_puzzle->board[0][0];
                        side_computer_number[1] = computer_puzzle->board[1][1];
                        side_computer_number[2] = computer_puzzle->board[2][0];

                    }
                    else if (i == 0 && j == 1) {
                        side_computer_number[0] = computer_puzzle->board[0][0];
                        side_computer_number[1] = computer_puzzle->board[1][1];
                        side_computer_number[2] = computer_puzzle->board[0][2];

                    }
                    else if (i == 1 && j == 2) {
                        side_computer_number[0] = computer_puzzle->board[2][2];
                        side_computer_number[1] = computer_puzzle->board[1][1];
                        side_computer_number[2] = computer_puzzle->board[0][2];

                    }
                    else if (i == 2 && j == 1) {
                        side_computer_number[0] = computer_puzzle->board[1][1];
                        side_computer_number[1] = computer_puzzle->board[2][2];
                        side_computer_number[2] = computer_puzzle->board[2][0];

                    }
                }
            }
        }
    }

    do {
        //if 0 is in the center of puzzle
        if (flag == 1) {
            number_index = rand() % 4;
            random_computer_number = center_computer_number[number_index];
        }
        //if 0 is in the one of the corner of puzzle
        else if (flag == 2) {
            number_index = rand() % 2;
            random_computer_number = corner_computer_number[number_index];
        }
        //if 0 is in the one of the side of puzzle
        else if (flag == 3) {
            number_index = rand() % 3;
            random_computer_number = side_computer_number[number_index];
        }
    } while (random_computer_number == *previous_number);

  

    //if the move is legal the program saves the state to the txt file and prints the computer's move and the board
    if (move(computer_puzzle, random_computer_number, computer_direction) == 1) {
    	*previous_number = random_computer_number;
        computer_moves++;
        save_state(computer_puzzle, "auto_finish.txt", computer_moves);
        printf("Computer Move: %d-%c\n", random_computer_number, computer_direction);
        display_puzzle(computer_puzzle);
    }
    return *computer_puzzle;
}

/*
    auto finish function.
*/
void auto_finish(Puzzle* computer_puzzle, int* previous_number) {
    
    if (is_complete(computer_puzzle) == 1) {
        printf("Computer finished the game.\n");
    }
    else if (is_complete(computer_puzzle) == 0) {
	computer_play_game(computer_puzzle, previous_number);
        auto_finish(computer_puzzle, previous_number);
    }
}
/*----------------------------------------------------------------------------*/

// saving the best score to a txt file
void save_best_score(int score) {

    //getting the previous best score
    int previous_best_score = get_best_score();

    FILE* file;

    //if score > previous best score program writes the new best score to the file.
    if (score > previous_best_score) {
        file = fopen("best_score.txt", "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }
        fprintf(file, "%d", score);
        fclose(file);
    }
}

// getting the best score from the txt file
int get_best_score() {
    int score;
    FILE* file = fopen("best_score.txt", "r");
    if (file == NULL) {
        return -1;
    }
    fscanf(file, "%d", &score);
    fclose(file);
    return score;
}

// displaying the best score
void show_best_score() {
    int best_score = get_best_score();
    if (best_score == -1) {
        printf("No best score found.\n");
    }
    else {
        printf("Best score: %d\n", best_score);
    }
}

/*----------------------------------------------------------------------------*/

// exiting the game
void exit_game() {
    printf("Program terminated...\n");
}
int main() {

    int choice;

    //for rand function
    srand(time(NULL));

    //printing the menu and calling the functions
    do {
        printf("\nWelcome to the 8-Puzzle Game!\nPlease select an option:\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            play_game();
            break;
        case 2: {
            finish_with_pc();
            break;
        }
        case 3:
            show_best_score();
            break;
        case 4:
            exit_game();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}



