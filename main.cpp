#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

//height & weight of boundry
const int width = 80;
const int height = 20;

//Snake Head coordinates of snake (x-axis, y-axis)
int x,y;
//food coordinates
int fruitCordX, fruitCordY;
//var to store player score
int score;
//Arr to store coordinates of snake tail (x-axis, y-axis)
int snakeTailX[100], snakeTailY[100];
//var to store snake's tail length
int tailLen;
//enum for storing snake's direction
enum snakesDir {STOP = 0, LEFT, RIGHT, UP, DOWN};
//Snake's Direction var
snakesDir sDir;
//bool for checking game state
bool gameState;

void GameInit()
{
    gameState = false;
    sDir = STOP;
    x = width/2;
    y = height/2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    score = 0;
}