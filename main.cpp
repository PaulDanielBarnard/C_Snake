#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

//height & width of boundary
const int width = 80;
const int height = 20;

//Snake Head coordinates of snake (x-axis, y-axis)
int x, y;
//food coordinates
int fruitCordX, fruitCordY;
//var to store player score
int score;
//Arr to store coordinates of snake tail (x-axis, y-axis)
int snakeTailX[100], snakeTailY[100];
//var to store snake's tail length
int tailLen;
//enum for storing snake's direction
enum snakesDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
//Snake's Direction var
snakesDir sDir;
//bool for checking game state
bool gameState;

void GameInit()
{
    gameState = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    score = 0;
    tailLen = 0;
    //Spawn fruit away from snake
    do {
        fruitCordX = rand() % (width - 2) + 1;
        fruitCordY = rand() % (height - 2) + 1;
    } while (fruitCordX == x && fruitCordY == y);
}

//Function for creating game board & rendering
void GameRender(std::string playerName)
{
    system("cls"); //clr console

    //Create Top Walls
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    //Create Middle Walls & game content
    for (int i = 0; i < height; i++)
    {
        std::cout << "#";
        for (int j = 1; j < width; j++)
        {
            //Snake head
            if (i == y && j == x)
                std::cout << "O";

            //Food
            else if (i == fruitCordY && j == fruitCordX)
                std::cout << "*";

            //Snake tail
            else
            {
                bool printTail = false;
                for (int k = 0; k < tailLen; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        std::cout << "o";
                        printTail = true;
                        break;
                    }
                }

                //Empty space
                if (!printTail)
                    std::cout << " ";
            }
        }
        std::cout << "#" << std::endl;
    }

    //Create Bottom Walls
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    //Display Score
    std::cout << playerName << "'s Score: " << score << std::endl;
}

//Function for handling player input
void GameInput()
{
    //Check if a key is pressed
    if (_kbhit())
    {
        //Get the pressed key
        switch (_getch())
        {
        case 'a':
            if (sDir != RIGHT)
                sDir = LEFT;
            break;
        case 'd':
            if (sDir != LEFT)
                sDir = RIGHT;
            break;
        case 'w':
            if (sDir != DOWN)
                sDir = UP;
            break;
        case 's':
            if (sDir != UP)
                sDir = DOWN;
            break;
        case 'x':
            gameState = true;
            break;
        }
    }
}

//Function for game logic
void GameLogic()
{
    if (sDir == STOP) return;

    //Save old head position before moving
    int prevHeadX = x;
    int prevHeadY = y;

    //Move snake head based on direction
    switch (sDir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //Wall collision (wrap around)
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    //Self collision
    for (int i = 0; i < tailLen; i++)
    {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameState = true;
    }

    //Fruit collision
    if (x == fruitCordX && y == fruitCordY)
    {
        score += 10;
        tailLen++;
        //Spawn fruit away from snake body
        bool onSnake;
        do {
            onSnake = false;
            fruitCordX = rand() % (width - 2) + 1;
            fruitCordY = rand() % (height - 2) + 1;
            if (fruitCordX == x && fruitCordY == y)
                onSnake = true;
            for (int i = 0; i < tailLen && !onSnake; i++)
            {
                if (snakeTailX[i] == fruitCordX && snakeTailY[i] == fruitCordY)
                    onSnake = true;
            }
        } while (onSnake);
    }

    //Shift tail from end to start
    for (int i = tailLen - 1; i > 0; i--)
    {
        snakeTailX[i] = snakeTailX[i - 1];
        snakeTailY[i] = snakeTailY[i - 1];
    }
    //Place old head position at front of tail
    if (tailLen > 0)
    {
        snakeTailX[0] = prevHeadX;
        snakeTailY[0] = prevHeadY;
    }
}

int main()
{
    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    GameInit();

    while (!gameState)
    {
        GameRender(playerName);
        GameInput();
        GameLogic();
        Sleep(100); //Game speed
    }

    //Game Over screen
    system("cls");
    std::cout << "============================" << std::endl;
    std::cout << "       GAME OVER!" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << playerName << "'s Final Score: " << score << std::endl;
    std::cout << "============================" << std::endl;

    return 0;
}
