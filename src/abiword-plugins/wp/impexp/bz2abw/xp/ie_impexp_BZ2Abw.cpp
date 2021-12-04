/* AbiWord
 * Copyright (C) 2001 Dom Lachowicz <doml@appligent.com>
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

#include <stdio.h>
#include <bzlib.h>

#include "ie_imp_AbiWord_1.h"
#include "ie_exp_AbiWord_1.h"

#include "ut_string.h"
#include "ut_types.h"

#include "xap_Module.h"

#define PLUGIN_NAME "AbiBZ2::AWML-1.1/compressed (bzip2)"

/************************************************************************/
/************************************************************************/

/*********************************/
/* Exporter class */
/*********************************/

class ABI_EXPORT IE_Exp_BZ2AbiWord : public IE_Exp_AbiWord_1
{
public:

  /*!
   * Derive from the normal ABW export filter
   */
  IE_Exp_BZ2AbiWord(PD_Document * pDocument)
    : IE_Exp_AbiWord_1(pDocument, false), m_fp(0), m_bzout(0)
  {
  }

  virtual ~IE_Exp_BZ2AbiWord()
  {
  }
  
protected:

  /*!
   * Opens the bz2-compressed file. Extends IE_Exp::_openFile
   * Returns true if successful, false if not
   */
  bool _openFile(const char * szFilename)
  {
    UT_ASSERT(!m_bzout);
    UT_ASSERT(!m_fp);
    
    int d_error = 0;
    
    m_fp = fopen(szFilename, "wb");
    
    if (!m_fp)
      {
	return false;
      }
    
    // smallest memory block-sizes, non-verbose output, 
    // default compression level
    m_bzout = BZ2_bzWriteOpen(&d_error, m_fp, 1, 0, 0);
    
    if (d_error != BZ_OK)
      {
	return false;
      }
    
    return (m_bzout != 0);
  }
  
  /*!
   * Write length number of pBytes to the BZ2-compressed file
   * Return number of bytes written, or 0 if none written
   * Extends IE_Exp::_writeBytes
   */
  UT_uint32 _writeBytes(const UT_Byte * pBytes, UT_uint32 length)
  {
    UT_ASSERT(m_fp);
    UT_ASSERT(m_bzout);

    if (!pBytes || !length)
      return 0;
    
    int d_error = 0;
    BZ2_bzWrite(&d_error, m_bzout, (void*)pBytes, length);
    
    if(d_error != 0)
      {
	return 0;
      }
    return length;
  }

  /*!
   * Close our BZ2-compressed file. Extends IE_Exp::_closeFile
   * Return true if successful, false if not
   */
  bool _closeFile(void)
  {
    int d_error = 0;
    
    if (m_bzout) {
      // no need to get back byte counts... 0=NULL=don't report
      BZ2_bzWriteClose(&d_error, m_bzout, 0, 0, 0);
      m_bzout = 0;
    }
    if (m_fp) {
      fclose (m_fp);
      m_fp = 0;
    }
    return true;
  }
  
private:
  FILE   *m_fp;
  BZFILE *m_bzout;
};

/*********************************/
/* Export sniffer */
/*********************************/

class ABI_EXPORT IE_Exp_BZ2AbiWord_Sniffer 
  : public IE_ExpSniffer
{
  friend class IE_Exp;
  
public:
  IE_Exp_BZ2AbiWord_Sniffer () :
    IE_ExpSniffer(PLUGIN_NAME)
  {
    // 
  }

  virtual ~IE_Exp_BZ2AbiWord_Sniffer () {}

  /*!
   * Recognize the bz2 suffixes
   */
  virtual bool recognizeSuffix (const char * szSuffix)
  {
    return (!UT_stricmp(szSuffix,".bzabw") || 
	    !UT_stricmp(szSuffix, ".abw.bz2"));
  }

  /*!
   * Get the dialog lables and the file type
   */
  virtual bool getDlgLabels (const char ** pszDesc,
			     const char ** pszSuffixList,
			     IEFileType * ft)
  {
    *pszDesc = "BZ2 AbiWord (.bzabw)";
    *pszSuffixList = "*.abw.bz2; *.bzabw";
    *ft = getFileType();
    return true;
  }

  /*!
   * Construct an exporter object to actually write to
   */
  virtual UT_Error constructExporter (PD_Document * pDocument,
				      IE_Exp ** ppie)
  {
    IE_Exp_BZ2AbiWord * p = new IE_Exp_BZ2AbiWord(pDocument);
    *ppie = p;
    return UT_OK;
  }
};

/************************************************************************/
/************************************************************************/

/*********************************/
/* Importer Class */
/*********************************/

