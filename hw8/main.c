#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 10

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    char type;
    int value;
} Block;


Block** init_board();
void draw_board(Block** board, Point* snake, int snake_length);
void play(Block** board);
Point move(Point head, char* previous_move, int snake_length, int* is_invalid_move);
int check_status(Block** board, Point* snake, int snake_length, Point new_head);
void update(Block** board, Point* snake, int snake_length, Point new_head, int* is_bait_eaten,int move_count);

int main() {
    srand(time(NULL));
    Block** board = init_board();
    play(board);
    int i;
    for (i = 0; i < BOARD_SIZE; i++) {
        free(board[i]);
    }
    free(board);
}

/* initialize board function */
Block** init_board() {
    Block** board = (Block**) malloc(BOARD_SIZE * sizeof(Block*));
    
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        board[i] = (Block*) malloc(BOARD_SIZE * sizeof(Block));
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j].type = 'e'; //at first all the cell is empty
            board[i][j].value = 0; //all cells' values equal to 0 at first
        }
    }
    /* generating a random obstacle */
    int obs_row = rand() % BOARD_SIZE;
    int obs_col = rand() % BOARD_SIZE;
    
    /* generating a random bait */
    int bait_row, bait_col;
    do {
        bait_row = rand() % BOARD_SIZE;
        bait_col = rand() % BOARD_SIZE;
    } while(bait_row == obs_row && bait_col == obs_col);

    board[obs_row][obs_col].type = 'o'; //type o for obstacle
    board[obs_row][obs_col].value = rand() % 9 + 1; //random value for obstacle between 1-9
    board[bait_row][bait_col].type = 'b'; //type b for bait
    
    return board; //returning the board
}

/* draw the board function */
void draw_board(Block** board, Point* snake, int snake_length) {
    char cell[3] = " ";
    int i,j,k;
    printf(" - - - - - - - - - -\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("|");
        for (j = 0; j < BOARD_SIZE; j++) {
            strcpy(cell, " ");  //resetting cell to empty
            for (k = 0; k < snake_length; k++) {
                if (snake[k].row == i && snake[k].col == j) {
                    if (k == 0) {
                        cell[0] = 'O';
                    }
                    else {
                        cell[0] = 'X';
                    }
                    break;  
                }
            }
            if (cell[0] != 'O' && cell[0] != 'X') {
                switch (board[i][j].type) {
                    case 'e':
                        break;
                    case 'o':
                        sprintf(cell, "%d", board[i][j].value);
                        break;
                    case 'b':
                        strcpy(cell, ".");
                        break;
                }
            }
            printf("%2s", cell);
        }
        printf("|\n");
    }
    printf(" - - - - - - - - - -\n");
}

/* play function */
void play(Block** board){

    /* allocating memory for the snake */
    Point* snake = malloc(sizeof(Point));

    /* snake's head is top-left block at first*/
    snake[0].row = 0;
    snake[0].col = 0;
    
    int snake_length = 1;
    int move_count = 0;
    int i;

    char previous_move = 's';
    int is_invalid_move = 0; // add a new variable to check if the move is invalid
    //infinite loop until the game over
    while (1) {
        draw_board(board, snake, snake_length);

        //sending the snake to the move function and it returns the new head
        Point new_head = move(snake[0], &previous_move,snake_length, &is_invalid_move);

        int is_bait_eaten = 0; //checker for is the bait eaten by snake

        //checking the game status
        if (check_status(board, snake, snake_length, new_head)) {
            printf("Game over! Your score: %d\n", snake_length-1); //the score is lenght of the snake without head
            break;
        }

        // if move is valid, update the board and move the snake
        if (!is_invalid_move) {
            update(board, snake, snake_length, new_head, &is_bait_eaten, move_count);
            move_count++;  //updating move count

            //if the bait was eaten by snake the lenght increases
            if (is_bait_eaten) {
                snake_length++;
                snake = realloc(snake, snake_length * sizeof(Point)); //reallocation for the snake
            }
            for (i = snake_length - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0] = new_head; //the first index is head of snake again
        }
    }

    free(snake); // free snake at the end of the game
}


/* move function */
Point move(Point head, char* previous_move, int snake_length, int* is_invalid_move) {
    char input;
    printf("Enter your move (w/a/s/d): ");
    scanf(" %c", &input);

    /* if the snake's length is greater than 1 and new move is opposite of the previous move, ignore it */    
    if (snake_length > 1 &&
        ((*previous_move == 'w' && input == 's') || (*previous_move == 's' && input == 'w') ||
         (*previous_move == 'a' && input == 'd') || (*previous_move == 'd' && input == 'a'))) {
        printf("You cannot move to snake's body\n");
        *is_invalid_move = 1;
        return head;
    }
    *is_invalid_move = 0;  // reset the flag if the move is valid

    /* changing the head's row and col with using the input in switch-case */
    switch (input) {
        case 'w':
            head.row--;
            *previous_move = 'w';
            break;
        case 'a':
            head.col--;
            *previous_move = 'a';
            break;
        case 's':
            head.row++;
            *previous_move = 's';
            break;
        case 'd':
            head.col++;
            *previous_move = 'd';
            break;
    }
    return head; //returning the head
}

/* check status function */
int check_status(Block** board, Point* snake, int snake_length, Point new_head) {
    int i;

    /*collision with wall*/ 
    if (new_head.row < 0 || new_head.row >= BOARD_SIZE || new_head.col < 0 || new_head.col >= BOARD_SIZE) {
        return 1;  
    }

    /*collision with snake's itself*/ 
    for (i = 1; i < snake_length; i++) {
        if (snake[i].row == new_head.row && snake[i].col == new_head.col) {
            return 1;
        }
    }
    
    /*collision with obstacle bigger than snake*/
    if (board[new_head.row][new_head.col].type == 'o') {
        if (board[new_head.row][new_head.col].value > snake_length) {
            return 1; 
        }
    }
    return 0;
}

/* update function */
void update(Block** board, Point* snake, int snake_length, Point new_head, int* is_bait_eaten, int move_count) {
    int i, j;

    // if the bait is eaten by snake
    if (board[new_head.row][new_head.col].type == 'b') {
        *is_bait_eaten = 1;
        // generating a new bait
        int bait_row, bait_col;
        do {
            bait_row = rand() % BOARD_SIZE;
            bait_col = rand() % BOARD_SIZE;
        } while(bait_row == new_head.row && bait_col == new_head.col);
        board[bait_row][bait_col].type = 'b';
    }
    
    // if the bait is not eaten by snake snake's last block will be empty now
    if (!*is_bait_eaten) {
        board[snake[snake_length-1].row][snake[snake_length-1].col].type = 'e';
    }

    // adding new obstacle if current move count is a multiple of 5
    if(move_count % 5 == 0) {
        // remove all current obstacles
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j].type == 'o') {
                    board[i][j].type = 'e';
                    board[i][j].value = 0;
                }
            }
        }
        // adding 3 new obstacles
        for(i = 0; i < 3; i++) {
            int obs_row, obs_col;
            do {
                obs_row = rand() % BOARD_SIZE;
                obs_col = rand() % BOARD_SIZE;
            } while(board[obs_row][obs_col].type != 'e');

            // adding new obstacle
            board[obs_row][obs_col].type = 'o';
            board[obs_row][obs_col].value = rand() % 9 + 1; // obstacle value between 1-9
        }
    }
}




