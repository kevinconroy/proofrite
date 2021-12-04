/* Abiword
 * Copyright (C) 2001 Christian Biesinger <cbiesinger@web.de>
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

#include <memory.h>
#include "ie_imp.h"
#include "ut_types.h"
#include "ut_string.h"
#include "ut_iconv.h"
#include "ut_debugmsg.h"
#include "pd_Document.h"
#include "libole2/ms-ole.h"

static const UT_Byte hwpSignature[] = {0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1};


// -------------------------------------------------------------------------------------
// The importer
class ABI_EXPORT IE_Imp_Hancom : public IE_Imp {
	public:
		IE_Imp_Hancom(PD_Document *pDoc);
		virtual ~IE_Imp_Hancom();

		virtual UT_Error importFile(const char* szFilename);
	private:
		MsOle* mDoc;
		MsOleStream* mTextStream;
};

IE_Imp_Hancom::IE_Imp_Hancom(PD_Document* pDoc) : IE_Imp(pDoc), mDoc(NULL), mTextStream(NULL) {
}

IE_Imp_Hancom::~IE_Imp_Hancom() {
	if (mTextStream)
		ms_ole_stream_close(&mTextStream);
	if (mDoc)
		ms_ole_destroy(&mDoc);
}

UT_Error IE_Imp_Hancom::importFile(const char* szFilename) {
	MsOleErr err = ms_ole_open(&mDoc, szFilename);
	if (err != MS_OLE_ERR_OK)
		return UT_IE_BOGUSDOCUMENT;
	err = ms_ole_stream_open(&mTextStream, mDoc, "/", "PrvText", 'r');
	if (err != MS_OLE_ERR_OK)
		return UT_IE_BOGUSDOCUMENT;

	MsOleStat s;
	err = ms_ole_stat(&s, mDoc, "/", "PrvText");
	if (err != MS_OLE_ERR_OK)
		return UT_IE_BOGUSDOCUMENT;

	UT_DEBUGMSG(("HANCOM: Text length = %lu bytes\n", s.size));
	char* buf = new char[s.size];
	if (!buf)
		return UT_IE_NOMEMORY;
	if (!ms_ole_stream_read_copy(mTextStream, (guint8*)buf, s.size)) {
		delete[] buf;
		UT_ASSERT_NOT_REACHED();
		return UT_IE_BOGUSDOCUMENT;
	}
	UT_uint32 length;
	UT_UCS4Char* text = (UT_UCS4Char*)UT_convert(buf, s.size, "UCS-2LE", UCS_INTERNAL, NULL, &length);
	delete[] buf;
	if (!text)
		return UT_IE_NOMEMORY;

	UT_DEBUGMSG(("HANCOM: Text successfully converted.\n"));

	if (!getDoc()->appendStrux(PTX_Section, NULL))
		return UT_IE_NOMEMORY;

	if (!getDoc()->appendStrux(PTX_Block, NULL))
		return UT_IE_NOMEMORY;

	if (!getDoc()->appendSpan(text, length/4))
		return UT_IE_NOMEMORY;

	return UT_OK;
}

// -------------------------------------------------------------------------------------
// Sniffer
class ABI_EXPORT IE_Imp_Hancom_Sniffer : public IE_ImpSniffer {
	public:
		IE_Imp_Hancom_Sniffer() :
		  IE_ImpSniffer("AbiHancom:HWP:")
		{
		  // 
		}
		virtual ~IE_Imp_Hancom_Sniffer() {}

		virtual UT_Confidence_t recognizeContents(const char* szBuf, UT_uint32 iNumBytes) {
			if (iNumBytes >= sizeof(hwpSignature))
				return (memcmp(szBuf, hwpSignature, sizeof(hwpSignature)) == 0) ? UT_CONFIDENCE_GOOD : UT_CONFIDENCE_ZILCH;
			return UT_CONFIDENCE_ZILCH;

		}
		virtual UT_Confidence_t recognizeSuffix(const char* szSuffix) {
			return (UT_stricmp(szSuffix, ".hwp") == 0) ? UT_CONFIDENCE_PERFECT : UT_CONFIDENCE_ZILCH;
		}
		virtual bool getDlgLabels(const char** szDesc, const char** szSuffixList, IEFileType *ft) {
			*szDesc = "Hancom Word (*.hwp)";
			*szSuffixList = "*.hwp";
			*ft = getFileType();
			return true;

		}
		virtual UT_Error constructImporter(PD_Document* pDocument, IE_Imp **ppie) {
			*ppie = new IE_Imp_Hancom(pDocument);
			if (!ppie)
				return UT_OUTOFMEM;
			return UT_OK;
		}

};

// -------------------------------------------------------------------------------------
// Plugin Code

#include "xap_Module.h"

ABI_PLUGIN_DECLARE("Hancom")

// we use a reference-counted sniffer
static IE_Imp_Hancom_Sniffer * m_impSniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    if (!m_impSniffer)
    {
    	m_impSniffer = new IE_Imp_Hancom_Sniffer ();
    }
    else
    {
	m_impSniffer->ref();
    }

    mi->name    = "Hancom .hwp file importer";
    mi->desc    = "Imports Hancom binary (OLE) documents";
    mi->version = ABI_VERSION_STRING;
    mi->author  = "Christian Biesinger <cbiesinger@web.de>";
    mi->usage   = "No Usage";
  
    IE_Imp::registerImporter (m_impSniffer);
    return 1;
}

ABI_FAR_CALL
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;
  
    UT_ASSERT (m_impSniffer);

    IE_Imp::unregisterImporter (m_impSniffer);
    if(!m_impSniffer->unref())
    {
	m_impSniffer = 0;
    }

    return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
                                 UT_uint32 release)
{
    return 1;
}

