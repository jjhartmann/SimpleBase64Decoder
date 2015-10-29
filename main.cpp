#include <iostream>
#include <fstream>
#include <map>
#ifdef DEBUG_PROGRAM
#define DEBUG(x) cout << (x) << endl;
#else
#define DEBUG(x)
#endif

#define PRINT(x) cout << (x) << endl;

typedef unsigned char byte;
using namespace std;

static map<byte, byte> lookup = {
        {65,  0},        {66,  1},        {67,  2},        {68,  3},        {69,  4},        {70,  5},        {71,  6},
        {72,  7},        {73,  8},        {74,  9},        {75,  10},       {76,  11},       {77,  12},       {78,  13},
        {79,  14},       {80,  15},       {81,  16},       {82,  17},       {83,  18},       {84,  19},       {85,  20},
        {86,  21},       {87,  22},       {88,  23},       {89,  24},       {90,  25},       {97,  26},       {98,  27},
        {99,  28},       {100, 29},       {101, 30},       {102, 31},       {103, 32},       {104, 33},       {105, 34},
        {106, 35},       {107, 36},       {108, 37},       {109, 38},       {110, 39},       {111, 40},       {112, 41},
        {113, 42},       {114, 43},       {115, 44},       {116, 45},       {117, 46},       {118, 47},       {119, 48},
        {120, 49},       {121, 50},       {122, 51},       {48,  52},       {49,  53},       {50,  54},       {51,  55},
        {52,  56},       {53,  57},       {54,  58},       {55,  59},       {56,  60},       {57,  61},       {43,  62},
        {47,  63},
};

int main(int argn, char *argv[]) {
    // Check to make sure the cmd is in proper format
    if (argn < 2)
    {
        cout << "NEED TO PROVIDE INPUT FILE (ie ./converttobase64 XXX.in)" << endl;
        return 1;
    }

    // Get data from input file.
    string file = argv[1];
    ifstream infile(file.c_str());
    string base64encode, base64decode;
    getline(infile, base64encode);
    infile.close();

    // decode the data.
    for (int i = 0; i < base64encode.length(); i+=4)
    {
        base64decode += static_cast<char> (((lookup[base64encode[i]] & 0b00111111) << 2) |
                                        ((lookup[base64encode[i+1]] & 0b00110000) >> 4));
        base64decode += static_cast<char> (((lookup[base64encode[i+1]] & 0b00001111) << 4) |
                                        ((lookup[base64encode[i+2]] & 0b00111100) >> 2));
        base64decode += static_cast<char> (((lookup[base64encode[i+2]] & 0b00000011) << 6) |
                                        ((lookup[base64encode[i+3]] & 0b00111111)));

        DEBUG("TSTING Base Deciding: "  + base64decode)
    }

    PRINT("The Endcoded String: " + base64encode)
    PRINT("The Decoded String: " + base64decode)

    // Output the data to text file.
    ofstream outfile(file.substr(0, file.length()-3) + ".out");
    outfile << base64decode;
    outfile.close();

    return 0;
}