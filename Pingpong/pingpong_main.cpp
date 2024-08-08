#include <raylib.h>
#include <iostream>
#include <string>
#include <fstream>
#include<vector>

using namespace std;


Color Green = Color{38, 184, 155 , 255};
Color Blue = Color{45, 110, 230, 255};
Color DarkBlue  = Color{25, 50, 180, 255};
Color LightB = Color{72, 146, 220 ,255};
Color Yellow = Color{243 , 213 , 91, 255};
Color roun = Color{141 , 188 , 232 , 255};
Color skyblue = Color{179 , 235 , 235 , 255};

Color lightBlue = Color{173, 216, 230, 255};    // Light Blue with full opacity
Color mediumDarkBlue = Color{0, 102, 204, 255}; // Medium Dark Blue with full opacity
Color lighterBlue = Color{192, 230, 242, 255};  // Slightly Lighter Blue with full opacity

Color backgroundGradientTop = {30, 60, 114, 255};   // #1E3C72
Color backgroundGradientBottom = {42, 82, 152, 255}; // #2A5298
Color ballColor = {255, 69, 0, 255};                // #FF4500
Color playerPaddleColor = {50, 205, 50, 255};       // #32CD32
Color cpuPaddleColor = {220, 20, 60, 255};          // #DC143C
Color netColor = WHITE;
Color textColor = WHITE;
Color textShadowColor = BLACK;
Color highScoreColor = {255, 215, 0, 255};  


int player_score = 0;
int cpu_score = 0;
int player2_score = 0;




class Ball{
float x,y ;
float speed_x,speed_y;
int r=12;
int player1 ,player2,round , cpu_score , life, player_score;


public:
Ball(){}
Ball(float a,float b){
    x=a;
    y=b;
    speed_x=6;
    speed_y=6;
    player1 = 0;
    player2 = 0;
    round =1;
    life =3;
    cpu_score =0;
     player_score=0;

    
}
void Draw(){

DrawCircle(x,y,r,WHITE);

}

   
void move(){
  x=x+speed_x;
  y=y+speed_y;

    if(y+r>= GetScreenHeight() || y-r<=0){
    speed_y*=-1.05;

    }

    if(x+r>= GetScreenWidth()){
        Sound lose = LoadSound("resources/lose.wav");
        PlaySound (lose);
         player2++;
         round++;
         life--;
         cpu_score++;

         resetball();

    }


    if ( x-r<=0){
         Sound win = LoadSound("resources/win.wav");
         PlaySound (win);
         player1++;
         round++;
          player_score++;
         resetball();

    }
}

void move2(){
  x=x+speed_x;
  y=y+speed_y;

    if(y+r>= GetScreenHeight() || y-r<=0){
    speed_y*=-1.0;

    }
 
     if(x+r>= GetScreenWidth() || x-r<=0){
    speed_x*=-1.0;

    }

}
     void colli(){
       
        speed_x*=-1;
       
        

     }

     //posion of ball in x and y  in return type
    float ballpy(){
    
      return y;
     }

    float ballpx(){
     
       return x;
      }

     //radius of ball
    float ballpr(){
        return r;
     }

    //score return
    int player1r (){

       return player1;
      
     }
    int player2r (){

       return player2;
      
      }

    int rounds(){

        return round ;
    }
    int lifes(){

        return life;
    }
    int  cpu_scores(){

        return  cpu_score;
    }
    int player_scores(){

        return  player_score;
    }


    void resetball()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[2]={-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)] ;
        speed_y =6*speed_choices[GetRandomValue(0,1)] ;
    }


};


class Paddle{
    protected:

float x,y;
float width,height;
int speed;

public:
Paddle(){}
Paddle( float a, float b,float w, float h){
    x=a;
    y=b;
    width=w;
    height=h;
    speed=6;

}
void Draw(){

        DrawRectangleRounded(Rectangle{x,y,width,height}, 0.8, 0,Green);

}
void avoidObstruction(){
    if(y<=0){

        y=0;
    }

    if(y+height >= GetScreenHeight() ){

        y=GetScreenHeight() -height;
    }



}

void move(){
    if (IsKeyDown(KEY_UP)){

        y=y-speed;

    }

    if (IsKeyDown(KEY_DOWN)){

        y=y+speed;

    }

   avoidObstruction();
}

//posion of paddie  in x and y  in return type
float paddlepy(){
    
    return y;
}
float paddlepx(){
    
    return x;
}
float paddlewidth(){
    
    return width;
}
float paddleheight(){
    

    return height;
}

};


