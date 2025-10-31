#ifndef VIEW_H
#define VIEW_H
#include "../task.h"

void clear();

void landingPage();

struct Task *viewTasks(int taskCount, char *filename);

char *viewTaskChoice(int taskCount);

void displayTask(char *filename);

int addTask(char *filename); // returns 0 if no probs

void statistics(char *filename);

char *search(/* name, tag, or date */);

void printTask(struct Task task);


#endif