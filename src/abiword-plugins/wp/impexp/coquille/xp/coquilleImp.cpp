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

#include	"ut_string.h"

/*****************************************************************************\
* Importation de document au format Coquille                                  *
\*****************************************************************************/
#include	"coquille.h"
#include	"coquilleImp.h"
#include "ut_debugmsg.h"
#include	"ut_vector.h"



/* useful macros */
#define X_TestParseState(ps)	((m_parseState==(ps)))
#define X_TestExtendedParseState(ps)	((m_extendedParseState==(ps)))

#define X_VerifyParseState(ps)	do {  if (!(X_TestParseState(ps)))			\
									  { UT_DEBUGMSG(("DOM: X_VerifyParseState failed: %s\n", #ps)); \
									    m_error = UT_IE_BOGUSDOCUMENT;	\
										 return; } } while (0)
										 
#define X_VerifyExtendedParseState(ps)	do {  if (!(X_TestExtendedParseState(ps)))			\
									  { UT_DEBUGMSG(("DOM: X_VerifyExtendedParseState failed: %s\n", #ps)); \
									    m_error = UT_IE_BOGUSDOCUMENT;	\
										 return; } } while (0)
										 

#define X_CheckDocument(b)		do {  if (!(b))								\
									  { UT_DEBUGMSG(("DOM: X_CheckDocument failed: %s\n", #b)); \
									    m_error = UT_IE_BOGUSDOCUMENT;	\
										 return; } } while (0)

#define X_CheckError(v)			do {  if (!(v))								\
									  { UT_DEBUGMSG(("DOM: X_CheckError failed: %s\n", #v)); \
									    m_error = UT_ERROR;			\
										 return; } } while (0)

#define	X_EatIfAlreadyError()	do {  if (m_error) { UT_DEBUGMSG(("Already failed...\n")); return; } } while (0)

extern int m_dDay, m_dMonth, m_dYear;
/* IE_Imp_Coquille_Sniffer ***************************************************/
IE_Imp_Coquille_Sniffer :: IE_Imp_Coquille_Sniffer (void) :
  IE_ImpSniffer(COQUILLE_PLUGIN_NAME)
{
}

IE_Imp_Coquille_Sniffer :: ~IE_Imp_Coquille_Sniffer (void)
{
}

UT_Confidence_t IE_Imp_Coquille_Sniffer :: recognizeContents(
		const char * szBuf,
		UT_uint32 iNumbytes
	)
{
	/* TODO */
	//printf ("Coquille :: recognizeContents\n");
	return UT_CONFIDENCE_ZILCH;
}

UT_Confidence_t IE_Imp_Coquille_Sniffer :: recognizeSuffix (
		const char * szSuffix
	)
{
	if (UT_stricmp (szSuffix, "." DOCUMENT_EXT) == 0)
	{
		//printf ("OK.\n");
		return UT_CONFIDENCE_PERFECT;
	}
	return UT_CONFIDENCE_ZILCH;
}

UT_Error IE_Imp_Coquille_Sniffer :: constructImporter (
		PD_Document * pDocument,
		IE_Imp ** ppie
	)
{
	*ppie = (IE_Imp *) new IE_Imp_Coquille (pDocument);
	return UT_OK;
}

bool IE_Imp_Coquille_Sniffer :: getDlgLabels (
		const char **pszDesc,
		const char **pszSuffixList,
		IEFileType * ft
	)
{
	*pszDesc = DOCUMENT_NAME " (." DOCUMENT_EXT ")";
	*pszSuffixList = "*." DOCUMENT_EXT;
	*ft = getFileType ();

	return true;
}
/*****************************************************************************/


/* IE_Imp_Coquille ***********************************************************/
IE_Imp_Coquille :: IE_Imp_Coquille (PD_Document *pDocument)
	: IE_Imp_DocBook (pDocument)
{
		m_bInHead = false;
}

IE_Imp_Coquille :: ~IE_Imp_Coquille (void)
{
}

/*****************************************************************************/

/* docbook */
#define TT_OTHER		0               // anything else
#define TT_DOCUMENT	        1		// a document <book>
#define TT_SECTION              2               // card or section
#define TT_BLOCK		3		// a paragraph <para>
#define TT_PHRASE               4               // formatted text
#define TT_EMPHASIS             5               // emphasized (italic) text
#define TT_SUPERSCRIPT          6               // superscript
#define TT_SUBSCRIPT            7               // subscript
#define TT_BLOCKQUOTE           8               // block quote
#define TT_BRIDGEHEAD           9               // heading  <bridgehead ...>
#define TT_CHAPTER              10              // legacy abiword documents
#define TT_TITLE                11              // title
#define	TT_PAGEBREAK		12
#define	TT_PLAINTEXT		13
#define	TT_LINK			14
#define	TT_ULINK		15
#define	TT_BOOKMARK		16
#define	TT_FIGURE		17
#define	TT_MEDIAOBJECT		18
#define	TT_IMAGEOBJECT		19
#define	TT_IMAGEDATA		20

/* coquille */
#define	TT_HEAD			28
#define	TT_BODY			29

static struct xmlToIdMapping s_Tokens_coq [] =
{
	/* classer la liste des tokens DANS L'ORDRE ALPHABETIQUE *****************/
	{	"anchor",		TT_BOOKMARK		},
	{	"beginpage",		TT_PAGEBREAK		},
	{       "blockquote",           TT_BLOCKQUOTE           },
	{	"book",			TT_DOCUMENT		},
	{       "bridgehead",           TT_BRIDGEHEAD           },
	{       "chapter",              TT_CHAPTER              },
	{ "coq-body", TT_BODY },
	{ "coq-head", TT_HEAD },
	{ "document", TT_DOCUMENT },
	{       "emphasis",             TT_EMPHASIS             },
	{	"figure",		TT_FIGURE		},
	{	"imagedata",		TT_IMAGEDATA		},
	{	"imageobject",		TT_IMAGEOBJECT		},
	{	"link",			TT_LINK			},
	{	"mediaobject",		TT_MEDIAOBJECT		},
	{	"para",			TT_BLOCK		},
	{       "phrase",               TT_PHRASE               },
	{	"programlisting",	TT_PLAINTEXT		},
	{       "section",              TT_SECTION              },
	{       "subscript",            TT_SUBSCRIPT            },
	{       "superscript",          TT_SUPERSCRIPT          },
	{       "title",                TT_TITLE                },
	{	"ulink", 		TT_ULINK 		},
	{	"xref",			TT_LINK			}
	/*************************************************************************/
};
#define		TokenTableSize	(sizeof (s_Tokens_coq) / sizeof (s_Tokens_coq [0]))

/*****************************************************************************/
/* this function is called when a beginning tag (< > or < />) is found. */
void IE_Imp_Coquille :: startElement (const char *name, const char **atts)
{
	UT_DEBUGMSG(("Coquille import: startElement: %s\n", name));

	UT_Vector *header_values = get_header ();

	// xml parser keeps running until buffer consumed
	X_EatIfAlreadyError();


	if (m_bInHead)
	{
		if (UT_strcmp (name, "coq-date-creation") == 0)
		{
			const XML_Char *day, *month, *year;
			day = _getXMLPropValue((const XML_Char *)"d", atts);
			month = _getXMLPropValue((const XML_Char *)"m", atts);
			year = _getXMLPropValue((const XML_Char *)"y", atts);
			X_CheckError (day && month && year);
			m_dDay = atoi (day);
			m_dMonth = atoi (month);
			m_dYear = atoi (year);
		}
		else if (UT_strcmp (name, "coq-date-update") == 0)
		{
			X_CheckError (
					_getXMLPropValue((const XML_Char *)"d", atts) &&
					_getXMLPropValue((const XML_Char *)"m", atts) &&
					_getXMLPropValue((const XML_Char *)"y", atts)
				);		
		}
		else
		{
			const XML_Char *szValue = _getXMLPropValue((const XML_Char *)"value", atts);
			X_CheckError (szValue != NULL);
			/* already inserted? */
			for (int i = 0; i < (header_values -> getItemCount()); i++)
			{
				keyvalue *kv = (keyvalue *) (header_values -> getNthItem (i));
				if (UT_strcmp ((kv -> m_key) -> c_str (), name) == 0)
				{
					/* already inserted here. we replace the value */
//					delete kv -> m_value;
					kv -> m_value = new UT_String (szValue);
					return;
				}
			}

			/* if we go here, that means that we haven't inserted this key so far */
			header_values -> push_back (new keyvalue ((char *)name, (char *)szValue));
		}
	}
	else
	{
		UT_uint32 tokenIndex = _mapNameToToken (name, s_Tokens_coq, TokenTableSize);
		
		switch (tokenIndex)
		{
		case TT_DOCUMENT:
			return;

		case TT_HEAD:
			m_bInHead = true;
			return;

		case TT_BODY:
			/* starts the document */
			/* is like the "book" command in docbook */
			IE_Imp_DocBook :: startElement ("book", NULL);
			return;

		case TT_TITLE:
			IE_Imp_DocBook :: startElement (name, atts);
			return;

		case TT_OTHER:
		default:
			IE_Imp_DocBook :: startElement (name, atts);
			return;
		}
	}
}

/* this function is called when an ending tag (</ > or < />) is found. */
void IE_Imp_Coquille :: endElement (const char *name)
{
    UT_DEBUGMSG(("Coquille import: endElement: %s\n", name));

    // xml parser keeps running until buffer consumed
	X_EatIfAlreadyError();
	
	if (m_bInHead)
	{
		if ((strcmp ("coq-date-update", name) == 0) || (strcmp ("coq-date-creation", name) == 0))
			return;
		if (UT_strcmp (name, "coq-head") == 0)
			m_bInHead = false;
		/*else
			*/
		return;
	}
	else
	{
		UT_uint32 tokenIndex = _mapNameToToken (name, s_Tokens_coq, TokenTableSize);

		switch (tokenIndex)
		{
		case TT_BODY:
			/* like </book> in docbook */
			IE_Imp_DocBook :: endElement ("book");
			return;
			
		case TT_TITLE:
			if (! m_bInHead)
				IE_Imp_DocBook :: endElement (name);
			return;

		/* end of document */
		case TT_DOCUMENT:
			return;
			
		case TT_OTHER:
		default:
			X_CheckError (! m_bInHead);
			IE_Imp_DocBook :: endElement (name);
			return;
		}
	}
}
/*****************************************************************************/

/*****************************************************************************/
void IE_Imp_Coquille::charData(const XML_Char *s, int len)
{
	if (m_bInHead)
	{
		/* we're in header, nothing is echoed */
		return;
	}
	IE_Imp_DocBook :: charData (s, len);
}
/*****************************************************************************/
