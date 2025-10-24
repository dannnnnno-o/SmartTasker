// ctrl/ctrl.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctrl.h" // Include its own header for prototypes

// --- Global Variables Definition ---
Task taskList[MAX_TASKS];
int taskCount = 0;

// --- Helper Functions ---

void calculatePriority(Task *t) {
    t->priority = t->difficulty; 
}

int compareTasks(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskB->priority - taskA->priority;
}

// --- File I/O Functions ---

void saveTasksToFile() {
    FILE *file = fopen("text.txt", "w"); // Overwrites file
    if (file == NULL) {
        perror("Error opening text.txt for writing");
        return;
    }

    sortTasksByPriority();

    for (int i = 0; i < taskCount; i++) {
        // FORMAT: Name|Deadline|Tag|Description|Difficulty|Priority|CompletedStatus
        fprintf(file, "%s|%s|%s|%s|%d|%d|%d\n", // Using '|' as separator
            taskList[i].name, 
            taskList[i].deadline, 
            taskList[i].tag, 
            taskList[i].description, 
            taskList[i].difficulty,
            taskList[i].priority,
            taskList[i].completed);
    }
    fclose(file);
}

void loadTasksFromFile() {
    FILE *file = fopen("text.txt", "r");
    char line[512];
    taskCount = 0;

    if (file == NULL) {
        return;
    }

    while (fgets(line, sizeof(line), file) && taskCount < MAX_TASKS) {
        char *token;
        Task tempTask;

        // Load 7 fields separated by '|'
        token = strtok(line, "|"); if (token) strncpy(tempTask.name, token, MAX_NAME_LEN - 1);
        token = strtok(NULL, "|"); if (token) strncpy(tempTask.deadline, token, MAX_DEADLINE_LEN - 1);
        token = strtok(NULL, "|"); if (token) strncpy(tempTask.tag, token, MAX_TAG_LEN - 1);
        token = strtok(NULL, "|"); if (token) strncpy(tempTask.description, token, MAX_DESC_LEN - 1);
        token = strtok(NULL, "|"); if (token) tempTask.difficulty = atoi(token);
        token = strtok(NULL, "|"); if (token) tempTask.priority = atoi(token);
        token = strtok(NULL, "|"); if (token) tempTask.completed = atoi(token);

        taskList[taskCount] = tempTask;
        taskCount++;
    }
    fclose(file);
}

// --- Task Management Functions ---

int addTask(Task newTask) {
    if (taskCount < MAX_TASKS) {
        calculatePriority(&newTask);
        newTask.completed = 0;
        taskList[taskCount] = newTask; 
        taskCount++;
        saveTasksToFile();
        return 1;
    }
    return 0;
}

void deleteTask(int index) {
    if (index >= 0 && index < taskCount) {
        for (int i = index; i < taskCount - 1; i++) {
            taskList[i] = taskList[i + 1];
        }
        taskCount--;
        saveTasksToFile();
    }
}

void editTask(int index, Task updatedTask) {
    if (index >= 0 && index < taskCount) {
        calculatePriority(&updatedTask);
        taskList[index] = updatedTask;
        saveTasksToFile();
    }
}

void markTaskComplete(int index) {
    if (index >= 0 && index < taskCount) {
        taskList[index].completed = 1;
        saveTasksToFile();
    }
}

// --- Priority/Sorting Functions ---

void sortTasksByPriority() {
    qsort(taskList, taskCount, sizeof(Task), compareTasks);
}