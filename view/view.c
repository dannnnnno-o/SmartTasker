#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#include "../task.h"
#define limit 16 // UI text overflow limit
#define taskAttributes 6
#define taskLimit 9

void clear(){system("cls");}
void newLine(){printf("\n");}

void landingPage(){
    printf("Welcome to Smart Tasker.\n");
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. Statistics\n");
    printf("4. Search\n");
    printf("5. Exit\n");
    
    printf("\nWhat would you like to do?: ");
}

void printTask(struct Task task){

    const char *name = task.name ? task.name : "";
    const char *tag = task.tag ? task.tag : "";
    const char *desc = task.description ? task.description : "";
    const char *diff = task.difficulty ? task.difficulty : "";
    const char *deadline = task.deadline ? task.deadline : "";

    // helper: safe strlen and min
    #define MAX(a,b) ((a) > (b) ? (a) : (b))
    #define MAX3(a,b,c) (MAX(MAX((a),(b)), (c)))
    #ifndef MIN
    #define MIN(a,b) ((a) < (b) ? (a) : (b))
    #endif



    // Make local mutable copies and trim trailing newlines (fields read from file may include '\n')
    char nameBuf[256]; strncpy(nameBuf, name, sizeof(nameBuf)-1); nameBuf[sizeof(nameBuf)-1] = '\0';
    char tagBuf[128]; strncpy(tagBuf, tag, sizeof(tagBuf)-1); tagBuf[sizeof(tagBuf)-1] = '\0';
    char diffBuf[64]; strncpy(diffBuf, diff, sizeof(diffBuf)-1); diffBuf[sizeof(diffBuf)-1] = '\0';
    char deadlineBuf[64]; strncpy(deadlineBuf, deadline, sizeof(deadlineBuf)-1); deadlineBuf[sizeof(deadlineBuf)-1] = '\0';

    // trim trailing whitespace/newline helper (manual below)
    // trim fields
    // fallback manual trim in case the lambda cast isn't supported by C compiler
    char *tmp;
    tmp = nameBuf; while(strlen(tmp) && (tmp[strlen(tmp)-1]=='\n' || tmp[strlen(tmp)-1]=='\r' || tmp[strlen(tmp)-1]==' ' || tmp[strlen(tmp)-1]=='\t')) tmp[strlen(tmp)-1]='\0';
    tmp = tagBuf; while(strlen(tmp) && (tmp[strlen(tmp)-1]=='\n' || tmp[strlen(tmp)-1]=='\r' || tmp[strlen(tmp)-1]==' ' || tmp[strlen(tmp)-1]=='\t')) tmp[strlen(tmp)-1]='\0';
    tmp = diffBuf; while(strlen(tmp) && (tmp[strlen(tmp)-1]=='\n' || tmp[strlen(tmp)-1]=='\r' || tmp[strlen(tmp)-1]==' ' || tmp[strlen(tmp)-1]=='\t')) tmp[strlen(tmp)-1]='\0';
    tmp = deadlineBuf; while(strlen(tmp) && (tmp[strlen(tmp)-1]=='\n' || tmp[strlen(tmp)-1]=='\r' || tmp[strlen(tmp)-1]==' ' || tmp[strlen(tmp)-1]=='\t')) tmp[strlen(tmp)-1]='\0';

    // compute minimal content width based on pieces
    int nameLen = (int)strlen(nameBuf);
    int tagLen = (int)strlen(tagBuf);
    int tagWithAtLen = tagLen + (tagLen>0 ? 1 : 0); // include '@' when tag present
    // bottom length should account for the "/10" we will append to difficulty
    int bottomLen = (int)(strlen(diffBuf) + 3 + strlen(deadlineBuf)); // "diff/10 deadline"

    // compute a starting content width (prefer wider cards)
    // start from a reasonable minimum so cards feel rectangular rather than square
    int contentWidth = MAX3(nameLen + 2 + tagWithAtLen, bottomLen, 32);

    // split description into words for wrapping
    // make a mutable copy
    char *descCopy = strdup(desc);
    if(!descCopy) return; // oom -> bail

    // function to wrap description into lines with given max width
    #define MAX_LINES 200
    char *lines[MAX_LINES];
    int lineCount = 0;

    auto_wrap: ; // label for simple rewrap loop

    for(int i=0;i<MAX_LINES;i++) lines[i] = NULL;

    // greedy word wrap
    // reserve a few chars of indent inside the content area for description
    // (increase indent to give description horizontal breathing room)
    int indent = 2;
    /* add a right-side padding to balance the visual gap on the right */
    int rightPad = 4;
    int maxLine = contentWidth - indent - rightPad;
    if(maxLine < 1) maxLine = 1;
    char *token = strtok(descCopy, " \t\n");
    char current[1024] = "";
    while(token){
        if((int)strlen(token) > maxLine){
            // expand width to accommodate a single long word (account for indent and right padding)
            contentWidth = (int)strlen(token) + indent + rightPad;
            free(descCopy);
            descCopy = strdup(desc);
            if(!descCopy) return;
            goto auto_wrap; // restart wrapping with larger width
        }

        if(strlen(current) == 0){
            strcpy(current, token);
        } else {
            if((int)(strlen(current) + 1 + strlen(token)) <= maxLine){
                strcat(current, " ");
                strcat(current, token);
            } else {
                lines[lineCount++] = strdup(current);
                current[0] = '\0';
                strcpy(current, token);
            }
        }

        token = strtok(NULL, " \t\n");
    }
    if(strlen(current) > 0){
        lines[lineCount++] = strdup(current);
    }

    // header needs one line; footer needs one line; total minimal height
    int minimalHeight = 1 /*header*/ + 1 /*gap*/ + (lineCount>0?lineCount:1) + 1 /*gap*/ + 1 /*footer*/;

    // enforce a simple aspect: prefer a wider rectangle (width ~= 3 * height)
    int desiredWidth = contentWidth;
    int desiredHeight = minimalHeight;
    int minWidth = 40; // minimum visual width for cards (slightly increased)
    // prefer a width:height ratio of 5:2 (~2.5)
    int preferred = (desiredHeight * 5) / 2; /* integer arithmetic */
    if(desiredWidth < preferred) desiredWidth = preferred;
    if(desiredWidth < minWidth) desiredWidth = minWidth;
    // limit to a reasonable size for terminal width
    if(desiredWidth > 75) desiredWidth = 75;

    // if desiredWidth increased, rewrap description using new width
    if(desiredWidth != contentWidth){
        contentWidth = desiredWidth;
        free(descCopy);
        descCopy = strdup(desc);
        for(int i=0;i<lineCount;i++){ free(lines[i]); lines[i]=NULL; }
        lineCount = 0;
        goto auto_wrap;
    }

    // box drawing
    int inner = contentWidth;
    // top border
    printf("+"); for(int i=0;i<inner+2;i++) putchar('-'); printf("+\n");

    // header: build a content line of exactly 'inner' characters between the two padding spaces.
    // We'll place name left and @tag right; if they don't fit, put a prefix of name on the
    // header line and the remainder on the next line.
    int fieldWidth = inner; // characters available for content between the two padding spaces
    // prepare tag string with '@' if present
    char tagWithAt[128] = "";
    if(tagLen > 0){
        /* build '@' + tag safely without relying on snprintf truncation behavior */
        size_t cap = sizeof(tagWithAt) - 1; /* reserve NUL */
        tagWithAt[0] = '@';
        if(cap > 1){
            /* copy at most cap-1 bytes of tagBuf into tagWithAt+1 */
            strncpy(tagWithAt + 1, tagBuf, cap - 1);
            tagWithAt[cap] = '\0';
        } else {
            tagWithAt[1] = '\0';
        }
    }
    int tagTotalLen = (int)strlen(tagWithAt);

    // create header content buffer
    char headerContent[1024];
    for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
    headerContent[fieldWidth] = '\0';

    if(tagTotalLen > 0 && nameLen + 1 + tagTotalLen <= fieldWidth){
        // fits on one line: place name at start and tag right-aligned
        memcpy(headerContent, nameBuf, MIN(nameLen, fieldWidth));
        int tagPos = fieldWidth - tagTotalLen;
        memcpy(headerContent + tagPos, tagWithAt, tagTotalLen);
        printf("| %s |", headerContent);
        printf("\n");
    } else if(tagTotalLen > 0){
        // need to split name: allowed chars on first line before tag
        int allowed = fieldWidth - tagTotalLen - 1; // leave one space between name and tag
        if(allowed < 1) allowed = 1;
        // build first line
        for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
        memcpy(headerContent, nameBuf, MIN(allowed, fieldWidth));
        int tagPos = fieldWidth - tagTotalLen;
        memcpy(headerContent + tagPos, tagWithAt, tagTotalLen);
        headerContent[fieldWidth] = '\0';
        printf("| %s |\n", headerContent);

        // build second line with remainder of name
        const char *rem = nameBuf + allowed;
        for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
        int remLen = (int)strlen(rem);
        if(remLen > 0){
            if(remLen > fieldWidth){
                // truncate with ellipsis
                int take = fieldWidth - 3;
                if(take < 0) take = 0;
                memcpy(headerContent, rem, take);
                if(fieldWidth >= 3) memcpy(headerContent + take, "...", 3);
            } else {
                memcpy(headerContent, rem, remLen);
            }
        }
        headerContent[fieldWidth] = '\0';
        printf("| %s |\n", headerContent);
    } else {
        // no tag: print name left aligned
        for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
        if(nameLen > fieldWidth){
            int take = fieldWidth - 3; if(take < 0) take = 0;
            memcpy(headerContent, nameBuf, take);
            if(fieldWidth >= 3) memcpy(headerContent + take, "...", 3);
        } else {
            memcpy(headerContent, nameBuf, nameLen);
        }
        headerContent[fieldWidth] = '\0';
        printf("| %s |\n", headerContent);
    }

    // blank line between header and description for visual separation
    for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
    headerContent[fieldWidth] = '\0';
    printf("| %s |\n", headerContent);

    // description lines (left aligned) with indent (build into headerContent buffer)
    for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
    headerContent[fieldWidth] = '\0';
    if(lineCount == 0){
        // empty description -> print an empty content row
        printf("| %s |\n", headerContent);
    } else {
        for(int i = 0; i < lineCount; ++i){
            char *ln = lines[i];
            int lnlen = (int)strlen(ln);
            // fill buffer with spaces
            for(int j=0;j<fieldWidth;j++) headerContent[j] = ' ';
            // copy with indent
            int copyLen = lnlen;
            int maxCopy = fieldWidth - indent - rightPad; if(maxCopy < 0) maxCopy = 0;
            if(copyLen > maxCopy) copyLen = maxCopy;
            if(copyLen > 0) memcpy(headerContent + indent, ln, copyLen);
            // if truncated, add ellipsis
            if(lnlen > copyLen && copyLen >= 3){
                headerContent[indent + copyLen - 3] = '.';
                headerContent[indent + copyLen - 2] = '.';
                headerContent[indent + copyLen - 1] = '.';
            }
            headerContent[fieldWidth] = '\0';
            printf("| %s |\n", headerContent);
        }
    }

    // blank line before footer (empty content row)
    for(int i=0;i<fieldWidth;i++) headerContent[i] = ' ';
    headerContent[fieldWidth] = '\0';
    printf("| %s |\n", headerContent);

    // footer: difficulty/10 on the left, deadline on the right
    char diffDisplay[64];
    if(strlen(diffBuf) == 0) {
        diffDisplay[0] = '\0';
    } else {
        /* Safely build diffDisplay = truncated(diffBuf) + "/10" */
        size_t cap = sizeof(diffDisplay);
        /* reserve 3 bytes for "/10" and 1 for NUL */
        size_t maxCopy = (cap > 4) ? cap - 4 : 0;
        if(maxCopy > 0){
            strncpy(diffDisplay, diffBuf, maxCopy);
            diffDisplay[maxCopy] = '\0';
            /* append "/10" */
            strncat(diffDisplay, "/10", cap - strlen(diffDisplay) - 1);
        } else {
            /* not enough room for diff, just store empty */
            diffDisplay[0] = '\0';
        }
    }
    int diffLen2 = (int)strlen(diffDisplay);
    int dlLen = (int)strlen(deadlineBuf);

    // If difficulty + deadline don't fit, truncate the difficulty (keep deadline visible)
    if(diffLen2 + dlLen > inner){
        int allowed = inner - dlLen - 1; // leave at least one space between
        if(allowed < 0) allowed = 0;
        if(allowed < diffLen2){
                if(allowed > 3){
                    /* truncate with ellipsis safely into diffDisplay */
                    size_t take = (size_t)allowed - 3;
                    if(take > sizeof(diffDisplay)-1) take = sizeof(diffDisplay)-1;
                    /* copy prefix */
                    memmove(diffDisplay, diffDisplay, take);
                    /* append ellipsis */
                    if(take + 3 <= sizeof(diffDisplay)-1){
                        memcpy(diffDisplay + take, "...", 3);
                        diffDisplay[take + 3] = '\0';
                    } else {
                        /* fallback - ensure NUL */
                        diffDisplay[sizeof(diffDisplay)-1] = '\0';
                    }
                } else {
                    /* not enough room for ellipsis, just truncate */
                    size_t take = (size_t)allowed;
                    if(take > sizeof(diffDisplay)-1) take = sizeof(diffDisplay)-1;
                    diffDisplay[take] = '\0';
                }
            diffLen2 = (int)strlen(diffDisplay);
        }
    }

    int spaceFooter = inner - diffLen2 - dlLen;
    if(spaceFooter < 1) spaceFooter = 1;
    printf("| ");
    // difficulty
    printf("%s", diffDisplay);
    for(int s = 0; s < spaceFooter; ++s) putchar(' ');
    // deadline
    printf("%s ", deadlineBuf);
    printf("|\n");

    // bottom border
    printf("+"); for(int i=0;i<inner+2;i++) putchar('-'); printf("+\n");

    // cleanup
    for(int i=0;i<lineCount;i++) free(lines[i]);
    free(descCopy);

    #undef MIN
    #undef MAX_LINES
}

