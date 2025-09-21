#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *file;
    char line[256]; // buffer to store each line 

    //open the file in read mode
    file = fopen("text.txt", "r");

    while(fgets(line, sizeof(line), file)){
        for(int i = 0; i < 3; i++){
            char *myPtr = strtok(line, ",");
            char *myPtrCpy;
            int ptrLen = strlen(myPtr);
            int above11;
            int under11;
            int just11;
            switch(i){
                case 1:
                    if(ptrLen > 11){above11 = 1;}
                    else if(ptrLen < 11){under11 = 1;}
                    else if(ptrLen == 11){just11 = 1;}
                    int key = (above11 << 2 | under11 << 1 | just11);  

                    switch(key){
                        case 1: printf("%s", myPtr);
                                break;
                        case 2:
                        printf("%s", myPtr);
                        for(int i = ptrLen; i < 11; i++){
                        printf(" ");
                        break;
                        }
                        case 4: strncpy(myPtrCpy, myPtr, 10);
                        printf("%s", myPtr);
                        break;
                    } 
                        break;

                case 2: printf("@%s", myPtr);
            }
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