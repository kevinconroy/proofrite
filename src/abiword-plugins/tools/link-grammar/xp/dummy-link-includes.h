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

/*
 * This file includes dummy implementations of the Link
 * Grammar checker API bits that AbiWord uses. The calls 
 * don't actually do anything other than return dummy values
 * and as such, aren't useful in real life. The structs are
 * equally meaningless.
 */

#ifndef DOM_LINK_INCLUDES
#define DOM_LINK_INCLUDES

#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
  int dummy ;
} DictionaryStr, *Dictionary;

typedef struct
{
  int dummy ;
} SentenceStr, *Sentence;

typedef struct
{
  int dummy ;
} Parse_OptionsStr, *Parse_Options;

Dictionary dictionary_create ( const char * dict,
			       const char * knowledge,
			       const char * constituent_knowledge,
			       const char * affix )
{
  return ( Dictionary ) malloc ( sizeof ( DictionaryStr ) ) ;
}

void dictionary_delete ( Dictionary dict )
{
  free ( dict ) ;
}

Sentence sentence_create ( char * string,
			   Dictionary dict )
{
  return ( Sentence )malloc ( sizeof ( SentenceStr ) ) ;
}

int sentence_parse( Sentence sent, Parse_Options opts )
{
  /* false */
  return 0 ;
}

void sentence_delete( Sentence sent )
{
  free ( sent ) ;
}

Parse_Options parse_options_create ( void )
{
  return ( Parse_Options )malloc ( sizeof( Parse_OptionsStr ) );
}

void parse_options_delete( Parse_Options opts )
{
  free ( opts ) ;
}

#endif /* DOM_LINK_INCLUDES */
