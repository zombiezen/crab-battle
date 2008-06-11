/*
 *  exceptions.h
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

#include <exception>

#ifndef _CRAB_BATTLE_EXCEPTIONS_H_
#define _CRAB_BATTLE_EXCEPTIONS_H_

namespace CrabBattle
{
    class FileNotFoundError : public std::exception
    {
    private:
        const char *fname;
    public:
        FileNotFoundError(const char *) throw();
        virtual const char *what(void) const throw();
    };
}

#endif
