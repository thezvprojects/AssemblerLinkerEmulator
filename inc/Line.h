#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>

using namespace std;

struct ParametersElement
{
    enum ParamType
    {
        SYMBOL,
        LITERAL,
        HEXA_LITERAL,
        REGISTER,
        VALUEOPERAND,
        MEMREGOPERAND,
        SECTION
    } type;
    string value;
    ParametersElement(ParamType t, std::string val) : type(t), value(val) {}
};

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
    vector<ParametersElement> parameters;
    AssemblyInstructionName asmInstructionName;
    AssemblyInstructionType asmOpType;

public:
    Line(int number, const string &type, const string &instructionName, const vector<ParametersElement> &params);

    int getLineNumber() const;
    void setLineNumber(int lineNumber);

    string getLabel() const;
    void setLabel(const string &lbl);

    // params
    vector<ParametersElement> getParameters() const;
    void setParameters(const vector<ParametersElement> &parameters);

    // assembly operation and directive
    AssemblyInstructionType getAssemblyOpType() const;
    void setAssemblyOpType(const string &type);
    AssemblyInstructionName getAssemblyDirectiveType() const;
    void setAssemblyDirectiveType(const string &instructionName);

    // print stuff
    string toString() const;
    friend ostream &operator<<(ostream &os, const Line &line);
};

#endif