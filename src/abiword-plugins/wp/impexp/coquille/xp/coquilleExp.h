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

#ifndef		_COQUILLEEXP_HH
#define		_COQUILLEEXP_HH
/*****************************************************************************/
#include	"pl_Listener.h"
#include	"ie_exp_DocBook.h"


class PD_Document;
class s_Coquille_Listener;

class ABI_EXPORT IE_Exp_Coquille_Sniffer : public IE_ExpSniffer
{
	friend class IE_Exp;

	public:
		IE_Exp_Coquille_Sniffer ();
		~IE_Exp_Coquille_Sniffer ();

		bool recognizeSuffix (const char *);
		bool getDlgLabels (const char **, const char **, IEFileType *);
		UT_Error constructExporter (PD_Document *, IE_Exp **);

	protected:
	private:
};


class ABI_EXPORT IE_Exp_Coquille : public IE_Exp_DocBook
{
	public:
		IE_Exp_Coquille (PD_Document * pDocument);
		~IE_Exp_Coquille ();
	

	protected:
		virtual UT_Error _writeDocument(void);
		s_Coquille_Listener *m_pListener;
		
	private:	
};


class s_Coquille_Listener : public s_DocBook_Listener
{
	public:
		s_Coquille_Listener (PD_Document *, IE_Exp_Coquille *);
		virtual ~s_Coquille_Listener (void);

//		virtual bool populate (PL_StruxFmtHandle, const PX_ChangeRecord *);
//		virtual bool populateStrux
//			(
//				PL_StruxDocHandle,
//				const PX_ChangeRecord *,
//				PL_StruxFmtHandle *
//			);
//		virtual bool change (PL_StruxFmtHandle, const PX_ChangeRecord *);
//		virtual bool insertStrux
//			(
//				PL_StruxFmtHandle,
//				const PX_ChangeRecord *,
//				PL_StruxDocHandle,
//				PL_ListenerId,
//				void (* pfnBindHandles)
//					(
//						PL_StruxDocHandle,
//						PL_ListenerId,
//						PL_StruxFmtHandle
//					)
//			);
//		virtual bool signal(UT_uint32);

		virtual bool		_initFile(void);
		virtual void		_closeFile(void);

	protected:
//		PD_Document *m_pDocument;
//		IE_Exp_Coquille *m_pie;
		char *author;
	
	private:
};


/*****************************************************************************/
#endif		/*!_COQUILLEEXP_HH*/
