#include "callbacks.h"

void threeCB(char sequence[11],char THAT_VERY_SYMBOL){
    sequence[10] = '\0';
printf("\n\n\nTHREE! AT! ALL! !THE! !SEQUENCE! !IS! !!!%s!!!\n THE SYMBOL IS !!!!%c!!!!",sequence,THAT_VERY_SYMBOL);
return;
}

void threeInRowCB(char THAT_VERY_SYMBOL)
{
    printf("THAT WAS THAT SYMBOOLLLLLLLLLLL !!!THREE!!!IN!!!THE!!!ROW!!!\n %c %c %c %c %c\n\n\n",THAT_VERY_SYMBOL,THAT_VERY_SYMBOL,THAT_VERY_SYMBOL,THAT_VERY_SYMBOL,THAT_VERY_SYMBOL);
    return;
}

int main()
{
    CB_list for_detect;
    for_detect.single_arg_CB = threeInRowCB;
    for_detect.double_arg_CB = threeCB;
    detect(for_detect);
    return 0;
}
