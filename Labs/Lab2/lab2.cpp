#include <iostream>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;

const int PATTERN_SIZE = 8;
const int WIDTH = 60;
const int HEIGHT = 15;

int initialState[WIDTH]; // the initial state
int grid[HEIGHT][WIDTH]; // the grid for display
int rule[PATTERN_SIZE];  // the rule in binary, 1 bit per array element
int curRow;              // current row
int curStep;             // current step
int ruleNum;             // rule number in decimal
int tempRuleNum;         // for binary conversion

const unsigned long MAX_RAND = 0x80000000;
static unsigned long rng_lab1 = 0;
static void _srand(unsigned long seed)
{
    rng_lab1 = seed;
}

static unsigned long _rand()
{
    rng_lab1 = (1103515245 * rng_lab1 + 12345) % (1 << 31);
    return rng_lab1 & 0x7FFFFFFF;
}

int getRandNum(double probability)
{
    unsigned long threshold = probability * MAX_RAND;
    return _rand() < threshold ? 1 : 0;
}

bool checkArrForExsistingItem(int array[], int size, int item)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == item)
            return true;
    }
    return false;
}

void initRule()
{

    //
    // TODO: task 1.1, initialize the rule
    // Ask the user to input the decimal rule number.
    // Check whether the number is in between 0 and 255, inclusive
    // If not, ask the user to retry
    // Otherwise, convert the number to binary and store the bits into rule[]
    //
    // Your code here
    //
    while (1)
    {
        cout << "Please enter the rule number:" << endl;
        cin >> ruleNum;
        if (ruleNum >= 0 && ruleNum <= 255)
            break;
        cout << "Invalid rule number, please retry:" << endl;
    }

    tempRuleNum = ruleNum;

    // converting the number into binary and storing in to rule[PATTERN_SIZE]
    for (int i = 0; i < PATTERN_SIZE; i++)
    {
        rule[i] = tempRuleNum % 2;
        tempRuleNum /= 2;
    }
}

void initStateFromInput()
{

    //
    // TODO: task 1.2, initialize the initial state from user input
    // Ask the user to input the number of initially living cells and their positions
    // Report error if the number or the positions are invalid
    // Initialize grid[][] and initialState[] accordingly
    //
    // Your code here
    //
    int num_of_cells_alive_initially = 0;
    int enteredColums[WIDTH] = {};
    for (int i = 0; i <= 60; i++)
    {
        enteredColums[i] = -5;
    }

    int colum = 0;
    cout << "Please enter the number of cells alive in the initial state:" << endl;
    while (1)
    {
        cin >> num_of_cells_alive_initially;
        if (num_of_cells_alive_initially > 0 && num_of_cells_alive_initially <= WIDTH)
        {
            break;
        }

        cout << "Invalid number of living cells, please retry:" << endl;
    }

    cout << "Please enter the column at which the cells are alive:" << endl;

    for (int i = 0; i < num_of_cells_alive_initially; i++)
    {
        cin >> colum;
        if (colum < 0 || colum > WIDTH - 1)
        {
            cout << "Column out of bound" << endl;
            i--;
            continue;
        }
        if (checkArrForExsistingItem(enteredColums, WIDTH, colum))
        {
            cout << "Column duplicated" << endl;
            i--;
            continue;
        }
        initialState[colum] = 1;
        grid[0][colum] = 1;
    }
}

void initStateRandomly()
{

    //
    // TODO: task 1.3, initialize the initial state randomly
    // Ask the user for a fill rate and use it as the probability to generate random 0 and 1s
    // using getRandNum(). Fill in initialState[] and grid[][] accordingly
    //
    // Your code here
    //
    float inputProb;

    cout << "Please enter the fill rate:" << endl;
    while (1)
    {
        cin >> inputProb;
        if (inputProb >= 0 && inputProb <= 1)
        {
            break;
        }
        cout << "Invalid probability, please retry:" << endl;
    }

    for (int i = 0; i < WIDTH; i++)
    {
        grid[0][i] = getRandNum(inputProb);
        initialState[i] = getRandNum(inputProb);
    }
}

int getNeighbourState(int row, int col)
{

    //
    // TODO: task 2.1, get a decimal number repersenting the current state of the neighbours
    // Compute the state of the neighbours with respect to the given row and col
    // Wrap around the boundaries if necessary
    //
    // Your code here
    //
    int middleDig, leftDig, rightDig = 0;
    middleDig = grid[row][col];
    leftDig = col >= 1 ? grid[row][col - 1] : grid[row][WIDTH - 1];
    rightDig = col < WIDTH - 1 ? grid[row][col + 1] : grid[row][0];

    int returnValue = 0;
    if (rightDig)
        returnValue += 1;
    if (middleDig)
        returnValue += 2;
    if (leftDig)
        returnValue += 4;

    return returnValue;
}

void update()
{

    //
    // TODO: task 2.2, update to the next state
    // Compute the next state according to the current state and the rule
    // Update grid[][], curRow and curStep correspondingly
    // Wrap around the boundaries if needed
    //
    // Your code here
    //
    int nextState[WIDTH] = {};
    int nextRow = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        nextState[i] = rule[7 - getNeighbourState(curRow, i)];
    }
    if (curRow == HEIGHT - 1)
        nextRow = 0;
    else
        nextRow = curRow + 1;
    curRow = nextRow;
    curRow %= HEIGHT;
    curStep++;
    for (int i = 0; i < WIDTH; i++)
    {
        grid[curRow][i] = nextState[i];
    }
}

void getState(int step)
{

    //
    // TODO: task 2.3, get the state of the automaton after given steps
    // Modify grid[][] so that its content represents the state of the automaton
    // after the given number of steps
    //
    // Your code here
    //
    if (step < curStep)
    {
        curStep = curRow = 0;
        for (int i = 0; i < WIDTH; i++)
        {
            grid[curRow][i] = initialState[i];
        }
    }

    while (step >= curStep)
    {
        update();
    }
}

void initState()
{
    cout << "Please specify the initial state. 'R' for random generation, 'M' for manual input." << endl;
    char mode;
    cin >> mode;
    while (mode != 'R' && mode != 'M')
    {
        cout << "Invalid mode, please enter 'R' or 'M':" << endl;
        cin >> mode;
    }

    if (mode == 'R')
    {
        initStateRandomly();
    }
    else
    {
        initStateFromInput();
    }
}

void displayGrid()
{
    cout << "State of rule " << ruleNum << " after " << curStep << " steps:" << endl;
    cout << std::string(WIDTH, '=') << endl;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cout << (grid[i][j] ? '@' : ' ');
        }
        cout << endl;
    }

    cout << std::string(WIDTH, '=') << endl;
}

int main()
{
    _srand(2012);

    cout << "Elementary Cellular Automaton" << endl;
    initRule();
    initState();
    displayGrid();

    while (true)
    {
        cout << "Please specify the number of steps" << endl;
        int step;
        cin >> step;

        if (step == -1)
        {
            break;
        }

        if (step < 0)
        {
            cout << "Invalid step" << endl;
            continue;
        }

        getState(step);
        displayGrid();
    }
}
