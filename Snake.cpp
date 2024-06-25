#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <vector>

using namespace std;

#define W 30
#define H 17
#define upArrow 72
#define downArrow 80
#define leftArrow 75
#define rightArrow 77

class Food
{
     COORD foodPos;

public:
     Food()
     {
          generateFood();
     }
     void generateFood()
     {
          srand(time(NULL));
          foodPos.X = rand() % W + 1;
          foodPos.Y = rand() % H + 1;
     }
     COORD getFoodPos()
     {
          return foodPos;
     }
};

class Snake : public Food
{
     int len;
     char direction;
     COORD snake_Position;
     vector<COORD> snakeBody;

public:
     Snake(COORD pos)
         : Food()
     {
          snake_Position = pos;
          len = 1;
          snakeBody.push_back(pos);
     }
     void moveSnake()
     {

          switch (direction)
          {
          case upArrow:
               snake_Position.Y--;
               break;
          case downArrow:
               snake_Position.Y++;
               break;
          case leftArrow:
               snake_Position.X--;
               break;
          case rightArrow:
               snake_Position.X++;
               break;
          }
          snakeBody.push_back(snake_Position);
          if (snakeBody.size() > len)
          {
               snakeBody.erase(snakeBody.begin());
          }
     }
     int get_len()
     {
          return len;
     }
     void setDir(int dir)
     {
          direction = dir;
     }
     COORD getPos()
     {
          return snake_Position;
     }

     const bool isHit() {}

     void grow()
     {
          ++len;
     }
     bool isEaten()
     {
          return (snake_Position.X == getFoodPos().X && snake_Position.Y == getFoodPos().Y);
     }
     vector<COORD> getSnakeBody()
     {
          return snakeBody;
     }
};

class GameBoard : public Snake
{
private:
     int b_width;
     int b_height;

public:
     GameBoard(int w, int h, COORD POS)
         : Snake(POS)
     {
          b_width = w;
          b_height = h;
     }
     void gameBoard()
     {
          COORD f_Pos = getFoodPos();
          vector<COORD> snakeBody = getSnakeBody();
          for (int i = 0; i <= b_height + 1; i++)
          {
               cout << "\t\t\t";
               for (int j = 0; j <= b_width + 1; j++)
               {
                    if (i == 0 || i == b_height + 1 || j == 0 || j == b_width + 1)
                    {
                         cout << "#";
                    }
                    else if (i == f_Pos.Y && j == f_Pos.X)
                    {
                         cout << "*";
                    }
                    else
                    {
                         bool s_Pos = false;
                         for (int k = 0; k < snakeBody.size(); k++)
                         {
                              if (i == snakeBody[k].Y && j == snakeBody[k].X)
                              {
                                   cout << "O";
                                   s_Pos = true;
                                   break;
                              }
                         }
                         if (!(s_Pos))
                              cout << " ";
                    }
               }
               cout << endl;
          }
     }
     const bool isHit(GameBoard &snake)
     {
          return (snake.getPos().X == 0 || snake.getPos().Y == 0 || snake.getPos().X == b_width + 1 || snake.getPos().Y == b_height + 1);
     }
};

main()
{
     GameBoard snake(W, H, {W / 2, H / 2});
     while (true)
     {
          Sleep(40);
          snake.gameBoard();
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
          if (kbhit())
          {
               switch (getch())
               {
               case upArrow:
                    snake.setDir(upArrow);
                    break;
               case downArrow:
                    snake.setDir(downArrow);
                    break;
               case leftArrow:
                    snake.setDir(leftArrow);
                    break;
               case rightArrow:
                    snake.setDir(rightArrow);
                    break;
               }
          }
          snake.moveSnake();
          if (snake.isHit(snake))
          {
               cout << "GAME OVER!!!" << endl;
               exit(0);
          }
          if (snake.isEaten())
          {
               snake.grow();
               snake.generateFood();
          }
     }
}
