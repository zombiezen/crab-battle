/*
 *  exceptions.h
 *  Crab Battle
 *
 *  Created by Ross Light on 5/7/08.
 *  $Id$
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
