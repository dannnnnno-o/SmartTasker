#ifndef VIEW_H
#define VIEW_H
#include "../task.h"

void clear();

void landingPage();

void viewTasks(int taskCount, char *filename);

char viewTaskChoice();

void displayTask(char *filename);

void addTask(char *filename);

void history(char *filename);

void printTask(struct Task task);


#endif