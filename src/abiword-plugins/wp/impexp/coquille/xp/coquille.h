/* AbiWord
 * Copyright (C) 2002 Nicolas Mercier <nscreetch@free.fr>
 * Copyright (C) 1998 AbiSource, Inc.
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
 */

/*****************************************************************************\
* projet Oeuf - Coquille : module d'importation/exportation de fichier pour   *
*                          Abiword                                            *
* Nicolas MERCIER <nmr@infobi.com>                                            *
*                                                                             *
* 05/07/2002                                                                  *
\*****************************************************************************/

#ifndef		_COQUILLE_HH
#define		_COQUILLE_HH
/*****************************************************************************/
#include "ie_imp_XML.h"
#include	"ut_string_class.h"
#define	DOCUMENT_NAME	"Coquille"
#define DOCUMENT_EXT	"coq"

#define COQUILLE_PLUGIN_NAME "AbiCoquille::DocBook (Coquille)"

class keyvalue
{
	public:
		keyvalue (char *key, char *value);
		~keyvalue ();
		UT_String *m_key, *m_value;
};
UT_Vector * get_header ();

/*****************************************************************************/
#endif		/*!_COQUILLE_HH*/
