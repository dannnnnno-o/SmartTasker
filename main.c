#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "ctrl/ctrl.h"
#include "view/view.h"
#include "task.h"



int main(){
char continue_running = 'y';
while(continue_running == 'y'){

    landingPage();

    int choice;
    scanf("%d", &choice);
    switch(choice){

        case 1: // View Tasks //
            int taskCount = countTasks("tasks.txt"); 
            if(taskCount){
                viewTasks(taskCount, "tasks.txt"); // lists task
                char taskChoice = viewTaskChoice(taskCount); //prints out choices and prompts the user, returns the input to char taskChoice

                switch(taskChoice){
                    case 'b': break;
                }            
                break;
            }
        printf("There are no tasks available.\n");
        break;












                   
        case 2: addTask("tasks.txt");
                break;

        case 3: history("tasks.txt");
                break;
        case 4: printf("Thank you for using Smart Tasker.\n");
                continue_running = 'n';
                break;
    }
}

    return 0;
}