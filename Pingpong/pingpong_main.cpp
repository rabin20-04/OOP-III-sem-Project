#include <iostream>
#include <raylib.h> /// Raylib is a library for making games

using namespace std;
int player_score = 0;
int cpu_score = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    // function to move the ball
    void move()
    {
        x += speed_x;
        y += speed_y;

        if (y+radius>=GetScreenHeight() || y-radius<=0) { // checking if the ball touch the bottom or top of the screen
        speed_y*=-1; //changing the direction of the ball in y direction



        if (x+radius>=GetScreenWidth())  cpu_score++;//computer wins
        
    

         if(x-radius<=0)  player_score++;// for left and right side obstruction
        
          if (x+radius>=GetScreenWidth() || x-radius<=0) // checking if the ball touch the left or right side of the screen  
          {
            speed_x*=-1; //changing the direction of the ball in x direction
          }  
           
    
            
        
    }
};

class Paddle{avoidObstruction(){

     if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
}

    protected:


public:
    float x, y;
    int speed;
    int width, height;

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

       avoidObstruction();
    }


};
class cpuPaddle: public Paddle
{

    public:
    void move(bally)
    {
        if (y + height/2 < bally)
        {
            y += speed;
        }
        if (y + height/2 > bally)
        {
            y -= speed;
        }

        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
        avoidobstruction();
    }

};

Ball ball;
Paddle player;

cpuPaddle cpu;

int main()
{
    cout << "Starting the game" << endl;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Ping Pong");

    SetTargetFPS(60); // this function will set the frame rate of the game to 60 frames per second
    // if we didn't set the frame rate the game will run as fast as the computer can handle

    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    
    player.width = 25;
    player.height = 120;
    player.x = screenWidth-player.width-12;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;  
    cpu.x = 12;
    cpu.y = screenHeight/2 - cpu.height/2;
    cpu.speed = 6;


    while (WindowShouldClose() == false)
    {                   // the game will run until window function get false value either from windows close or esc key
        BeginDrawing(); // this function creates a blankcanvas so that we can starting drawinng

ClearBackground(BLACK); // this function will clear the background of the canvas and set it to black

        ball.move();
        // remember that the coordinate system in raylib starts from the top left corner of the screen updown :y side: x
player.move();
cpu.move(ball.y);



//check for the colloision between the ball and the player
if (CheckCollisionCircleRec({ball.x, ball.y, ball.radius}, {player.x, player.y, player.width, player.height}) || CheckCollisionCircleRec({ball.x, ball.y, ball.radius}, {cpu.x, cpu.y, cpu.width, cpu.height}))
{
    ball.speed_x *= -1;
}
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE); // x1 y1 x2 y2 color

        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(FormatText("%i",cpu_score), screenWidth /4- 20, 20, 80, WHITE); // text x y font size color
                DrawText(FormatText("%i",player_score), screenWidth - 20, 20, 80, WHITE); // text x y font size color

       
        DrawRectangle(12, screenHeight / 2 - 60, 25, 120, WHITE); // x y width height color

 

        EndDrawing(); // this function will end the drawing and display the canva
    }

    CloseWindow();
    return 0;
}
