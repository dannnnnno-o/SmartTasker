#ifndef VIEW_H
#define VIEW_H
#include "../task.h"

void clear();

void landingPage();

void viewTasks(struct Task *task, int taskCount);

char *viewTaskChoice(int taskCount);

void displayTask(char *filename);

int addTask(char *filename); // returns 0 if no probs

void statistics(char *filename);

char *search(/* name, tag, or date */);
char *getSearchInput();

void printTask(struct Task task);


#endif