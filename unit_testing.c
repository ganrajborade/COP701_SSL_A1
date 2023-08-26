/**
 * @file unit_testing.c
 * @author Ganraj Borade
 * @brief Here I have created a test_directory where there are various markdown files of each feature and the corresponding output files are 
 * also present there in .html format. Here I am checking whether after running the code, I am getting the same output result or not.
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "helper.h"
int main() {
     const char* testFiles[] = {
        "test_directory/header.md",
        "test_directory/bold.md",
        "test_directory/image.md",
        "test_directory/italics.md",
        "test_directory/ordered_list.md",
        "test_directory/unordered_list.md",
        "test_directory/url.md",
        "test_directory/paragraph.md",
        "test_directory/table.md"
    };

    const char* output_file = "output_unit_test.html";

    const char* outputreferenceFiles[] = {
        "test_directory/header.html",
        "test_directory/bold.html",
        "test_directory/image.html",
        "test_directory/italics.html",
        "test_directory/ordered_list.html",
        "test_directory/unordered_list.html",
        "test_directory/url.html",
        "test_directory/paragraph.html",
        "test_directory/table.html"
    };

    int numTests = sizeof(testFiles) / sizeof(testFiles[0]);

    for (int i = 0; i < numTests; ++i) {
        const char* input_file = testFiles[i];
        const char* reference_file = outputreferenceFiles[i];
        
        // Run the conversion command
        char command[1024];
        snprintf(command, sizeof(command), "./run.sh %s %s", input_file, output_file);
        system(command);

        // Compare the output with the reference file. >dev/null 2>&1 basically ignore the unused variables warning.
        snprintf(command, sizeof(command), "diff -q %s %s >/dev/null 2>&1", output_file, reference_file);
        int result = system(command);
        
        if (result == 0) {
            printf("Test %d: Conversion is correct.\n", i);
        } else {
            printf("Test %d: Conversion is not correct.\n", i);
        }
    }

    remove(output_file);
    return 0;
}