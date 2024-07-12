//yo arko version ko ho where there been no use of the GUI


// I have left it so may be I could work on it later for better unnderstanding of the project

#include<iostream>
using namespace std;
enum eDir { STOP = 0, LEFT =1, UPLEFT =2, DOWNLEFT=3, RIGHT=4, UPRIGHT=5, DOWNRIGHT=6};
//enum is the just a way to store the value

class cball
{

private:
int x,y;//to store the position of the ball
int originalX, originalY;
eDir direction;


public:
cball(int posX, int posY)
{
originalX = posX;
originalY = posY;
x=posX; 
y=posY;
direction = STOP;

}

void Reset()
{

x = originalX; y = originalY;
direction = STOP;
}

void changeDirection(edir d)
{

    direction = d;
}
void randomDirection()
{
  direction = (eDir) ((rand() %6 )+)1; //random number from 1 to 6

}

    inline int getX() { return x;}
    inline int getY() { return y;}
    inline eDir getDirection () { return direction;}

     void Move()
     {
        switch (direction)
        {
            case STOP:
            break;

            case LEFT:
            x--;
            break;

            case RIGHT:
            x++;
            break;


        }


     }
};




int main (){


    return 0;
}