class ABI_EXPORT IE_Imp_BZ2AbiWord : 
  public IE_Imp_AbiWord_1, public UT_XML::Reader
{
private:
  FILE   *m_fp;
  BZFILE *m_bzin;
  
public:

  /*!
   * Open the bz2-compressed file. Return true if successful, false
   * if not. Extends UT_XML::Reader
   */
  virtual bool openFile (const char * szFilename) 
  {
    UT_ASSERT (m_bzin == 0);
    
    m_fp = fopen (szFilename, "rb");
    if (!m_fp) return false;
    
    int d_error = 0;
    m_bzin = BZ2_bzReadOpen (&d_error, m_fp, 0, 0, NULL, 0);
    if (d_error != BZ_OK) return false;
    return (m_bzin != NULL);
  }

  /*!
   * Read at most length bytes from our file into buffer, and return
   * the number of bytes read. Extends UT_XML::Reader
   */
  virtual UT_uint32 readBytes (char * buffer, UT_uint32 length) 
  {
    UT_ASSERT (m_bzin);
    
    int d_error = 0;
    return BZ2_bzRead (&d_error, m_bzin, buffer, length);
  }
  
  /*!
   * Close the underlying file stream. Extends UT_XML::Reader
   */
  virtual void closeFile (void)
  {
    if (m_bzin) {
      int d_error = 0;
      BZ2_bzReadClose (&d_error, m_bzin); 
      m_bzin = 0;
    }
    if (m_fp) {
      fclose (m_fp);
      m_fp   = 0;
    }
  }
  
  /*!
   * Public virtual d'tor
   */
  virtual ~IE_Imp_BZ2AbiWord ()
  {
    closeFile ();
  }
  
  /*!
   * Public importer class
   */
  IE_Imp_BZ2AbiWord (PD_Document * pDocument)
    : IE_Imp_AbiWord_1(pDocument),
      m_fp(0),
      m_bzin(0)
  {
    setReader (this); // IE_Imp_BZ2AbiWord derives from UT_XML::Reader
  }
};

/*********************************/
/* Import Sniffer */
/*********************************/

class ABI_EXPORT IE_Imp_BZ2AbiWord_Sniffer : public IE_ImpSniffer
{
  friend class IE_Imp;

public:
  IE_Imp_BZ2AbiWord_Sniffer () :
    IE_ImpSniffer(PLUGIN_NAME)
  {
    // 
  }

  /*!
   * Return true if we recognize the contents in szBuf,
   * false if we don't
   */
  virtual UT_Confidence_t recognizeContents (const char * szBuf, 
				  UT_uint32 iNumbytes)
  {
    // i think that this is the correct BZ2 header
    // but this is bogus - it will recognize any bz2 document
    if (!strncmp(szBuf, "BZh", 3)) 
      return UT_CONFIDENCE_POOR;
    return UT_CONFIDENCE_ZILCH;
  }
  
  /*!
   * Return true if we recognize the suffix szSuffix,
   * false if not
   */
  virtual UT_Confidence_t recognizeSuffix (const char * szSuffix)
  {
    if (!UT_stricmp(szSuffix,".bzabw") || 
	!UT_stricmp(szSuffix,".abw.bz2"))
      return UT_CONFIDENCE_PERFECT;
    return UT_CONFIDENCE_ZILCH;
  }

  /*!
   * Get the dialog labels and file type
   */
  virtual bool getDlgLabels (const char ** szDesc,
			     const char ** szSuffixList,
			     IEFileType * ft)
  {
    *szDesc = "BZipped AbiWord (.bzabw)";
    *szSuffixList = "*.bzabw; *.abw.bz2";
    *ft = getFileType();
    return true;
  }
  
  /*!
   * Construct an importer object to actually do stuff with
   * Return UT_OK on success, anything else if not
   */
  virtual UT_Error constructImporter (PD_Document * pDocument,
				      IE_Imp ** ppie)
  {
    *ppie = new IE_Imp_BZ2AbiWord(pDocument);;
    return UT_OK;
  }
};
  
/*********************************/
/* General plugin stuff */
/*********************************/

ABI_PLUGIN_DECLARE("BZ2Abw")

// we use a reference-counted sniffer
static IE_Imp_BZ2AbiWord_Sniffer * m_impSniffer = 0;
static IE_Exp_BZ2AbiWord_Sniffer * m_expSniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
  if (!m_impSniffer)
    {
      m_impSniffer = new IE_Imp_BZ2AbiWord_Sniffer ();
    }
  else
    {
      m_impSniffer->ref();
    }
  
  if (!m_expSniffer)
    {
      m_expSniffer = new IE_Exp_BZ2AbiWord_Sniffer ();
    }
  else
    {
      m_expSniffer->ref();
    }

  mi->name    = "BZ2AbiWord Import/Export Filter";
  mi->desc    = "Import & Export BZ2AbiWord Documents";
  mi->version = ABI_VERSION_STRING;
  mi->author  = "Dom Lachowicz <cinamod@hotmail.com>";
  mi->usage   = "No Usage";
  
  IE_Imp::registerImporter (m_impSniffer);
  IE_Exp::registerExporter (m_expSniffer);
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
  UT_ASSERT (m_expSniffer);

  IE_Imp::unregisterImporter (m_impSniffer);
  if (!m_impSniffer->unref())
    {
      m_impSniffer = 0;
    }

  IE_Exp::unregisterExporter (m_expSniffer);
  if(!m_expSniffer->unref())
    {
      m_expSniffer = 0;
    }

  return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
				 UT_uint32 release)
{
  return 1;
}
