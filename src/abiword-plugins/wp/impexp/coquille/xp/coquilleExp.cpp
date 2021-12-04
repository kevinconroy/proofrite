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

#include	"coquille.h"
#include	"coquilleExp.h"

#include	<time.h>

/* AbiWord includes */
#include	"pd_Document.h"

#include	"ut_vector.h"

extern int m_dDay, m_dMonth, m_dYear;
/* IE_Exp_Coquille_Sniffer ***************************************************/
IE_Exp_Coquille_Sniffer::IE_Exp_Coquille_Sniffer () :
  IE_ExpSniffer(COQUILLE_PLUGIN_NAME)
{
}

IE_Exp_Coquille_Sniffer::~IE_Exp_Coquille_Sniffer ()
{
}

bool IE_Exp_Coquille_Sniffer::recognizeSuffix (const char * szSuffix)
{
	if (!(UT_stricmp (szSuffix, "."DOCUMENT_EXT)))
		return true;
	return false;
}

bool IE_Exp_Coquille_Sniffer::getDlgLabels (
		const char ** pszDesc,
		const char ** pszSuffixList,
		IEFileType * ft
	)
{
	*pszDesc = DOCUMENT_NAME " (." DOCUMENT_EXT ")";
	*pszSuffixList = "*." DOCUMENT_EXT;
	*ft = getFileType ();
	return true;
}

UT_Error IE_Exp_Coquille_Sniffer::constructExporter (
		PD_Document * pDocument,
		IE_Exp ** ppie
	)
{
	IE_Exp_Coquille * p = new IE_Exp_Coquille (pDocument);
	*ppie = p;
	return UT_OK; 
}
/*****************************************************************************/


/* IE_Exp_Coquille ***********************************************************/
IE_Exp_Coquille :: IE_Exp_Coquille (PD_Document * pDocument)
	: IE_Exp_DocBook (pDocument)
{
}

IE_Exp_Coquille :: ~IE_Exp_Coquille ()
{
}

/*****************************************************************************/


/* s_Coquille_Listener *******************************************************/
s_Coquille_Listener :: s_Coquille_Listener (
		PD_Document *pDocument,
		IE_Exp_Coquille *pie
	)
	: s_DocBook_Listener (pDocument, pie)
{
}

s_Coquille_Listener :: ~s_Coquille_Listener (void)
{
}

bool s_Coquille_Listener :: _initFile (void)
{	
	UT_Vector *header_values = get_header ();
	/* ecrit le header */
	time_t doc_time;	// Current time
	struct tm *doc_date;	// Current date

	((IE_Exp_Coquille *) m_pie) -> writeln ("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
	((IE_Exp_Coquille *) m_pie) -> writeln ("<!DOCTYPE coq-document PUBLIC \"-//INFOBI//DTD Oeuf Coquille XML V1.0\"");
	((IE_Exp_Coquille *) m_pie) -> writeln ("\t\t\t\"http://www.infobi.com/dtd/coquille.dtd\">");
	((IE_Exp_Coquille *) m_pie) -> writeln ("<coq-document>");
	((IE_Exp_Coquille *) m_pie) -> indent ();
	((IE_Exp_Coquille *) m_pie) -> writeln ("<coq-head>");
	((IE_Exp_Coquille *) m_pie) -> indent ();

	for (int i = 0; i < (header_values -> getItemCount()); i++)
	{
		keyvalue *kv = (keyvalue *) (header_values -> getNthItem (i));
		((IE_Exp_Coquille *) m_pie) -> iwrite ("<");
		((IE_Exp_Coquille *) m_pie) -> write ((kv -> m_key) -> c_str ());
		((IE_Exp_Coquille *) m_pie) -> write (" value=\"");
		((IE_Exp_Coquille *) m_pie) -> write ((kv -> m_value) -> c_str());
		((IE_Exp_Coquille *) m_pie) -> write ("\"/>\n");

	}

	/* date creation */
	((IE_Exp_Coquille *) m_pie) -> iwrite ("<coq-date-creation");
	char date [12];
	sprintf (
			date, 
			" d=\"%02d\" m=\"%02d\" y=\"%04d\"",
			m_dDay, m_dMonth, m_dYear
		);
	m_pie -> write (date);
	m_pie -> write ("/>\n");

	/* date last update */
	((IE_Exp_Coquille *) m_pie) -> iwrite ("<coq-date-update");
	doc_time = time (NULL);
	doc_date = localtime (&doc_time);
	sprintf (
			date, 
			" d=\"%02d\" m=\"%02d\" y=\"%04d\"",
			doc_date -> tm_mday,		/* jour */
			doc_date -> tm_mon + 1,		/* mois */
			doc_date -> tm_year + 1900	/* année */
		);
	m_pie -> write (date);
	m_pie -> write ("/>\n");
	
	((IE_Exp_Coquille *) m_pie) -> unindent ();
	((IE_Exp_Coquille *) m_pie) -> writeln ("</coq-head>\n");
	((IE_Exp_Coquille *) m_pie) -> writeln ("<coq-body>");
	((IE_Exp_Coquille *) m_pie) -> indent ();
	return true;
}

void s_Coquille_Listener :: _closeFile (void)
{
	_closeChapter ();
	_handleDataItems();

	((IE_Exp_Coquille *) m_pie) -> unindent ();
	((IE_Exp_Coquille *) m_pie) -> writeln ("</coq-body>");
	((IE_Exp_Coquille *) m_pie) -> unindent ();
	((IE_Exp_Coquille *) m_pie) -> writeln ("</coq-document>");
}
/*****************************************************************************/

/*****************************************************************************/
UT_Error IE_Exp_Coquille :: _writeDocument(void)
{
	m_pListener = new s_Coquille_Listener (getDoc(), this);

	if (!m_pListener)
		return UT_IE_NOMEMORY;
	if (! m_pListener -> _initFile ())
		return UT_ERROR;

	if (!(getDoc()->tellListener(static_cast<PL_Listener *>(m_pListener))))
		return UT_ERROR;
	m_pListener -> _closeFile ();
	delete m_pListener;

	m_pListener = NULL;
	
	return ((m_error) ? UT_IE_COULDNOTWRITE : UT_OK);
}
/*****************************************************************************/

/* TODO: il manque aussi plein de fonctions **********************************/
#if 0
bool s_Coquille_Listener :: populate (PL_StruxFmtHandle, const PX_ChangeRecord *)
{
	return true;
}

bool s_Coquille_Listener :: populateStrux
	(
		PL_StruxDocHandle,
		const PX_ChangeRecord *,
		PL_StruxFmtHandle *
	)
{
	return true;
}

bool s_Coquille_Listener :: change (PL_StruxFmtHandle, const PX_ChangeRecord *)
{
	return true;
}

bool s_Coquille_Listener :: insertStrux
	(
		PL_StruxFmtHandle,
		const PX_ChangeRecord *,
		PL_StruxDocHandle,
		PL_ListenerId,
		void (* pfnBindHandles)
			(
				PL_StruxDocHandle,
				PL_ListenerId,
				PL_StruxFmtHandle
			)
	)
{
	return true;
}

bool s_Coquille_Listener :: signal(UT_uint32)
{
	return true;
}
#endif
/*****************************************************************************/
