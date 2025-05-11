#ifndef SYMBOLTABLEELEMENT_H
#define SYMBOLTABLEELEMENT_H

enum ScopeType
{
  LOC,
  GLOB
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
  int value;
  int size;
  ScopeType type;
  bool defined;
  ST_forwardrefs *flink;
};

#endif