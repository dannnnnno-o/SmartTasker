// view/view.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "view.h"

// --- Helper Display Functions ---

// The printStars function was removed to fix the display errors.

void printLine(char c, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", c);
    }
    printf("\n");
}

// --- Menu Functions ---

int displayLandingPage() {
    int choice;
    printf("\n\n");
    printLine('=', TASK_LIST_WIDTH);
    printf(" ||| SMART TASKER DASHBOARD |||\n");
    printLine('=', TASK_LIST_WIDTH);
    printf("1. View Tasks (Priority List)\n");
    printf("2. Add New Task\n");
    printf("3. History/Statistics\n");
    printf("0. Exit\n");
    printLine('-', TASK_LIST_WIDTH);
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); 
        return -1;
    }
    while (getchar() != '\n');
    return choice;
}

// --- Task List View (UPDATED FOR 1-5 NUMBER RATING) ---

void displayTasks(int page, int maxPerPage) {
    int start = (page - 1) * maxPerPage;
    int end = start + maxPerPage;
    if (end > taskCount) end = taskCount;
    int maxPages = (taskCount + maxPerPage - 1) / maxPerPage;
    if (maxPages == 0) maxPages = 1;

    printf("\n\n");
    printLine('=', TASK_LIST_WIDTH);
    printf(" ||| ACTIVE TASKS (Page %d / %d) |||\n", page, maxPages);
    printLine('=', TASK_LIST_WIDTH);
    
    // Header for the list
    printf("| No.| %-18s | %-9s | %-10s | %-4s |\n", "TITLE", "TAG", "DEADLINE", "IMP");
    printLine('-', TASK_LIST_WIDTH);

    if (taskCount == 0) {
        printf("|    | %-18s | %-9s | %-10s | %-4s |\n", "No tasks found. Add a new one!", " ", " ", " ");
        printLine('-', TASK_LIST_WIDTH);
    }

    // Display tasks 
    for (int i = start; i < end; i++) {
        Task *t = &taskList[i];
        
        printf("| %-2d | %-18.18s | %-9s | %-10s | ", 
            i - start + 1,        // No. (1-5 on the page)
            t->name,              // Title
            t->tag,               // Tag
            t->deadline           // Deadline
        );
        
        // Print 1-5 RATING instead of stars
        printf("%-4d |\n", t->difficulty); 
    }
    printLine('=', TASK_LIST_WIDTH);

    // Navigation Menu
    printf("Select task (1-%d) | 6. Next | 7. Prev | 8. Dashboard\n", end - start);
    printf("Enter choice: ");
}

// --- Task Detail View ---

void displayTaskDetails(int globalIndex) {
    Task *t = &taskList[globalIndex];
    
    printf("\n\n");
    printLine('_', 45);
    printf("| %-41.41s |\n", t->name);
    printf("| Tag: @%-15s Deadline: #%-13s |\n", t->tag, t->deadline);
    printLine('-', 45);
    
    printf("| DESCRIPTION:\n");
    char descCopy[MAX_DESC_LEN];
    strcpy(descCopy, t->description);
    char *line = strtok(descCopy, "\n");
    while (line != NULL) {
        printf("|    %-39.39s |\n", line);
        line = strtok(NULL, "\n");
    }
    printf("|                                             |\n");
    printf("| Importance: %d", t->difficulty); // Print number here
    // Align status to the right
    printf("%*s |\n", (int)(45 - 13 - 1 - strlen(t->completed ? "DONE" : "PENDING")), t->completed ? "DONE" : "PENDING");
    printLine('_', 45);
}

int displayTaskDetailsMenu() {
    int choice;
    printf("1. Mark as complete\n");
    printf("2. Delete Task\n");
    printf("3. Edit Task\n");
    printf("4. Exit (Back to List)\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return choice;
}

// --- Add/Edit Task Forms ---

void displayAddTaskForm() {
    Task newTask;
    
    printf("\n\n");
    printLine('=', 40);
    printf(" ||| ADD NEW TASK |||\n");
    printLine('=', 40);

    printf("Title (max %d chars): ", MAX_NAME_LEN - 1);
    fgets(newTask.name, MAX_NAME_LEN, stdin);
    newTask.name[strcspn(newTask.name, "\n")] = 0;

    do {
        printf("Tag (e.g., Work, Personal, School): ");
        fgets(newTask.tag, MAX_TAG_LEN, stdin);
        newTask.tag[strcspn(newTask.tag, "\n")] = 0;
    } while (strlen(newTask.tag) == 0);

    printf("Description (multiline OK, max %d chars): ", MAX_DESC_LEN - 1);
    fgets(newTask.description, MAX_DESC_LEN, stdin);
    newTask.description[strcspn(newTask.description, "\n")] = 0;

    do {
        printf("Deadline (e.g., 9/27/25): ");
        fgets(newTask.deadline, MAX_DEADLINE_LEN, stdin);
        newTask.deadline[strcspn(newTask.deadline, "\n")] = 0;
    } while (strlen(newTask.deadline) == 0);

    do {
        printf("Difficulty/Importance (1=unimportant, 5=super important): ");
        if (scanf("%d", &newTask.difficulty) != 1) {
            while (getchar() != '\n');
            newTask.difficulty = 0;
        }
        while (getchar() != '\n');
    } while (newTask.difficulty < 1 || newTask.difficulty > 5);

    if (addTask(newTask)) {
        printf("\n✅ Task '%s' added successfully!\n", newTask.name);
    } else {
        printf("\n❌ Failed to add task. List is full.\n");
    }
}

void displayEditTaskForm(int globalIndex) {
    Task *current = &taskList[globalIndex];
    Task updated = *current;

    printf("\n\n");
    printLine('=', 40);
    printf(" ||| EDIT TASK: %s |||\n", current->name);
    printLine('=', 40);
    printf("Leave field blank to keep current value.\n");

    printf("Title (Current: %s): ", current->name);
    char buffer[MAX_NAME_LEN];
    fgets(buffer, MAX_NAME_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strncpy(updated.name, buffer, MAX_NAME_LEN);

    printf("Tag (Current: %s): ", current->tag);
    fgets(buffer, MAX_TAG_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strncpy(updated.tag, buffer, MAX_TAG_LEN);

    printf("Description (Current: %s): ", current->description);
    fgets(buffer, MAX_DESC_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strncpy(updated.description, buffer, MAX_DESC_LEN);

    printf("Deadline (Current: %s): ", current->deadline);
    fgets(buffer, MAX_DEADLINE_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strncpy(updated.deadline, buffer, MAX_DEADLINE_LEN);

    int difficulty_input = 0;
    printf("Difficulty (Current: %d): Enter new (1-5) or 0 to keep: ", current->difficulty);
    if (scanf("%d", &difficulty_input) == 1 && difficulty_input >= 1 && difficulty_input <= 5) {
        updated.difficulty = difficulty_input;
    }
    while (getchar() != '\n');

    editTask(globalIndex, updated);
    printf("\n✅ Task '%s' updated successfully!\n", updated.name);
}