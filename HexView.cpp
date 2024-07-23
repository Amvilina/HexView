#include "HexView.hpp"

#include <iostream>

HexView::HexView(const std::string& fileName){
    inputFile.open(fileName);
    assert(inputFile.is_open());
}

void HexView::WriteToFile(const std::string& fileName){
    std::ofstream outputFile(fileName);
    assert(outputFile.is_open());
    WriteToOutput(outputFile);
    outputFile.close();
}

void HexView::WriteToConsole(){
    WriteToOutput(std::cout);
    std::cout << '\n';
}

void HexView::WriteToOutput(std::ostream& output){
    this->output = &output;
    
    u64 offset = 0;
    while (true) {
        u8 amount = ReadBytesAndReturnReadAmount();
        if(amount == 0)
            break;
        PrintOffset(offset);
        offset += BYTES_IN_ONE_LINE;
        if(amount != BYTES_IN_ONE_LINE){
            PrintBytesInHexAmount(amount);
            PrintASCIIAmount(amount);
            break;
        }
        PrintBytesInHexLine();
        PrintASCIILine();
    }
    
    inputFile.clear();
    inputFile.seekg(0);
}

HexView::u8 HexView::ReadBytesAndReturnReadAmount(){
    u8 i = 0;
    for (; i < BYTES_IN_ONE_LINE; ++i) {
        u8 byte = u8(inputFile.get());
        if(inputFile.eof())
            break;
        bytes[i] = byte;
    }
    return i;
}

void HexView::PrintOffset(u64 offset){
    *output << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << offset;
    *output << " | ";
}

void HexView::PrintBytesInHexLine(){
    PrintBytesInHexAmount(BYTES_IN_ONE_LINE);
}

void HexView::PrintBytesInHexAmount(u8 amount){
    u8 i = 0;
    for (; i < amount; ++i) {
        *output << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << int(bytes[i]);
        output->put(' ');
    }
    
    for (; i < BYTES_IN_ONE_LINE; ++i) {
        *output << "   ";
    }
}

void HexView::PrintASCIILine(){
    PrintASCIIAmount(BYTES_IN_ONE_LINE);
    if(inputFile.peek() != EOF)
        output->put('\n');
}

void HexView::PrintASCIIAmount(u8 amount){
    *output << "| ";
    for (u8 i = 0; i < amount; ++i)
        output->put(GetPrintableFromASCII(bytes[i]));
    
}

char HexView::GetPrintableFromASCII(u8 c) const{
    return (c >= 32 && c <= 126) ? char(c) : NON_PRINTABLE_ASCII_CHARACHTER_SUBSTITUTE;
}
