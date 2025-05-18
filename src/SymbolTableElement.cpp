#include "SymbolTableElement.h"

using namespace std;

string SymbolTableElement::toString() const
{
    ostringstream oss;

    oss << "Index: " << index << " Name: " << name << " Value: " << value << ", Size: " << size
        << ", Type: " << (type == LOC ? "LOC" : (type == GLOB ? "GLOB" : "UND")) << ", Defined: " << (defined ? "true" : "false")
        << ", Forward References: ";
    return oss.str();
}

string SymbolTableElement::getName()
{
    return name;
}

string SymbolTableElement::getValue()
{
    return value;
}
void SymbolTableElement::setSection(string section)
{
    this->section = section;
}

void SymbolTableElement::setDefined(bool defined)
{
    this->defined = defined;
}

bool SymbolTableElement::getDefined()
{
    return defined;
}

ostream &operator<<(ostream &os, const SymbolTableElement &symbolTableElement)
{
    return os << symbolTableElement.toString();
}