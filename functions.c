/**
 * @file functions.c
 * @author Ganraj Borade
 * @brief This file contains the functions which are used to do code generation. 
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "helper.h"
int c=0;

char *H_BEGIN[] = {" ", "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>"};
char *H_END[] = {" ", "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>"};


/**
 * @brief The problem with the strcat function in c is that it is not able to take first input as NULL pointer string. Hence I have defined stringAppend
 * function which will capture this aspect.
 */

char* stringAppend(char* dest, const char* source) {
    int source_len = strlen(source);
    if (dest == NULL) {
        dest = (char*)malloc((source_len + 1) * sizeof(char));
        strcpy(dest, source);
    } else {
        int dest_len = strlen(dest);
        dest = realloc(dest, (dest_len + source_len + 1) * sizeof(char));
        strcat(dest, source);
    }
    return dest;
}

/**
 * @brief This newAST is the function which is returning the pointer of struct AST type. This is to be done as we have to construct the abstract syntax tree
 * for the grammer written in bison.y file.
 */

struct AST *newAST(char tag, struct AST *left, struct AST *right) {
  struct AST *temp = (struct AST *)malloc(sizeof(struct AST));
  if(!temp) {
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = tag;
  temp->left = left;
  temp->right = right;
  return temp;
}

/**
 * @brief This is the function used to create a AST node having only one child.
 */

struct AST *newSTRINGNODE(char *value){
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  temp->value = value;
  return (struct AST *)temp;
}

/**
 * @brief Below functions are self explanatory according to their names.
 */

/**
 -------------------------------------------------------------------------------------
 */
struct AST *header_Generator(int level, const char* text) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp) {
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, H_BEGIN[level]);
  str = stringAppend(str, text);
  str = stringAppend(str, H_END[level]);
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *paragraph_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<p>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</p>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *unorderedListParagraph_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<ul>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</ul>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *unorderedList_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<li>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</li>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *orderedListParagraph_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<ol>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</ol>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *table_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<table>");
  if(c==1){
    str = stringAppend(str, "<thead>");
    str = stringAppend(str, text_content);
    str = stringAppend(str, "</thead>");
    temp->value = str;
  }else{
    str = stringAppend(str, "<tbody>");
    str = stringAppend(str, text_content);
    str = stringAppend(str, "</tbody>");
    temp->value = str;
  }
  str = stringAppend(str, "</table>");
  return (struct AST *)temp;
}

struct AST *table_head_body_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  if(c==0){
    str = stringAppend(str, "<th>");
    str = stringAppend(str, text_content);
    str = stringAppend(str, "</th>");
    temp->value = str;
  }else{
    str = stringAppend(str, "<td>");
    str = stringAppend(str, text_content);
    str = stringAppend(str, "</td>");
    temp->value = str;
  }
  
  return (struct AST *)temp;
}

struct AST *table_para_Generator(const char* text_content1, const char* text_content2) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<tr>");
  str = stringAppend(str, text_content1);
  str = stringAppend(str, "</tr>");
  str = stringAppend(str, "<tr>");
  str = stringAppend(str, text_content2);
  str = stringAppend(str, "</tr>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *table_body_Generator(const char* text_content1, const char* text_content2) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<tbody>");
  str = stringAppend(str, text_content1);
  str = stringAppend(str, text_content2);
  str = stringAppend(str, "</tbody>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *boldText_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<b>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</b>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *italicText_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<i>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</i>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *bold_italicText_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<strong>");
  str = stringAppend(str, "<em>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "</em>");
  str = stringAppend(str, "</strong>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *codeText_Generator(const char* text_content) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<code>");
  str = stringAppend(str, text_content);
  str = stringAppend(str, "<code>");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *image_Generator(const char* image_name, const char* image_url) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  
  char* str = NULL;
  str = stringAppend(str, "<img src=\"");
  str = stringAppend(str, image_url);
  str = stringAppend(str, "\" alt=\"");
  str = stringAppend(str, image_name);
  str = stringAppend(str, "\">");
  temp->value = str;
  return (struct AST *)temp;
}

struct AST *url_Generator(const char* url_name, const char* url) {
  struct STRINGNODE *temp = (struct STRINGNODE *)malloc(sizeof(struct STRINGNODE));
  if(!temp){
    yyerror("Out of Space");
    exit(0);
  }
  temp->tag = 'C';
  char* str = NULL;
  str = stringAppend(str, "<a href=\"");
  str = stringAppend(str, url); 
  str = stringAppend(str, "\">");
  str = stringAppend(str, url_name); 
  str = stringAppend(str, "</a>");
  temp->value = str;
  return (struct AST *)temp;
}

/**
 * @brief This function is used for getting our result from the AST. We basically need to combine what is there in the left subtree
 * and the right subtree to obtain the html file.
 */

char *evaluateAST(struct AST *temp) {
  if(temp->tag == 'P'){
    if((temp->left)==NULL && (temp->right)==NULL) {
        return NULL;
      } else if ((temp->left)!=NULL && (temp->right)==NULL) {
        char *result = stringAppend(NULL, evaluateAST(temp->left));
        temp = NULL;
        free(temp);
        return result;
      } else if ((temp->left)==NULL && (temp->right)!=NULL) {
        char *result = stringAppend(NULL, evaluateAST(temp->right));
        temp = NULL;
        free(temp);
        return result;
      } else {
        char *result = stringAppend(evaluateAST(temp->left), evaluateAST(temp->right));
        temp = NULL;
        free(temp);
        return result;
      }
  }else{
    char *result = stringAppend(NULL, (((struct STRINGNODE *)temp) -> value));
    temp = NULL;
    free(temp);
    return result;
  }
}