//CPU paddle 
class cpuPaddle : public Paddle
{

public:
    cpuPaddle(float a, float b,float w,float h) :Paddle (a,b,w,h){
        speed =4.5;

        
    }


    void move(float by){
        if ( y+ height >= by){

            y = y - speed;
         }
         else if (y + height <= by){

            y = y + speed;
         }

       avoidObstruction();
    }



};



class player2 :public Paddle{

    public:
    player2(){}
    //using concept of constructor in single inheratance
    player2(float a, float b,float w,float h) :Paddle (a,b,w,h){
    
    }

     void move(){
    if (IsKeyDown(KEY_W)){

        y=y-speed;

    }

    if (IsKeyDown(KEY_S)){

        y=y+speed;

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

    void animation(int temhighscore, int new_highscore, int &player_score, int life)
    {
        Sound celebration = LoadSound("resources/celebration.wav");

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
            ClearBackground(SKYBLUE);

            for (const auto &ball : balls)
            {
                DrawCircleV(ball.position, ball.radius, ball.color);
            }
            DrawText("Congratulations! You have gained the highscore", screenWidth / 6, screenHeight / 2, 45, BLACK); // Use BLACK or define highScoreColor
            DrawText(TextFormat("Previous record:%i", temhighscore), screenWidth / 6, 460, 45, BLACK);              // Use BLACK or define highScoreColor
            DrawText(TextFormat("New Record:%i", new_highscore), screenWidth / 6, 560, 45, BLACK);                  // Use BLACK or define highScoreColor
            DrawText("Press ENTER to continue ,ESC to exit the game", screenWidth / 6, 620, 30, BLACK);             // Use BLACK or define highScoreColor
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER))
            {
                UnloadSound(celebration);
                break;
            }
        }
    }

    void animation(int player1_score, int player2_score) // function overloading
    {
        Sound celebration = LoadSound("resources/celebration.wav");

        int screenWidth = 1280;
        int screenHeight = 720;
        vector<AnimateBall> balls;
        for (int i = 0; i < 60; i++)
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
            ClearBackground(SKYBLUE);

            for (const auto &ball : balls)
            {
                DrawCircleV(ball.position, ball.radius, ball.color);
            }

            if (player1_score > player2_score)
            {
                DrawText("Congratulations! Player 1 wins", screenWidth / 6, screenHeight / 2, 45, BLACK); // Use BLACK or define highScoreColor
            }
            else if (player1_score < player2_score)
            {
                DrawText("Congratulations! Player 2 wins", screenWidth / 6, screenHeight / 2, 45, BLACK); // Use BLACK or define highScoreColor
            }
            else
            {
                DrawText("It's a tie!", screenWidth / 6, screenHeight / 2, 45, BLACK); // Add this for a tie case
            }

            DrawText("Press ENTER to play ESC to exit", screenWidth / 6, 600, 40, BLACK); // Use BLACK or define highScoreColor
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER))
            {
                UnloadSound(celebration);
                break;
            }
        }
    }
};


class Button {
private:
    string name;
    float x, y;
    float width, height;

public:
    Button(const string& a, float xPos, float yPos) : name(a), x(xPos), y(yPos), width(250), height(40) {}

