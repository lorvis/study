#include "callbacks.h"
void detect(CB_list list_for_detect){
    int fullness_count = 0;
    char sequence[11] = "hereistext";
    FILE * stdin_stream = stdin;
do{
    char input;
    input = getchar();
    if(input!='\n'){
        puts("\b \b");
    sequence[0]=input;
    printf("\nyou have entered %c\n",sequence[0]);
    if(fullness_count<10)
        fullness_count++;
        else{
                if(sequence[0]==sequence[1]&&sequence[1]==sequence[2])
        list_for_detect.single_arg_CB(sequence[0]);
        else{
        for(int i = 0;i<10;i++){
        int ins_num = 0;
        for(int j = 0;j<10;j++){
        if(sequence[i]==sequence[j])
        ins_num++;
        }
        if(ins_num >= 3){
            list_for_detect.double_arg_CB(sequence,sequence[i]);
            break;
        }
        }
        }
        }
            for(int i = 10;i>0;i--){
        sequence[i]=sequence[i-1];
    }
    }
}while(sequence[0]!='e'&&sequence[0]!='E');
fclose(stdin_stream);
}
