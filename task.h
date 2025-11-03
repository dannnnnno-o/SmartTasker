#ifndef TASK_H
#define TASK_H

struct Task {
    char *id;
    char *name;
    char *tag;
    char *deadline;
    char *description;
    char *difficulty;
    float finalRating;
};

#endif