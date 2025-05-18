#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "Line.h"
#include "../misc/parser.tab.h"
#include "LineProcessor.h"

using namespace std;

// Declare the external file pointer for Flex
extern FILE *yyin;

// Global vector to store parameters
vector<ParametersElement> parameters;
vector<Line> lines;
char *label;
int variable_type;
char comma;

// Counters for directives and commands (declared in parser.y)
extern int count_asmd;
extern int count_asmc;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Error opening file");
        exit(1);
    }

    // Set yyin to the file to read (used by Flex)
    yyin = file;

    // Parse the file using the parser
    if (yyparse() == 0)
    {
        cout << "Parsing completed successfully." << endl;
        cout << "Symbol table" << endl;
        LineProcessor *lineProcessor = new LineProcessor();

        for (const auto &line : lines)
        {
            lineProcessor->ProcessLine(line);
            // cout << "- " << line << endl;
        }
    }
    else
    {
        cerr << "Parsing failed." << endl;
    }

    fclose(file);

    // Output counts
    printf("Total Assembly Directives (ASMD): %d\n", count_asmd);
    printf("Total Assembly Commands (ASMC): %d\n", count_asmc);

    return 0;
}