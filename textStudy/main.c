#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *file;
    char line[256]; // buffer to store each line 

    //open the file in read mode
    file = fopen("text.txt", "r");

    int number = 1;
    while(fgets(line, sizeof(line), file)){
        //printf("%s", line); //each iteration from while = single line from txt

        char *token = strtok(line, ",");
        int len = strlen(token); // 
        int limit1 = 16; // declares the limit of characters for each 1st iteration
        printf("%d. ", number); // prints the number for each line
        number = number + 1;
        for(int i = 1; i <= 3; i++){
            switch(i){
                case 1: /* Case 0 */
                    if (len == limit1){
                        printf("%s", token);
                    }
                    else if(len < limit1){
                        printf("%s", token);
                        for(int i = len; i <= limit1; i++){
                            printf(" ");
                        }
                    }
                    else if(len > limit1){
                        char tokenCopy[16 - 3];
                        strncpy(tokenCopy, token, 15 - 3);
                        printf("%s...", tokenCopy);
                    }
                break;  /* Case 1 */

                case 2: /* case 2 */
                printf("\t\t\t");
                if(len < limit1){
                    printf("%s", token);
                }
                // else if(len == limit1)
                break;
                        
                case 3: printf("%s\n", token);
            }


            //printf("%s ", token);
            token = strtok(NULL, ",");
        }
}

    fclose(file);    
    /*     printf("Tasks\n");
    //        name                        tag         deadline
    printf("1. Cook Dinner              @Personal    #9/17/25\n");
    printf("2. Submit Podcast           @School      #9/18/25\n");
    printf("3. Review for MMW           @School      #9/19/25\n");
    printf("4. Go Back\n");
     */
    return 0;
}