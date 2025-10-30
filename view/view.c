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

void landingPage(){
    printf("Welcome to Smart Tasker.\n");
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. History\n");
    printf("4. Exit\n");
    
    printf("\nWhat would you like to do?: ");
}

void printTask(struct Task task){
    // printf("%s. ", task.id);
    printf("%s   ", task.name);
    printf("@%s ", task.tag);
    printf("|%s| ", task.deadline);
    printf("%s\n", task.difficulty);
}


struct Task *viewTasks(int taskCount, char *filename){

    printf("\n      Name                                Tag             Deadline     Difficulty(?/10)\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    if(no_file(filename)){
        make_file(filename);
    }
    FILE *file;
    file = fopen(filename, "r");
    char lineBuffer[255];

    struct Task *taskList = malloc(taskCount * sizeof(struct Task)); // define task array
    // int listLength = sizeof(taskList)/sizeof(taskList[0]); // size of array

    struct Task task; // task attributes changes per iteration
    int n = 0; //index for keeping track
    while(fgets(lineBuffer, sizeof(lineBuffer), file)){
        char *token = strtok(lineBuffer, "|");
        for(int i = 0; i < taskAttributes; i++){
            int tokenLen = strlen(token);
            switch(i){
                case 0: /* id */
                printf("%s. ", token); task.id = strdup(token); break;
                case 1: /* name */
                nameFormat(token, tokenLen); task.name = strdup(token); break;
                case 2: /* tag */
                tagFormat(token, tokenLen); task.tag = strdup(token); break;
                case 3: /* deadline */
                deadlineFormat(token); task.deadline = strdup(token); break;
                case 4: /* description */
                task.description = strdup(token); break;
                case 5: /* difficulty */
                difficultyFormat(token); task.difficulty= strdup(token); break;
            }
            token = strtok(NULL, "|");
        }
        taskList[n] = task;
        n++;
    }
    printf("\n\n");
    fclose(file);   
    return taskList; 
}

    //have an access to reading the tasks.txt to and print an overview to the console.
    //take in user input to select a certain task, to go to next page, the previous page, as well as the menu.


char *viewTaskChoice(int taskCount){
    if(taskCount == 1)
    {printf("B = Back, %d = Task Detail\n", taskCount);}
    else if(taskCount > 1)
    {printf("B = Back, 1-%d = Task Detail.\n", taskCount);}
    
    printf("What do you want to do?: ");
    char *option = malloc(16);
    if(!option) return NULL;



    clearBuffer();
    if(scanf("%s", option) != 1){
        free(option);
        return NULL;
    }

     if(strcmp(option, "b") == 0 || strcmp(option, "B") == 0){
        return "b";
    }

    return option;
}




void displayTask(char *filename){
    printf("displayTask");
    //After selecting a specific task, display all it's information
    //Add a next and previous (if available), return, submit, and remove button.
}

void addTask(char *filename){
    printf("Add\n");
    /* 
    NAME:
    DES:

 */


    //have an access to tasks.txt, and append user input 
    //text format not yet to be disclosed.
}

/* void manageTasks(char *filename){
    printf("Manage\n");
    //also have an read access to tasks.txt have an overview
    //complex functionality of buttons such as select many tasks at once that can either be removed or submitted.
    //after tasks are removed or completed, they will be moved to records.txt
} */

void history(char *filename){
    printf("History\n");
    //have an access to records.txt and display the overview of removed/submitted tasks
    //by default, a user is allowed to select a certain task at once and have an option to restore it or to simply return

    //have the option to manage -- to select many tasks at once and also have an option to restore or abort the operation
}
