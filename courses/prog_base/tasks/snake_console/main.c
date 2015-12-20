#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#define WHITE BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED
#define BLACK 0

enum direction {UP,LEFT,DOWN,RIGHT};

struct point{
int _x;
int _y;
BYTE _ifnew;
};
typedef struct point point;

void move(point* snake,int* size);
point* expand(point* snake,int* size);
void draw_interface();
point* make_food(point* snake,int* size);
void showrecords();

int main()
{
    srand(time(NULL));
    int i;
    BYTE startpoint[2]={40,20};
    int* size = malloc(4);
    while(NULL==size){
        size = realloc(size,4);
    }
    *size = 3;
  point* snake = malloc(*size * sizeof(point));
  while(NULL==snake){
        realloc(snake,1);
    }
  for(i=0;i<*size;i++) {
    snake[i]._x=startpoint[0]+*size-i;
    snake[i]._y=startpoint[1];
    snake[i]._ifnew=0;
  }
  move(snake,size);
  free(snake);
  free(size);
    return 0;
}

void move(point* snake,int* size){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
int i,score=0,level=0;
char nickname[40];
char tablewish[10];
Pos.X=20;
Pos.Y=10;
SetConsoleCursorPosition(hConsole,Pos);
do{
puts("write your difficulty level [1;9]");
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
scanf("%i",&level);
}while(level<1||level>9);
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
puts("write your nickname");
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
scanf("%s",&nickname);
do{
Pos.X=20;
Pos.Y=10;
system("cls");
SetConsoleCursorPosition(hConsole,Pos);
puts("do you want to see the records? type 'no' or 'yes'");
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
scanf("%s",&tablewish);
}while(strcmp(tablewish,"yes")&&strcmp(tablewish,"no"));
if(strcmp(tablewish,"yes")==0){
showrecords();
}
system("cls");
draw_interface();
BYTE collision=0;
SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE|BACKGROUND_INTENSITY);
char cur_dir='d';
char prev_dir='d';
point* food = make_food(snake,size);
Pos.X=food->_x;
Pos.Y=food->_y;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
while(cur_dir!='t'){
Sleep(100-10*level);
if(kbhit()!=0){
prev_dir=cur_dir;
cur_dir=_getch();
}
SetConsoleTextAttribute(hConsole,BLACK);
Pos.X=snake[*size-1]._x;
Pos.Y=snake[*size-1]._y;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
for(i=*size-1;i>=1;i--){
if(snake[i]._ifnew!=0){
snake[i]._ifnew=0;
continue;
}
snake[i]._x=snake[i-1]._x;
snake[i]._y=snake[i-1]._y;
}
Pos.X=62;
Pos.Y=5;
SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_INTENSITY);
SetConsoleCursorPosition(hConsole,Pos);
printf("LEVEL:%i",level);
Pos.Y+=5;
SetConsoleCursorPosition(hConsole,Pos);
printf("SCORE:%i",score);
Pos.Y+=5;
SetConsoleCursorPosition(hConsole,Pos);
printf("NAME:%s",nickname);
switch(cur_dir){
case 97:  if(prev_dir!='d'){snake[0]._x-=1; break;} else {cur_dir='d';snake[0]._x+=1;} break;
case 100: if(prev_dir!='a'){snake[0]._x+=1; break;} else {cur_dir='a';snake[0]._x-=1;} break;
case 115: if(prev_dir!='w'){snake[0]._y+=1; break;} else {cur_dir='w';snake[0]._y-=1;} break;
case 119: if(prev_dir!='s'){snake[0]._y-=1; break;} else {cur_dir='s';snake[0]._y+=1;} break;
default: cur_dir=prev_dir; switch(cur_dir){
case 97:  if(prev_dir!='d'){snake[0]._x-=1; break;} else {cur_dir='d';snake[0]._x+=1;} break;
case 100: if(prev_dir!='a'){snake[0]._x+=1; break;} else {cur_dir='a';snake[0]._x-=1;} break;
case 115: if(prev_dir!='w'){snake[0]._y+=1; break;} else {cur_dir='w';snake[0]._y-=1;} break;
case 119: if(prev_dir!='s'){snake[0]._y-=1; break;} else {cur_dir='s';snake[0]._y+=1;} break;
} break;
}
SetConsoleTextAttribute(hConsole,WHITE);
for(i=0;i<*size;i++){
Pos.X=snake[i]._x;
Pos.Y=snake[i]._y;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
}
for(i=3;i<*size;i++){
if(snake[0]._x==snake[i]._x&&snake[0]._y==snake[i]._y){
collision=1;
}
}
if(snake[0]._x>=60||snake[0]._x<=0||snake[0]._y>=23||snake[0]._y<=0||collision){
Beep(260,800);
Beep(400,700);
Beep(430,700);
Beep(230,900);
Pos.X=0;
Pos.Y=0;
SetConsoleTextAttribute(hConsole,BACKGROUND_RED);
SetConsoleCursorPosition(hConsole,Pos);
for(i=0;i<200;i++){
printf("GAME OVER!");
free(food);
}
break;
}
if(snake[0]._x==food->_x&&snake[0]._y==food->_y){
score+=100*level;
if(score>=level*600&&level!=9){
level++;
}
Beep(600,100);
snake = expand(snake,size);
snake[*size-1]._x=snake[*size-2]._x;
snake[*size-1]._y=snake[*size-2]._y;
snake[*size-1]._ifnew=1;
free(food);
food=make_food(snake,size);
Pos.X=food->_x;
Pos.Y=food->_y;
SetConsoleCursorPosition(hConsole,Pos);
SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE|BACKGROUND_INTENSITY);
puts(" ");
}
}
}
point* expand(point* snake,int* size){
*size+=1;
point* newsnake = realloc(snake,sizeof(point)*(*size));
while(snake==NULL){
realloc(snake,sizeof(point)*(*size));
}
return newsnake;
}

void draw_interface(){
COORD Pos;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int i;
SetConsoleTextAttribute(hConsole,BACKGROUND_RED|BACKGROUND_INTENSITY);
for(i=0;i<24;i++){
Pos.X=0;
Pos.Y=i;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
Pos.X=60;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
}
for(i=0;i<60;i++){
Pos.X=i;
Pos.Y=0;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
Pos.Y=23;
SetConsoleCursorPosition(hConsole,Pos);
puts(" ");
}
}

point* make_food(point* snake,int* size){
int i;
BYTE wrong_spawn;
point* food = malloc(sizeof(point));
food->_x=rand()%59+1;
food->_y=rand()%22+1;
do{
wrong_spawn=0;
for(i=0;i<*size;i++){
if(snake[i]._x==food->_x&&snake[i]._y==food->_y){
wrong_spawn=1;
}
}
if(wrong_spawn){
food->_x=rand()%59+1;
food->_y=rand()%22+1;
}
}while(wrong_spawn);
return food;
}
void showrecords(){
COORD Pos;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
FILE* stream;
char name[30];
int score;
stream = fopen("records.txt","r+");
system("cls");
Pos.X=20;
Pos.Y=1;
SetConsoleCursorPosition(hConsole,Pos);
puts("RECORDS");
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
do{
fscanf(stream,"%s %i",&name,&score);
printf("%s %i",name,score);
do{
fseek(stream,ftell(stream)+1,SEEK_CUR);
}while(fgetc(stream)!='\n');
fseek(stream,ftell(stream)+1,SEEK_CUR);
Pos.Y++;
SetConsoleCursorPosition(hConsole,Pos);
}while(feof(stream)==0);
fclose(stream);
Sleep(900);
}
