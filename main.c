#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ctrl/ctrl.h"
#include "view/view.h"
#include "task.h"



int main(){
char continue_running = 'y';
while(continue_running == 'y'){
    // clear();
    landingPage();

    int choice;
    scanf("%d", &choice);
    switch(choice){

        case 1: clear(); // View Tasks //
            int taskCount = countTasks("tasks.txt"); 
            if(taskCount){
                struct Task *tasks = viewTasks(taskCount, "tasks.txt"); // lists task
                
                char *taskChoice = viewTaskChoice(taskCount); //prints out choices and prompts the user, returns the input to char *taskChoice


                if(strcmp(taskChoice, "b") == 0){ free(taskChoice); free(tasks); break;}

                else if(isTaskId(taskChoice, taskCount)){
                    struct Task selectedTask = selectTask(tasks, taskCount, taskChoice);
                    printTask(selectedTask);
                }

                free(taskChoice);
                free(tasks);
                break;
            }
        printf("There are no tasks available.\n");
        break;


                   
        case 2: clear(); 
            if(addTask("tasks.txt") == 0){
            printf("Task added successfully.\n");
            break;
        }
            printf("Failed to add task.\n");
            break;


        case 3: statistics("records.txt");
                break;

        case 4: search();
                break;

        case 5: clear();
                printf("Thank you for using Smart Tasker.\n");
                continue_running = 'n';
                break;
    }
}

    return 0;
}