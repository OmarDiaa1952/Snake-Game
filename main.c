/* Library includes. */
#include "bsp.h"

#include "system.h"

#define WIN_SCORE 30     /* Required score to win game */
#define POWER_CHAR 36    /* ASCII CODE for $ */
#define ENEMY_CHAR 88    /* ASCII CODE for X */
#define SNAKE_CHAR 111   /* ASCII CODE for o */
#define BORDER_CHAR 35  /* ASCII CODE for # */


#define DX   16
#define DY   32
int game_running=0;
typedef unsigned long uint32;
typedef unsigned char uint8;
char screen[DX*DY] = {0};
int snakelen = 3;
int highestScore = 0;
int latestScore = 0;
int score = 0;


#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8))
void idleHook( void ) ;
void uart0_putchar(char c)
{
  while ((UART0_FR_R & (1<<5)) != 0);				 
  UART0_DR_R = c;						
}

char uart0_getchar(void)
{
  //panic();  
  while (!(UART0_FR_R & 0x40));				 
  return (UART0_DR_R & 0xFF);						
}

/* Variables for XOR-Shift Pseudo Ramdom Numbers Generator */
uint32 x = 123456789;
uint32 y = 362436069;
uint32 z = 521288629;
uint32 w = 88675121;


typedef struct PointStruct
{
    short x, y;
}Point;

Point snake[DX*DY] =
{
    {DX/2,DY/2},//tail
    {DX/2+1, DY/2},
    {DX/2+2, DY/2}//head
};

typedef enum SnakeDirEnum
{
    DIR_RIGHT,
    DIR_LEFT,
    DIR_UP,
    DIR_DOWN
}SnakeDir;

SnakeDir dir = DIR_RIGHT;

