#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<MMsystem.h>        //MMsystem.h and windows.h header files are used to play sounds and add colors to the maze and objects in the game
#define H 30                  //H and W are the hight and width of the maze
#define W 60
#define gho1 5

typedef struct coordinates
{
   int x,y;                         //x and y represents the actual co-ordinates in the maze
}co;

typedef struct PacMan
{
   co position;
   int vx,vy;
   int food_coll;
}pac;

typedef struct Ghost
{
   co position;
   int vx,vy;
}gh;


gh allGhosts[gho1];
gh allGhosts2[gho1];

pac myPacMan = {
                    {
                        .x = 1,
                        .y = 5,
                    },
                    .vx = 0,
                    .vy = 0,
                    .food_coll = 0,
                };

char playfield[H][W] =
{
   { "############################################################" },
   { "#                                                          #" },
   { "#   ##################     ######    ###################   #" },
   { "#                  ####      ##     ####                   #" },
   { "#    ####   ###    ####      ##     ####    ###    ####    #" },
   { "#    ####   ###    ####    ######   ####    ###    ####    #" },
   { "#    ####                                          ####    #" },
   { "#     ##################     ##     ##################     #" },
   { "#                            ##                            #" },
   { "#   ###############   ###    ##    ###   ###############   #" },
   { "#   ###               ###          ###               ###   #" },
   { "#   ###  ###   ##########  ##  ##  ##########  ###   ###   #" },
   { "#   ###               ###          ###               ###   #" },
   { "#   ###############   ###  ##  ##  ###   ###############   #" },
   { "#                                                          #" },
   { "#   ####    ###   #######   ####   #######   ###    ####   #" },
   { "#   ####    ###   #######   ####   #######   ###    ####   #" },
   { "#   ####    ###       ###   ####   ###       ###    ####   #" },
   { "#   ####                    ####                    ####   #" },
   { "#   ####     ############          ############     ####   #" },
   { "#   ####     ###                            ###     ####   #" },
   { "#   ####     ###                            ###     ####   #" },
   { "#   ####     ##################################     ####   #" },
   { "#   ####                                            ####   #" },
   { "#   ####   #############     ##     #############   ####   #" },
   { "#   ####   #############     ##     #############   ####   #" },
   { "#   ####        ####         ##          ####       ####   #" },
   { "#               ####     ##########      ####              #" },
   { "#       ####             ##########             ####       #" },
   { "############################################################" }
};
void display();
void SetColor(int);
void initialize()
{
   int i;

   for(i = 0; i < H; i++)                           //all the co-ordinates in the playfield are initialised
   {
       int j;
      for( j = 0; j < W; j++)
      {
         if (playfield[i][j]==' ')
            playfield[i][j] = '.';
      }
   }

   for ( i = 0; i <gho1; i++)
   {
      allGhosts[i].vx = 0;
      allGhosts[i].vy = 0;
      int x,y;
      do
     {
         x = 1 + rand() % (W-1);            //all ghost co-ordinates are initialised here
         y = 1 + rand() % (H-1);

     } while (playfield[y][x] != '.');
      allGhosts[i].position.x = x;
      allGhosts[i].position.y = y;        //ghosts are represented by % and pacman by @
      playfield[y][x] = '%';

   }
     for ( i = 0; i < gho1; i++)
   {
      allGhosts2[i].vx = 0;
      allGhosts2[i].vy = 0;
      int x,y;
      do
     {
         x = 1 + rand() % (W-1);
         y = 1 + rand() % (H-1);

     } while (playfield[y][x] != '.');
      allGhosts2[i].position.x = x;
      allGhosts2[i].position.y = y;
      playfield[y][x] = '%';

   }



}
void user_input()
{
   if (_kbhit())
   {
      char c1 = _getch();               //please go through the readme file to know the function of _khbit()

      if (c1 == -32)
      {
         char c2 = _getch();

         myPacMan.vx = 0;
         myPacMan.vy = 0;
         int i;
         for(i=0;i<gho1;i++)
        {
             allGhosts[i].vx=0;
             allGhosts[i].vy=0;
             allGhosts2[i].vx=0;
             allGhosts2[i].vy=0;

        }

         switch (c2)
         {
            case 72: myPacMan.vy = -1; break; // cursor up
            case 80: myPacMan.vy = +1; break; // cursor down
            case 75: myPacMan.vx = -1; break; // cursor left
            case 77: myPacMan.vx = +1; break; // cursor right
         }
         for(i=0;i<gho1;i++)
         {
             allGhosts[i].vx=+1;
             allGhosts[i].vy=+1;
             allGhosts2[i].vx=0;
             allGhosts2[i].vy=+1;
         }
      }
   }
}
void display()
{
    SetColor(1);
printf("                                      _______   ______    _____   ___      ___   ______   ___       \n");
printf("                                     ||     || ||    ||  ||      ||  |    |  || ||    || ||  |    ||\n");
printf("                                     ||     || ||    ||  ||      ||   |  |   || ||    || ||   |   ||\n");
printf("                                     ||_____|| ||____||  ||      ||    ||    || ||____|| ||    |  ||\n");
printf("                                     ||        ||    ||  ||      ||          || ||    || ||     | ||\n");
printf("                                     ||        ||    ||  ||____  ||          || ||    || ||      |||\n");
SetColor(15);
}


