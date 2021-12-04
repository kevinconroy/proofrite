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

#ifndef		_COQUILLEIMP_HH
#define		_COQUILLEIMP_HH
/*****************************************************************************/
#include	"ie_imp_DocBook.h"

class ABI_EXPORT IE_Imp_Coquille_Sniffer : public IE_ImpSniffer
{
	friend class IE_Imp;

	public:
		IE_Imp_Coquille_Sniffer (void);
		~IE_Imp_Coquille_Sniffer (void);

		UT_Confidence_t recognizeContents (const char *, UT_uint32);
		UT_Confidence_t recognizeSuffix (const char *);
		bool getDlgLabels (const char **, const char **, IEFileType *);
		UT_Error constructImporter (PD_Document *, IE_Imp **);

	protected:
	private:
};


class ABI_EXPORT IE_Imp_Coquille : public IE_Imp_DocBook
{
	public:
		IE_Imp_Coquille (PD_Document *);
		~IE_Imp_Coquille ();

		static bool RecognizeContents (const char *, UT_uint32);
		static bool RecognizeSuffix (const char *);
		static UT_Error StaticConstructor (PD_Document *, IE_Imp **);
		static bool GetDlgLabels (const char **, const char **, IEFileType *);
		static bool SupportsFileType (IEFileType);
		
		void startElement (const char *, const char **);
		void endElement (const char *);
		void charData(const XML_Char *s, int len);

	protected:
		bool m_bInHead;
		int m_iHeadSection;
	private:
};

/*****************************************************************************/
#endif		/*!_COQUILLEIMP_HH*/
