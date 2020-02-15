#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#define height 21
#define width 51
	bool gameover;
	int x,y,score,g1x,g1y,g2x,g2y;  //x,y are pacman's co-ortinates
	enum eDirection{STOP=0, LEFT,RIGHT,UP,DOWN};
	enum ghostDirection1{STOP1=0, LEFT1,RIGHT1,UP1,DOWN1};
	enum ghostDirection2{STOP2=0, LEFT2,RIGHT2,UP2,DOWN2};
	enum eDirection dir;
    enum ghostDirection1 dir1;
    enum ghostDirection2 dir2;
    char grid[height][width]={
        "**************************************************",
        "*.......................**.......................*",
        "*.****.....****.........**.........****.....****.*",
        "*.****.....****.........**.........****.....****.*",
        "*................................................*",
        "*.***.....*.......**.********.**.......*.....***.*",
        "*.***.....*.......**....**....**.......*.....***.*",
        "*.***.....****....**************....****.....***.*",
        "*.........*.......**..........**.......*.........*",
        "*.................**..........**.................*",
        "*.....****..............................****.....*",
        "*.....****..............................****.....*",
        "*.....**..........**..........**..........**.....*",
        "*.................**..******..**.................*",
        "*.......**..............**..............**.......*",
        "*.......**........****..**..****........**.......*",
        "*.......**..............................**.......*",
        "*..*********........***********.......*********..*",
        "*................................................*",
        "**************************************************"
    };
   void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void main_menu(){
        char ch;
        int i;
        char title[7][62]=
        {
            "*********  *********  ******* **       ** ********* **      *",
            "*       *  *       * *        * *     * * *       * * *     *",
            "*       *  *       * *        *  *   *  * *       * *  *    *",
            "*********  ********* *        *   * *   * ********* *   *   *",
            "*          *       * *        *    *    * *       * *    *  *",
            "*          *       * *        *         * *       * *     * *",
            "*          *       *  ******* *         * *       * *      **",
        };
        for (i=0;i<7;i++){
            gotoxy(25,5+i);
            printf("%s\n",title[i]);
        }
        gotoxy(50,20);
        printf("1.Play Game");
        gotoxy(50,21);
        printf("2.Quit ");
        loop:
            ch=getch();
        switch(ch){
            case '1':break;
            case '2':
                    gotoxy(50,22);
                    printf("Quitting...\n");
                    exit(0);
                    break;
            default:
                    goto loop;
                break;
        }
    }
    void loading_screen(){
        system("cls");
    int row,col,r,c,q;
    gotoxy(50,14);
    printf("loading...");
    gotoxy(44,15);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);
    printf("%c",176);}
}

	void Setup(){
		gameover=false;
		dir=STOP;
		x = width / 2;
		y = height / 2;
		g1x=21;
		g1y=6;
		g2x=28;
		g2y=6;
		score=0;
        main_menu();
        loading_screen();
	}

	void Draw()
	{
		int i,j;
		char sv1=' ',sv2=' ';
		system("cls");

		if(grid[y][x]=='.') score++;
        if(grid[g1y][g1x]=='.') sv1='.';
        if(grid[g2y][g2x]=='.') sv2='.';
		if((grid[g1y][g1x]=='.') || (grid[g1y][g1x]==' '))
            grid[g1y][g1x]='E';
        if((grid[g2y][g2x]=='.') || (grid[g2y][g2x]==' '))
            grid[g2y][g2x]='Q';
		if((grid[y][x]=='.') || (grid[y][x]==' '))
            grid[y][x]='C';

		for(i=0;i<height;i++)
		{
            for(j=0;j<width;j++)
            {
                printf("%c",grid[i][j]);

                if(grid[i][j]=='C' || grid[i][j]=='E' || grid[i][j]=='Q')
                {
                    if(grid[i][j]=='C')
                        grid[i][j]=' ';
                    if(sv1=='.')
                    {
                        grid[i][j]='.';
                    }
                    else
                    {
                        grid[i][j]=' ';
                    }

                    if(sv2=='.')
                    {
                        grid[i][j]='.';
                    }
                    else
                    {
                        grid[i][j]=' ';
                    }
                }
            }
        printf("\n");
		}
		gotoxy(55,5);
        printf("Score=%d",score);
	}

	void Input(){
		if(_kbhit()){
			switch(_getch()){                           //if user presses stuff then only getch() activates and hence takes input
				case 'a':
					dir=LEFT;
					break;

				case 'd':
					dir=RIGHT;
					break;

				case 'w':
					dir=UP;
					break;


				case 's':
					dir=DOWN;
					break;

				case 'x':
					gameover=true;
					break;
			}
		}
	}

	void ghost1move(){
        int r;
        r=(rand()%4)+1;
        switch(r){
        case 1:
                dir1 = LEFT1;
                break;
        case 2:
                dir1 = RIGHT1;
                break;
        case 3:
                dir1 =  UP1;
                break;
        case 4:
                dir1 = DOWN1;
                break;
        }
	}

    void ghost2move(){
         int r;
        r=(rand()%4)+1;
        switch(r){
        case 1:
                dir2 = LEFT2;
                break;
        case 2:
                dir2 = RIGHT2;
                break;
        case 3:
                dir2 =  UP2;
                break;
        case 4:
                dir2 = DOWN2;
                break;
        }
    }

	void Logic(){

        ghost1move();
        ghost2move();

        switch(dir1){                            //pacman's co-ordinate changes when corresponding key is pressed
				case LEFT1:
					g1x--;
					if(grid[g1y][g1x]=='*')
                        g1x+=1;
					break;
				case RIGHT1:
					g1x++;
					if(grid[g1y][g1x]=='*')
                        g1x-=1;
					break;
				case UP1:
					g1y--;
					if(grid[g1y][g1x]=='*')
                        g1y+=1;
					break;
				case DOWN1:
					g1y++;
					if(grid[g1y][g1x]=='*')
                        g1y-=1;
					break;
			}
			switch(dir2){                            //pacman's co-ordinate changes when corresponding key is pressed
				case LEFT2:
					g2x--;
					if(grid[g2y][g2x]=='*')
                        g2x+=1;
					break;
				case RIGHT1:
					g2x++;
					if(grid[g2y][g2x]=='*')
                        g2x-=1;
					break;
				case UP2:
					g2y--;
					if(grid[g2y][g2x]=='*')
                        g2y+=1;
					break;
				case DOWN2:
					g2y++;
					if(grid[g2y][g2x]=='*')
                        g2y-=1;
					break;
			}
        switch(dir){                            //pacman's co-ordinate changes when corresponding key is pressed
				case LEFT:
					x--;
					if(grid[y][x]=='*')
                        x+=1;
					break;
				case RIGHT:
					x++;
					if(grid[y][x]=='*')
                        x-=1;
					break;
				case UP:
					y--;
					if(grid[y][x]=='*')
                        y+=1;
					break;
				case DOWN:
					y++;
					if(grid[y][x]=='*')
                        y-=1;
					break;
			}
		if(x>width) x=width-2;
		if(y>height) y=height-1;
		if(x<0) x=1;
		if(y<0)y=0;
		if (score==667) gameover=true;

	}
	void Game_Over(){
	    int i;
	    system("cls");
	    char end[7][90]=
        {
            " *******   *******   **       ** ********      *******  *           * ********  ******* ",
            "*         *       *  * *     * * *            *       *  *         *  *        *       *",
            "*         *       *  *  *   *  * *            *       *   *       *   *        *       *",
            "*   ****  *********  *   * *   * ********     *       *    *     *    ******** * ****** ",
            "*      *  *       *  *    *    * *            *       *     *   *     *        *   *    ",
            "*      *  *       *  *         * *            *       *      * *      *        *     *  ",
            " *******  *       *  *         * ********      *******        *       ******** *       *",
        };
        for(i=0;i<7;i++)
            {
                gotoxy(20,3+i);
                printf("%s\n",end[i]);
            }
        if(score==667)
        {
            gotoxy(45,14);
            printf("Congratulations you won:");
        }
		else
        {
            gotoxy(45,14);
            printf("Too bad....you lost..");
        }
        gotoxy(45,15);
        printf("Press any key to continue");
	}
	int main(){
		Setup();
		while(!gameover){
			Draw();
			Input();
			Logic();
			Sleep(50);
		}
        Game_Over();
        getch();
		return 0;
	}
