#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *file;
    char line[256]; // buffer to store each line 

    //open the file in read mode
    file = fopen("text.txt", "r");

    while(fgets(line, sizeof(line), file)){
        char *currentLine = line;
        char *myPtr = strtok(line, ",");
        while(myPtr != NULL){
            printf("%s\n", myPtr);
            myPtr = strtok(NULL, ",");
        }
    }

    fclose(file);
    
    /*     printf("Tasks\n");
    //        name                     tag           deadline
    printf("1. Cook Dinner              @Personal    #9/17/25\n");
    printf("2. Submit Podcast           @School      #9/18/25\n");
    printf("3. Review for MMW           @School      #9/19/25\n");
    printf("4. Go Back\n");
     */
    return 0;
}