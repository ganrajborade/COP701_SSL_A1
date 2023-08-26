%{
/**
 * @file bison.y
 * @author Ganraj Borade
 * @brief Brief description of the Bison file.
 *
 * Detailed description of the file and its contents.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
extern FILE *ff;
extern int c;
%}


%union 
{
  	struct AST *ast;
  	char *string;
}

%token NEWLINE SINGLE_NEWLINE WHITESPACE
%token HEADER TEXTWORD INT 
%token ITALIC BOLD BOLD_ITALICS
%token URL1 IMG1 IMG2_URL2 IMG3 IMG4 IMG5_URL5 
%token UNORDERED_LIST ORDERED_LIST
%token TABLE IGNORE_TABLE_TOKEN
%token CODE_TOKEN

%{
/**
 * @brief Here we are defining the types of our both terminals and non_terminals.
 *
 */
%}

%start begin
%type <ast> NEWLINE
%type <ast> header
%type <ast> markdown sub_content content lines 
%type <ast> items word_format text textword image url 
%type <ast> unordered_list ordered_list 
%type <ast> table table_para table_gen
%type <ast> code_text
%type <string> HEADER TEXTWORD INT IGNORE_TABLE_TOKEN

%{
 /**
 * @brief These are the grammer rules. 
 * Since Bison's default behavior is LEFT RECUSION, I am writing only LEFT RECURSIVE GRAMMER.
 */

/**
 * @brief For each productions, we are doing the code generation subsequently. The information for the functions used will be in the functions.c file.
 */          
%}

%%
begin                                       :       markdown                        {
                                                                                          char *HTML_BEGIN = "<!DOCTYPE html>\n<html>\n<body>\n";
                                                                                          char *HTML_END = "\n</body>\n</html>";
                                                                                          fprintf(ff, "%s%s%s", HTML_BEGIN, evaluateAST($1), HTML_END);
                                                                                          fclose(ff);
                                                                                    }

markdown                                    :       markdown content                {
                                                                                          $$ = newAST('P',$1, $2);
                                                                                    }

                                            |       markdown SINGLE_NEWLINE content {
                                                                                          $$ = newAST('P',$1, $3);
                                                                                    }

                                            |       markdown NEWLINE content        {
                                                                                          $$ = newAST('P',$1, $3);
                                                                                    }

                                            |                                       {
                                                                                          $$ = newSTRINGNODE("");
                                                                                    }
                                                                                    
content                                     :       WHITESPACE                      {
                                                                                          $$ = newSTRINGNODE("");
                                                                                    }
	
	                                      |       sub_content SINGLE_NEWLINE      {
                                                                                          $$ = newAST('P',$1, NULL);
                                                                                    } 
                                            
                                            |       sub_content NEWLINE             {
                                                                                          $$ = newAST('P',$1, newSTRINGNODE("\n"));
                                                                                    } 

sub_content                                 :       header 

                                            |       lines                           {
                                                                                          $$ = paragraph_Generator(evaluateAST($1));
                                                                                    }
                                            
                                            |       unordered_list                  {
                                                                                          $$ = unorderedListParagraph_Generator(evaluateAST($1));
                                                                                    }

                                            |       ordered_list                    {
                                                                                          $$ = orderedListParagraph_Generator(evaluateAST($1));
                                                                                    }

                                            |       table_gen                       {       
                                                                                          /* This c variable is used for differentiating between thead and
                                                                                          tbody */
                                                                                          c++;
                                                                                          $$ = table_Generator(evaluateAST($1));
                                                                                    }                                                 

table_gen                                   :       table_para TABLE           

table_para                                  :       table_para table                {
                                                                                          $$ = table_para_Generator(evaluateAST($1), evaluateAST($2));
                                                                                    }
                                            
                                            |       table                           {
                                                                                          $$ = table_head_body_Generator(evaluateAST($1));
                                                                                    }



