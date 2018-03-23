/* Program that simulates a highway
 * Takes 3 inputs, being the number of rows, columns and max time steps
 * Then takes the arrival time followed by the lane on the second row
 * Prints the state of the array after the simulation
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Constants for car and space, can be changed
 */
#define CAR '1'
#define SPACE '.'

/*
 * Initialises the board matrix with spaces
 * Takes the total number of rows and columns and the pointer to pointer array board
 */
void initialiseBoard(int rows, int cols, char **board) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = SPACE;
        }
    }
}

/*
 * Checks to see if a car is arriving at the lane and time passed into it
 * Takes the current run time, the lane, the pointer to board and the number of user inputs
 * Returns 1 if a car is arriving
 * Returns 0 if not
 */
int isArriving(int runTime, int lane, int **carTimes, int numOfInputs) {
    for(int i = 0; i < numOfInputs; i++) {
        /* Checks to see each lane */
        if(carTimes[i][1] == lane) {
            /* Checks to see the arrival time at that lane */
            if(carTimes[i][0] == runTime) {
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Shifts the lane array to the right
 * Takes the lane, total number of columns and the pointer to the board
 */
void shiftBoard(int lane, int cols, char **board) {
    for(int i = cols; i > 0; i--) {
        board[lane][i] = board[lane][i - 1];
    }
}

/*
 * Starts the simulation of the problem
 * Takes the total rows, columns as well as the pointers to the board and car time array and the number of inputs and
 * total number of time steps to take
 */
void runSimulation(int rows, int cols, int **carTimes, int numOfInputs, int timeSteps, char **board) {
    /* Simulates the time passing */
    for(int runTime = 0; runTime < timeSteps; runTime++) {
        for(int lane = 0; lane < rows; lane++) {
            /* Calls the method that shifts the board to the right */
            shiftBoard(lane, cols, &*board);
            /* Checks to see if a car is arriving at the current runtime, if so, set a car on the first step of the
             * board, otherwise set a space
             */
            if(isArriving(runTime, lane, &*carTimes, numOfInputs)) {
                board[lane][0] = CAR;
            } else {
                board[lane][0] = SPACE;
            }
        }
    }
}

/* Prints the board
 * Takes the rows, columns and board pointer
 * Prints it
 */
void printResult(int rows, int cols, char **board) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/* Main function to take input and call the calculation and printing */
int main() {
    /* Taking the initial input line */
    int rows, cols, timeSteps;
    scanf("%d %d %d", &rows, &cols, &timeSteps);
    if (rows <= 0 || cols <= 0) {
        printf("Error. Rows and columns must be larger than 0.\n");
        exit(1);
    }
    
    /* Dynamically allocate an array of pointers to pointers that will be used as the game board*/
    char **board;
    board = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        board[i] = (char *)malloc(cols * sizeof(char));
    }
    /* Check to see if memory space was given, if not then exit */
    if (board == NULL) {
        printf("Error. Not enough space available.\n");
        exit(1);
    }
    
    int count = 0;
    int number1, number2;
    int **carTimes = 0;
    /* Loops through the input given by the user and assigns it to the carTimes dynamically allocate an array */
    while (scanf("%d %d", &number1, &number2) != EOF) {
        /* Reallocates the size of the array to allow for more inputs */
        carTimes = (int **) realloc(carTimes, (count + 1) * sizeof(int *));
        /* Check to see if memory space was given, if not then exit */
        if (carTimes == NULL) {
            printf("Error. Not enough space available.\n");
            exit(1);
        }
        /* Allocates the column and checks */
        carTimes[count] = (int *) malloc(2 * sizeof(int));
        if (carTimes[count] == 0) {
            exit(1);
        }
        /* Sets the given values to the array */
        carTimes[count][0] = number1;
        carTimes[count][1] = number2;
        count++;
    }
    
    /* Calls for the initialisation of the board, the simulation and the printing */
    initialiseBoard(rows, cols, &*board);
    runSimulation(rows, cols, &*carTimes,count , timeSteps, &*board);
    printResult(rows, cols, &*board);
    
    /* Free the memory that was used by the board and input arrays */
    free(carTimes);
    free(board);
    return 0;
}
