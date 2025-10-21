#ifndef CTRL_H
#define CTRL_H

int no_file(char *filename);

void taskOverview(char *filename);

int landingChoice();

void make_file(char *filename);

void nameFormat(char *text, int len);

void tagFormat(char *tag, int len);

void deadlineFormat(char *deadline);

int countTasks(char *filename);

void selectTask(char* taskName);

#endif