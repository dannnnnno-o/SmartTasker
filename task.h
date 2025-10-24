#ifndef TASK_H
#define TASK_H

struct Task {
    char id;
    char name[50];
    char tag[30];
    char deadline[15];
    char description[255];
};

#endif