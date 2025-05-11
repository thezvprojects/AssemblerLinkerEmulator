#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>

using namespace std;

enum AssemblyInstructionType
{
    Directive,
    Command,
    None
};

enum AssemblyInstructionName
{
    // directives
    Global,
    Extern,
    Section,
    Word,
    Skip,
    End,
    // commands
    Halt,
    Int,
    Iret,
    Call,
    Ret,
    Jmp,
    Beq,
    Bne,
    Bgt,
    Push,
    Pop,
    Xchg,
    Add,
    Sub,
    Mul,
    Div,
    Not,
    And,
    Or,
    Xor,
    Shl,
    Shr,
    Ld,
    St,
    Csrrd,
    Csrwr
};

class Line
{
private:
    int instructionType;
    int lineNumber;
    string label;
    vector<string> parameters;
    AssemblyInstructionName asmInstructionName;
    AssemblyInstructionType asmOpType;

public:
    Line(int number, const string &type, const string &instructionName, const vector<string> &params);

    int getLineNumber() const;
    void setLineNumber(int lineNumber);

    string getLabel() const;
    void setLabel(const string &lbl);

    // params
    vector<string> getParameters() const;
    void setParameters(const vector<string> &parameters);

    // assembly operation and directive
    AssemblyInstructionType getAssemblyOpType() const;
    void setAssemblyOpType(const string &type);
    AssemblyInstructionName getAssemblyDirectiveType() const;
    void setAssemblyDirectiveType(const string &instructionName);

    // print stuff
    string toString() const;
    friend std::ostream &operator<<(std::ostream &os, const Line &line);
};

#endif // LINE_H
