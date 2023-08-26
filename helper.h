/**
 * @file helper.h
 * @author Ganraj Borade
 * @brief This is the header file which is used by al the major files in the directory.
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

extern int yylineno;
void yyerror(const char *response);
int yylex();

/**
 * @brief Structure for the ABSTRACT SYNTAX TREE
 */
struct AST 
{
  char tag;
  struct AST *left;
  struct AST *right;
};

/**
 * @brief Structure for STRING NODE used to create a node with one child
 */
struct STRINGNODE 
{
  char tag;			
  char *value;
};

char* stringAppend(char* dest, const char* source);

/**
 * @brief Functions of return type as pointer to struct AST.
 */
struct AST *newAST(char tag, struct AST *left, struct AST *right);

struct AST *newSTRINGNODE(char *value);

struct AST *header_Generator(int level, const char* text_content);

struct AST *paragraph_Generator(const char* text_content);

struct AST *unorderedListParagraph_Generator(const char* text_content);

struct AST *unorderedList_Generator(const char* text_content);

struct AST *orderedListParagraph_Generator(const char* text_content);

struct AST *table_Generator(const char* text_content);

struct AST *table_head_body_Generator(const char* text_content);

struct AST *table_para_Generator(const char* text_content1, const char* text_content2); 

struct AST *boldText_Generator(const char* text_content);

struct AST *italicText_Generator(const char* text_content);

struct AST *bold_italicText_Generator(const char* text_content);

struct AST *codeText_Generator(const char* text_content);

struct AST *image_Generator(const char* image_name, const char* image_url);

struct AST *url_Generator(const char* url_name, const char* url);

/**
 * @brief Evaluation of the AST.
 */
char *evaluateAST(struct AST *temp);

