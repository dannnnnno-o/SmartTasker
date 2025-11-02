#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#include "../task.h"
#define limit 16 // UI text overflow limit
#define taskAttributes 6
#define taskLimit 9

void clear(){system("cls");}
void newLine(){printf("\n");}

void landingPage(){
    printf("Welcome to Smart Tasker.\n");
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. Statistics\n");
    printf("4. Search\n");
    printf("5. Exit\n");
    
    printf("\nWhat would you like to do?: ");
}

void printTask(struct Task task){
    printf("%s. ", task.id);
    nameFormat(task.name, strlen(task.name));
    tagFormat(task.tag, strlen(task.tag));
    deadlineFormat(task.deadline);
    difficultyFormat(task.difficulty);
}

void viewTasks(struct Task *tasks, int taskCount){
    for(int i = 0; i < taskCount; i++){
        printTask(tasks[i]);
    }
    printf("\n\n");
}

char *viewTaskChoice(int taskCount){
    if(taskCount == 1)
    {printf("B = Back, %d = Task Detail\n", taskCount);}
    else if(taskCount > 1)
    {printf("B = Back, 1-%d = Task Detail.\n", taskCount);}
    
    printf("What do you want to do?: ");
    char *option = malloc(16);
    if(!option){return NULL;}

    clearBuffer();
    if(scanf("%s", option) != 1){
        free(option);
        return NULL;
    }

    if(scanBack(option)){
        return scanBack(option);
    }

    return option;
}

void displayTask(char *filename){
    printf("displayTask");
    //After selecting a specific task, display all it's information
    //Add a next and previous (if available), return, submit, and remove button.
}

int addTask(char *filename){
    printf("Add Task\n");

    if(no_file(filename)){
        make_file(filename);
    }

    FILE *file = fopen(filename, "a");

    struct Task task = {0};
    char strBuffer[256];

    task.id = toStr(countTasks(filename) + 1);
    
    clearBuffer();

    //name
    printf("Input task name: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.name = strdup(strBuffer);

    //tag
    printf("Input task tag: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.tag = strdup(strBuffer);   

    //deadline
    printf("Input task deadline: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.deadline = strdup(strBuffer);  

    //description
    printf("Input task description: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.description = strdup(strBuffer);   

    //difficulty
    printf("Input task difficulty: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.difficulty = strdup(strBuffer);  

    // printTask(task);

    fprintf(file, "\n%s|%s|%s|%s|%s|%s", task.id, task.name, task.tag, task.deadline,task.description, task.difficulty);

    fclose(file);

    return 0;
/* 
    NAME:
    TAG:
    DEADLINE:
    DESCRIPTION:
    DIFFICULTY:
 */
}

void statistics(char *filename){
    printf("Statistics\n");
    //have an access to records.txt and display the overview of removed/submitted tasks
    //by default, a user is allowed to select a certain task at once and have an option to restore it or to simply return

    //have the option to manage -- to select many tasks at once and also have an option to restore or abort the operation
}


/* START OF SEARCH */
char *search(){
    printf("Search a task by: \n");
    printf("B = Back\n1. Name\n2. Tag\n3. Deadline\n");
    printf("What would you like to do?: ");

    char *option = malloc(16);
    if(!option){return NULL;}

    clearBuffer();
    if(scanf("%s", option) != 1){
        free(option);
        return NULL;
    }

    else if(scanBack(option)){
        return scanBack(option);
    }

    return option;
}

char *getSearchInput(){
    char *option = malloc(16);
    if(!option){return NULL;}
    clearBuffer();

    printf("Enter task name: ");

    char optionBuffer[256];
    
    fgets(optionBuffer, sizeof(optionBuffer), stdin);
    optionBuffer[strcspn(optionBuffer, "\n")] = 0;
 
    if(scanBack(option)){
        return scanBack(option);
    }
    return strdup(optionBuffer);
}
