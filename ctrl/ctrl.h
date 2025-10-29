#ifndef CTRL_H
#define CTRL_H

int no_file(char *filename);
void make_file(char *filename);
int countTasks(char *filename);

/* 1. View Tasks */

void nameFormat(char *text, int len);
void tagFormat(char *tag, int len);
void deadlineFormat(char *deadline);
void difficultyFormat(char *difficulty);
void clearBuffer();
char *toStr(int x);

/* END OF 1. View Tasks */

#endif