void move_figures()
{
   playfield[myPacMan.position.y][myPacMan.position.x] = ' ';    //first pacman is removed from old co-ordinates and updated to a newer one
   int i;
   for(i=0;i<gho1;i++)
   {
       playfield[allGhosts[i].position.y][allGhosts[i].position.x] = ' ';
        playfield[allGhosts2[i].position.y][allGhosts2[i].position.x] = ' ';
   }

   int nx = myPacMan.vx + myPacMan.position.x;
   int ny = myPacMan.vy + myPacMan.position.y;      //nx, ny, mx, my are the new co-ordinates
   int mx[5];
   int my[5];
   int mx1[5];
   int my1[5];
 for(i=0;i<gho1;i++)
   {
        mx[i] = allGhosts[i].vx + allGhosts[i].position.x;
        my[i] = allGhosts[i].vy + allGhosts[i].position.y;
        mx1[i] = allGhosts2[i].vx + allGhosts2[i].position.x;
        my1[i] = allGhosts2[i].vy + allGhosts2[i].position.y;
   }
   if (playfield[ny][nx] == '#')                //THIS part is to make sure that the object stops when it encounters a wall(#)
   {
      myPacMan.vx = 0;
      myPacMan.vy = 0;
   }
   for(i=0;i<gho1;i++)
   {

   if(playfield[my[i]][mx[i]]=='#')
      {
          if(allGhosts[i].vx>0 || allGhosts[i].vy>0)
          {

                allGhosts[i].vx=-1;
                allGhosts[i].vy=-1;
            }
            else
            {
                allGhosts[i].vx=+1;
                allGhosts[i].vy=+1;
            }
      }
    if(playfield[my1[i]][mx1[i]]=='#')
    {
        if(allGhosts2[i].vy<0)
          {

                allGhosts2[i].vx=0;
                allGhosts2[i].vy=+1;
            }
            else
            {
                allGhosts2[i].vx=0;
                allGhosts2[i].vy=-1;
            }
    }



}

   myPacMan.position.x += myPacMan.vx;                      //pacman and ghost co-ordinates are updated here
   myPacMan.position.y += myPacMan.vy;
    for(i=0;i<gho1;i++)
      {
          allGhosts[i].position.x+=allGhosts[i].vx;
          allGhosts[i].position.y+=allGhosts[i].vy;
          allGhosts2[i].position.x+=allGhosts2[i].vx;
          allGhosts2[i].position.y+=allGhosts2[i].vy;

      }

   if (playfield[ny][nx] == '.')                        //we simultaneously update the score i.e the food eaten by pacman
   {
      myPacMan.food_coll++;
   }
   for(i=0;i<gho1;i++)
   {

    if(playfield[my[i]][mx[i]] == '.')
    {

            playfield[my[i]-allGhosts[i].vy][mx[i]-allGhosts[i].vx]='.';  //this part of the code makes sure that ghost dont eat the food
    }
    if(playfield[my1[i]][mx1[i]] == '.')
    {

            playfield[my1[i]-allGhosts2[i].vy][mx1[i]-allGhosts2[i].vx]='.';
    }
    }

   playfield[myPacMan.position.y][myPacMan.position.x] = '@';          //here we put back the pacman and ghost back to the playfield with updated co-ordinates
    for(i=0;i<gho1;i++)
    {
        playfield[allGhosts[i].position.y][allGhosts[i].position.x]='%';
        playfield[allGhosts2[i].position.y][allGhosts2[i].position.x]='%';
    }

}

void show_playfield()
{
    int i;
   for ( i = 0; i < H; i++)
   {
       printf("                                       ");
       int j;
      for ( j = 0; j < W; j++)
      {
          if(playfield[i][j]=='.')
          {
              SetColor(4);
            printf("%c", playfield[i][j]);
                SetColor(15);
          }
            else if(playfield[i][j]=='%')
            {
                SetColor(9);
                printf("%c", playfield[i][j]);
                SetColor(15);
            }
            else if(playfield[i][j]=='@')
            {
                SetColor(14);
                printf("%c", playfield[i][j]);
                SetColor(15);
            }
            else
            {
                printf("%c", playfield[i][j]);
            }
      }
      printf("\n");
   }

   printf("                                       Score: %d\n", myPacMan.food_coll);
}
void check_coll()                       //This function is to check for any collisions
{
    int i=0;
     for(i=0;i<gho1;i++)
   {
       if((allGhosts[i].position.x==myPacMan.position.x && allGhosts[i].position.y==myPacMan.position.y) || (allGhosts2[i].position.x==myPacMan.position.x && allGhosts2[i].position.y==myPacMan.position.y))
        {
            system("cls");
            display();
            printf("\n\n\n");
            printf("     \t\t\t\t\t\t\t\t\tYOUR SCORE IS:%d",myPacMan.food_coll);
            PlaySound(TEXT("death.wav"),NULL,SND_SYNC);
            getchar();
            exit(0);
        }
        if(myPacMan.food_coll>=250)
        {
            system("cls");
            display();
            printf("\n\n\n");
            printf("     \t\t\t\t\t\t\t\tU WON THE GAME!!!!!\n");
            printf("     \t\t\t\t\t\t\t\tYOUR SCORE IS:%d",myPacMan.food_coll);
            PlaySound(TEXT("fireworks.wav"),NULL,SND_SYNC);
            getchar();
            exit(0);
            }
   }
}


void set_cursor_position(int x, int y)    //Since we do not want the entire playfield to print multiple times we simply use this hack by setting the cursor position to 0 in every iteration
{

   COORD coord = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}


void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


int main()
{
   system("cls");
   hidecursor();
   initialize();
   PlaySound(TEXT("pacman.wav"),NULL,SND_ASYNC);
   while (1)
   {
      user_input();
      move_figures();
      display();
      show_playfield();
      check_coll();
      Sleep( 100/ 30 );
      set_cursor_position(0,0);
   }

}