table                                       :       TABLE WHITESPACE text WHITESPACE
                                                                                    {
                                                                                          $$ = table_head_body_Generator(evaluateAST($3));
                                                                                    } 
                                            
                                            |       TABLE WHITESPACE IGNORE_TABLE_TOKEN WHITESPACE        
                                                                                    {
                                                                                          $$ = newSTRINGNODE("");
                                                                                    }

header                                      :       HEADER WHITESPACE lines         { 
                                                                                          $$ = header_Generator(strlen($1), evaluateAST($3)); 
                                                                                    }

lines                                       :       lines WHITESPACE items          {                                                                                         
                                                                                          char *temp_initial = stringAppend(evaluateAST($1), " ");
                                                                                          $$ = newSTRINGNODE(stringAppend(temp_initial, evaluateAST($3)));
                                                                                    }
                                            |       lines items
                                                                                    {
                                                                                          $$ = newSTRINGNODE(stringAppend(evaluateAST($1), evaluateAST($2)));
                                                                                    }

                                            |       items                           {
                                                                                          $$ = $1;
                                                                                    }
                                            
                                            |       lines WHITESPACE SINGLE_NEWLINE              
                                                                                    {
                                                                                          $$ = newSTRINGNODE(stringAppend(evaluateAST($1), "<br>"));
                                                                                    }

unordered_list                              :       UNORDERED_LIST WHITESPACE lines {
                                                                                          $$ = unorderedList_Generator(evaluateAST($3));	
                                                                                    }

ordered_list                                :       ORDERED_LIST WHITESPACE lines   {
                                                                                          $$ = unorderedList_Generator(evaluateAST($3));	
                                                                                    }                                                                                    


items                                       :       word_format 

                                            |       image 

                                            |       textword

                                            |       url

                                            |       code_text
                                        
word_format                                 :       BOLD word_format BOLD           { 
                                                                                          $$ = boldText_Generator(evaluateAST($2)); 
                                                                                    }
		
                                            |       BOLD text BOLD                  { 
                                                                                          $$ = boldText_Generator(evaluateAST($2)); 
                                                                                    }
                                           
                                            |       ITALIC word_format ITALIC       { 
                                                                                          $$ = italicText_Generator(evaluateAST($2)); 
                                                                                    }
		
                                            |       ITALIC text ITALIC              { 
                                                                                          $$ = italicText_Generator(evaluateAST($2)); 
                                                                                    }

                                            |       BOLD_ITALICS word_format BOLD_ITALICS  
                                                                                    {
                                                                                          $$ = bold_italicText_Generator(evaluateAST($2));
                                                                                    } 

                                            |       BOLD_ITALICS text BOLD_ITALICS  {
                                                                                          $$ = bold_italicText_Generator(evaluateAST($2));
                                                                                    }

code_text                                   :       CODE_TOKEN text CODE_TOKEN      {
                                                                                          $$ = codeText_Generator(evaluateAST($2));
                                                                                    } 


url                                         :       URL1 text IMG2_URL2 text IMG5_URL5        
                                                                                    { 
                                                                                          $$ = url_Generator(evaluateAST($2), evaluateAST($4));
                                                                                    }

image                                       :       IMG1 text IMG2_URL2 text IMG5_URL5 
                                                                                    { 
                                                                                          $$ = image_Generator(evaluateAST($2), evaluateAST($4));
                                                                                    }

text                                        :       text WHITESPACE textword        {
                                                                                          char *temp_initial = stringAppend(evaluateAST($1), " ");
                                                                                          $$ = newSTRINGNODE(stringAppend(temp_initial, evaluateAST($3)));
                                                                                    }
                                            |       text textword
                                                                                    {
                                                                                          $$ = newSTRINGNODE(stringAppend(evaluateAST($1), evaluateAST($2)));
                                                                                    }

                                            |       textword                        {
                                                                                          $$ = $1;
                                                                                    }

textword                                    :       TEXTWORD	                  {
                                                                                          $$ = newSTRINGNODE($1);
                                                                                    }
                                            
                                            |       INT                             {
                                                                                          $$ = newSTRINGNODE($1);
                                                                                    }
	
%%
