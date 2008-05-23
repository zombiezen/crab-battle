/*
 *  exceptions.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/7/08.
 *  $Id$
 */

#include "exceptions.h"
#include <cstdio>

using CrabBattle::FileNotFoundError;

FileNotFoundError::FileNotFoundError(const char *error_fname) throw() : exception()
{
    fname = error_fname;
}

const char *FileNotFoundError::what(void) const throw()
{
    using namespace std;
    char *buffer = new char[1024];
    sprintf(buffer, "Could not find file \"%s\"", fname);
    return buffer;
}
