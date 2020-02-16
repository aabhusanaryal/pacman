#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<math.h>
#define height 30
#define width 120
	bool gameover;
	int x,y,score,g2x,g2y;  //x,y are pacman's co-ortinates
	enum eDirection{STOP=0, LEFT,RIGHT,UP,DOWN};
	enum ghostDirection2{STOP2=0, LEFT2,RIGHT2,UP2,DOWN2};
	enum eDirection dir;
    enum ghostDirection2 dir2;
    char lives[3]={157,157,157};
    int life;
   char grid[height][width]={
            "=======================================================================================================================",
            "=======================================================================================================================",
            "||.........................||.............................................................||.........................||",
            "||.........................||.............................................................||.........................||",
            "||.........................||.............................................................||.........................||",
            "||.........................||..........=========================================..........||.........................||",
            "||.................||......||.............................................................||......||.................||",
            "||.................||......||.............................................................||......||.................||",
            "||....||=====||....||.............................................................................||....||=====||....||",
            "||....||.....||....||.............................................................................||....||.....||....||",
            "||....||.....||....||....................||============...    ...============||...................||....||.....||....||",
            "||....||.....||....||....................||..................................||...................||....||.....||....||",
            "||....||.....||....||....................||..................................||...................||....||.....||....||",
            "||....||.....||....||....................||..................................||...................||....||.....||....||",
            "||.................||....................||..................................||...................||.................||",
            "||.................||....................||..................................||...................||.................||",
            "||.................||....................||..................................||...................||.................||",
            "||.................||....................||==================================||...................||.................||",
            "||.......||........||.............................................................................||........||.......||",
            "||.......||........||.............................................................................||........||.......||",
            "||.......||........||.............................................................................||........||.......||",
            "||.......||........||..............==================================================.............||........||.......||",
            "||.......||........||.............................................................................||........||.......||",
            "||.......||.................................................................................................||.......||",
            "||.......||.................................................................................................||.......||",
            "||.......||========================================..................=======================================||.......||",
            "||...................................................................................................................||",
            "||...................................................................................................................||",
            "=======================================================================================================================",
            "======================================================================================================================="
    };

    void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 15;
    SetConsoleCursorPosition(hOut, Position);

}
   void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

    void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void write_record(){
    system("cls");
    FILE *fp;
    char text[500],name[50];
    printf("Enter your name\n");
    gets(name);
    fp=fopen("score.txt","a");
    fprintf(fp,"%s\t",name);
    fprintf(fp,"%d\n",score);
    fclose(fp);
	}

	void main_menu();

	void show_record(){
    system("cls");
	char ch;
	FILE *file;
	char str[500];
	printf("High Scores:\n");
    file=fopen("score.txt","r");
	if (file) {
    while (fscanf(file, "%s", str)!=EOF)
        printf("%s\n",str);
	}
	fclose(file);

	printf("go back?(y/n)");
	lop: ch=getch();
        switch(ch){
        case 'y':
                main_menu();
                break;
        case 'n':
                exit(0);
                break;
        default:
                goto lop;
                break;
        }
    }

    void main_menu(){
        char ch;
        int i;
        char title[12][62]=
        {


                     " ######:::::::::::'##::::'##::::'###::::'##::: ##:",
                     "##... ##:::::::::: ###::'###:::'## ##::: ###:: ##:",
                     "##:::..::::::::::: ####'####::'##:. ##:: ####: ##:",
                     "##:::::::'#######: ## ### ##:'##:::. ##: ## ## ##:",
                     "##:::::::........: ##. #: ##: #########: ##. ####:",
                     "##::: ##:::::::::: ##:.:: ##: ##.... ##: ##:. ###:",
                     " ######::::::::::: ##:::: ##: ##:::: ##: ##::. ##:",
                     "                                                   ",
                     "         .-.   .-.     .--.                       ",
                     "        | OO| | OO|   / _.-' .-.   .-.  .-.       ",
                     "        |   | |   |   \  '-. '-'   '-'  '-'       ",
                     "        '^^^' '^^^'    '--'                       "
        };
        system("cls");
        for (i=0;i<12;i++){
            gotoxy(78,15+i);
            printf("%s\n",title[i]);
        }
        gotoxy(99,34);
        printf("1.Play Game");
        gotoxy(99,35);
        printf("2.Scores");
        gotoxy(99,36);
        printf("3.Quit ");
        loop:
            ch=getch();
        switch(ch){
            case '1':
                    break;
            case '2':
                    show_record();
                    break;
            case '3':
                    gotoxy(85,37);
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
    gotoxy(95,25);
    printf("loading...");
    gotoxy(89,26);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);
    printf("%c",176);}
}

	void Setup(){
		gameover=false;
		dir=STOP;
		x = width / 2;
		y = height / 2;
		g2x=60;
		g2y=5;
		score=0;
		life=2;
        main_menu();
        loading_screen();
	}

	void Draw()
	{
		int i,j;
		char sv2=' ';
		clearScreen();


        if(grid[g2y][g2x]=='.') sv2='.';
        if(grid[g2y][g2x]=='|') sv2='|';
        if(grid[g2y][g2x]=='=') sv2='=';
        if((grid[g2y][g2x]=='.') || (grid[g2y][g2x]==' ') || (grid[g2y][g2x]=='|') || (grid[g2y][g2x]=='='))
            grid[g2y][g2x]='Q';
        if(grid[y][x]=='.') score++;
		if((grid[y][x]=='.') || (grid[y][x]==' '))
            grid[y][x]='C';
        if(x==g2x && y==g2y && life<0) gameover=true;


		for(i=0;i<height;i++)
		{
		    gotoxy(46,15+i);
            for(j=0;j<width;j++)
            {
                printf("%c",grid[i][j]);
                if(grid[i][j]=='C')
                {
                    grid[i][j]=' ';
                }
                if(grid[i][j]=='Q')
                {
                    if(sv2=='.')
                    {
                        grid[i][j]='.';
                    }
                    else if (sv2==' ')
                    {
                        grid[i][j]=' ';
                    }
                    else if (sv2=='|')
                    {
                        grid[i][j]='|';
                    }
                    else if (sv2=='=')
                    {
                        grid[i][j]='=';
                    }
                }
            }
        printf("\n");
		}
		gotoxy(96,10);
        printf("Score=%d",score);
        gotoxy(96,11);
        printf("Lives=%d",life+1);
        gotoxy(89,12);
         if(score<=100) printf("Random Mode Activated");
        else if(score>100 && score <=200)printf("Target Mode Activated");
        else if(score>200 && score<=300) printf("Random Mode Activated");
        else if(score>300 && score<=400) printf("Target Mode Activated");
        else if(score>400 && score<=500) printf("Random Mode Activated");
        else printf("Target Mode Activated");

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

    void ghost2randmove(){
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

    void ghost2targetmove(){
        int i,low,index=0;
        float dis[4]; //distance array
        if(grid[g2y][g2x-1]!='*')
           {
            dis[0] = sqrt(pow(x-(g2x-1),2)+pow(y-g2y,2));
           }else dis[0]=50000;
        if(grid[g2y-1][g2x]!='*' ){
            dis[1] = sqrt(pow(x-g2x,2)+pow(y-(g2y-1),2));}else dis[1]=50000;
        if(grid[g2y][g2x+1]!='*'){
            dis[2] = sqrt(pow(x-(g2x+1),2)+pow(y-g2y,2));}else dis[2]=50000;
        if(grid[g2y+1][g2x]!='*') {
            dis[3] = sqrt(pow(x-g2x,2)+pow(y-(g2y+1),2));}else dis[3]=50000;
        low=dis[0];
        for(i=0;i<4;i++){
            if(dis[i]<low) //finds shortest dist and its index in dis array
            {
                low=dis[i];
                index=i;
            }
        }
        switch(index+1){
        case 1:
                dir2 = LEFT2;
                break;
        case 2:
                dir2 = UP2;
                break;
        case 3:
                dir2 =  RIGHT2;
                break;
        case 4:
                dir2 = DOWN2;
                break;
    }


}

	void Logic(){

        if(score<=100) ghost2randmove();
        else if(score>100 && score <=200)ghost2targetmove();
        else if(score>200 && score<=300) ghost2randmove();
        else if(score>300 && score<=400) ghost2targetmove();
        else if(score>400 && score<=500) ghost2randmove();
        else ghost2targetmove();
        if(((y==g2y+1 || y==g2y-1)&& (x==g2x)) && (((dir2==UP2)&&(dir==DOWN))||((dir2==DOWN2)&&(dir==UP))))
        {life--;x=width/2;y=height/2;g2x=60;g2y=5;}
        if(((x==g2x+1 || x==g2x-1)&& (y==g2y)) && (((dir2==LEFT2)&&(dir==RIGHT))||((dir2==RIGHT2)&&(dir==LEFT))))
        {life--;x=width/2;y=height/2;g2x=60;g2y=5;}
                if(gameover==false)
                {
                switch(dir){                            //pacman's co-ordinate changes when corresponding key is pressed
				case LEFT:
					x--;
					if(grid[y][x]=='|' || grid[y][x]=='=')
                        x+=1;
					break;
				case RIGHT:
					x++;
					if(grid[y][x]=='|' || grid[y][x]=='=')
                        x-=1;
					break;
				case UP:
					y--;
					if(grid[y][x]=='|' || grid[y][x]=='=')
                        y+=1;
					break;
				case DOWN:
					y++;
					if(grid[y][x]=='|' || grid[y][x]=='=')
                        y-=1;
					break;
			}
                }
			if(y==g2y && x== g2x){life--;x=60;y=15;g2x=60;g2y=5;}
			if(life<0) gameover=true;
			if(gameover==false)
            {
			switch(dir2){
				case LEFT2:
					g2x--;
					//if(grid[g2y][g2x]=='|' || grid[g2y][g2x]=='=')
                       // g2x+=1;
					break;
				case RIGHT2:
					g2x++;
					//if(grid[g2y][g2x]=='|' || grid[g2y][g2x]=='=')
                       // g2x-=1;
					break;
				case UP2:
					g2y--;
					//if(grid[g2y][g2x]=='|' || grid[g2y][g2x]=='=')
                       // g2y+=1;
					break;
				case DOWN2:
					g2y++;
					//if(grid[g2y][g2x]=='|' || grid[g2y][g2x]=='=')
                        //g2y-=1;
					break;
			}
            }
            if(g2x<2) g2x+=1; if(g2x>117) g2x-=1;
            if(g2y>27) g2y-=1; if(g2y<2) g2y+=1;
            if(y==g2y && x== g2x){life--;x=25;y=10;g2x=25;g2y=6;}
			if(life<0) gameover=true;
        if (score==669) gameover=true;


	}
	void Game_Over(){
	    int i;
	    system("cls");
	    char ch;
	    char end[7][90]=
        {
            " _____  _____  _____  _____    _____  _____  _____  _____ ",
            "|   __||  _  ||     ||   __|  |     ||  |  ||   __|| __  |",
            "|  |  ||     || | | ||   __|  |  |  ||  |  ||   __||    -|",
            "|_____||__|__||_|_|_||_____|  |_____|  \___/ |_____||__|__|"

        };
        for(i=0;i<4;i++)
            {
                gotoxy(74,24+i);
                printf("%s\n",end[i]);
            }
        if(score==669)
        {
            gotoxy(95,30);
            printf("Congratulations you won:");
        }
		else
        {
            gotoxy(95,30);
            printf("Too bad....you lost..");
        }
        gotoxy(95,31);
        printf("Save Score?(y/n)");
       loop2:
            ch=getch();
        switch(ch){
        case 'y':
                write_record();
                break;
        case 'n':
                break;
        default:
                goto loop2;
                break;
        }
	}

	int main(){
	    char ch;
        fullscreen();
begin:
        Setup();
		while(!gameover){
			Draw();
			Input();
			Logic();
			Sleep(1);
		}
        Game_Over();
        system("cls");
        printf("Go to main menu?(y/n)");
    loop3:ch=getch();
        switch(ch){
        case 'y':
                goto begin;
                break;
        case 'n':
                break;
        default:
                goto loop3;
                break;
        }
		return 0;
	}
