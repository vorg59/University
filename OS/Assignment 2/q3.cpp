#include <iostream>
#include <unistd.h>
#include <termios.h>
using namespace std;
#define GameWidth 80
#define GameHeight 17
#define PaddleHeight 4
#define Ball 'O'
#define PaddleSpeed 2

char Board[GameHeight][GameWidth];
int Paddle1_Y = GameHeight / 2 - PaddleHeight / 2;
int Paddle2_Y = GameHeight / 2 - PaddleHeight / 2;
int Ball_X = GameWidth / 2;
int Ball_Y = GameHeight / 2;
int BallVelocity_X = 1;
int BallVelocity_Y = 1;
int Score_Player1 = 0;
int Score_Player2 = 0;
int OLDScore_Player1 = 0;
int OLDScore_Player2 = 0;
bool GameOver = false;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to set terminal to non-blocking mode
void set_nonblock(int fd) 
{
    struct termios ttystate;
    tcgetattr(fd, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSANOW, &ttystate);
}


void DrawBoard() 
{
    system("clear");
    cout<<"P1 "<<Score_Player1<<endl;
    cout<<"P2 "<<Score_Player2<<endl;
    for (int i = 0; i < GameWidth; i++)
        cout<<"=";
    cout<<endl;
    for (int i = 0; i < GameHeight; i++) 
    {
        for (int j = 0; j < GameWidth; j++)
            cout<<Board[i][j];
        cout<<endl;
    }
    for (int i = 0; i < GameWidth; i++)
        cout<<"=";
    cout<<endl;
}


void Update() 
{
    // Move ball
    if(OLDScore_Player1!=Score_Player1)
        Ball_X -= BallVelocity_X;
    else
        Ball_X += BallVelocity_X;
    Ball_Y += BallVelocity_Y;

    // Check for collisions with walls and paddles
    if (Ball_Y <= 0 || Ball_Y >= GameHeight - 1)
        BallVelocity_Y = -BallVelocity_Y;

    if (Ball_X <= 0) 
    {
        OLDScore_Player2=Score_Player2;
        Score_Player2++;
        if (Score_Player2 == 10) 
        {
            GameOver = true;
            return;
        }
        Ball_X = GameWidth / 2;
        Ball_Y = GameHeight / 2;
    }

    if (Ball_X >= GameWidth - 1) 
    {
        OLDScore_Player1=Score_Player1;
        Score_Player1++;
        if (Score_Player1 == 10) 
        {
            GameOver = 1;
            return;
        }
        Ball_X = GameWidth / 2;
        Ball_Y = GameHeight / 2;
    }

    if (Ball_X == 1 && Ball_Y >= Paddle1_Y && Ball_Y < Paddle1_Y + PaddleHeight)
        BallVelocity_X = -BallVelocity_X;
    if (Ball_X == GameWidth - 2 && Ball_Y >= Paddle2_Y && Ball_Y < Paddle2_Y + PaddleHeight)
        BallVelocity_X = -BallVelocity_X;

    // Clear Board and redraw paddles and ball
    for (int i = 0; i < GameHeight; i++) 
        for (int j = 0; j < GameWidth; j++)
            Board[i][j] = ' ';

    for (int i = 0; i < PaddleHeight; i++) 
    {
        Board[Paddle1_Y + i][1] = '|';
        Board[Paddle2_Y + i][GameWidth - 2] = '|';
    }

    Board[Ball_Y][Ball_X] = Ball;
}


void *Input_Player1(void *arg) 
{
    set_nonblock(STDIN_FILENO);
    char c;
    while (!GameOver) 
    {
        if (read(STDIN_FILENO, &c, 1) > 0) 
        {
            if (c == 'w' && Paddle1_Y > 1) 
            {
                pthread_mutex_lock(&mutex);
                Paddle1_Y-=PaddleSpeed;
                pthread_mutex_unlock(&mutex);
            } 
            else if (c == 's' && Paddle1_Y < GameHeight - PaddleHeight - 1) 
            {
                pthread_mutex_lock(&mutex);
                Paddle1_Y+=PaddleSpeed;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    return NULL;
}


void *Input_Player2(void *arg) 
{
    set_nonblock(STDIN_FILENO);
    char c;
    while (!GameOver) 
    {
        if (read(STDIN_FILENO, &c, 1) > 0) 
        {
            if (c == 'i' && Paddle2_Y > 1) 
            {
                pthread_mutex_lock(&mutex);
                Paddle2_Y-=PaddleSpeed;
                pthread_mutex_unlock(&mutex);
            } 
            else if (c == 'k' && Paddle2_Y < GameHeight - PaddleHeight - 1) 
            {
                pthread_mutex_lock(&mutex);
                Paddle2_Y+=PaddleSpeed;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    return NULL;
}

int main() 
{
    pthread_t tp1, tp2;
    pthread_create(&tp1, NULL, Input_Player1, NULL);
    pthread_create(&tp2, NULL, Input_Player2, NULL);

    while (!GameOver) 
    {
        pthread_mutex_lock(&mutex);
        Update();
        DrawBoard();
        pthread_mutex_unlock(&mutex);
        usleep(70000);
    }

    pthread_join(tp1, NULL);
    pthread_join(tp2, NULL);
}
