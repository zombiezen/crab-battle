/*
 *  exceptions.cpp
 *  Crab Battle
 *
 *  Created by Ross Light on 5/7/08.
 *  $Id$
 *
 *  Copyright (C) 2008 Ross Light, TJ Ferrell, and Ephraim Ruprecht.
 *
 *  This file is part of Crab Battle.
 *
 *  Crab Battle is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Crab Battle is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Crab Battle.  If not, see <http://www.gnu.org/licenses/>.
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
