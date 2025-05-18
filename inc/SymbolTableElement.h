#ifndef SYMBOLTABLEELEMENT_H
#define SYMBOLTABLEELEMENT_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

const string defaultSymbolTableElementValue = "00000000";

enum ScopeType
{
    LOC,
    GLOB,
    UND
};

struct ST_forwardrefs
{
    int patch;
    ST_forwardrefs *nlink;
};

class SymbolTableElement
{
private:
    int index;
    string name;
    string value;
    int size;
    string section;
    ScopeType type;
    bool defined;
    ST_forwardrefs *flink;

public:
    SymbolTableElement(int index = 0, string name = "undefined", string value = "00000000", int size = 0, string section = "undefined", ScopeType type = LOC, bool defined = false)
        : index(index), name(name), value(value), size(size), type(type), defined(defined), flink(nullptr) {}
    string toString() const;
    string getName();
    void setSection(string section);
    void setDefined(bool defined);
    string getValue();
    bool getDefined();
    friend ostream &operator<<(ostream &os, const SymbolTableElement &symbolTableElement);
};

#endif