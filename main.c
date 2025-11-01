#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctrl/ctrl.h"
#include "view/view.h"
#include "task.h"



int main(){
char continue_running = 'y';
while(continue_running == 'y'){
    // clear();
    landingPage();

    if(no_file("tasks.txt"))
    {make_file("tasks.txt");}

    
    int taskCount = countTasks("tasks.txt");
    struct Task *tasks = malloc(taskCount * sizeof(struct Task));

    int choice;
    scanf("%d", &choice);
    switch(choice){

        case 1: // View Tasks //
            if(taskCount){
                tasks = getTasks("tasks.txt", taskCount);
                viewTasks(tasks, taskCount); // lists task
                
                char *taskChoice = viewTaskChoice(taskCount); //prints out choices and prompts the user, returns the input to char *taskChoice

                if(strcmp(taskChoice, "b") == 0)
                {free(taskChoice); free(tasks); break;}

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

        case 4: //clear();
                taskCount = countTasks("tasks.txt");
                struct Task *allTasks = NULL;
                if(taskCount > 0){
                    allTasks = getTasks("tasks.txt", taskCount);
                    if(!allTasks){
                        printf("There are no available tasks.\n"); break;
                    }
                }


                char *searchChoice = search();
                 if(strcmp(searchChoice, "b") == 0)
                    {free(searchChoice); break;}
                //to avoid redefinition error on each cases;
                char *searchInput = malloc(16);
                int matchCount;
                
                int key = searchKey(searchChoice); // B || 1~3;
                // printf("key: %d\n", key);
                taskCount = countTasks("tasks.txt");

                struct Task *matches = malloc(taskCount * sizeof(struct Task));

                // printf("taskCount: %d\n", taskCount);
                if(!taskCount){free(searchChoice); break;}
                switch(key){
                    case 1: // Name 
                        searchInput = getSearchInput(); //takes in user input for tas
                        if(!searchInput){printf("Please enter a valid input.\n");break;}
                        matchCount = 0;
                            matches = getSimilarTasks(allTasks, taskCount, searchInput, "name", &matchCount);

                        if(matches && matchCount > 0){
                            viewTasks(matches, matchCount); // list out matched tasks
                            free(matches); // free matches; array of structs;
                        } 

                        else{printf("No matches for <%s>.", searchInput);} // matches && matchCount <= 0; 
                        free(searchInput);
                        break;
                    case 2: // Tag 
                        searchInput = getSearchInput();
                        if(!searchInput){printf("Please enter a valid input.\n");}
                        matchCount = 0;
                        matches = getSimilarTasks(allTasks, taskCount, searchInput, "tag", &matchCount);

                        if(matches && matchCount > 0){
                            viewTasks(matches, matchCount);
                            free(matches);
                        }
                        else{printf("No matches for <%s>.", searchInput);}
                        free(searchInput);
                        break;

                    case 3: // Deadline 
                                                searchInput = getSearchInput();
                        if(!searchInput){printf("Please enter a valid input.\n");}
                        matchCount = 0;
                        matches = getSimilarTasks(allTasks, taskCount, searchInput, "deadline", &matchCount);

                        if(matches && matchCount > 0){
                            viewTasks(matches, matchCount);
                            free(matches);
                        }
                        else{printf("No matches for <%s>.", searchInput);}
                        free(searchInput);
                        break;

                    break; 
               }


                break;

        case 5: clear();
                printf("Thank you for using Smart Tasker.\n");
                continue_running = 'n';
                break;
        default: break;
    }

}

    return 0;
}