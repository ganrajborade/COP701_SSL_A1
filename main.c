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

#include "helper.h"
FILE *ff;


void yyerror(const char *response) {
    fprintf(stderr, "Error: %s\n", response);
}

int yyparse();

void replaceSubstring(char *str, const char *substring, const char *replacement) {
    char *ptr = strstr(str, substring);
    while (ptr != NULL) {
        memmove(ptr + strlen(replacement), ptr + strlen(substring), strlen(ptr + strlen(substring)) + 1);
        memcpy(ptr, replacement, strlen(replacement));
        ptr = strstr(ptr + 1, substring);
    }
}

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

    FILE *inputFile, *outputFile;
    char inputFilename[] = "output.html";
    char outputFilename[] = "output_cleaned.html";
    char *htmlContent;
    long fileSize;

    // Open the input file
    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Get the file size
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    htmlContent = (char *)malloc(fileSize + 1);
    if (htmlContent == NULL) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return 1;
    }

    // Read content from input file
    fread(htmlContent, 1, fileSize, inputFile);
    htmlContent[fileSize] = '\0';

    // Close input file
    fclose(inputFile);

    // Replace "</p><p>" with an empty string
    replaceSubstring(htmlContent, "</p><p>", " ");
    replaceSubstring(htmlContent, "</ol><ol>", "");
    replaceSubstring(htmlContent, "</tr><tr>", "");
    replaceSubstring(htmlContent, "<th><th>", "<th>");
    replaceSubstring(htmlContent, "</th></th>", "</th>");
    replaceSubstring(htmlContent, "<td><td>", "<td>");
    replaceSubstring(htmlContent, "</td></td>", "</td>");
    replaceSubstring(htmlContent, "</table><table>", "");
    // Open output file
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        free(htmlContent);
        return 1;
    }

    // Write cleaned content to output file
    fprintf(outputFile, "%s", htmlContent);

    // Close output file and free memory
    fclose(outputFile);
    free(htmlContent);
    return 0;
}