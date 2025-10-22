#include<stdio.h>
#include<stdlib.h>
#include "ctrl/ctrl.h"
#include "view/view.h"



int main(){
    landingPage();

    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1: // View Tasks //
            int taskCount = countTasks("tasks.txt"); 
            if(taskCount){
                viewTasks(taskCount, "tasks.txt"); // lists task
                printChoices(taskCount, "tasks.txt"); //prints out choices and prompts the user


                
                break;
            }

        printf("There are no tasks available.\n");
        break;
                   
        case 2: addTask("tasks.txt");
                break;
        case 3: manageTasks("tasks.txt");
                break;
        case 4: history("tasks.txt");
                break;
        case 5: printf("Thank you for using Smark Tasker.\n");
                exit(0);
    }

    /* 
    
    MAIN.C

    */

    return 0;
}