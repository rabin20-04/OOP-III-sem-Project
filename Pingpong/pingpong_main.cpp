
#include <iostream>
#include <raylib.h> /// Raylib is a library for making games
#include <fstream>
#include <string.h>
#include <vector>

Color lightBlue = Color{173, 216, 230, 255};    // Light Blue with full opacity
Color mediumDarkBlue = Color{0, 102, 204, 255}; // Medium Dark Blue with full opacity
Color lighterBlue = Color{192, 230, 242, 255};  // Slightly Lighter Blue with full opacity
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
        static Sound lose = LoadSound("resources/lose.wav");
        static Sound win = LoadSound("resources/win.wav");

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {                  // checking if the ball touch the bottom or top of the screen
            speed_y *= -1; // changing the direction of the ball in y direction

            if (x + radius >= GetScreenWidth())
            {
                PlaySound(lose);
                cpu_score++; // computer wins
                resetball();
            }

            if (x - radius <= 0)
            {
                PlaySound(win);
                player_score++;
                resetball();
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
    float width, height;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, BLACK);
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

class AnimateBall
{ // Animation class
public:
    Vector2 position;
    float radius;
    Color color;
    float speed;
    void animation(int temhighscore, int new_highscore, int &player_score, int &life)
    {
        Sound celebration = LoadSound("resources/celebration.mp3");

        int screenWidth = 1280;
        int screenHeight = 720;
        vector<AnimateBall> balls;
        for (int i = 0; i < 40; i++)
        {
            AnimateBall ball;
            ball.position = {(float)GetRandomValue(0, screenWidth), 0};
            ball.radius = (float)GetRandomValue(5, 10); // Reduced size
            ball.color = {(unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255};
            ball.speed = (float)GetRandomValue(50, 100) / 10.0f;
            balls.push_back(ball);
        }
        PlaySound(celebration);

        while (!WindowShouldClose())
        {
            // Update

            for (auto &ball : balls)
            {
                ball.position.y += ball.speed; // Move balls downwards
                if (ball.position.y > screenHeight + ball.radius)
                {
                    ball.position.y = -ball.radius;                          // Reset position to top if it goes beyond the bottom
                    ball.position.x = (float)GetRandomValue(0, screenWidth); // Randomize horizontal position
                }
            }

            // Draw
            BeginDrawing();
            ClearBackground(lightBlue);

            for (const auto &ball : balls)
            {
                DrawCircleV(ball.position, ball.radius, ball.color);
            }
            DrawText("Congratulations! You have gain the highscore", screenWidth / 6, screenHeight / 2, 45, BLACK); // text x y font size color
            DrawText(TextFormat("Previous record:%i", temhighscore), screenWidth / 6, 460, 45, BLACK);              // text x y font size color
            DrawText(TextFormat("New Record:%i", new_highscore), screenWidth / 6, 560, 45, BLACK);                  // text x y font size color
            DrawText("Press ENTER to continue ,ESC to exit the game", screenWidth / 6, 620, 30, BLACK);             // text x y font size color
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER))
            {
                UnloadSound(celebration);
                player_score = 0;
                life = 2;
                break;
            }
        }
    }
};

Ball ball;
Paddle player;
AnimateBall aniball;

cpuPaddle cpu;

int main()
{
    cout << "Starting the game" << endl;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int highscore, newcpu_score;
    int life = 2;
    int temhighscore = 0;

    fstream file("highscore.txt", ios::in | ios::out);

    // Check if the file opened successfully
    if (!file)
    {
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    file >> highscore;
    temhighscore = highscore;
    // Check if reading was successful
    if (!file)
    {
        cerr << "Error reading the number from the file!" << endl;
        file.close();
        return 1;
    }
    file.close();

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
    cpu.speed = 3;

    // loading of the sound
    Sound strike = LoadSound("resources/strike.wav");

    while (!WindowShouldClose())
    {

        while (!WindowShouldClose()) // this function will return true if the window is closed

        {

            if (life == 0)
            {
                break;
            }

            BeginDrawing(); // this function creates a blankcanvas so that we can starting drawinng

            ClearBackground(mediumDarkBlue); // this function will clear the background of the canvas and set it to black

            // slide  and middle lines for the game interface
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, BLACK);  // x1 y1 x2 y2 color
            DrawLine(2, 2, screenWidth, 2, BLACK);                               // x1 y1 x2 y2 color
            DrawLine(0, screenHeight - 2, screenWidth, screenHeight - 2, BLACK); // x1 y1 x2 y2 color

            DrawRectangle(screenWidth / 2, 0, 2, screenHeight, BLACK);   // x y width height color
            DrawRectangle(0, 0, screenWidth / 2, screenHeight, BLUE);    // x y width height color
            DrawCircle(screenWidth / 2, screenHeight / 2, 150, SKYBLUE); // x y radius color
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

            ball.Draw();
            player.Draw();
            cpu.Draw();
            DrawText(TextFormat("YOU:%i", player_score), 900, 20, 50, BLACK); // text x y font size color
            DrawText(TextFormat("CPU"), 300, 20, 50, BLACK); // text x y font size color
            DrawText(TextFormat("Enter ESC key to exit at any time"), 5, 5,20, BLACK); // text x y font size color

            DrawText(TextFormat("HighScore:%i", highscore), screenWidth - 190, 20, 30, BLACK); // text x y font size color
            if (newcpu_score != cpu_score)
            {
                life = life - 1;
                cpu_score = newcpu_score;
            }

            DrawText(TextFormat("Life:%i", life), screenWidth - 190, 50, 30, BLACK);

            EndDrawing(); // this function will end the drawing and display the canva

            if (player_score > highscore)
            {
                highscore = player_score;
                // Open the file in write mode
                ofstream file("highscore.txt", ios::out | ios::trunc);
                if (file.is_open())
                {
                    // Write the updated high score
                    file << highscore;
                    file.close();
                }
                else
                {
                    // Handle error if file cannot be opened
                    cerr << "Unable to open file for writing." << endl;
                }
            }
        }

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(lightBlue);
            if (player_score > temhighscore)
            {
                aniball.animation(temhighscore, highscore, player_score, life);
                break;

                EndDrawing();
            }
            else
            {
                DrawText("Game Over ", screenWidth / 6, screenHeight / 2, 60, BLACK);
                DrawText(TextFormat("Your Score: %i", player_score), screenWidth / 6, 500, 60, BLACK);
                DrawText("Press ENTER to play ESC to exit", screenWidth / 6, 600, 40, BLACK);
                EndDrawing();
                if (IsKeyPressed(KEY_ENTER))
                {
                    player_score = 0;
                    life = 2;
                    break;
                }
            }
        }
    }
    CloseAudioDevice();

    CloseWindow();

    return 0;
}