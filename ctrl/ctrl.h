// ctrl/ctrl.h

#ifndef CTRL_H
#define CTRL_H

#define MAX_NAME_LEN 64
#define MAX_DEADLINE_LEN 16
#define MAX_TAG_LEN 16
#define MAX_DESC_LEN 256

// --- Core Data Structure ---
typedef struct {
    char name[MAX_NAME_LEN];          // Title of the task
    char deadline[MAX_DEADLINE_LEN];  // Date (e.g., 9/27/25)
    char tag[MAX_TAG_LEN];            // Work, School, Personal
    char description[MAX_DESC_LEN];   // Detailed description
    int difficulty;                   // 1-5 (user input)
    int priority;                     // Calculated Priority 
    int completed;                    // 0 (Pending), 1 (Done)
} Task;

// --- Global Task List ---
#define MAX_TASKS 100 
extern Task taskList[MAX_TASKS];
extern int taskCount;

// --- Control Prototypes ---

// File I/O
void loadTasksFromFile();
void saveTasksToFile();

// Task Management
int addTask(Task newTask);
void deleteTask(int index);
void editTask(int index, Task updatedTask);
void markTaskComplete(int index);

// Priority/Sorting
void calculateAllPriorities();
void sortTasksByPriority();

#endif // CTRL_H