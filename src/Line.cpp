#include "Line.h"

using namespace std;

static AssemblyInstructionName getDirectiveInstructionType(const string &instructionName)
{
    if (instructionName == "global")
        return AssemblyInstructionName::Global;
    if (instructionName == "extern")
        return AssemblyInstructionName::Extern;
    if (instructionName == "section")
        return AssemblyInstructionName::Section;
    if (instructionName == "word")
        return AssemblyInstructionName::Word;
    if (instructionName == "skip")
        return AssemblyInstructionName::Skip;
    if (instructionName == "end")
        return AssemblyInstructionName::End;
    if (instructionName == "halt")
        return AssemblyInstructionName::Halt;
    if (instructionName == "int")
        return AssemblyInstructionName::Int;
    if (instructionName == "iret")
        return AssemblyInstructionName::Iret;
    if (instructionName == "call")
        return AssemblyInstructionName::Call;
    if (instructionName == "ret")
        return AssemblyInstructionName::Ret;
    if (instructionName == "jmp")
        return AssemblyInstructionName::Jmp;
    if (instructionName == "beq")
        return AssemblyInstructionName::Beq;
    if (instructionName == "bne")
        return AssemblyInstructionName::Bne;
    if (instructionName == "bgt")
        return AssemblyInstructionName::Bgt;
    if (instructionName == "push")
        return AssemblyInstructionName::Push;
    if (instructionName == "pop")
        return AssemblyInstructionName::Pop;
    if (instructionName == "xchg")
        return AssemblyInstructionName::Xchg;
    if (instructionName == "add")
        return AssemblyInstructionName::Add;
    if (instructionName == "sub")
        return AssemblyInstructionName::Sub;
    if (instructionName == "mul")
        return AssemblyInstructionName::Mul;
    if (instructionName == "div")
        return AssemblyInstructionName::Div;
    if (instructionName == "not")
        return AssemblyInstructionName::Not;
    if (instructionName == "and")
        return AssemblyInstructionName::And;
    if (instructionName == "or")
        return AssemblyInstructionName::Or;
    if (instructionName == "xor")
        return AssemblyInstructionName::Xor;
    if (instructionName == "shl")
        return AssemblyInstructionName::Shl;
    if (instructionName == "shr")
        return AssemblyInstructionName::Shr;
    if (instructionName == "ld")
        return AssemblyInstructionName::Ld;
    if (instructionName == "st")
        return AssemblyInstructionName::St;
    if (instructionName == "csrrd")
        return AssemblyInstructionName::Csrrd;
    if (instructionName == "csrwr")
        return AssemblyInstructionName::Csrwr;

    throw std::invalid_argument("Unknown directive: " + instructionName);
}

Line::Line(int lineNumber, const string &type, const string &instructionName, const vector<ParametersElement> &params) : lineNumber(lineNumber)
{
    asmOpType = type == "directive" ? AssemblyInstructionType::Directive : AssemblyInstructionType::Command;
    label = "";
    parameters = params;

    try
    {
        asmInstructionName = getDirectiveInstructionType(instructionName);
    }

    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: line constructor dead" << std::endl;
    }
};

int Line::getLineNumber() const
{
    return lineNumber;
}

void Line::setLineNumber(int lineNumber)
{
    this->lineNumber = lineNumber;
}

vector<ParametersElement> Line::getParameters() const
{
    return parameters;
}

void Line::setParameters(const vector<ParametersElement> &parameters)
{
    this->parameters = parameters;
}

AssemblyInstructionType Line::getAssemblyOpType() const
{
    return asmOpType;
}

void Line::setAssemblyOpType(const string &type)
{
    asmOpType = type == "directive" ? AssemblyInstructionType::Directive : AssemblyInstructionType::Command;
}

AssemblyInstructionName Line::getAssemblyDirectiveType() const
{
    return asmInstructionName;
}

void Line::setAssemblyDirectiveType(const string &directive)
{
    asmInstructionName = getDirectiveInstructionType(directive);
}

string Line::getLabel() const
{
    return label;
}

void Line::setLabel(const string &lbl)
{
    if (!lbl.empty())
    {
        label = lbl;
        label.pop_back();
    }
}

string Line::toString() const
{
    ostringstream oss;

    oss << "Line Number: " << lineNumber << "\n"
        << "Instruction Type: " << instructionType << "\n"
        << "Assembly Directive: " << static_cast<int>(asmInstructionName) << "\n"
        << "Assembly Operation Type: " << static_cast<int>(asmOpType) << "\n"
        << "Label: " << label << "\n"
        << "Parameters: ";
    for (const auto &param : parameters)
    {
        oss << param.value << " ";
    }
    return oss.str();
}

ostream &operator<<(ostream &os, const Line &line)
{
    return os << line.toString();
}
