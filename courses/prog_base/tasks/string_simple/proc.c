#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * process(char * resultStr, const char * textLines[], \
               int linesNum, const char * extraStr)
{
    int vowelcou=0;
    char* consomax= {"not"};
    char* oper;
    const char vowel[10] = {'a','e','i','o','u','A','E','I','O','U'};
    const char conso[42] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z','y', \
                            'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Z','Y'
                           };
    int i,j,concon=0;
    for(i=0; i<linesNum; i++)
    {
        oper = textLines[i];
        for(j=0; j<=9; j++)
        {
            if(vowel[j]==oper[0])
            {
                vowelcou=vowelcou+1;
            }

        }
      for(concon=0; concon<=41; concon++)
            {
                if (conso[concon]==oper[0]&&strlen(oper)>strlen(consomax)) {
                    consomax = oper;
            }
    }
    }


