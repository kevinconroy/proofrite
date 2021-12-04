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

#ifndef LINK_GRAMMAR_CHECKER_H
#define LINK_GRAMMAR_CHECKER_H

#include "GrammarChecker.h"

/*
 * DISCLAIMER
 *
 * This class uses the Link Grammar checker, by
 * Davy Temperley, Daniel Sleator, John Lafferty, and (potentially) others. 
 * Link can be found at http://www.link.cs.cmu.edu/link/
 *
 * As for license (in)compatibilities, according to the Link webpage:
 * "Everybody is welcome to take the system and work with it. 
 *  If you would like to use it in a commercial product or service, 
 *  please contact us."
 *
 * AbiWord as a whole is not a commercial application. This plugin in specific
 * is not a commercial application, nor will it become one (or part of one).
 *
 * Link's license can be found (along with contact information) at:
 *
 * ftp://ftp.cs.cmu.edu/usr/ftp/usr/sleator/link-grammar/system-4.1/link-4.1/README
 *
 * HOWEVER
 *
 * The terms of the GPL *seemingly* make it impossible for AbiWord to link
 * against the Link grammar checker because of Link's alleged GPL-incompatible
 * license. If you compile and link this particular GrammarChecker instance 
 * class to the GPL AbiWord sources, you may be infringing upon the GPL and 
 * may suffer any number of unpleasant consequences resulting from your 
 * actions.
 *
 * We are currently in the process of contacting the Link authors and asking
 * them to modify their license (dual-license, perhaps) their grammar checker
 * to be GPL compatible. When and if they respond, we will modify/ammend this
 * disclaimer to include the proper instructions, warnings, etc... that
 * coincide with their new license or finalized stance on their current 
 * license.
 *
 * UNTIL LINK IS RELICENSED OR LINK'S LICENSE IS SHOWN TO INDEED BE GPL 
 * COMPATIBLE, THIS CLASS IS TO BE USED FOR EDUCATIONAL PURPOSES ONLY. It is
 * meant to show people how to use the Link API, the Abi plugin architecture,
 * and so forth. If you choose to not heed this warning, you do so at your own
 * risk and peril. Consider yourselves to be forewarned.
 *
 * If you are at all hesitant to compile this file, don't. What *is* legal
 * is for you to change the below #include statement to instead #include
 * my dummy-link-includes.h file, shipped inside of this plugin. Why you'd
 * want to do that is beyond me, but fully within your right AND 100%
 * permissible under the terms of the GPL.
 *
 * Dom Lachowicz
 * March 8, 2002
 *
 */

extern "C" {
#include "link-includes.h"
}

// see DISCLAIMER
#warning "You're using the Link Grammar Checker. You're probably doing something in violation of the GPL"

class ABI_EXPORT LinkGrammarChecker : public IGrammarChecker
{

public:
  LinkGrammarChecker () throw ()
    : IGrammarChecker (), mDict ( 0 ), mOpts ( 0 )
  {
    if ( !( mDict  = dictionary_create ( "4.0.dict", "4.0.knowledge", 
					 "4.0.constituent-knowledge", "4.0.affix") ) )
      throw mDict ;

    mOpts  = parse_options_create ();
  }

  virtual ~LinkGrammarChecker ()
  {
    if ( mOpts )
      {
	parse_options_delete( mOpts );
      }

    if ( mDict )
      {
	dictionary_delete( mDict );
      }
  }

  virtual bool check ( const char * input_string )
  {
    Sentence sent = sentence_create( const_cast< char * >( input_string ), 
				     mDict );

    if ( !sent )
      return false ;

    bool ret = sentence_parse( sent, mOpts ) == 1;
    sentence_delete ( sent ) ;
  }

private:
  Dictionary mDict ;
  Parse_Options mOpts ;
} ;

typedef LinkGrammarChecker IGrammarCheckerInstance ;

#endif // LINK_GRAMMAR_CHECKER_H
