/*
 * Grammar Checker plugin for AbiWord
 * Copyright (C) 2002 by Dom Lachowicz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */

#ifndef GRAMMAR_CHECKER_H
#define GRAMMAR_CHECKER_H

#include "ut_types.h"
#include "xap_Frame.h"

class ABI_EXPORT IGrammarChecker
{
public:
  
  virtual ~IGrammarChecker ()
  {
  }

  virtual bool check ( const char * sentence ) = 0 ;

  virtual bool check ( const UT_String & sentence )
  {
    return check ( sentence.c_str() ) ;
  }

protected:

  IGrammarChecker () 
  {
  }

private:


  // no impl
  IGrammarChecker ( const IGrammarChecker & other ) ;
  IGrammarChecker  & operator= ( const IGrammarChecker & other ) ;

} ;

// typedef MyGrammarCheckerClass IGrammarCheckerInstance ;

// work begins on a grammar checking dialog

class ABI_EXPORT IGrammarCheckerDialog 
{
 public:
  IGrammarCheckerDialog * static_constructor () ;

 private:
} ;

#endif // GRAMMAR_CHECKER_H
