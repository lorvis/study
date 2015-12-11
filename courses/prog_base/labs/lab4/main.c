#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
enum weaponry {minigun,AT_rifle,railgun,cannon,rocketlauncher, \
 plasmic_katana,plasmic_claymore,plasmic_axe,powered_termite_spear,powered_thermite_halberd, \
 exploding_bow,exploding_crossbow,flamethrower,laser};
enum armory {ricocheting_armor=13,reinforced_armor,fireproof_armor,fireproof_reinforced_armor};
const double  wmulti[14]={0.32,0.54,0.77,0.89,1.12,1.44,1.76,1.83,2.04,2.08,0.86,0.93,0.53,0.32};
const double w_weight[14]={5.3,3.7,4.7,3.8,7,6,2.1,2.5,3.6,3.2,4.6,3.1,3.3,4.1};
const double amulti[4] = {0.86,0.43,0.22,0.67};
const double a_weight[4] = {13,17,11,14};
char * const weaponslist[] = {
"minigun",
"AT_rifle",
"railgun",
"cannon",
"rocketlauncher",
"plasmic_katana",
"plasmic_claymore",
"plasmic_axe",
"powered_termite_spear",
"powered_thermite_halberd",
"exploding_bow",
"exploding_crossbow",
"flamethrower",
"laser"
};
char * const armorlist[] = {
"ricocheting_armor",
"reinforced_armor",
"fireproof_armor",
"fireproof_reinforced_armor"
};

char * const changelist[] = {
"addrobot",
"changewep",
"changearmor",
"changestat",
"goback"
};

char * const menulist[] = {
"fight",
"robots&equipment",
"showstats",
"exit"
};
struct robot{
int weapons[14];
double armor[4];
int level;
double health;
double weight;
double damagepool;
};

typedef struct robot robot;
double damagecalc(robot agrobot,robot defrobot);
void weightcalc(robot robots[],int size);
void rand_weapons(robot robots[],int size);
void rand_armor(robot robots[],int size);
void turn_sort(robot robots[], int size);
void change(robot robots[],int* sizep);
void menu(robot robots[],int *sizep);
void add_robot(robot robots[],int* sizep);
void change_weapons(robot robots[],int size);
void change_armor(robot robots[],int size);
void rand_health_and_level(robot robots[],int size, int mode);
void change_health_and_level(robot robots[], int size);
void showstats(robot robots[], int size);
void dpool_to_zero(robot robots[], int size);
void fight(robot robots[],int size);




int main()
{
    srand(time(NULL));
    int size;
    do{
        puts("insert size >0");
        scanf("%i",&size);
    }while(size<=0);
    int i,j;
   robot* robots = malloc(sizeof(robot)*size);
    for(i=0;i<size;i++){
        for(j=0;j<14;j++){
        robots[i].weapons[j]=0;
        }
        for(j=0;j<4;j++){
        robots[i].armor[j]=1;
        }
    }
int* sizep = &size;
rand_weapons(robots,size);
rand_armor(robots,size);
weightcalc(robots,size);
turn_sort(robots,size);
rand_health_and_level(robots,size,-1);
menu(robots,sizep);
free(robots);
    return 0;
}


double damagecalc(robot agrobot,robot defrobot){
double damage=0;
int i;
for(i=0;i<14;i++){
switch(i){
case 0 ... 2:damage+=agrobot.weapons[i]*wmulti[i]*defrobot.armor[0]*pow((double)agrobot.level,1/4); break;
case 3:
case 4:
case 11:
case 10: damage+=agrobot.weapons[i]*wmulti[i]*defrobot.armor[1]*pow((double)agrobot.level,1/4); break;
case 5 ... 9: damage+=agrobot.weapons[i]*wmulti[i]*defrobot.armor[3]*pow((double)agrobot.level,1/4); break ;
case 13:
case 12: damage+=agrobot.weapons[i]*wmulti[i]*defrobot.armor[2]*pow((double)agrobot.level,1/4); break ;
}
}
return damage;
}

void weightcalc(robot robots[],int size){
int i,j;
for(i=0;i<size;i++){
robots[i].weight=0;
for(j=0;j<4;j++){
robots[i].weight+=((int)(1.99-robots[i].armor[j]))*a_weight[j];
}
for(j=0;j<14;j++){
robots[i].weight+=robots[i].weapons[j]*w_weight[j];
}
}
}

void rand_weapons(robot robots[],int size){
int i,j;
for(i=0;i<size;i++){
    for(j=0;j<14;j++){
    robots[i].weapons[j]=rand()%3;
}
}
}

void rand_armor(robot robots[],int size){
int i,armor_trgt;
for(i=0;i<size;i++){
armor_trgt=rand()%4;
robots[i].armor[armor_trgt]=amulti[armor_trgt];
}
}

void turn_sort(robot robots[], int size){
int i,j,tgtin=0;
double min;
robot temp;
for(i=0;i<size;i++){
min=robots[i].weight;
for(j=i+1;j<size;j++){
if(robots[j].weight<min){
tgtin=j;
min=robots[j].weight;
}
}
if(min!=robots[i].weight){
temp=robots[i];
robots[i]=robots[tgtin];
robots[tgtin]=temp;
}
}
}

void menu(robot robots[],int* sizep){
int size = *sizep;
int w;
int i;
int mvalid;
char word[50];
do{
for(i=0;i<4;i++){
    printf("\n-%s",menulist[i]);
}
mvalid=-1;
do{
weightcalc(robots,*sizep);
size=*sizep;
puts("\n it's main menu, choose action, printed before");
scanf("%s",&word);
for(i=0;i<4;i++){
if(strcmp(word,menulist[i])==0){
mvalid=0;
w=i;
break;
}
}
}while(mvalid);
switch(w){
case 0: printf("%s",menulist[w]);
fight(robots,size);
break;
case 1: printf("%s",menulist[w]); change(robots,sizep); break;
case 2: printf("%s",menulist[w]); showstats(robots,size); break;
case 3: printf("%s",menulist[w]); mvalid=1; break;
default: return;
}
}
while(mvalid!=1);
}

