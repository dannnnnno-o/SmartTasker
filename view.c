#include <stdio.h>
#include "controller.c"

void viewTasks(char *file){

    if(no_file(file)){
        printf("No tasks yet\n");
    }
    else{printf("file found\n");}

/*     printf("Tasks\n");
    printf("1. Cook Dinner           @Personal    #9/17/25\n");
    printf("2. Submit Podcast        @School      #9/18/25\n");
    printf("3. Review for MMW        @School      #9/19/25\n");
    printf("4. Go Back\n"); */

    //have an access to reading the tasks.txt to and print an overview to the console.
    //take in user input to select a certain task, to go the previous, as well as next page.
}


void displayTask(){
    printf("displayTask");
    //After selecting a specific task, display all it's information
    //Add a next and previous (if available), return, submit, and remove button.

}

void addTask(){
    printf("Add\n");
    
    //have an access to append to tasks.txt 
    //text format not yet to be disclosed.
}

void manageTasks(){
    printf("Manage\n");
    //also have an read access to have an overview
    //complex functionality of buttons such as select many tasks at once that can either be removed or submitted.
    //after tasks are removed or completed, they will be moved to records.txt
}

void history(){
    printf("History\n");
    //have an access to records.txt and display the overview of removed/submitted takss
    //by default, a user is allowed to select a certain task at once and have an option to restore it or to simply return

    //have the option to manage -- to select many tasks at once and also have an option to restore or abort the operation
}

