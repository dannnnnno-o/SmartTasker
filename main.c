#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctrl/ctrl.h"
#include "view/view.h"
#include "task.h"



int main(){
char continue_running = 'y';
loop:
while(continue_running == 'y'){
// clear();
landingPage();

if(no_file("tasks.txt"))
{make_file("tasks.txt");}


int taskCount = countTasks("tasks.txt");
struct Task *tasks = malloc(taskCount * sizeof(struct Task));
char *taskChoice = malloc(16);
struct Task selectedTask;


int choice;
if(scanf("%d", &choice) != 1){
    clear();
    printf("Invalid input.\n");
    clearBuffer();
    goto loop;
}

switch(choice){

    case 1: // View Tasks //
    viewTask:
        if(taskCount){
            tasks = getTasks("tasks.txt", taskCount);
            viewTasks(tasks, taskCount); // lists task
            clearBuffer();
            taskChoice = viewTaskChoice(taskCount); //prints out choices and prompts the user, returns the input to char *taskChoice

            if(isTaskId(taskChoice, taskCount)){
                selectedTask = selectTask(tasks, taskCount, taskChoice);
                printTask(selectedTask);
                printf("\n"); //adds newline after printing task details
            }

            else if(strcmp(taskChoice, "b") == 0){
                free(taskChoice); 
                free(tasks); 
                break;
            }

            else{
                printf("Please enter a valid input.\n");
                goto viewTask;
            }
        }
    printf("There are no tasks available.\n");
    break;
    
    case 2: 
    // printf("isDate: %d\n", isDate("11/01/25"));
    clear(); 
        if(addTask("tasks.txt") != 0){
        printf("Something went wrong please try again.\n");
        break;
    }
        break; 

    case 3: statistics("statistics.txt");
            break;

    case 4: //clear();
            search:
            taskCount = countTasks("tasks.txt");
            struct Task *allTasks = NULL;

            if(!taskCount){ // if no tasks on "tasks.txt"
                clear();
                printf("There are no tasks available.\n");
                printf("Hint: You can add tasks by choosing 2 in the menu!\n\n");
                break;
            }

            //else:
            allTasks = getTasks("tasks.txt", taskCount); 
            char *searchChoice = search(); // 1-3

                if(strcmp(searchChoice, "b") == 0){ //if "b" or "B"
                    free(searchChoice);
                    break;
                }
            
            //to avoid redefinition error on each cases;
            char *searchInput = malloc(16);
            int matchCount; // declare counter for matched tasks
            
            int key = searchKey(searchChoice); // 1~3 : 0
            struct Task *matches = malloc(taskCount * sizeof(struct Task)); //store matched tasks


            switch(key){
                case 1: // Name 
                    searchInput = getSearchInput("name"); //takes in user input for task name
                    if(!searchInput){printf("Please enter a valid input.\n");break;}
                    matchCount = 0; // number of matching tasks with searchInput
                    matches = getSimilarTasks(allTasks, taskCount, searchInput, "name", &matchCount);

                    if(!(matches && matchCount > 0)){
                        clear();
                        printf("No matches for <%s>.\n", searchInput);
                        free(searchInput);
                        goto search;
                    }

                    // else
                    clear(); //clears out terminal before listing matched tasks
                    viewTasks(matches, matchCount); // list out matched tasks


                    taskChoice = viewTaskChoice(matchCount);
                    if(strcmp(taskChoice, "b") == 0){ // if taskChoice == "b" "B"
                        free(searchInput);
                        clear();
                        goto search;
                        break;
                    }

                    else if(isTaskId(taskChoice, matchCount)){
                        selectedTask = selectTask(matches, matchCount, taskChoice);
                        printTask(selectedTask);
                    }

                    break;
                case 2: // Tag 
                    searchInput = getSearchInput("tag");
                    if(!searchInput){printf("Please enter a valid input.\n");}
                    matchCount = 0;
                    matches = getSimilarTasks(allTasks, taskCount, searchInput, "tag", &matchCount);

                    if(!(matches && matchCount > 0)){
                        clear();
                        printf("No matches for <%s>.\n", searchInput);
                        free(searchInput);
                        goto search;
                    }

                    //else
                    clear(); //clears out terminal before listing matched tasks
                    viewTasks(matches, matchCount);
                    taskChoice = viewTaskChoice(matchCount);

                    if(strcmp(taskChoice, "b") == 0){ // if taskChoice == "b" "B"
                        free(searchInput);
                        clear();
                        goto search;
                        break;
                    }

                    else if(isTaskId(taskChoice, matchCount)){
                        selectedTask = selectTask(matches, matchCount, taskChoice);
                        printTask(selectedTask);
                    }

                    free(matches); // free matches; array of structs;
                    free(searchInput);

                    break;


                case 3: // Deadline 
                    searchInput = getSearchInput("deadline");
                    if(!searchInput){printf("Please enter a valid input.\n");}
                    matchCount = 0;
                    matches = getSimilarTasks(allTasks, taskCount, searchInput, "deadline", &matchCount);

                    if(!(matches && matchCount > 0)){
                        clear();
                        printf("No matches for <%s>.\n", searchInput);
                        free(searchInput);
                        goto search;
                    }

                    //else
                    clear(); //clears out terminal before listing matched tasks
                    viewTasks(matches, matchCount);
                    taskChoice = viewTaskChoice(matchCount);

                    if(strcmp(taskChoice, "b") == 0){ // if taskChoice == "b" "B"
                        free(searchInput);
                        clear();
                        goto search;
                        break;
                    }

                    else if(isTaskId(taskChoice, matchCount)){
                        selectedTask = selectTask(matches, matchCount, taskChoice);
                        printTask(selectedTask);
                    }

                    free(matches); // free matches; array of structs;
                    free(searchInput);
                    
            break;
                }
                
        break;
    case 5: clear();
            printf("Thank you for using Smart Tasker.\n");
            continue_running = 'n';
            break;

    default: clear(); printf("Invalid input.\n"); break;
    }
}

return 0;
}