void viewTasks(struct Task *tasks, int taskCount){
    printf("    Name                                  Tag              Deadline    Difficulty(/10)\n");
    printf("-------------------------------------------------------------------------------------\n");
    for(int i = 0; i < taskCount; i++){
        for(int j = 0; j < taskAttributes; j++){
            switch(j){
                case 0: printf("%s. ", tasks[i].id); break;
                case 1: nameFormat(tasks[i].name, strlen(tasks[i].name)); break;
                case 2: tagFormat(tasks[i].tag, strlen(tasks[i].tag)); break;
                case 3: deadlineFormat(tasks[i].deadline); break;
                case 4: break;
                case 5: difficultyFormat(tasks[i].difficulty); break;
            }
        }
    }
    printf("\n\n");
}

char *viewTaskChoice(int taskCount){
    if(taskCount == 1) {
        printf("B = Back, %d = Task Detail\n", taskCount);
    } else if(taskCount > 1) {
        printf("B = Back, 1-%d = Task Detail.\n", taskCount);
    }
    
    printf("What do you want to do?: ");
    
    char buffer[16];
    if(fgets(buffer, sizeof(buffer), stdin) == NULL){return NULL;}
    
    buffer[strcspn(buffer, "\r\n")] = '\0';
    if(scanBack(buffer)) {
        return scanBack(buffer);
    }
    
    return strdup(buffer);
}


