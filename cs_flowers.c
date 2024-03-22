// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// TODO: Description of program

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

#define MAX_ROW 11
#define MAX_COL 11
#define TRUE 1
#define FALSE 0

// TODO: put your constants here

//------------------------------------------------------------------------------
// Struct & Enum
//------------------------------------------------------------------------------

enum flower_state
{
    NONE,
    DORMANT,
    DISTURBED,
    AWAKENED,
    ANXIOUS,
    ENERGETIC
};

struct flower
{
    enum flower_state state;
    // TODO: You will need to add more to this struct in Stage 3
};

enum tile_type
{
    EMPTY,
    BUSH,
    BRANCH,
    DANGER,
    ROOT,
    POLLEN,
    SEEDLING,
    FLOWER,
};

struct tile
{
    enum tile_type type;
    struct flower flower;
};

// TODO: Put your structs here

//------------------------------------------------------------------------------
// Your Function Prototypes
//------------------------------------------------------------------------------

// TODO: Put your function prototypes here

//------------------------------------------------------------------------------
// Provided Function Prototypes
//------------------------------------------------------------------------------

bool is_starting_position_valid(int row, int col);
bool is_foliage_position_valid(int row, int col);
void initialise_map(struct tile map[MAX_ROW][MAX_COL]);
void print_map(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col);

void print_tile(struct tile tile);
void print_flower(struct flower flower);

//------------------------------------------------------------------------------
// Main Function
//------------------------------------------------------------------------------

int main(void)
{
    struct tile map[MAX_ROW][MAX_COL];
    initialise_map(map);

    printf("Welcome to CS Flowers!\n");

    // TODO: Start writing code here!

    int player_row, player_col, num_foliage, foliage_row, foliage_col, foliage_start_row, foliage_start_col, bush_length;
    char type_foliage, direction;
    char input[11];

    // TODO: Stage 1.1 - Scan in the player position and print out the map

    printf("Player's starting position: ");
    scanf("%d %d", &player_col, &player_row);

    // TODO: Stage 1.2 - Validate the player's spawn and re-scan if invalid

    while (!is_starting_position_valid(player_col, player_row))
    {
        printf("Invalid starting position\n");
        printf("Re-enter starting position: ");
        scanf("%d %d", &player_col, &player_row);
    }

    print_map(map, player_col, player_row);

    // TODO: Stage 1.3 - Add foliage onto the map, starting with branches

    printf("How many tiles of foliage: ");

    scanf("%d", &num_foliage);

    if (num_foliage > 0)
    {

        while (num_foliage > 0)
        {

            scanf(" %c", &type_foliage);

            if (type_foliage == 'b')
            {
                scanf("%d %d", &foliage_col, &foliage_row);
                if (is_foliage_position_valid(foliage_col, foliage_row)) {
                    map[foliage_row][foliage_col].type = BRANCH;
                    printf("Branch added!\n");
                    num_foliage--;
                } else {
                    printf("Invalid foliage position!\n");
                }
            }
            else if (type_foliage == 'u')
            {
                scanf("%d %d %c %d", &foliage_start_row, &foliage_start_col, &direction, &bush_length);
                if (is_foliage_position_valid(foliage_start_col, foliage_start_row)) {
                    for (int i = 0; i < bush_length; i++)
                    {
                        map[foliage_start_row][foliage_start_col].type = BUSH;

                        if (direction == 'v')
                        {
                            foliage_start_row = foliage_start_row + 1;
                        }
                        else if (direction == 'h')
                        {
                            foliage_start_col = foliage_start_col + 1;
                        };
                    };
                    printf("Bush added!\n");
                    num_foliage--;
                } else {
                    printf("Invalid foliage position!\n");
                }
            }
        }
    }

    print_map(map, player_col, player_row);
    return 0;
}

//------------------------------------------------------------------------------
// Your Function
//------------------------------------------------------------------------------

// TODO: Put your functions here

bool is_starting_position_valid(int col, int row)
{
    if (col == 0 || col == MAX_COL - 1)
    {
        return true;
    }
    else if (row == 0 || row == MAX_ROW - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_foliage_position_valid(int col, int row)
{
    if ((col != 0 && col != MAX_COL - 1) && (row != 0 && row != MAX_ROW - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------
// Provided Functions
//------------------------------------------------------------------------------

/**
 * Initialises the game map with empty tiles, setting the type of each tile to
 * `EMPTY` and initialising flower-related properties.
 *
 * @param map: The 2D array of `struct tile` representing the game map
 *
 * @returns None
 *
 **/
void initialise_map(struct tile map[MAX_ROW][MAX_COL])
{
    for (int row = 0; row < MAX_ROW; row++)
    {
        for (int col = 0; col < MAX_COL; col++)
        {
            map[row][col].type = EMPTY;
            map[row][col].flower.state = NONE;
        }
    }
}

/**
 * Prints the game map
 *
 * @param map: The 2D array of `struct tile` representing the game map.
 * @param player_row: The row coordinate of the player.
 * @param player_col: The column coordinate of the player.
 *
 * @returns None
 **/
void print_map(
    struct tile map[MAX_ROW][MAX_COL],
    int player_row,
    int player_col)
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < MAX_COL; j++)
        {
            printf("|");
            if (player_row != i || player_col != j)
            {
                print_tile(map[i][j]);
            }
            else if (map[i][j].type == EMPTY)
            {
                printf(" P ");
            }
            else if (map[i][j].type == DANGER)
            {
                printf("<P>");
            }
        }

        printf("|\n");
    }

    for (int j = 0; j < MAX_COL; j++)
    {
        printf("+---");
    }
    printf("+\n");
}

/**
 * Helper function which prints the representation of a single tile
 * based on its type.
 *
 * @params tile: The `struct tile` to be printed.
 *
 * @returns None
 **/
void print_tile(struct tile tile)
{
    if (tile.type == EMPTY)
    {
        printf("   ");
    }
    else if (tile.type == BUSH)
    {
        printf("###");
    }
    else if (tile.type == BRANCH)
    {
        printf("_/-");
    }
    else if (tile.type == DANGER)
    {
        printf("< >");
    }
    else if (tile.type == ROOT)
    {
        printf("<^>");
    }
    else if (tile.type == POLLEN)
    {
        printf(":::");
    }
    else if (tile.type == FLOWER)
    {
        print_flower(tile.flower);
    }
}

/**
 * Helper function which prints a visual representation of the
 * flower face based on its state.
 *
 * @params flower: The `struct flower` containing the state of the flower.
 *
 * @returns None
 *
 **/
void print_flower(struct flower flower)
{
    if (flower.state == DORMANT)
    {
        printf("uwu");
    }
    else if (flower.state == DISTURBED)
    {
        printf("uwo");
    }
    else if (flower.state == AWAKENED)
    {
        printf("owo");
    }
    else if (flower.state == ANXIOUS)
    {
        printf("o~o");
    }
    else if (flower.state == ENERGETIC)
    {
        printf("*w*");
    }
}
