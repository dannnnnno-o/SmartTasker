#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#define limit 16 // UI text overflow limit
#define overviewLimit 3
#define taskLimit 7

void clear(){system("cls");}

void landingPage(){
    printf("Welcome to Smart Tasker.\n");
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. Manage Tasks\n");
    printf("4. History\n");
    printf("5. Exit\n");
    
    printf("\nWhat would you like to do?: ");
}

void View(int choice){
    
}

void viewTasks(char *filename){
    if(no_file(filename)){
        make_file(filename);
    }

    int taskCount = countTasks("tasks.txt");

    if(!taskCount){
        printf("There are no tasks available.");
    }

    else if(taskCount <= taskLimit){

    }

    FILE *file;
    file = fopen(filename, "r");
    char lineBuffer[255];
    int lineNumber = 1;

    char *line = fgets(lineBuffer, sizeof(lineBuffer), file);
    while(line){
        printf("%d. ", lineNumber);
        lineNumber++;
        char *token = strtok(lineBuffer, ",");

        for(int i = 1; i <= overviewLimit; i++){
            int tokenLength = strlen(token);
            switch(i){
                case 1: /* first index = name */
                    //char* name = token
                    nameFormat(token, tokenLength);
                    break;
                case 2: /* second index = tag */
                    tagFormat(token, tokenLength);
                    break;
                case 3: /* third index = deadline */
                    deadlineFormat(token);
            }
            token = strtok(NULL, ",");
        }
        line = fgets(lineBuffer, sizeof(lineBuffer), file); // Read next line
    }
    fclose(file);


/*     taskNumber < 7
    printf("1. Cook Dinner           @Personal    #9/17/25\n");
    printf("2. Submit Podcast        @School      #9/18/25\n");
    printf("3. Review for MMW        @School      #9/19/25\n");
    printf("4. Go Back\n");
*/

/*      taskNumber == 7
    printf("1. Cook Dinner           @Personal    #9/17/25\n");
    printf("2. Submit Podcast        @School      #9/18/25\n");
    printf("3. Review for MMW        @School      #9/19/25\n");
    printf("4. Submit Podcast        @School      #9/18/25\n");
    printf("5. Review for MMW        @School      #9/19/25\n");
    printf("6. Submit Podcast        @School      #9/18/25\n");
    printf("7. Review for MMW        @School      #9/19/25\n");
    printf("8. Go Back\n"); 
*/
    
/*      taskNumber > 7 page 1
    printf("1. Cook Dinner           @Personal    #9/17/25\n");
    printf("2. Submit Podcast        @School      #9/18/25\n");
    printf("3. Review for MMW        @School      #9/19/25\n");
    printf("4. Submit Podcast        @School      #9/18/25\n");
    printf("5. Review for MMW        @School      #9/19/25\n");
    printf("6. Submit Podcast        @School      #9/18/25\n");
    printf("7. Review for MMW        @School      #9/19/25\n");
    printf("8. Next Page\n"); 
    printf("9. Go Back\n");  
*/
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


void displayTask(char *filename){
    printf("displayTask");
    //After selecting a specific task, display all it's information
    //Add a next and previous (if available), return, submit, and remove button.

}

void addTask(char *filename){
    printf("Add\n");
    
    //have an access to tasks.txt, and append user input 
    //text format not yet to be disclosed.
}


void history(char *filename){
    printf("History\n");
    //have an access to records.txt and display the overview of removed/submitted tasks
    //by default, a user is allowed to select a certain task at once and have an option to restore it or to simply return

    //have the option to manage -- to select many tasks at once and also have an option to restore or abort the operation
}
