#include <stdio.h>
#include <stdlib.h>


void fprocess(const char * pread, const char * pwrite){
FILE* readwriting = fopen(pread,"r");
double reading;
fscanf(readwriting,"%lf",&reading);
printf("%lf",reading);
fclose(readwriting);
readwriting = fopen(pwrite,"w");
fprintf(readwriting,"%i",(int)(reading+0.5));
}

