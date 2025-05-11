#ifndef LINEPROCESSOR_H
#define LINEPROCESSOR_H

#include "Line.h"

class LineProcessor
{
private:
  int locationCounter = 0;

public:
  void ProcessLine(const Line &line);
};

#endif