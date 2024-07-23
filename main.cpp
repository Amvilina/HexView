#include "HexView.hpp"

int main (int argc, char* argv[])
{
    HexView hv("input.txt");
    hv.WriteToConsole();
    return 0;
}
