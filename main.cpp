#include <iostream>
#include <raylib.h> /// Raylib is a library for making game

using namespace std;

Color Green = Color{38, 184, 155 , 255};
Color Blue = Color{45, 110, 230, 255};
Color DarkBlue  = Color{25, 50, 180, 255};
Color LightB = Color{72, 146, 220 ,255};
Color Yellow= Color{243 , 213 , 91, 255};
Color roun= Color{141 , 188 , 232 , 255};




class ball{
float x,y ;
float speed_x,speed_y;
int r=12;
int player1 ,player2,round;



public:
ball(){}
ball(float a,float b){
    x=a;
    y=b;
    speed_x=6;
    speed_y=6;
    player1 = 0;
    player2 = 0;
    round =1;
    
}
void Draw(){

DrawCircle(x,y,r,WHITE);

}

   
void update(){
  x+=speed_x;
  y+=speed_y;

    if(y+r>= GetScreenHeight() || y-r<=0){
    speed_y*=-1.05;

    }

    if(x+r>= GetScreenWidth()){
        Sound lose = LoadSound("resources/lose.wav");
        PlaySound (lose);
         player2++;
         round++;
         resetball();

    }


    if ( x-r<=0){
         Sound win = LoadSound("resources/win.wav");
         PlaySound (win);
         player1++;
         round++;
         resetball();

    }
}

     void colli(){
       
        speed_x*=-1;
       Sound strike = LoadSound("resources/strike.wav");
        PlaySound (strike);
       
        

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

        return round;
    }


    void resetball(){
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[2]={-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)] ;
        speed_y = 6* speed_choices[GetRandomValue(0,1)] ;
    }


};

class player2;

class paddle{
    protected:

float x,y;
float width,height;
int speed;

public:
paddle(){}
paddle( float a, float b,float w, float h){
    x=a;
    y=b;
    width=w;
    height=h;
    speed=6;

}
void Draw(){

        DrawRectangleRounded(Rectangle{x,y,width,height}, 0.8, 0,Green);

}
void limit(){
    if(y<=0){

        y=0;
    }

    if(y+height >= GetScreenHeight() ){

        y=GetScreenHeight() -height;
    }



}

void update(){
    if (IsKeyDown(KEY_UP)){

        y=y-speed;

    }

    if (IsKeyDown(KEY_DOWN)){

        y=y+speed;

    }

   limit();
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

class player2 :public paddle{

    public:
    player2(){}
    //using concept of constructor in single inheratance
    player2(float a, float b,float w,float h) :paddle (a,b,w,h){
        /* x=a;
         y=b;
         width=w;
         height=h;
         speed=6;
*/
    }

     void update(){
    if (IsKeyDown(KEY_W)){

        y=y-speed;

    }

    if (IsKeyDown(KEY_S)){

        y=y+speed;

    }

      limit();
   }

    /*void update(float by){
        if ( y+ height >= by){

            y = y - speed;
         }
         else if (y + height <= by){

            y = y + speed;
         }

        limit();
    }
  */


};

int main()
{   
    int  player1_score , player2_score;


    cout << "Starting the game" << endl;
    const int swidth = 1200;
    const int sheight = 700;
    InitWindow(swidth, sheight, "Ping Pong");
    InitAudioDevice();
    SetTargetFPS(60);

    //object define
    ball b(swidth/2,sheight/2);

    paddle p(swidth-35,sheight/2-50,25,130);

    player2 c(10,sheight/2-50,25,130);


    
    //game loop start 




    
while (WindowShouldClose() ==false){
    BeginDrawing();

    //updating
    b.update();
    c.update();
    //c.update(b.ballpy());
    p.update();
    player1_score =b.player1r();
    player2_score = b.player2r();

    //checking collisions
    if(CheckCollisionCircleRec(Vector2{b.ballpx(), b.ballpy()}, b.ballpr(), Rectangle{ p.paddlepx(), p.paddlepy(), p.paddlewidth(), p.paddleheight()}))
    {
    
         Sound strike = LoadSound("resources/strike.wav");
         PlaySound( strike);
         b.colli();

     }
    if(CheckCollisionCircleRec(Vector2{b.ballpx(), b.ballpy()}, b.ballpr(), Rectangle{ c.paddlepx(), c.paddlepy(), c.paddlewidth(), c.paddleheight()}))
    {

          Sound strike = LoadSound("resources/strike.wav");
         PlaySound( strike);
        b.colli();
      

    }

    //Drawing 
    ClearBackground(DarkBlue);

    DrawRectangle(swidth/2,0,swidth/2,sheight,Blue);
    DrawCircle( swidth/2 , sheight /2 ,150 , LightB );
    DrawLine(swidth/2,0,swidth/2,sheight, WHITE);
    b.Draw();
   // DrawRectangle(10,sheight/2-50,25,100,GREEN);
    c.Draw();
    p.Draw();
    DrawLine(0,0,swidth,0,WHITE);
    DrawLine(0,sheight,swidth,sheight,WHITE);

      DrawText(TextFormat("player 1 :%i", player2_score), swidth / 4 - 95, 20, 50, WHITE);    // text x y font size color
      DrawText(TextFormat("player 2: %i", player1_score),835 , 20, 50, WHITE);                  // text x y font size color

      DrawText( "ROUND ",swidth/2-25 , sheight /2-70, 20, roun);

       DrawText(TextFormat("%i",b.rounds()) ,swidth/2-25 , sheight /2-50, 100, roun);  

    EndDrawing();

    

    if (b.rounds()==5 ){

   break;
     }
  }

   //UnloadSound( strike);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}