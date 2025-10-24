#include <stdio.h>
#include <string.h>

struct Task{
int key;
char *name;
char *tag;
char *deadline;
char *description;
char *difficulty;
};

void printTask(struct Task task, int length);

int main(){

struct Task task1;
task1.key = 1;
task1.name = "Cook Dinner";
task1.tag = "Personal";
task1.deadline = "10/23/25"; 
task1.description = "Prepare dinner by 8pm today";
task1.difficulty = "*";

struct Task tasks[] = {task1};
int taskLength = sizeof(task1)/sizeof(task1.name);

printTask(task1, taskLength);

return 0;
}

void printTask(struct Task task, int length){
printf("%s\n", task.name);
printf("%s\n", task.tag);
printf("%s\n", task.deadline);
printf("%s\n", task.description);
printf("%s\n", task.difficulty);
}