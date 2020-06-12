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

struct PacMan
{
   co position;
   int vx,vy;
   int food_coll;
};


struct Ghost
{
   co position;
   int vx,vy;
};


struct Ghost allGhosts[gho1];
struct Ghost allGhosts2[gho1];

struct PacMan myPacMan = {
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
void SetColor(int ForgC);
void initialize()
{
   // 1. replace each empty field in the playfield with a food field
   int i;

   for(i = 0; i < H; i++)
   {
       int j;
      for( j = 0; j < W; j++)
      {
         if (playfield[i][j]==' ')
            playfield[i][j] = '.';
      }
   }

   // 2. initialize all ghosts

   for ( i = 0; i <gho1; i++)
   {
      allGhosts[i].vx = 0;
      allGhosts[i].vy = 0;
      // try to find a (x,y) coordinate randomly where a food piece is
      int x,y;
      do
     {
         x = 1 + rand() % (W-1);
         y = 1 + rand() % (H-1);

     } while (playfield[y][x] != '.');
      allGhosts[i].position.x = x;
      allGhosts[i].position.y = y;
      playfield[y][x] = '%';

   }
     for ( i = 0; i < gho1; i++)
   {
      allGhosts2[i].vx = 0;
      allGhosts2[i].vy = 0;
      // try to find a (x,y) coordinate randomly where a food piece is
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
      char c1 = _getch();

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
printf("                                        _______   ______    _____   ___      ___   ______   ___       \n");
printf("                                       ||     || ||    ||  ||      ||  |    |  || ||    || ||  |    ||\n");
printf("                                       ||     || ||    ||  ||      ||   |  |   || ||    || ||   |   ||\n");
printf("                                       ||_____|| ||____||  ||      ||    ||    || ||____|| ||    |  ||\n");
printf("                                       ||        ||    ||  ||      ||          || ||    || ||     | ||\n");
printf("                                       ||        ||    ||  ||____  ||          || ||    || ||      |||\n");
SetColor(15);
}


void move_figures()
{
   // 1. delete PacMan from old position
   playfield[myPacMan.position.y][myPacMan.position.x] = ' ';
   int i;
   for(i=0;i<gho1;i++)
   {
       playfield[allGhosts[i].position.y][allGhosts[i].position.x] = ' ';
        playfield[allGhosts2[i].position.y][allGhosts2[i].position.x] = ' ';
   }

   // 2. compute new desired coordinate (nx,ny)
   int nx = myPacMan.vx + myPacMan.position.x;
   int ny = myPacMan.vy + myPacMan.position.y;
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
   // 3. test whether there is a wall at (nx,ny)
   if (playfield[ny][nx] == '#')
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



   // 4. update PacMan's coordinate

   myPacMan.position.x += myPacMan.vx;
   myPacMan.position.y += myPacMan.vy;
    for(i=0;i<gho1;i++)
      {
          allGhosts[i].position.x+=allGhosts[i].vx;
          allGhosts[i].position.y+=allGhosts[i].vy;
          allGhosts2[i].position.x+=allGhosts2[i].vx;
          allGhosts2[i].position.y+=allGhosts2[i].vy;

      }

   // 5. check for a food piece at the new location
   if (playfield[ny][nx] == '.')
   {
      myPacMan.food_coll++;
   }
   for(i=0;i<gho1;i++)
   {

    if(playfield[my[i]][mx[i]] == '.')
    {

            playfield[my[i]-allGhosts[i].vy][mx[i]-allGhosts[i].vx]='.';
    }
    if(playfield[my1[i]][mx1[i]] == '.')
    {

            playfield[my1[i]-allGhosts2[i].vy][mx1[i]-allGhosts2[i].vx]='.';
    }
    }


   // 6. put PacMan back again to playfield

   playfield[myPacMan.position.y][myPacMan.position.x] = '@';
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
void check_coll()
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


void set_cursor_position(int x, int y)
{
   //Initialize the coordinates
   COORD coord = { x, y };
   //Set the position
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

} // set_cursor_position


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
