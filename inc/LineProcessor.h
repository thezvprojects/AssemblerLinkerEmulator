#ifndef LINEPROCESSOR_H
#define LINEPROCESSOR_H

#include "Line.h"
#include "SymbolTableElement.h"

struct SectionMemory
{
    int size;
    string memoryRep;
    string name;
    SectionMemory(string nm)
        : size(0), memoryRep(""), name(nm) {}
};

class LineProcessor
{
private:
    int locationCounter = 0;
    int symbolTableIndex = 0;
    int symbolTableSize = 0;
    int structMemorySectionCount = 0;
    string activeSection = "";
    SymbolTableElement **symbolTable;
    SectionMemory **sectionMemory;

public:
    LineProcessor() : locationCounter(0)
    {
        symbolTable = new SymbolTableElement *[100];
        sectionMemory = new SectionMemory *[8];
    }
    string ConvertLiteralToLittleEndian(ParametersElement &param);
    void ProcessLine(const Line &line);
    void ProcessDirective(const Line &line);
};

#endif