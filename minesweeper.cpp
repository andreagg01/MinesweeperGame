// Silly code that implements the Minesweeper game

#include <iostream>
#include <stdio.h>
#include <math.h>

// N is the dimension of the grid of the game, M is the number of mines
// N and M are modifiable from here to change difficulty (Suggestion: N=9, M=10 -> easy, N=16, M=40 -> medium, N=30, M=180 -> extreme)
#define N 9
#define M 10

// Struct for the Grid of the game, each cell has a number n (-1 for the bomb, 0 if it has no bomb near itself, 1 if it has one bomb near itself, ...)
// and an int show, to indicate whether the cell has been discovered by the player
typedef struct{
    int n;
    int show;
} grid;

int main() {
    grid matrix[N][N];
    int i, j;
    int a;
    int found=0;

    srand(time(0));

    printf("Welcome, press '1' to play, any other number to quit: \n");

    int play;
    if (scanf("%d", &play)){}

    if (play==1) {

        // Grid initialization
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrix[i][j].n = 0;
                matrix[i][j].show = 0;
            }
        }

        // mines initialization, random coordinates to guarantee a different game every time
        int n1,n2;
        for (i = 0; i < M; i++) {
            n1 = rand() %N;
            n2 = rand() %N;
            if (matrix[n1][n2].n == 0) {
                matrix[n1][n2].n = -1;
            } else {
                while (matrix[n1][n2].n != 0) {
                    n1 = rand() %N;
                    n2 = rand() %N;
                }
                matrix[n1][n2].n = -1;
            }
        }

        // Counting the mines near each cell to initialize the game
        int count;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (matrix[i][j].n == 0) {
                    count = 0;
                    if (matrix[i - 1][j - 1].n == -1)
                        count += 1;
                    if (matrix[i - 1][j].n == -1)
                        count += 1;
                    if (matrix[i - 1][j + 1].n == -1)
                        count += 1;
                    if (matrix[i][j - 1].n == -1)
                        count += 1;
                    if (matrix[i][j + 1].n == -1)
                        count += 1;
                    if (matrix[i + 1][j - 1].n == -1)
                        count += 1;
                    if (matrix[i + 1][j].n == -1)
                        count += 1;
                    if (matrix[i + 1][j + 1].n == -1)
                        count += 1;
                    matrix[i][j].n = count;
                }
            }
        }

        // GAME LOOP
        printf("The game is ready!\n");

        while (true) {
            // Print the grid
            // Graphically can be easily improved, for example adding colors or even just adjusting the spaces printed

            printf("      ");
            for (i=0; i<N; i++)
                printf("%2d  ", i);
            printf("\n");
            for (i=0; i<N; i++){
                printf("%3d   ", i);
                for(j=0; j<N; j++){
                    if (matrix[i][j].show == 0) {
                        printf("[ ] ");
                    } else {
                        if (matrix[i][j].n < 0 || matrix[i][j].show < 0)
                            printf("(*) ");
                        else {
                            printf("%3d ", matrix[i][j].n);
                        }
                    }
                }
                printf("\n");
            }

            // Player is asked to make his/her move form here
            printf("Do you want to place a flag or discover a cell?\n"
                   "1 - place flag, 2 - discover cell: \n");

            if (scanf(" %d", &a)){}

            while(a != 1 && a != 2){
                printf("Invalid choice, retry:\n");
                if (scanf(" %d", &a)){}
            }

            if (a == 2){
                printf("Which cell would you like to show?\n"
                       "Insert coordinates x and y: \n");
                printf("x: ");
                int x;
                if (scanf("%d", &x)){}

                printf("\n");
                printf("y: ");
                int y;
                if (scanf("%d", &y)){}

                while (x<0 || x>=N || y<0 || y>=N){
                    printf("Invalid coordinates, please insert valid ones.\n");
                    printf("Which cell would you like to show?\n"
                           "Insert coordinates x and y: \n");
                    printf("x: ");
                    if (scanf("%d", &x)){}
                    printf("\n");
                    printf("y: ");
                    if (scanf("%d", &y)){}

                }
                if (matrix[x][y].n == -1){
                    printf("That was a MINE!\n");
                    // An Ascii art with """explosion""" could be added to improve graphic
                    printf("                                888                   888         \n"
                           "                                888                   888         \n"
                           "                                888                   888         \n"
                           "888  888  .d88b.  888  888      888  .d88b.  .d8888b  888888      \n"
                           "888  888 d88\"\"88b 888  888      888 d88\"\"88b 88K      888         \n"
                           "888  888 888  888 888  888      888 888  888 \"Y8888b. 888         \n"
                           "Y88b 888 Y88..88P Y88b 888      888 Y88..88P      X88 Y88b.       \n"
                           " \"Y88888  \"Y88P\"   \"Y88888      888  \"Y88P\"   88888P'  \"Y888      \n"
                           "     888                                                          \n"
                           "Y8b d88P                                                          \n"
                           " \"Y88P\"              ");
                    break;

                } else {
                    matrix[x][y].show = 1;
                }

            } else {

                printf("Where would you like to place the flag?\n"
                       "Insert coordinates x and y: \n");
                printf("x: ");
                int x;
                scanf("%d", &x);

                printf("\n");
                printf("y: ");
                int y;
                scanf("%d", &y);

                if (matrix[x][y].n == -1){
                    matrix[x][y].show = -1;
                    found++;
                } else {
                    matrix[x][y].show = -2;
                }

            }

            // Game finishes when all the mines are found
            // ASCII art could be added
            if (found == M){
                printf("You found all the bombs! You won the game! \n");
                
                break;
            }
        }

    } else {
        printf("Bye!\n");
    }

    return 0;
}
