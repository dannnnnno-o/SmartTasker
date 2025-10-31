#ifndef VIEW_H
#define VIEW_H
#include "../task.h"

void clear();

void landingPage();

struct Task *viewTasks(int taskCount, char *filename);

char *viewTaskChoice(int taskCount);

void displayTask(char *filename);

void addTask(char *filename);

void history(char *filename);

void printTask(struct Task task);


#endif