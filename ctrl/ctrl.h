#ifndef CTRL_H
#define CTRL_H

int no_file(char *filename);
void make_file(char *filename);
int countTasks(char *filename);
int isValidNumber(char *str);

/* 1. View Tasks */

void nameFormat(char *text, int len);
void tagFormat(char *tag, int len);
void deadlineFormat(char *deadline);
void difficultyFormat(char *difficulty);
void clearBuffer();
char *toStr(int x);
int isTaskId(char *taskId, int taskCount);
struct Task selectTask(struct Task *taskList, int taskCount, char *taskId);
char *scanBack(char *option);
int searchKey(char* option);
struct Task *getTasks(char *filename, int taskCount);
struct Task *getSimilarTasks(struct Task *tasks, int taskCount, char *input, char* mode, int *outMatchCount);
int isDate(char *input);

/* END OF 1. View Tasks */

#endif