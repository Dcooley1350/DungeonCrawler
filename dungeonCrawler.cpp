
#include <iostream>
#include <limits>
#include "dungeonCrawler.hpp"

using std::cin, std::cout, std::endl;

void addObjectsToDungeon(char (&)[MAX_SIZE][MAX_SIZE], char, int);
void addObjectToDungeon(char (&)[MAX_SIZE][MAX_SIZE], char, int []);
void resetStream();
bool validateCharacterInput(char, const char [], int);

void createDungeon(char (&dungeon)[MAX_SIZE][MAX_SIZE], int currentPlayerCoordinates[], int numTraps, int numTreasures)
{
    // Fill Dungeon with 'E' for 'empty' areas
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            dungeon[i][j] = EMPTY;
        }
    }
    // Add traps
    addObjectsToDungeon(dungeon, TRAP, numTraps);
    // Add treasures
    addObjectsToDungeon(dungeon, TREASURE, numTreasures);
    // Add player start
    addObjectToDungeon(dungeon, PLAYER, currentPlayerCoordinates);
    // Add exit
    addObjectsToDungeon(dungeon, EXIT, 1);
}

void addObjectsToDungeon(char (&dungeon)[MAX_SIZE][MAX_SIZE], char object, int numObjectsToAdd)
{
    for (int i = 0; i < numObjectsToAdd;) {
        int xCoordinate = rand() % MAX_SIZE;
        int yCoordinate = rand() % MAX_SIZE;
        if(dungeon[yCoordinate][xCoordinate] == EMPTY){
            dungeon[yCoordinate][xCoordinate] = object;
                    i++;
        }
    }
}
void addObjectToDungeon(char (&dungeon)[MAX_SIZE][MAX_SIZE], char object, int coordinates[])
{
    bool openLocation;
    do {
        int xCoordinate = rand() % MAX_SIZE;
        int yCoordinate = rand() % MAX_SIZE;
        if(dungeon[yCoordinate][xCoordinate] == EMPTY){
            dungeon[yCoordinate][xCoordinate] = object;
            openLocation = true;
            coordinates[X_AXIS] = xCoordinate;
            coordinates[Y_AXIS] = yCoordinate;
        }

    } while(!openLocation);
}

void displayDungeon(const char (&dungeon)[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            cout << '[' << dungeon[i][j] << ']';
        }
        cout << endl;
    }
}

void getMove(const int currentPlayerCoordinates[], int nextPlayerCoordinates[])
{
    bool validInput;
    char userInput;
    cout << "Where to next, explorer? (W,A,S,D)" << endl;
    do {
        cin >> userInput;
        // Uppercase the input to allow lower and uppercase entries
        userInput = static_cast<char>(toupper(userInput));
        // Check input for fail or invalid characters
        if(validateCharacterInput( userInput, ACCEPTABLE_MOVES, NUM_VALID_INPUTS)){
            //Input is valid, must make sure it is in bounds, then record
            switch (userInput) {
                case UP:
                    if((currentPlayerCoordinates[Y_AXIS] - 1) >= 0) {
                        nextPlayerCoordinates[X_AXIS] = currentPlayerCoordinates[X_AXIS];
                        nextPlayerCoordinates[Y_AXIS] = currentPlayerCoordinates[Y_AXIS] - 1;
                        validInput = true;
                    }
                    else {
                        validInput = false;
                        cout << MOVE_OUT_OF_BOUNDS << endl;
                    }
                    break;
                case DOWN:
                    if((currentPlayerCoordinates[Y_AXIS] + 1) < MAX_SIZE) {
                        nextPlayerCoordinates[X_AXIS] = currentPlayerCoordinates[X_AXIS];
                        nextPlayerCoordinates[Y_AXIS] = currentPlayerCoordinates[Y_AXIS] + 1;
                        validInput = true;
                    }
                    else {
                        validInput = false;
                        cout << MOVE_OUT_OF_BOUNDS << endl;
                    }
                    break;
                case LEFT:
                    if((currentPlayerCoordinates[X_AXIS] - 1) >= 0) {
                        nextPlayerCoordinates[X_AXIS] = currentPlayerCoordinates[X_AXIS] - 1;
                        nextPlayerCoordinates[Y_AXIS] = currentPlayerCoordinates[Y_AXIS];
                        validInput = true;
                    }
                    else {
                        validInput = false;
                        cout << MOVE_OUT_OF_BOUNDS << endl;
                    }
                    break;
                case RIGHT:
                    if((currentPlayerCoordinates[X_AXIS] + 1) < MAX_SIZE) {
                        nextPlayerCoordinates[X_AXIS] = currentPlayerCoordinates[X_AXIS] + 1;
                        nextPlayerCoordinates[Y_AXIS] = currentPlayerCoordinates[Y_AXIS];
                        validInput = true;
                    }
                    else {
                        validInput = false;
                        cout << MOVE_OUT_OF_BOUNDS << endl;
                    }
                    break;
                default:
                    break;
            }
        }
        else {
            //Input is invalid
            validInput = false;
            cout << "Invalid input detected. Try again (W,A,S,D)" << endl;
        }
    } while(!validInput);
}

