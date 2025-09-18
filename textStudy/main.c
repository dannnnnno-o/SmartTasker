#include <stdio.h>

int main(){

    FILE *fh_output;
    fh_output = fopen("text.txt", "a");

    fputs("\nA second string\n", fh_output);

    fclose(fh_output);

    return 0;
}