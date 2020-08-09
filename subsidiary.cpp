#include "subsidiary.h"

string ConvertFileAndRankToPosition(char file, char rank)
{
    string position;
    position += file;
    position += rank;
    return position;
}
