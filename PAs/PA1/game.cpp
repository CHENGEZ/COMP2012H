#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

bool matches[HEIGHT][WIDTH] = {};
//int candidate_moves[(HEIGHT - 1) * WIDTH + (WIDTH - 1) * HEIGHT][4] = {};
//int num_candidate_moves = 0;
// int map_copy[][WIDTH] = {};

void readMap(string filename, int map[][WIDTH])
{
    // the map is 9 cells wide and 81 cells high, but only the bottom 9 rows cells are active.
    // The candies in the higher rows will "drop down" when candies in the "active area" are matched and removed
    ifstream file;
    file.open("map.txt");
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            file >> map[i][j];
        }
    }
}

// for debug
void printIntMap(int map[][WIDTH])
{
    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

void printMap(int map[][WIDTH])
{
    // only the bottom 9 rows of the map are printed
    // rows\cols 0 1 2 3 4 5 6 7 8
    // 8         ...
    // 7         ...
    // ...
    // 0         ...

    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << tile[map[i][j]] << ' ';
        }
        cout << endl;
    }
}

void printMatches(bool matches[HEIGHT][WIDTH])
{
    // prints the positions of all matching candies
    cout << "     0 1 2 3 4 5 6 7 8 \n";
    cout << "     \n";
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        cout << i << "    ";
        for (int j = 0; j < WIDTH; j++)
        {
            cout << matches[i][j] << ' ';
        }
        cout << endl;
    }
}

bool inBounds(int y, int x)
{
    // check if the input coordinates are out of the active 9x9 grid
    if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
    {
        return false;
    }
    return true;
}

/***********************************************************************
 * TODO 1: Find all tiles that are matched with other tiles of the same
 * type in a group of 3 horizontally or vertically
 ***********************************************************************/
int findMatches(int map[][WIDTH], bool matches[HEIGHT][WIDTH])
{
    int thisNumber = 0, nextNumber = 0;
    int consecutiveCnt = 0, trueCnt = 0;

    // each time first set every position to be false
    for (int rows = 0; rows <= HEIGHT - 1; rows++)
    {
        for (int cols = 0; cols <= WIDTH - 1; cols++)
        {
            matches[rows][cols] = false;
        }
    }

    // check matches within one row
    for (int y_cor = 0; y_cor <= HEIGHT - 1; y_cor++) // go through each row of the map
    {
        for (int x_cor = 0; x_cor <= WIDTH - 2; x_cor++) // go through each column of one row (except last column)
        {
            thisNumber = map[y_cor][x_cor];
            nextNumber = map[y_cor][x_cor + 1];
            if (nextNumber == thisNumber && thisNumber != 0)
                consecutiveCnt++;
            else
                consecutiveCnt = 0;

            if (consecutiveCnt >= 2)
            {
                matches[y_cor][x_cor - 1] = true;
                matches[y_cor][x_cor] = true;
                matches[y_cor][x_cor + 1] = true;
            }
        }
        consecutiveCnt = 0;
    }

    consecutiveCnt = 0;

    // check matches within one colmun
    for (int x_cor = 0; x_cor <= WIDTH - 1; x_cor++) // go through each column of the map
    {
        for (int y_cor = 0; y_cor <= HEIGHT - 2; y_cor++) // go through each row of one column (except top row)
        {
            thisNumber = map[y_cor][x_cor];
            nextNumber = map[y_cor + 1][x_cor];
            if (nextNumber == thisNumber && thisNumber != 0)
                consecutiveCnt++;
            else
                consecutiveCnt = 0;

            if (consecutiveCnt >= 2)
            {
                matches[y_cor - 1][x_cor] = true;
                matches[y_cor][x_cor] = true;
                matches[y_cor + 1][x_cor] = true;
            }
        }
        consecutiveCnt = 0;
    }

    // count how many trues have we got
    for (int rows = 0; rows <= HEIGHT - 1; rows++)
    {
        for (int cols = 0; cols <= WIDTH - 1; cols++)
        {
            if (matches[rows][cols] == true)
                trueCnt++;
        }
    }

    return trueCnt;
}

