#include <stdio.h>
int no_file(char *filename){
    FILE *file = fopen(filename, "r");

    if(file){
        fclose(file);
        return 0; // if file exists
    }
    return 1; // if file does not exists
}

void taskOverview(char *filename){
    FILE *file = fopen(filename, "r");

    int finput = 0;
    fscanf(file, "%d", &finput);
    printf("Number: %d\n", finput);

    fclose(file);


   //added code
}


// still missing the smart sorter that sorts tasks based on a given deadline and a difficulty;
