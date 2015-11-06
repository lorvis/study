#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,a,endsk=1,c;
    COORD pos;
    pos.X=-1;
    for(i=0;i<=1598;i++){
        pos.Y=(int)i/80;
        if(pos.Y%2==1&&pos.X==79){
                    SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole,a);
        puts("*");
        }
        pos.X+=1-2*((int)((i/80)%2));
        switch(((int)((pos.X-169)/10)-(int)(i/320))%9){
    case -1:
    case -4:
    case -7:
    case 7:
    case 4:
    case 1: a = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
    case -5:
    case -6:
    case 6:
    case 3:
    case 2: a = FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; break;
    case -3:
    case 8:
    case -8:
    case 5: a = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; break;
    case 0: if(pos.Y<=4){a = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; break;} else {
        a = FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; break;

    }
     case -2: if(pos.Y>=16){a = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; break;} else {
        a = FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; break;

    }
        }

        SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole,a);
        puts("*");
        Sleep(1);
    }
    return 0;

}