/***********************************************************************
 * TODO 2: Remove all tiles that are matched with 3 others of the same
 * type horizontally or vertically, and update the game grid accordingly
 ***********************************************************************/
int processMatches(int map[][WIDTH])
{
    int matchCntForThisSearch = 0, totalMatch = 0;

    while (findMatches(map, matches) != 0) // each time after shifting, entries shall be re-marked
    {
        matchCntForThisSearch = findMatches(map, matches);
        totalMatch += matchCntForThisSearch;
        for (int x_pos = 0; x_pos <= WIDTH - 1; x_pos++) // for each column
        {
            for (int y_pos = HEIGHT - 1; y_pos >= 0; y_pos--) // from up to down go through each row in one column
            {
                if (matches[y_pos][x_pos] == true) // if that entry was marked a match, shift the above down
                {
                    for (int index = y_pos; index <= MAX_ROWS - 2; index++)
                    {
                        map[index][x_pos] = map[index + 1][x_pos];
                        map[MAX_ROWS - 1][x_pos] = 0;
                    }
                }
            }
        }
    }
    return totalMatch;
}

/***********************************************************************
 * TODO 3: Swap the tiles at the specified locations
 ***********************************************************************/
void swapTiles(int map[][WIDTH], int x1, int y1, int x2, int y2)
{
    int temp = 0;
    temp = map[y1][x1];
    map[y1][x1] = map[y2][x2];
    map[y2][x2] = temp;
}

// copy the contents of the first rows_to_copy rows of map to map_copy
void copyMap(int map[][WIDTH], int map_copy[][WIDTH], int rows_to_copy)
{
    for (int i = 0; i < rows_to_copy; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map_copy[i][j] = map[i][j];
        }
    }
}

/***********************************************************************
 * TODO 4: Consider and calculate the score gain for each possible move
 ***********************************************************************/
