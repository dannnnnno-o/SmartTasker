#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctrl.h"
#include "../view/view.h"
#include "../task.h"
#define limit 16

int no_file(char *filename){
    FILE *file = fopen(filename, "r");

    if(file){
        fclose(file);
        return 0; // if file exists
    }
    return 1; // if file does not exists
}

void make_file(char *file){
        if(no_file(file)){ // if tasks aren't found, make one.
        FILE *tmpFile = fopen(file, "w");
        fclose(tmpFile);
    }
}

void clearBuffer(){
    int emptyChar;
    while((emptyChar = getchar()) != '\n' && emptyChar != EOF){/* do nothing because the while loop will run until the input buffer is cleared*/}
}




/* 1. View Tasks */
void taskOverview(char *filename){
    FILE *file = fopen(filename, "r");
    fclose(file);
}

void nameFormat(char *text, int len){
    if(len == limit){
        printf("%s", text);
    }

    else if(len < limit){
        printf("%s", text);
        for(int i = len; i <= limit; i++)
        printf(" ");
    }

    else if(len > limit){
        char newText[limit - 3]; // -3 for ellipses
        strncpy(newText, text, limit - 4); // -4 for cutting of the last three letters and the null terminator
        printf("%s...", newText);
    }
}

void tagFormat(char *tag, int len){
    printf("\t\t\t");
    if(len == limit){
        printf("%s", tag);
    }

    else if(len < limit){
        printf("#%s", tag);
        for(int i = len; i < limit; i++){
            printf(" ");
        }
    }

    else if (len > limit){
        char newTag[limit - 3]; // -3 for ellipses
        strncpy(newTag, tag, limit - 4); // -4 for cutting of the last three letters and null terminator
        printf("%s...", newTag);
    }
}

void deadlineFormat(char *deadline){
    printf("| %s |\n", deadline);
}

int countTasks(char *filename){
    FILE *file = fopen(filename, "r");

    char lineBuffer[255];
    
    char *line = fgets(lineBuffer, sizeof(lineBuffer), file);
    int taskNumber = 0;
    while(line){
        taskNumber++;
        line = fgets(lineBuffer, sizeof(lineBuffer), file);
    }

    fclose(file);
    return taskNumber;
}

void selectTask(char* taskName){
    FILE *file = fopen(taskName, "r");



    fclose(file);
}

/* END OF 1. View Tasks */