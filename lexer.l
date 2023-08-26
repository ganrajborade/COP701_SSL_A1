%{
/**
 * @file lexer.y
 * @author Ganraj Borade
 * @brief Brief description of the Lexer file.
 *
 * Detailed description of the file and its contents.
 */
#include <stdio.h>
#include "helper.h"
#include "bison.tab.h" 
%}

textword            [a-zA-Z:\.\,'/\%\&\?!]+
digits              [0-9]+
header              #|##|###|####|#####|######

%option noyywrap

%{
 /**
 * @brief Following are the regular expressions for the tokens that we have to recognise.
 *
 */   
%}


%%
                                                   
[ \t]+                                             { 
                                                    return WHITESPACE; 
                                                   }                                                    

[\n]                                               { 
                                                    return SINGLE_NEWLINE;
                                                   }

[\n][\n]+                                          { 
                                                    return NEWLINE;
                                                   }

{header}                                           { 
                                                    yylval.string=(char* )malloc(yyleng);
                                                    strcpy(yylval.string,yytext);
                                                    return HEADER;
                                                   }

{textword} 					                       { 
                                                    yylval.string=(char* )malloc(yyleng);
                                                    strcpy(yylval.string,yytext);
                                                    return TEXTWORD;
                                                   }

{digits}     					                   { 
                                                    yylval.string=(char* )malloc(yyleng);
                                                    strcpy(yylval.string,yytext);
                                                    return INT;
                                                   }

^{digits}[.]                                       { 
                                                    yylval.string=(char* )malloc(yyleng);
                                                    strcpy(yylval.string,yytext);
                                                    return ORDERED_LIST;
                                                   }            

[_*]                                               {
                                                    return ITALIC;
                                                   }

                                                   {
[*]{2}                                              return BOLD;
                                                   }

                                                   {
[*]{3}                                              return BOLD_ITALICS;
                                                   }

\[                                                 {
                                                    return URL1;
                                                   }

!\[                                                {
                                                    return IMG1;
                                                   }

\]\(                                               {
                                                    return IMG2_URL2;
                                                   }

=                                                  {
                                                    return IMG3;
                                                   }

@                                                  {
                                                    return IMG4;
                                                   }

\)                                                 {
                                                    return IMG5_URL5;
                                                   }

[|]                                                {
                                                    return TABLE;
                                                   }

^[*+-]                                             {
                                                    return UNORDERED_LIST;
                                                   }

[-][-]+                                            {
                                                    return IGNORE_TABLE_TOKEN;
                                                   }

[`]+                                               {
                                                    return CODE_TOKEN;
                                                   }
                                                   

%%