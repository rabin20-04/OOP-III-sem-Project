#include <iostream>
#include <raylib.h> /// Raylib is a library for making games

Color SkyBlue = Color{102, 191, 255, 255};
Color DarkBlue = Color{0, 82, 172, 255};
Color DarkGreen = Color{0, 128, 0, 255};
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
        Sound lose = LoadSound("resources/lose.wav");
        Sound win = LoadSound("resources/win.wav");

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {                  // checking if the ball touch the bottom or top of the screen
            speed_y *= -1; // changing the direction of the ball in y direction

            if (x + radius >= GetScreenWidth())
            {
                PlaySound(lose);
                cpu_score++; // computer wins
                resetball();
                // UnloadSound(lose);
            }

            if (x - radius <= 0)
            {
                PlaySound(win);
                player_score++;
                resetball();
                // UnloadSound(win);
            }
        }
    }

    void resetball()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speed_x *= -1;
        speed_y *= -1;
    }
};

class Paddle
{
protected:
    void avoidObstruction()
    {

        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    int speed;
    int width, height;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, DarkBlue);
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

class cpuPaddle : public Paddle
{

public:
    void move(int bally)
    {
        if (y + height / 2 < bally)
        {
            y += speed;
        }
        if (y + height / 2 > bally)
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
        avoidObstruction();
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
    InitAudioDevice();

    SetTargetFPS(60); // this function will set the frame rate of the game to 60 frames per second
    // if we didn't set the frame rate the game will run as fast as the computer can handle

    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 12;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 12;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 1;

    // loading of the sound
    Sound strike = LoadSound("resources/strike.wav");

    while (WindowShouldClose() == false) //// the game will run until window function get false value either from windows close or esc key
    {

        BeginDrawing(); // this function creates a blankcanvas so that we can starting drawinng

        ClearBackground(SkyBlue); // this function will clear the background of the canvas and set it to black

        DrawRectangle(screenWidth / 2, 0, 2, screenHeight, WHITE);   // x y width height color
        DrawCircle(screenWidth / 2, screenHeight / 2, 90, DarkBlue); // x y radius color
        ball.move();
        // remember that the coordinate system in raylib starts from the top left corner of the screen updown :y side: x
        player.move();
        cpu.move(ball.y);

        // check for the colloision between the ball and the player
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
            PlaySound(strike);
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
            PlaySound(strike);
        }

        // slide  and middle lines for the game interface
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);  // x1 y1 x2 y2 color
        DrawLine(2, 2, screenWidth, 2, WHITE);                               // x1 y1 x2 y2 color
        DrawLine(0, screenHeight - 2, screenWidth, screenHeight - 2, WHITE); // x1 y1 x2 y2 color

        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("CPU:%i", cpu_score), screenWidth / 4 - 20, 20, 50, WHITE);        // text x y font size color
        DrawText(TextFormat("YOU:%i", player_score), 3 * screenWidth / 4 - 20, 20, 50, WHITE); // text x y font size colo

        EndDrawing(); // this function will end the drawing and display the canva
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}