void change(robot robots[],int* sizep){
int i,w;
int size = *sizep;
int cvalid=-1;
char word[50];
do{

for(i=0;i<5;i++){
    printf("\n-%s",changelist[i]);
}
cvalid=-1;
do{
weightcalc(robots,*sizep);
puts("\n it's change menu choose action, printed before");
scanf("%s",&word);
for(i=0;i<5;i++){
if(strcmp(word,changelist[i])==0){
cvalid=0;
w=i;
break;
}
}
}while(cvalid);
switch(w){
case 0: printf("%s",changelist[w]); add_robot(robots,sizep); size = *sizep;  printf("\n size - %i",*sizep); break;
case 1: printf("%s",changelist[w]); change_weapons(robots,size); break;
case 2: printf("%s",changelist[w]); change_armor(robots,size); break;
case 3: printf("%s",changelist[w]); change_health_and_level(robots,size); break;
case 4:  printf("%s",changelist[w]); cvalid=1; break;
default: return;
}
}
while(cvalid!=1);
}

void add_robot(robot robots[],int* sizep){
int i,j,size;
*sizep+=1;
size = *sizep;
realloc(robots,sizeof(robot)*(size));
if (robots==NULL){
    puts("REALLOC IS NULL");
}
for(i=0;i<14;i++){
robots[size-1].weapons[i]=rand()%3;
}
for(i=0;i<size;i++){
for(j=0;j<4;j++){
robots[i].armor[j]=1;
}
}
i=rand()%4;
robots[size-1].armor[i]=amulti[i];
rand_health_and_level(robots,size,size-1);
return;
}

void rand_health_and_level(robot robots[],int size,int mode){
int i;
if(mode=-1){
for(i=0;i<size;i++){
robots[i].health=1000 + rand()%9000;
robots[i].level=10 + rand()%60;
}
} else {
robots[mode].health=1000 + rand()%9000;
robots[mode].level=10 + rand()%60;
}
}

void change_health_and_level(robot robots[],int size){
int i,scale;
do{
puts(" \nenter index of robot");
scanf("%i",&i);
}while(i<0||i>size-1);
do{
puts("enter health of robot [100;10000]");
scanf("%i",&scale);
}while(scale<100||scale>10000);
robots[i].health=scale;
do{
puts("enter level of robot [1;100]");
scanf("%i",&scale);
}while(scale<1||scale>100);
}

void change_weapons(robot robots[],int size){
int i,amount,flag=-1,index,wepindex;
char type[50];
do{
puts("\n type index of robot");
scanf("%i",&index);
}while(index<0||index>size-1);
for(i=0;i<14;i++){
printf("\n %s",weaponslist[i]);
}
do{
    puts("\nprint type of weapon, space and amount of it");
    scanf("%s %i",&type,&amount);
    for(i=0;i<14;i++){
    if(strcmp(type,weaponslist[i])==0){
    flag=0;
    wepindex=i;
    break;
    }
    }
}while(flag!=0||amount<0);
robots[index].weapons[wepindex]=amount;
}

void change_armor(robot robots[],int size){
int i,flag=-1,index,armindex;
char type[50];
do{
puts("\n type index of robot");
scanf("%i",&index);
}while(index<0||index>size-1);
for(i=0;i<4;i++){
printf("\n %s",armorlist[i]);
}
do{
    puts("\nprint type of armor");
    scanf("%s",type);
    for(i=0;i<4;i++){
    if(strcmp(type,armorlist[i])==0){
    flag=0;
    armindex=i;
    break;
    }
    }
}while(flag!=0);
robots[index].armor[armindex]=amulti[armindex];
}

void showstats(robot robots[],int size){
int i, index=-1;
do{
    puts(" \nenter index of robot");
    scanf("%i",&index);
}while(index<0||index>size-1);
printf("\n Index - %i \n Level - %i \n Health - %lf \n Weight - %lf",index,robots[index].level,robots[index].health, robots[index].weight);
for(i=0;i<14;i++){
printf("\n GUN %s - %i",weaponslist[i],robots[index].weapons[i]);
}
for(i=0;i<4;i++){
    if(robots[index].armor[i]!=1){
        printf("\n Armor - %s",armorlist[i]);
    }
}
}

void dpool_to_zero(robot robots[],int size){
int i;
for(i=0;i<size;i++){
    robots[i].damagepool=0;
}
}

void fight(robot robots[], int size){
char answer;
int i,j,count=0;
dpool_to_zero(robots,size);
puts("\nsort robots by weight? it influences on index and turn order 'y' or 'n'");
do{
scanf("%c",&answer);
}while(answer!='y'&&answer!='n');
if(answer=='y'){turn_sort(robots,size);}
do{
count=0;
for(i=0;i<size;i++){
for(j=0;j<size;j++){
if(j!=i||robots[i].damagepool<robots[i].health){robots[j].damagepool+=damagecalc(robots[i],robots[j]);}
}
}
for(i=0;i<size;i++){
    if(robots[i].health>robots[i].damagepool){
    count++;
    }
}
}while(count>1);
count=0;
for(i=0;i<size;i++){
if(robots[i].health>robots[i].damagepool){
    printf("%i SURVIVED",i);
    count++;
}
}
if(count==0){
    puts("NO ONE SURVIVED");
}
}
