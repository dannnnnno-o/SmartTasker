// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include project headers
#include "ctrl/ctrl.h"
#include "view/view.h"

// --- Prototypes for functions defined later in this file ---
void handleTaskDetail(int globalIndex);
void handleViewTasks();
void handleAddTask(); 

// --- Main Application Loop Functions ---

void handleViewTasks() {
    int currentPage = 1;
    const int TASKS_PER_PAGE = 5;
    int choice = 0;
    int maxPages;
    
    loadTasksFromFile(); 
    sortTasksByPriority();

    do {
        system("cls"); 

        maxPages = (taskCount + TASKS_PER_PAGE - 1) / TASKS_PER_PAGE;
        if (maxPages == 0) maxPages = 1;

        if (currentPage < 1) currentPage = 1;
        if (currentPage > maxPages) currentPage = maxPages;

        displayTasks(currentPage, TASKS_PER_PAGE);

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while (getchar() != '\n');

        if (choice >= 1 && choice <= TASKS_PER_PAGE) {
            int localIndex = choice; 
            int globalIndex = (currentPage - 1) * TASKS_PER_PAGE + localIndex - 1;
            
            if (globalIndex < taskCount) {
                handleTaskDetail(globalIndex);
                loadTasksFromFile();
                sortTasksByPriority();
            } else {
                printf("\nInvalid task number selected. Press Enter to continue...\n");
                getchar();
            }
            choice = 1;
            
        } else {
            switch (choice) {
                case 6: // Next Page
                    if (currentPage < maxPages) currentPage++;
                    break;
                case 7: // Previous Page
                    if (currentPage > 1) currentPage--;
                    break;
                case 8: // Return to Dashboard
                    return;
                default:
                    printf("\nInvalid choice. Please try again. Press Enter...\n");
                    getchar();
            }
        }
    } while (choice != 8);
}

void handleTaskDetail(int globalIndex) {
    int detailChoice = 0;
    do {
        system("cls");
        displayTaskDetails(globalIndex);
        detailChoice = displayTaskDetailsMenu();

        switch (detailChoice) {
            case 1: // Mark as complete
                markTaskComplete(globalIndex);
                printf("\nTask marked as COMPLETE. Press Enter...\n");
                getchar();
                return;
            case 2: // Delete Task
                deleteTask(globalIndex);
                printf("\nTask DELETED. Press Enter...\n");
                getchar();
                return;
            case 3: // Edit Task
                displayEditTaskForm(globalIndex);
                break;
            case 4: // Exit (Back to List)
                return;
            default:
                printf("\nInvalid choice. Press Enter...\n");
                getchar();
        }
    } while (detailChoice != 4);
}

void handleAddTask() {
    system("cls");
    displayAddTaskForm();
    printf("\nPress Enter to return to Dashboard...\n");
    getchar();
}

// --- Main Function ---

int main() {
    int choice;

    loadTasksFromFile(); 

    do {
        system("cls");
        choice = displayLandingPage();

        switch (choice) {
            case 1: // View Tasks
                handleViewTasks();
                break;
            case 2: // Add New Task
                handleAddTask();
                break;
            case 3: // History/Statistics
                printf("\nHistory/Statistics feature coming soon! Press Enter...\n");
                getchar();
                break;
            case 0: // Exit
                printf("\nExiting Smart Tasker. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again. Press Enter...\n");
                getchar();
        }
    } while (choice != 0);

    return 0;
}