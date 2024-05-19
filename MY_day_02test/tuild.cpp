#include"tuild.h"
#include<stdlib.h>
#include<stdio.h>

void __ERRIF(bool condition ,const char*errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}