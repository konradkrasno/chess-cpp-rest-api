#pragma once
#include <iostream>
using std::string;


string const fileRange = "abcdefgh";
string const inverted_fileRange = "hgfedcba";
string const rankRange = "87654321";
string const inverted_rankRange = "12345678";

string ConvertFileAndRankToPosition(char file, char rank);
