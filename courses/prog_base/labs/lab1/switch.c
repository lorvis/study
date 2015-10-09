#include <stdio.h>
#include <stdlib.h>
#include <math.h>

min(a,b) {if (a<b) {return a;} else {return b;};} //Як в коментарях знизу,можливо, тут
max(a,b) {if (a>b) {return a;} else {return b;};} //повинна була бути інтегровані функції,
                                                  //але воно каже, що я не заделарував ці змінні.

int sizeofnum(int a,int b) { // Не знаю, що саме мається на увазі в 10 операторі, тому
switch (abs(b)%8) {          // зроблю у формі switch і функції. Тут функція.
case 0: return abs(a)*sizeof(char);
case 1: return abs(a)*sizeof(signed char);
case 2: return abs(a)*sizeof(short);
case 3: return abs(a)*sizeof(unsigned int);
case 4: return abs(a)*sizeof(long);
case 5: return abs(a)*sizeof(unsigned long long);
case 6: return abs(a)*sizeof(float);
case 7: return abs(a)*sizeof(double);
}
}

int variant(int a,int b) {  // Та ж сама ситуація, що і зверху ^ , тільки з 11.
int n0 = 1;
int n1 = 1;
double PI = 3.14159265358979323846;
if (a==0) {return 0;};
return ((n0+1)*PI*cos((n1+1)*a*b)/a);
}

int default1(int op, int a, int b) { //Аналогічно і тут.
 if (op<100) {
    return ((op%abs(a+1)) + (op % abs(b+1)));
 }
 if (op>=100) {
    return -1;
}
}

int exec(int op, int a, int b) {
int inverse;
double PI = 3.14159265358979323846; // Наскільки я зрозумів, в моєму math.h немає значення PI,
                                    // тому я його декларую. Спираюся на http://goo.gl/6NiyIz
if (op<0) {
inverse = a;
a = b;
b = inverse;
op = abs(op);
};
switch (op) {
case 0: return -a;
case 1: return a+b;
case 2: return a-b;
case 3: return a*b;
case 4: return a/b;
case 5: return abs(a);
case 6: return pow(a,b);
case 7:
case 13:
case 77: return a%b;
case 8: if (a>b) {return a;} else {return b;};
case 9: if (a<b) {return a;} else {return b;};
case 10:
     switch (abs(b)%8) {
case 0: return abs(a)*sizeof(char);
case 1: return abs(a)*sizeof(signed char);
case 2: return abs(a)*sizeof(short);
case 3: return abs(a)*sizeof(unsigned int);
case 4: return abs(a)*sizeof(long);
case 5: return abs(a)*sizeof(unsigned long long);
case 6: return abs(a)*sizeof(float);
case 7: return abs(a)*sizeof(double);
     };
case 11: if (a==0) {
return 0;
}
 else {
return (int)((1+1)*PI*cos((1+1)*a*b)/a); //Округляю аналогом floor.
};
default:
 if (op<100) {
    return (int)((op%abs(a+1)) + (op % abs(b+1))); //Округляю аналогом floor.
 }
 if (op>=100) {
    return -1;
 }
 }
}



int main()
{ int op =-4; int a = 2; int b = 4;
int result = exec(op,a,b);
    return result;
}
