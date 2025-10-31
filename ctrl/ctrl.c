#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ctrl.h"
#include "../view/view.h"
#include "../task.h"
#define limit 15

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

char *toStr(int x){
    char str[] = "  ";
    sprintf(str, "%d", x);
    char *strValue = str; 
    return strdup(strValue);
}


void clearBuffer(){
    int emptyChar;
    while((emptyChar = getchar()) != '\n' && emptyChar != EOF){/* do nothing because the while loop will run until the input buffer is cleared*/}
}

int isValidNumber(char *str){
    for(int i = 0; i < strlen(str); i++){
        if(isdigit(str[i])){
            continue;
        }
        else{
            return 0; // false = not a valid number
        }
    }
    return 1;
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
        printf("@%s", tag);
    }

    else if(len < limit){
        printf("@%s", tag);
        for(int i = len; i < limit; i++){
            printf(" ");
        }
    }

    else if (len > limit){
        char newTag[limit - 4]; // -3 for ellipses
        strncpy(newTag, tag, limit - 6); // -4 for cutting of the last three letters and null terminator
        printf("@%s...", newTag);
    }
}

void deadlineFormat(char *deadline){
    printf("| %s |    ", deadline);
}

void difficultyFormat(char *difficulty){
    printf("    %s", difficulty);
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

int isTaskId(char *taskId, int taskCount){
    if(isValidNumber(taskId)){
        if(atoi(taskId) < 0 || atoi(taskId) > taskCount ){
            return 0; // false = not a valid Task ID
        }
    }
    return 1;
}

struct Task selectTask(struct Task *taskList, int taskCount, char *taskId){
    for(int i = 0; i < taskCount; i++){
        if(strcmp(taskList[i].id, taskId) == 0){
            return taskList[i]; 
        }
        continue;
    }
    struct Task emptyTask = {0};  // Initialize all fields to 0/NULL
    return emptyTask;
}


/* END OF 1. View Tasks */

/* START OF 4. SEARCH */

char *scanBack(char *option){
    if(strcmp(option, "b") == 0 || strcmp(option, "B") == 0){
        return strcpy(option, "b");
    }
    return NULL;
}