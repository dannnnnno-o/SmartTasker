// view/view.h

#ifndef VIEW_H
#define VIEW_H

#include "../ctrl/ctrl.h"

// Define a constant for the width of the task list display
#define TASK_LIST_WIDTH 60 

// --- Helper Display Functions ---
// printStars REMOVED, as it caused errors
void printLine(char c, int len);

// --- Menu Functions ---
int displayLandingPage();

// --- Task Management Display ---
void displayAddTaskForm();
void displayTaskDetails(int globalIndex);
int displayTaskDetailsMenu();
void displayEditTaskForm(int globalIndex);

// --- Task List View (The main feature) ---
void displayTasks(int page, int maxPerPage);

#endif // VIEW_H