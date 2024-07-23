#ifndef HexView_hpp
#define HexView_hpp

#include <fstream>

class HexView{
private:
    using u8 = uint8_t;
    using u64 = uint64_t;
    
    static constexpr u8 BYTES_IN_ONE_LINE = 16;
    static constexpr char NON_PRINTABLE_ASCII_CHARACHTER_SUBSTITUTE = '.';
    
    std::ifstream inputFile;
    std::ostream* output;
    u8 bytes[BYTES_IN_ONE_LINE];
public:
    HexView(const std::string& fileName);
    void WriteToFile(const std::string& fileName);
    void WriteToConsole();
private:
    void WriteToOutput(std::ostream& output);
    u8 ReadBytesAndReturnReadAmount();
    void PrintOffset(u64 offset);
    void PrintBytesInHexLine();
    void PrintBytesInHexAmount(u8 amount);
    void PrintASCIILine();
    void PrintASCIIAmount(u8 amount);
    char GetPrintableFromASCII(u8 c) const;
};

#endif
