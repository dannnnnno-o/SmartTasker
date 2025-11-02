#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "ctrl.h"
#include "../view/view.h"
#include "../task.h"
#define limit 16
#define taskAttributes 6

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

int isDate(char *input){

    if (!input || strlen(input) < 8) return 0;
    if (input[2] != '/' || input[5] != '/') return 0;

    char mm[3] = {input[0], input[1], '\0'}; 
    char dd[3] = {input[3], input[4], '\0'}; 
    char yy[3] = {input[6], input[7], '\0'}; 
    char *date[3] = {mm, dd, yy};
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            if(isdigit(date[i][j])){
                continue;
            }
            else{
            return 0;
            }
        }
    }
    int newM = atoi(mm);
    int newD = atoi(dd);
    int newY = atoi(yy); // gets the all the year after 1900 so we add it, then subtract 2000 to get the last 2 digit of the year. 


    if(newM <= 0 || newM > 12){
        return 0; // month is out of range
    }
    int maxDays;

//maxDays
    if(newM == 1){
    maxDays = 28;
    }
    
    else if(newM == 4 || newM == 6 || newM == 9 || newM == 11){
    maxDays = 30;
    }

    else{
    maxDays = 31;
    }

    if(newD <= 0 || newD > maxDays){ // day out of range
        return 0; 
    }

    time_t now = time(NULL);

    struct tm *local_time = localtime(&now);
    int local_year = local_time->tm_year + 1900 - 2000;
    int local_month = local_time->tm_mon + 1;
    int local_mday = local_time->tm_mday;

    if(newY < local_year){
        return 0;
    }

    else if(newY == local_year){
    if(newM < local_month){
        return 0;
    }
    else if(newM == local_month && newD < local_mday){
        return 0;
    }
}
    return 1;
}


struct Task *getTasks(char *filename, int taskCount){
    FILE *file = fopen(filename, "r");
    char lineBuffer[256];

    struct Task *tasks = malloc(taskCount * sizeof(struct Task));
    struct Task task; // changes after each iteration::after reading new line

    int n = 0; //for keeping track of index
    while(fgets(lineBuffer, sizeof(lineBuffer), file)){ // while there is a line
        char *token = strtok(lineBuffer, "|");
        for(int i = 0; i < taskAttributes; i++){
            switch(i){
                case 0: task.id = toStr(n + 1); break; //assign ID
                case 1: task.name = strdup(token); break;
                case 2: task.tag = strdup(token); break;
                case 3: task.deadline = strdup(token); break;
                case 4: task.description = strdup(token); break;
                case 5: task.difficulty = strdup(token); break;
            }
            token = strtok(NULL, "|");
        }
        tasks[n] = task; // assign task at index n of tasks
        n++;
    }
    fclose(file);
    return tasks;
}

struct Task *getSimilarTasks(struct Task *tasks, int taskCount, char *input, char *mode, int *outMatchCount){
    struct Task *tasksBuffer = malloc(taskCount *sizeof(struct Task));
    if(!tasksBuffer){return NULL;}
    int n = 0; // for keeping track of index
    if(strcmp(mode, "name") == 0){
        for(int i = 0; i < taskCount; i++){
            if(strcmp(tasks[i].name, input) == 0){
                tasks[i].id = toStr(n + 1);
                tasksBuffer[n] = tasks[i];
                n++; 
            }
            else{
                continue;
            }
        }
    }

    else if (strcmp(mode, "tag") == 0) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].tag && strcmp(tasks[i].tag, input) == 0) {
                tasks[i].id = toStr(n + 1);
                tasksBuffer[n++] = tasks[i];
            }
        }
    }
    
    else if (strcmp(mode, "deadline") == 0) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].deadline && strcmp(tasks[i].deadline, input) == 0) {
                tasks[i].id = toStr(n + 1);
                tasksBuffer[n++] = tasks[i];
            }
        }
    }

    if(n == 0){
        free(tasksBuffer);
        *outMatchCount = 0;
        return NULL;
    }

    //shrink the allocation
    struct Task *shrink = realloc(tasksBuffer, n * sizeof(*shrink));
    if(shrink){tasksBuffer = shrink;}

    *outMatchCount = n; // directly updates the variable using the memory

    return tasksBuffer;
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
        if(!(atoi(taskId) < 0) || !(atoi(taskId) > taskCount)){
            return 1; // returns true
        }
    }
    return 0;
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
        return strdup("b");
    }
    return NULL;
}

int searchKey(char *option){
    if(strcmp(option, "1") == 0){
        return 1;
    }
    else if(strcmp(option, "2") == 0){
        return 2;
    }
    else if(strcmp(option, "3") == 0){
        return 3;
    }
    return 0;

}