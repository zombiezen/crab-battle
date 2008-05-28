/*
 *  util.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/27/08.
 *  $Id$
 */

#include "util.h"
#include "exceptions.h"
#include <fstream>

using namespace std;

vector<string> CrabBattle::LoadConfigFile(const char *fname)
{
    ifstream file;
    string buffer;
    vector<string> result;
    // Open file
    file.open(fname);
    if (!file.is_open())
        throw FileNotFoundError(fname);
    // Read in file
    while (file)
    {
        getline(file, buffer);
        result.push_back(buffer);
    }
    // Close file
    file.close();
    // Return result
    return result;
}
