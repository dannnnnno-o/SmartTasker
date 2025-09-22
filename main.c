#include<stdio.h>
#include<stdlib.h>
#include "view.c"

int main(){

    printf("Welcome to Smart Tasker.\n");
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. Manage Tasks\n");
    printf("4. History\n");
    printf("5. Exit\n");
    printf("\nWhat would you like to do?: ");


    
    int choice;
    scanf("%d", &choice);

    system("clear");


    switch(choice){
        case 1: viewTasks("tasks.txt");
                break;
        case 2: addTask();
                break;
        case 3: manageTasks("Tasks.txt");
                break;
        case 4: history();
                break;
        case 5: printf("Thanks for using Smart Tasker!\n");
                return 0;
    }

    return 0;
}