int addTask(char *filename){
    clearBuffer(); 

    printf("Add Task\n");

    if(no_file(filename)){
        make_file(filename);
    }

    FILE *file = fopen(filename, "a");

    struct Task task = {0};
    char strBuffer[256];

    task.id = "#";
    
    printf("Input task name: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.name = strdup(strBuffer);

    printf("Input task tag: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.tag = strdup(strBuffer);  

    printf("Input task deadline: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.deadline = strdup(strBuffer);   

    printf("Input task description: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.description = strdup(strBuffer); 

    printf("Input task difficulty: ");
    fgets(strBuffer, sizeof(strBuffer), stdin);
    strBuffer[strcspn(strBuffer, "\r\n")] = '\0';
    task.difficulty = strdup(strBuffer); 

    char confirmBuffer[256];
    while(1){
    printf("Are you sure you want to add this task? (y/n): ");
    if(fgets(confirmBuffer, sizeof(confirmBuffer), stdin) == NULL){
        printf("No input received. Cancelling.\n");
        fclose(file);
        return 0;
    }

    confirmBuffer[strcspn(confirmBuffer, "\r\n")] = '\0';

    if(confirmBuffer[0] == 'y' || confirmBuffer[0] == 'Y'){
        fprintf(file, "\n%s|%s|%s|%s|%s|%s", task.id, task.name, task.tag, task.deadline, task.description, task.difficulty);
        fclose(file);
        clear();
        printf("Task was added successfully.\n\n");
        break;
    }
    else if(confirmBuffer[0] == 'n' || confirmBuffer[0] == 'N'){
        clear();
        printf("Task was not added.\n\n");
        fclose(file);
        break;
    }
    else{
        clear();
        printf("Add Task\n");
        printf("Input task name: %s\n", task.name);
        printf("Input task tag: %s\n", task.tag);
        printf("Input task deadline: %s\n", task.deadline);
        printf("Input task description: %s\n", task.description);
        printf("Input task difficulty: %s\n", task.difficulty);
    }
    }
return 0;
}
void statistics(char *filename){
    printf("Statistics\n");
    //have an access to records.txt and display the overview of removed/submitted tasks
    //by default, a user is allowed to select a certain task at once and have an option to restore it or to simply return

    //have the option to manage -- to select many tasks at once and also have an option to restore or abort the operation
}


/* START OF SEARCH */
char *search(){
    printf("Search a task by: \n");
    printf("B = Back\n1. Name\n2. Tag\n3. Deadline\n");
    printf("What would you like to do?: ");

    char *option = malloc(16);
    if(!option){return NULL;}
    
    if(scanf("%s", option) != 1){
        free(option);
        return NULL;
    }
    clearBuffer();
    if(scanBack(option)){
        return scanBack(option);
    }



    return option;
}

char *getSearchInput(char *mode){
    printf("Enter task %s: ", mode);
    char optionBuffer[256];
    fgets(optionBuffer, sizeof(optionBuffer), stdin);
    optionBuffer[strcspn(optionBuffer, "\n")] = 0;
 

    if(scanBack(optionBuffer)){
        return strdup("b");
    }

    return strdup(optionBuffer);
}