uint32 rand2()
{
    uint32 t;
    t = (x ^ (x << 11));
    x = y; y = z; z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

void placeItem(char type)
{
    uint8 done =0;
    uint32 x,y;
    while(!done)
    {
        x = 1 + rand2()%(DX-2);
        y = 1 + rand2()%(DY-2);
        if (screen[DX*y+x] == ' ')
        {
            screen[DX*y+x] = type;
            done = 1;
        }
    }
}

void drawBorder(void)
{
    long i = 0;
    for(i=0; i<DX; ++i) //top row
    {
        screen[i] = BORDER_CHAR;
    }
    for(i=0; i<DX; ++i) //bottom row
    {
        screen[DX*(DY-1)+i] = BORDER_CHAR;
    }
    for(i=0; i<DY; ++i) //left column
    {
        screen[DX*i] = BORDER_CHAR; 
    }  
    for(i=0; i<DY; ++i) //right column
    {
        screen[DX*i + DX-1] = BORDER_CHAR;
    }
}

void drawSnake(void)
{
    long i =0;
    for(i=0; i<snakelen; i++) 
    {
        Point *p = snake+i;
        screen[(DX*(p->y))+(p->x)] = SNAKE_CHAR;
    }
}
void resetScreen(void)
{
    memset(screen,' ',DX*DY);
    drawBorder();
    placeItem(POWER_CHAR);
    placeItem(ENEMY_CHAR);
    drawSnake();
}

void resetSnake(void)
{
    latestScore = score;
    if(latestScore>highestScore)
    {
        highestScore = latestScore;
    }
    snakelen = 3;
    score = 0;
    snake->x = DX/2;
    snake->y = DY/2;
    snake[1].x = DX/2+1;
    snake[1].y = DY/2;               
    snake[2].x = DX/2+2;
    snake[2].y = DY/2;   
    dir = DIR_RIGHT;
}

void crudeDelay(void)
{
        for(volatile long k = 0;k<1000000;++k);
}

int taskDraw(void *pvParameters)
{
    long i = 0;
	int removeTail = 1;
      volatile unsigned time=OS_getTickCount();   
    for(;;)
    {
    if(!game_running){
         if(highestScore != 0)
    {
        long i = 0;
        unsigned char highestBuf[15] = {0};
        unsigned char latestBuf[15] = {0};
        print("Highest Score achieved : ");
				print(highestBuf);
        i = 0;
        print("Latest Score achieved : ");
				print(latestBuf);
    }
    print("Welcome to the Snake Game!\n");
    print("Use the 'w', 'a', 's', 'd' keys to move the snake.\n");
    print("Collect the Power-ups to increase score and grow the snake.\n");
    print("Press s to start the game...\n");
    while(!game_running){
        time=OS_getTickCount();
        //print_idec(time+5);
        //print("\n");
        OS_sleepUntil(time+5);
    }
    continue;
    }
        /* Print current score */
        print("Score:   ");
				print_idec(score);
                print("\n");
                //print_idec(game_running);
                //print("\n");
        for(i=0;i<DY;++i)
        {
            printn(screen+(DX*i), DX); //print row by row
            print("\n");
        }
        print("\n\n");
        //delayuntil(20)
        OS_sleepUntil(time+20);
        time=OS_getTickCount();
        
        //update
        switch(dir)
        {
            case DIR_RIGHT:
                snake[snakelen].x = snake[snakelen-1].x+1;
                snake[snakelen].y = snake[snakelen-1].y;
                break;
            case DIR_LEFT:
                snake[snakelen].x = snake[snakelen-1].x-1;
                snake[snakelen].y = snake[snakelen-1].y;
                break;
            case DIR_UP:
                snake[snakelen].x = snake[snakelen-1].x;
                snake[snakelen].y = snake[snakelen-1].y-1;
                break;
            case DIR_DOWN:
                snake[snakelen].x = snake[snakelen-1].x;
                snake[snakelen].y = snake[snakelen-1].y+1;             
                break;
			default:
				break;
        }
        removeTail = 1;
        switch(screen[(DX*(snake[snakelen].y))+snake[snakelen].x])
        {

            case SNAKE_CHAR:
            case BORDER_CHAR:
            case ENEMY_CHAR:
                print("Game Over \n");
                resetSnake();
                game_running=0;
                resetScreen();
                OS_sleepUntil(time+20);
                time=OS_getTickCount();
                continue;
            case POWER_CHAR:
                //++snakelen;
                //++score;
                removeTail = 0;
                placeItem(POWER_CHAR);
                break;
        }
        screen[DX*snake[snakelen].y+snake[snakelen].x] = SNAKE_CHAR; //set head
        if(removeTail)
        {
            screen[(DX*(snake->y))+(snake->x)] = ' '; //remove tail
            for(i=0;i<snakelen;++i)
            {
                snake[i] = snake[i+1];
            }
        }
        else
        {
            snakelen++;
            score = snakelen-3;
        }
        if(score == WIN_SCORE)
        {
            print("Game WON! \n");
            resetSnake();
            game_running=0;
            resetScreen();
            OS_sleepUntil(time+20);
            time=OS_getTickCount();
        }   
    }
}

int taskInput( void *pvParameters)
{
    for(;;)
    {
        //print_idec(game_running);
    if(!game_running){
        //print_idec(game_running);
        //char c = uart0_getchar();
        //printn(&c,1);
        //print_idec(game_running);
        while(uart0_getchar()!='s');
        game_running=1;
        continue;
        }        
        switch(uart0_getchar())
        {
            case 'w':
            case 'W':
                if(dir!= DIR_DOWN)
                {
                    dir = DIR_UP;
                }
                break;
            case 'a':
            case 'A':
                if(dir!= DIR_RIGHT)
                {
                    dir = DIR_LEFT;
                }
                break;
            case 's':
            case 'S':
                if(dir!= DIR_UP)
                {
                    dir = DIR_DOWN;
                }
                break;
            case 'd':
            case 'D':
                if(dir!= DIR_LEFT)
                {
                    dir = DIR_RIGHT;
                }
                break;   
        }
    }
}

int main( void )
{
    /*char str[]={'H','e','l','l','o' ,0};
    for(;;){
        str[0]=uart0_getchar();
        print(str);
    }*/
  resetScreen();
	OS_newTask( taskDraw, 0, 256, 3, "DrawTask" );
	OS_newTask( taskInput, 0, 256, 1, "InputTask" );
	OS_startScheduler(0x07FFFF,idleHook);

	for( ;; );
}

/*-----------------------------------------------------------*/

void idleHook( void ) 
{
	for( ;; )
	{

	}
	
}