int considerMoves(int map[][WIDTH], int candidate_moves[][4], int &num_candidate_moves)
{
    int maxScore = 0, scoreForThisSwap = 0;
    num_candidate_moves = 0;
    int exeCnt = -1;

    // empty the candidate_moves list
    for (int i = 0; i < (HEIGHT - 1) * WIDTH + (WIDTH - 1) * HEIGHT; i++)
    {
        for (int dummy = 0; dummy <= 3; dummy++)
        {
            candidate_moves[i][dummy] = 0;
        }
    }

    // a list storing all possible scores of each possible swap for the given map
    int possibleScores[(HEIGHT - 1) * WIDTH + (WIDTH - 1) * HEIGHT] = {};

    // first consider all horizontal swaps (right swaps)
    for (int y_cor = 0; y_cor <= HEIGHT - 1; y_cor++)
    {
        for (int x_cor = 0; x_cor <= WIDTH - 2; x_cor++)
        {
            exeCnt++;
            swapTiles(map, x_cor, y_cor, x_cor + 1, y_cor);
            scoreForThisSwap = findMatches(map, matches);
            possibleScores[exeCnt] = scoreForThisSwap;
            swapTiles(map, x_cor, y_cor, x_cor + 1, y_cor);
        }
    }

    // then consider all vertical swaps (up swaps)
    for (int x_pos = 0; x_pos <= WIDTH - 1; x_pos++)
    {
        for (int y_pos = 0; y_pos <= HEIGHT - 2; y_pos++)
        {
            exeCnt++;
            swapTiles(map, x_pos, y_pos, x_pos, y_pos + 1);
            scoreForThisSwap = findMatches(map, matches);
            possibleScores[exeCnt] = scoreForThisSwap;
            swapTiles(map, x_pos, y_pos, x_pos, y_pos + 1);
        }
    }

    // go through the list of possible scores to find the maxScore for the given map
    for (int i = 0; i <= exeCnt - 1; i++)
    {
        if (possibleScores[i] > maxScore)
            maxScore = possibleScores[i];
    }

    /* go through each swap again to find where does maxScore occur */
    // first review all horizontal swaps (right swaps)
    for (int y_cor = 0; y_cor <= HEIGHT - 1; y_cor++)
    {
        for (int x_cor = 0; x_cor <= WIDTH - 2; x_cor++)
        {
            swapTiles(map, x_cor, y_cor, x_cor + 1, y_cor);
            if (findMatches(map, matches) == maxScore)
            {
                candidate_moves[num_candidate_moves][0] = x_cor;
                candidate_moves[num_candidate_moves][1] = y_cor;
                candidate_moves[num_candidate_moves][2] = x_cor + 1;
                candidate_moves[num_candidate_moves][3] = y_cor;
                num_candidate_moves++;
            }
            swapTiles(map, x_cor, y_cor, x_cor + 1, y_cor);
        }
    }
    // then review all vertical swaps (up swaps)
    for (int x_pos = 0; x_pos <= WIDTH - 1; x_pos++)
    {
        for (int y_pos = 0; y_pos <= HEIGHT - 2; y_pos++)
        {
            swapTiles(map, x_pos, y_pos, x_pos, y_pos + 1);
            if (findMatches(map, matches) == maxScore)
            {
                candidate_moves[num_candidate_moves][0] = x_pos;
                candidate_moves[num_candidate_moves][1] = y_pos;
                candidate_moves[num_candidate_moves][2] = x_pos;
                candidate_moves[num_candidate_moves][3] = y_pos + 1;
                num_candidate_moves++;
            }
            swapTiles(map, x_pos, y_pos, x_pos, y_pos + 1);
        }
    }

    return maxScore;
}

/***********************************************************************
 * TODO 5: Implement the solver
 ***********************************************************************/
int solver(int map[][WIDTH], int return_coordinates[4])
{
    int candidate_moves[(HEIGHT - 1) * WIDTH + (WIDTH - 1) * HEIGHT][4] = {};
    int num_candidate_moves = 0;

    int optimalGain = considerMoves(map, candidate_moves, num_candidate_moves);

    if (num_candidate_moves == 1)
    {
        return_coordinates[0] = candidate_moves[0][0];
        return_coordinates[1] = candidate_moves[0][1];
        return_coordinates[2] = candidate_moves[0][2];
        return_coordinates[3] = candidate_moves[0][3];
        return optimalGain;
    }

    else if (num_candidate_moves == 0)
    {
        return 0;
    }

    else
    {
        int map_copy[][WIDTH] = {};
        int possibleGains[num_candidate_moves] = {};
        for (int candidate = 0; candidate < num_candidate_moves; candidate++)
        {
            int subOptimalGain = 0;
            copyMap(map, map_copy, MAX_ROWS);
            swapTiles(map_copy, candidate_moves[candidate][0], candidate_moves[candidate][1], candidate_moves[candidate][2], candidate_moves[candidate][3]);
            subOptimalGain += solver(map_copy);
            possibleGains[candidate] = subOptimalGain;
        }

        int bestCandidate = 0;

        for (int k = 0; k < num_candidate_moves; k++)
        {
            if (possibleGains[k] > possibleGains[bestCandidate])
                bestCandidate = k;
        }

        return_coordinates[0] = candidate_moves[bestCandidate][0];
        return_coordinates[1] = candidate_moves[bestCandidate][1];
        return_coordinates[2] = candidate_moves[bestCandidate][2];
        return_coordinates[3] = candidate_moves[bestCandidate][3];

        return possibleGains[bestCandidate];
    }
}

// overloaded solver() used when returning the optimal move is not required
int solver(int map[][WIDTH])
{
    int dummy[4];
    return solver(map, dummy);
}
