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
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    score = 0;
    tailLen = 0;
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
        for (int j = 0; j <= width; j++)
        {
            //Left wall
            if (j == 0)
                std::cout << "#";

            //Snake head
            else if (i == y && j == x)
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

            //Right wall
            if (j == width)
                std::cout << "#";
        }
        std::cout << std::endl;
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
    //Store previous tail position
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;

    //Update tail positions
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < tailLen; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

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
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        tailLen++;
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

    return 0;
}
