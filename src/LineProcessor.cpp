#include "LineProcessor.h"
#include "Line.h"
#include "SymbolTableElement.h"

void LineProcessor::ProcessLine(const Line &line)
{
    switch (line.getAssemblyOpType())
    {
    case AssemblyInstructionType::Directive:
        cout << "Processing directive: " << line.getAssemblyDirectiveType() << endl;
        ProcessDirective(line);
        break;

    case AssemblyInstructionType::Command:
        cout << "Processing command: " << line.getAssemblyDirectiveType() << endl;
        break;

    default:
        cout << "Unknown line type." << endl;
        break;
    }
    locationCounter += 4; // Assuming each instruction is 4 bytes

    return;
}

void LineProcessor::ProcessDirective(const Line &line)
{
    vector<ParametersElement> parameters = line.getParameters();
    switch (line.getAssemblyDirectiveType())
    {
    case AssemblyInstructionName::Global:
        for (int i = 0; i < parameters.size(); i++)
        {
            bool found = false;
            for (int j = 0; j < symbolTableSize; j++)
            {
                if (symbolTable[j]->getName().compare(parameters[i].value) == 0)
                {
                    symbolTable[j]->setDefined(true);
                    symbolTable[j]->setSection(activeSection);
                    found = true;
                }
                break;
            }
            if (found)
            {
                break;
            }
            symbolTable[i] = new SymbolTableElement(symbolTableIndex + 1, parameters[i].value, defaultSymbolTableElementValue, 0, "", GLOB, false);
            cout << *symbolTable[i] << endl;
            symbolTableSize++;
        }

        break;

    case AssemblyInstructionName::Extern:
        for (int i = 0; i < parameters.size(); i++)
        {
            symbolTable[i] = new SymbolTableElement(symbolTableIndex + 1, parameters[i].value, defaultSymbolTableElementValue, 0, "", UND, false);
            cout << *symbolTable[i] << endl;
            symbolTableSize++;
        }

        break;

    case AssemblyInstructionName::Section:
        symbolTable[symbolTableSize] = new SymbolTableElement(symbolTableIndex + 1, parameters[0].value, defaultSymbolTableElementValue, 0, parameters[0].value, UND, false);
        cout << *symbolTable[symbolTableSize] << endl;
        symbolTableSize++;
        sectionMemory[structMemorySectionCount] = new SectionMemory(parameters[0].value);
        activeSection = parameters[0].value;

        break;

    case AssemblyInstructionName::Word:
        for (int i = 0; i < structMemorySectionCount; i++)
        {
            if (sectionMemory[i]->name == activeSection)
            {
                sectionMemory[i]->size += parameters.size() * 4;
                if (parameters[i].type != ParametersElement::ParamType::SYMBOL)
                {
                }
                sectionMemory[i]->memoryRep += ConvertLiteralToLittleEndian(parameters[0]);
            }
        }
        for (int i = 0; i < parameters.size(); i++)
        {
            symbolTable[i] = new SymbolTableElement(symbolTableIndex + 1, parameters[i].value, defaultSymbolTableElementValue, 0, "", LOC, false);
            cout << *symbolTable[i] << endl;
            symbolTableSize++;
        }

        break;

    default:
        cout << "Unknown directive type." << endl;
        break;
    }
}

string LineProcessor::ConvertLiteralToLittleEndian(ParametersElement &param)
{
    uint32_t value = 0;
    string result = "";

    if (param.type == ParametersElement::ParamType::HEXA_LITERAL)
    {
        std::string hexStr = param.value;
        if (hexStr.rfind("0x", 0) == 0 || hexStr.rfind("0X", 0) == 0)
        {
            hexStr = hexStr.substr(2);
        }
        value = std::stoul(hexStr, nullptr, 16);
    }
    if (param.type == ParametersElement::ParamType::LITERAL)
    {
        value = std::stoul(param.value);
    }
    if (param.type == ParametersElement::ParamType::SYMBOL)
    {
        // Assuming the symbol is already defined and has a value
        for (int i = 0; i < symbolTableSize; i++)
        {
            if (symbolTable[i]->getDefined())
            {
                value = std::stoul(symbolTable[i]->getValue());
                break;
            }
        }
    }
    else
    {
        throw std::invalid_argument("Unsupported ParamType");
    }

    // Little-endian convert
    for (int i = 0; i < 4; ++i)
    {
        result += static_cast<char>(value & 0xFF);
        value >>= 8;
    }
    return result;
}