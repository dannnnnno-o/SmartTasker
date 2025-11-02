#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
                tasksBuffer[n++] = tasks[i];
            }
        }
    }
    
    else if (strcmp(mode, "deadline") == 0) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].deadline && strcmp(tasks[i].deadline, input) == 0) {
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