    void Draw() {
        Vector2 mousePosition = GetMousePosition();
        Rectangle buttonRect = {x, y, width, height};
        Color buttonColor = CheckCollisionPointRec(mousePosition, buttonRect) ? GREEN : BLACK;

        // Draw border
        const float borderThickness = 4.0f;
        DrawRectangleRounded(buttonRect, 0.8f, 0, WHITE); // Draw the border
        DrawRectangleRounded({x - borderThickness, y - borderThickness, width + 2 * borderThickness, height + 2 * borderThickness}, 0.8f, 0, GOLD); // Draw border rectangle

        // Draw the button with its color
        DrawRectangleRounded(buttonRect, 0.8f, 0, buttonColor);
        // Draw text centered in the button
        int textWidth = MeasureText(name.c_str(), 30);
        int textX = x + (width - textWidth) / 2;
        int textY = y + (height - 30) / 2;
        DrawText(name.c_str(), textX, textY, 30, WHITE);
    }

    bool IsPressed(){
        Rectangle rect = {x, y, width, height};
        Vector2 mousePosition = GetMousePosition();
        return CheckCollisionPointRec(mousePosition, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
};

int main() {

    const int screenWidth = 1200;
    const int screenHeight = 700;
    InitWindow(screenWidth , screenHeight, "PING PONG");
    InitAudioDevice();
    SetTargetFPS(60);

    Button button1("Multi Play", screenWidth /2 -120, screenHeight /2 -200);
    Button button2("Single Play", screenWidth /2 -120, screenHeight /2-100);
    Button button3("Quit", screenWidth /2 -120, screenHeight /2);
    Sound strike =LoadSound("resources/strike.wav");

        //object define
    Ball b(screenWidth/2,screenHeight /2) ,b2(screenWidth/2,screenHeight /2);

    Paddle player1(screenWidth-35,screenHeight /2-50,25,130),play1(screenWidth-35,screenHeight,25,130);


    player2 player3(10,screenHeight /2-50,25,130),play2(10,0,25,130);

     AnimateBall aniball;


    while (!WindowShouldClose()) {
        if (button1.IsPressed()) {

             int  player1_score , player2_score;


    cout << "Starting the game" << endl;



    //game loop start 

    
    while (WindowShouldClose() ==false){

    //game end in 5 rounds 
     if (b.rounds()==4 ){

         aniball.animation( player1_score, player2_score);
        
        break;
     }
    else
        {

    BeginDrawing();

    //updating
    b.move();
    player3.move();
    //c.update(b.ballpy());
    player1.move();
    player1_score =b.player1r();
    player2_score = b.player2r();

    //checking collisions
    if(CheckCollisionCircleRec(Vector2{b.ballpx(), b.ballpy()}, b.ballpr(), Rectangle{ player1.paddlepx(), player1.paddlepy(), player1.paddlewidth(), player1.paddleheight()}))
    {
    
       
         b.colli();
         PlaySound(strike);

     }
    if(CheckCollisionCircleRec(Vector2{b.ballpx(), b.ballpy()}, b.ballpr(), Rectangle{ player3.paddlepx(), player3.paddlepy(), player3.paddlewidth(), player3.paddleheight()}))
    {

        b.colli();
                 PlaySound(strike);

      

    }

    //Drawing 
    ClearBackground(DarkBlue);


    DrawLine(0,0,screenWidth,0,WHITE);
    DrawLine(0,screenHeight ,screenWidth,screenHeight ,WHITE);
    DrawRectangle(screenWidth/2,0,screenWidth/2,screenHeight ,Blue);
    DrawCircle( screenWidth/2 , screenHeight  /2 ,150 , LightB );
    DrawLine(screenWidth/2,0,screenWidth/2,screenHeight , WHITE);
    b.Draw();
   // DrawRectangle(10,sheight/2-50,25,100,GREEN);
    player3.Draw();
    player1.Draw();
    
      DrawText(TextFormat("player 2 :%i",player2_score), screenWidth / 4 - 95, 20, 50, WHITE);    // text x y font size color
      DrawText(TextFormat("player 1: %i", player1_score),835 , 20, 50, WHITE);                  // text x y font size color

      DrawText( "ROUND ",screenWidth/2-25 , screenHeight  /2-70, 20, roun);

      DrawText(TextFormat("%i",b.rounds()) ,screenWidth/2-25 , screenHeight  /2-50, 100, roun);     

    EndDrawing();
   
     }

    }
 

        }
        
        if (button2.IsPressed()) {


      
    int highscore ;
    int temhighscore = 0;
    Ball ball(screenWidth/2,screenHeight/2);

Paddle player(screenWidth-35,screenHeight/2-50,25,130);
cpuPaddle cpu(10,screenHeight/2-50,25,130);
AnimateBall aniball;

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


     
      while (!WindowShouldClose()) // this function will return true if the window is closed

        {

            if (ball.lifes() == 0)
            {
                break;
            }

            BeginDrawing(); // this function creates a blankcanvas so that we can starting drawinng

            ClearBackground(backgroundGradientBottom); // this function will clear the background of the canvas and set it to black
            // slide  and middle lines for the game interface
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, BLACK);  // x1 y1 x2 y2 color
            DrawLine(2, 2, screenWidth, 2, BLACK);                               // x1 y1 x2 y2 color
            DrawLine(0, screenHeight - 2, screenWidth, screenHeight - 2, BLACK); // x1 y1 x2 y2 color

            DrawRectangle(screenWidth / 2, 0, 2, screenHeight, BLACK);     // x y width height color
            DrawRectangle(0, 0, screenWidth / 2, screenHeight, backgroundGradientTop);      // x y width height color
            DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightB ); // x y radius color
            ball.move();
            // remember that the coordinate system in raylib starts from the top left corner of the screen updown :y side: x
            player.move();
            cpu.move(ball.ballpy());


            // check for the colloision between the ball and the player
           if(CheckCollisionCircleRec(Vector2{ball.ballpx(), ball.ballpy()}, ball.ballpr(), Rectangle{ player.paddlepx(), player.paddlepy(), player.paddlewidth(), player.paddleheight()}))
             {
                ball.colli();
                         PlaySound(strike);


                }
            if(CheckCollisionCircleRec(Vector2{ball.ballpx(), ball.ballpy()}, ball.ballpr(), Rectangle{ cpu.paddlepx(), cpu.paddlepy(), cpu.paddlewidth(), cpu.paddleheight()}))
                {
                ball.colli();
                         PlaySound(strike);


                }

            ball.Draw();
            player.Draw();
            cpu.Draw();
            DrawText("CPU", 300, 20, 50, WHITE);                            // text x y font size color
            DrawText(TextFormat("Player:%i", ball.player_scores()),3*screenWidth/4-200,20,50,WHITE); // text x y font size color
            DrawText(TextFormat("Enter ESC key to exit at any time"), 5, 5, 20, BLACK); // text x y font size color

            DrawText(TextFormat("HighScore:%i", highscore), screenWidth - 190, 20, 30, BLACK); // text x y font size color
            // if (newcpu_score != cpu_score)
            // {
            //     life = life - 1;
            //     cpu_score = newcpu_score;
            // }

            DrawText(TextFormat("Life:%i", ball.lifes()), screenWidth - 190, 50, 30, BLACK);

            EndDrawing(); // this function will end the drawing and display the canva

            if (ball.player_scores() > highscore)
            {
                highscore = ball.player_scores();
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
            ClearBackground(backgroundGradientTop);


            if (ball.player_scores() > temhighscore)
            {
                aniball.animation(temhighscore, highscore, player_score,ball.lifes());
                //break;

                EndDrawing();
            }

            else
            {
            ClearBackground(backgroundGradientTop);

                DrawText("Game Over ", screenWidth / 6, screenHeight / 2, 60, highScoreColor);
                DrawText(TextFormat("Your Score: %i", player_score), screenWidth / 6, 500, 60, textColor);
                DrawText("Press ENTER to play ESC to exit", screenWidth / 6, 600, 40, BLACK);

                EndDrawing();
                if (IsKeyPressed(KEY_ENTER))
                {
                   
                    break;
                }
            }
        }
        
      






           // cout << "Play Button 2 Pressed!" << endl;
        }

        if (button3.IsPressed()) {
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
        b2.Draw();
        play1.Draw();
        play2.Draw();
        button1.Draw();
        button2.Draw();
        button3.Draw();

        b2.move2();
        play1.move();
        play2.move();

        EndDrawing();
    }

    
     CloseAudioDevice();
    CloseWindow();
    return 0;
}
