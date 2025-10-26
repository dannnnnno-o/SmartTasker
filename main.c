#include<stdio.h>
#include<stdlib.h>
#include "ctrl/ctrl.h"
#include "view/view.h"

int PROFIT(int TR, int TC){
        // printf("%d", TR - TC);
        return TR - TC;
}

int main(){
    landingPage();

    int choice = landingChoice();
    switch(choice){
        case 1: viewTasks("tasks.txt");
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


    return 0;
}