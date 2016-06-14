/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

//blank space position
int blankSpace[2];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

bool compareTiles(int currentTile[], int space[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // get the total number of titles
    int numberOfTiles = d * d;
    int currentTile = numberOfTiles - 1;
    //populate the board by looping through arrays and decrementing current tile 
    for (int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = currentTile;
            currentTile = currentTile - 1;
        }
    }
    //swap one and two if we have an odd number of tiles
    int temp;
    if ((numberOfTiles - 1) % 2 == 1)
    {
        temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp;
    }
    //set the position of the blank space global var to bottom right corner
    blankSpace[0] = d - 1;
    blankSpace[1] = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //iterate through and when you reach 0 print the blank symbol  
            //otherwise print the value 
            if (board[i][j] == 0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //iterate over board and find tile user input
            if (tile == board[i][j])
            {
                //get the position of that tile
               int currentTilePosition[2] = {i, j}; 
               //compare tile position to blank space to make sure legal move
               if (compareTiles(currentTilePosition, blankSpace))
               {
                   //swap the tile into blank and update blankSpace
                   board[i][j] = 0;
                   board[blankSpace[0]][blankSpace[1]] = tile;
                   blankSpace[0] = i;
                   blankSpace[1] = j;
                   return true;
               }
               else
               {
                   return false;
               }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //creation of counter and single array to copy values of board into a
    // 1D array
    int counter = 0;
    int totalTiles = d * d;
    int singleArray[totalTiles];
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d ; j++)
        {
            //iterate over board and copy values to singleArray
            singleArray[counter] = board[i][j];
            counter++;
        }
    }
    //check for ascending order of elements in single array
    for (int i = 0; i < totalTiles - 2; i++)
    {
        if (singleArray[i] != singleArray[i + 1] - 1)
        {
            return false;
        }
    }
    return true;
}

/**
 * Compares two tiles and returns true if they are next to each other. 
*/
bool compareTiles(int currentTile[], int space[])
{
    //compares the position of two tiles 
    if (currentTile[0] != space[0] && currentTile[1] != space[1])
    {
        return false;
    }
    else if (currentTile[0] - space[0] > 1 || currentTile[0] - space[0] < -1)
    {
        return false;
    }
    else if (currentTile[1] - space[1] > 1 || currentTile[1] - space[1] < -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}