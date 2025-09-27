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
        int limit = 16; // declares the limit of characters for each 1st iteration
        printf("%d. ", number); // prints the number for each line
        number = number + 1;
        for(int i = 1; i <= 3; i++){
            int len = strlen(token); // 
            switch(i){
                case 1: /* Case 1 */
                    if (len == limit){
                        printf("%s", token);
                    }
                    else if(len < limit){
                        printf("%s", token);
                        for(int i = len; i <= limit; i++){
                            printf(" ");
                        }
                    }
                    else if(len > limit){
                        char tokenCopy[16 - 3];
                        strncpy(tokenCopy, token, 15 - 3);
                        printf("%s...", tokenCopy);
                    }
                break;  /* Case 1 */

                case 2: /* case 2 */
                printf("\t\t\t");
                if(len < limit){
                    printf("#%s", token);
                    for(int i = len; i < limit; i++){
                        printf(" ");
                    }
                }
                // else if(len == limit1)
                break;
                        
                case 3: printf("| %s |\n", token);
            }


            //printf("%s ", token);
            token = strtok(NULL, ",");
        }
}

/*     fclose(file);    
         printf("Tasks\n");
    //        name                        tag         deadline
    printf("1. Cook Dinner              @Personal    #9/17/25\n");
    printf("2. Submit Podcast           @School      #9/18/25\n");
    printf("3. Review for MMW           @School      #9/19/25\n");
    printf("4. Cook Dinner              @Personal    #9/17/25\n");
    printf("5. Submit Podcast           @School      #9/18/25\n");
    printf("6. Review for MMW           @School      #9/19/25\n");
    printf("7. Cook Dinner              @Personal    #9/17/25\n");
    printf("8. Previous\n");
    printf("9. Next\n");
    printf("0. Go Back\n"); */

     
    printf(" ____________________________________\n");
    printf("| Cook Dinner             #Personal  |\n");
    printf("|                                    |\n");
    printf("|    Prepare three course meal       |\n");
    printf("|    for the family by 8pm           |\n");
    printf("|                                    |\n");
    printf("|  *****                      9/27/25|\n");
    printf("|____________________________________|\n");
    /*
 ____________________________________ 
| Cook Dinner             #Personal  |
|                                    |
|    Prepare three course meal       |
|    for the family by 8pm           |
|                                    |
|  *****                      9/27/25|
|____________________________________|
    */

    printf("1. Mark as complete\n");
    printf("2. Discard Task\n");
    printf("3. Next\n");
    printf("4. Previous\n");
    printf("5. Go Back\n");
    
    printf("What do you want to do?: ");

    return 0;
}