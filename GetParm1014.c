//
//  GetParam.c
//  
//
//  Created by YueDai on 10/14/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*
void GetParameters(char *FileName, int *parameters){
    
    FILE *fp = fopen(FileName, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        strtok (line,"=");
        parameters[i] = atoi(strtok (NULL,"()\t\n"));
        i++;
    }
    fclose(fp);
}

void GetParameters(){
    
    FILE *fp = fopen(FileName, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        strtok (line,"=");
        parameters[i] = atoi(strtok (NULL,"()\t\n"));
        i++;
    }
    fclose(fp);
}
*/