bool checkMove(const char (&dungeon)[MAX_SIZE][MAX_SIZE], int newPlayerCoordinates[], char objectToCheck)
{
    bool spaceContainsObject = false;
    if(dungeon[newPlayerCoordinates[Y_AXIS]][newPlayerCoordinates[X_AXIS]] == objectToCheck){
        spaceContainsObject = true;
    }
    return spaceContainsObject;
}

void updateDungeon(char (&dungeon)[MAX_SIZE][MAX_SIZE], const int currentPlayerCoordinate[], const int newPlayerCoordinate[])
{
    dungeon[currentPlayerCoordinate[Y_AXIS]][currentPlayerCoordinate[X_AXIS]] = EMPTY;
    dungeon[newPlayerCoordinate[Y_AXIS]][newPlayerCoordinate[X_AXIS]] = PLAYER;
}

bool playAgain()
{

    char userInput, acceptableInput[2] {'y', 'n'};
    bool playAgain, validInput;
    cout << "Would you like to play again?(y/n)" << endl;
    do {
        cin >> userInput;
        if(validateCharacterInput(userInput, acceptableInput, 2)){
            validInput = true;
        }
        else {
            cout << "Invalid input detected. Enter y/n." << endl;
            resetStream();
            validInput = false;
        }
    } while(!validInput);
    if(userInput == 'y'){
        playAgain = true;
    }
    else {
        playAgain = false;
    }
    return playAgain;
}

int getInteger(int min, int max)
{
    int userInput, validatedInput;
    bool validInput;
    do {
        cin >> userInput;
        // Validate input
        if( !cin.fail() && userInput >= min && userInput <= max ) {
            validInput = true;
            validatedInput = userInput;
        }
        else {
            validInput = false;
            cout << "Invalid input detected. Try again" << endl;
        }
    } while(!validInput);

    return validatedInput;
}

bool validateCharacterInput(char input, const char validInputs[], int validInputsLength)
{
    bool validInput = false;
    for (int i = 0; i < validInputsLength; ++i) {
        if(validInputs[i] == input) {
            validInput = true;
        }
    }
    return validInput;
}

void resetStream()
{
    const long large = std::numeric_limits<std::streamsize>::max();
    const char endLine = '\n';
    // Clear input and errors
    cin.clear();
    // Flush the buffer
    cin.ignore(large,endLine);
}

void displayWelcome()
{
    cout << "Welcome to Dungeon Crawler!" << endl
         << "Avoid traps and gather as much gold as you can on the way to the exit!" << endl
         << "----------" << endl
         << "Map Key:" << endl
         << TREASURE << " = Gold" << endl
         << TRAP << " = Trap" << endl
         << PLAYER << " = Player Position" << endl
         << EXIT << " = Dungeon Exit" << endl
         << "----------" << endl
         << "Controls:" << endl
         << LEFT << " = Move player left" << endl
         << RIGHT << " = Move player right" << endl
         << UP << " = Move player up" << endl
         << DOWN << " = Move player down" << endl;
}
