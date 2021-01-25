
#ifndef W3DUNGEONCRAWLERDCOOLEY_DUNGEONCRAWLER_HPP
#define W3DUNGEONCRAWLERDCOOLEY_DUNGEONCRAWLER_HPP

// Global Constants
const int MAX_SIZE = 10, NUM_VALID_INPUTS = 4, X_AXIS = 0, Y_AXIS = 1;
const char TRAP = 'T', TREASURE = 'G', PLAYER = 'P', EXIT = 'E', EMPTY = '-',
            LEFT = 'A', RIGHT = 'D', UP = 'W', DOWN = 'S';
const char ACCEPTABLE_MOVES[4] {LEFT, RIGHT, UP, DOWN};
const std::string MOVE_OUT_OF_BOUNDS = "Can not move farther in that direction! Try another direction!";

// Prototypes
void createDungeon(char (&)[MAX_SIZE][MAX_SIZE], int [], int, int);
void displayDungeon(const char (&)[MAX_SIZE][MAX_SIZE]);
void getMove(const int [], int []);
bool checkMove(const char (&)[MAX_SIZE][MAX_SIZE], int [], char);
void updateDungeon(char (&)[MAX_SIZE][MAX_SIZE], const int [], const int []);
bool playAgain();
int getInteger(int, int);
void displayWelcome();


#endif //W3DUNGEONCRAWLERDCOOLEY_DUNGEONCRAWLER_HPP
