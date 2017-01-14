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

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

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
    // TODO 
    /*
    cycle throgh matrix, print 1++. going down. last is zero
    then swap zero with space, and swap 1 and 2 ONLY IF ODD NUMBER OF TILES
    NOTE: empty tile will be zero, but print '_'
    */
    int tiles = d*d - 1;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++, tiles--)
        {
            board[i][j] = tiles;
        }
    }
    if ((d*d-1) % 2 == 1)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }

    
}

/**
 * Prints the board in its current state.

 */
void draw(void)
{
    // TODO
     /*
 print space, then x, then space. new line for each array switch
 make two spacs for single digits
 print _ instead of 0
     */
    int tiles = d*d - 1;
    for(int i = 0; i < d; i++)
    {
        printf("  ");
        for(int j = 0; j < d; j++, tiles--)
        {
            if(board[i][j] != 0)
                printf("%i  " ,board[i][j]);
            else
                printf("_  ");
            if(board[i][j] < 10)
                printf(" ");

        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    /*
    if tile adjacent to space (not diagonal), 
    swap them and return true, else return false
    so search for tile value, save its [x][y] . check if either:
    [x+-1] [y] , or [x][y+/-1] is the zero 
    (make sure not to check beyond memory limits)
    */
    bool exists = false;
    int i, j, ii, jj;
    if (tile == 0)
        return false;
    for(i = 0; i < d && exists == false; i++)
    {
        for(j = 0; j < d && exists == false; j++)
        {
            if (board[i][j] == tile)
            {
            exists = true;
            ii = i; 
            jj = j;
            }
        }
    
    }
    
    if(exists == true)
    {
        if(board[ii-1][jj] == 0 && (ii-1) >= 0) //up
        {
            board[ii-1][jj] = board[ii][jj];
            board[ii][jj] = 0;
            return true;
        }
        if(board[ii+1][jj] == 0 && (ii+1) < d) //down
        {
            board[ii+1][jj] = board[ii][jj];
            board[ii][jj] = 0;
            return true;   
        }
        if(board[ii][jj+1] == 0 && (jj+1) < d) //right
        {
            board[ii][jj+1] = board[ii][jj];
            board[ii][jj] = 0;
            return true;  
        }
        if(board[ii][jj-1] == 0 && (jj-1) >= 0) //left
        {
            board[ii][jj-1] = board[ii][jj];
            board[ii][jj] = 0;
            return true;    
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
    int tile = 1;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++, tile++)
        {
            if(board[i][j] != tile && !(i == d-1 && j == d-1))
            return false;
        }
    }
    /* 
    loop throguh board. if single element not in order (except last one which is space!) return false, else return true
    */
    return true;
}