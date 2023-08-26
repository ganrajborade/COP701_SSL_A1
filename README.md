# COP701_SSL_A1
In this assignment our main objective was to convert a Markdown document to an equivalent HTML document using Flex, Bison, Abstract Syntax Tree and Code Generation phase of Compiler.

## How to run?
<pre>
./run input.md output.html
</pre>

This will create 2 files : output.html and output_cleaned.html.

output.html is created from the grammer rules. After removing some unwanted strings from it, we will get output_cleaned.html. The code for the same can be seen in the main.c file.
output_cleaned.html is the final output file which will render the required html page.

## Other ways to run :
<pre>
make clean
make all
</pre>

## For UNIT_TESTING, run this :
<pre>
make -f makefile_unit_test
</pre>
This will generate **unit_test** file. To run this :

<pre>
./unit_test
</pre>

To delete **unit_test** file, use :
<pre>
make -f makefile_unit_test clean
</pre>
