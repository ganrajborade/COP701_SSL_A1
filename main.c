/**
 * @mainpage Software Systems Lab Assignment 1
 * @file main.c
 * @author Ganraj Borade
 * @brief This is the main file which has yyparse() function. 
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * \include input.md
 */

/**
 * @page 
 * \include input.md
 * 
 */

#include "helper.h"
FILE *ff;


void yyerror(const char *response) {
    fprintf(stderr, "Error: %s\n", response);
}
    
int yyparse();

int main(int argc, char** argv){
    extern FILE *yyin;
    if(argc > 1){
        // file name is passed as argument
        if(!(yyin = fopen(argv[1], "r"))){
        perror(argv[1]);
        return (1);
        }
        if(!(ff = fopen(argv[2], "w"))){
        perror(argv[2]);
        return (1);
        }
    }
    yyparse();
    return 0;
}