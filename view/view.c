#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#include "../task.h"
#define limit 16 // UI text overflow limit
#define overviewLimit 6
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
    printf("%s. ", task.id);
    printf("%s   ", task.name);
    printf("@%s ", task.tag);
    printf("|%s| ", task.deadline);
    printf("%s\n", task.difficulty);
}



void viewTasks(int taskCount, char *filename){
    if(no_file(filename)){
        make_file(filename);
    }
    FILE *file;
    file = fopen(filename, "r");
    char lineBuffer[255];
    // int id = 1;

    char *line = fgets(lineBuffer, sizeof(lineBuffer), file);
    
    
if(taskCount < 10){
    struct Task taskList[9];
    struct Task task;
    for(int i = 1; i <= taskCount; i++) {
        int size = i - 1;
        char *token = strtok(lineBuffer, "|");
        for(int j = 1; j <= overviewLimit; j++){
            // int tokenLength = strlen(token);
            switch(j){
                case 1: /* id */
                    task.id = token;
                    break;
                case 2: /* = name */
                    task.name = token;
                    // nameFormat(token, tokenLength);
                    break;
                case 3: /* tag */
                    task.tag = token;
                    // tagFormat(token, tokenLength);
                    break;
                case 4: /* deadline */
                    task.deadline = token;
                    // deadlineFormat(token);
                case 5: /* description */
                    task.description = token;
                    break;
                case 6: /* difficulty */
                    task.difficulty = token;
                    break;
            }
            token = strtok(NULL, "|");
        }
        taskList[size] = task;
        size++;
        printTask(task);
        line = fgets(lineBuffer, sizeof(lineBuffer), file); // Read next line
    }

    fclose(file);    
}

else if(taskCount > 10){
    for(int i = 1; i <= 10; i++){
        printf("%d. ", i);
        char *token = strtok(lineBuffer, "|");

        for(int j = 1; j <= overviewLimit; j++){
            int tokenLength= strlen(token);
            switch(j){
                case 1: /* name */
                    nameFormat(token, tokenLength);
                    break;
                case 2: /* tag */
                    tagFormat(token, tokenLength);
                    break;
                case 3: /* deadline */
                    deadlineFormat(token);
            }
            token = strtok(NULL, "|");
        }
        line = fgets(lineBuffer, sizeof(lineBuffer), file);
    }
    fclose(file);
}

/*      taskNumber > 7 page 2
    printf("1. Cook Dinner2           @Personal    #9/17/25\n");
    printf("2. Submit Podcast        @School      #9/18/25\n");
    printf("3. Review for MMW        @School      #9/19/25\n");
    printf("4. Submit Podcast        @School      #9/18/25\n");
    printf("5. Review for MMW        @School      #9/19/25\n");
    printf("6. Submit Podcast        @School      #9/18/25\n");
    printf("7. Review for MMW        @School      #9/19/25\n");
    printf("8. Previous Page\n"); 
    printf("9. Next Page\n"); 
    printf("0. Go Back\n");  
*/

    //have an access to reading the tasks.txt to and print an overview to the console.
    //take in user input to select a certain task, to go to next page, the previous page, as well as the menu.
}


char viewTaskChoice(){
    printf("B = Back     N = Next Page     P = Previous Page\n\n");
    printf("What do you want to do?: ");
    char option;
    clearBuffer();
    scanf("%c", &option);

     if(option == 'b' || option == 'b'){
        return 'b';
    }

    else if(option == 'n' || option == 'n'){
        return 'n';
    }

    else if(option == 'p' || option == 'P'){
        return 'p';
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
