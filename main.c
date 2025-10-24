#include<stdio.h>
#include<stdlib.h>
#include "ctrl/ctrl.h"
#include "view/view.h"



int main(){
    landingPage();

    int choice = landingChoice();
    switch(choice){
        case 1: viewTasks("tasks.txt");
                break;
        case 2: addTask("tasks.txt");
                break;
        case 3: history("tasks.txt");
                break;
        case 4: printf("Thank you for using Smart Tasker.\n");
                exit(0);
    }


    return 0;
}