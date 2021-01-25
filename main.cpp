
#include <iostream>
#include "dungeonCrawler.hpp"

using std::cout, std::cin, std::endl;

int main() {
    bool playing;
    srand(static_cast<unsigned int>(time(nullptr)));
    // Greet player and display rules
    displayWelcome();

    // Start new Game
    do {
        bool gameOver = false;
        bool win;
        char dungeon[MAX_SIZE][MAX_SIZE];
        int currentPlayerCoordinates[2],
            nextPlayerCoordinates[2],
            trapsInDungeon,
            maxTrapsInDungeon = 30,
            treasuresInDungeon,
            maxTreasuresInDungeon = 30,
            treasuresInInventory = 0;

        cout << "New game initializing!" << endl;
        // Get number of traps
        cout << "How many traps would you like in the dungeon? (0-30)" << endl;
        trapsInDungeon = getInteger(0, maxTrapsInDungeon);

        // Get number of treasures
        cout << "How many treasures would you like in the dungeon? (0-30)" << endl;
        treasuresInDungeon = getInteger(0, maxTreasuresInDungeon);

        // Create game map
        cout << "MAP INITIALIZING" << endl;
        createDungeon(dungeon, currentPlayerCoordinates, trapsInDungeon, treasuresInDungeon);

        // Turn loop
        do {
            displayDungeon(dungeon);
            getMove(currentPlayerCoordinates,nextPlayerCoordinates);
            if(checkMove(dungeon, nextPlayerCoordinates, TRAP)){
                gameOver = true;
                win = false;
                cout << "Bummer! You hit a trap!" << endl;
            }
            else if(checkMove(dungeon, nextPlayerCoordinates, TREASURE)){
                gameOver = false;
                win = false;
                treasuresInInventory++;
                cout << "You found treasure! You have " << treasuresInInventory << " treasures!" << endl;
            }
            else if(checkMove(dungeon,nextPlayerCoordinates, EXIT)){
                gameOver = true;
                win = true;
                cout << "You found the Exit! You have exited the dungeon with "
                << treasuresInInventory << " gold in your inventory!" << endl;
            }
            else {
                gameOver = false;
                win = false;
            }
            if(!gameOver) {
                updateDungeon(dungeon,currentPlayerCoordinates, nextPlayerCoordinates);
                currentPlayerCoordinates[X_AXIS] = nextPlayerCoordinates[X_AXIS];
                currentPlayerCoordinates[Y_AXIS] = nextPlayerCoordinates[Y_AXIS];
            }
        } while(!gameOver);
        if(win) {
            cout << "You win!" << endl;
        }
        else {
            cout << "You lose!" << endl;
        }
    } while(playAgain());
    return 0;
}
