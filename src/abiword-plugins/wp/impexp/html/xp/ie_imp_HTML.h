/* AbiWord: ie_imp_HTML - plugin for non-XHTML HTML
 * Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
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


#ifndef IE_IMP_HTML_H
#define IE_IMP_HTML_H

#include <stdio.h>

#include "HTML_Parser.h"
#include "HTML_StyleString.h"

#include "ut_string.h"
#include "ie_imp.h"

class UT_ByteBuf;
class PD_Document;
class IE_Imp;

class ABI_EXPORT IE_Imp_HTML_Sniffer : public IE_ImpSniffer
{
  friend class IE_Imp;

 public:
  IE_Imp_HTML_Sniffer ();
  ~IE_Imp_HTML_Sniffer () { }

  UT_Confidence_t supportsMIME (const char * szMIME);

  UT_Confidence_t recognizeContents (const char * szBuf, UT_uint32 iNumbytes);
  UT_Confidence_t recognizeSuffix (const char * szSuffix);
  bool getDlgLabels (const char ** szDesc, const char ** szSuffixList, IEFileType * ft);

  UT_Error constructImporter (PD_Document * pDocument, IE_Imp ** ppie);
};

class ABI_EXPORT IE_Imp_HTML : public IE_Imp, public HTML_Parser::Listener
{
 public:
  IE_Imp_HTML (PD_Document * pDocument);
  ~IE_Imp_HTML ();

  UT_Error importFile (const char * szFilename);

  // implementation of HTML_Parser::Listener
  void startElement (const char * name, const char ** atts);
  void endElement (const char * name);
  void charData (const char * buffer, int length);

  void addStyle (const char ** atts); // for internal use only - there's probably a better way to do this in C++

 private:
  void flushData ();
  void stripData ();

  void _Element (int token, const char * name, const char ** atts, bool start);

  bool m_hasContent;
  bool m_stripWhitespace;
  bool m_stripFirstspace;

  bool _Section (const char * type = 0);
  bool _Block (const char * style = 0, const char * props = 0);

  bool m_inSection;
  bool m_inBlock;

  bool m_bookmarkOpen;
  bool m_hyperlinkOpen;

  char * m_bookmark;  // name of bookmark being set
  char * m_hyperlink; // name of bookmark being set

  void bookmark (bool start);  // begin/end bookmark
  void hyperlink (bool start); // begin/end hyperlink

  enum DocumentPlace
  {
    dp_PreDocument = 0,
    dp_PreHead,
    dp_Head,
    dp_PreBody,
    dp_Body,
    dp_PostBody,
    dp_PostDocument
  };

  DocumentPlace m_DocumentPlace;

  enum CharDataMode
  {
    cdm_Ignore,
    cdm_Title,
    cdm_Body
  };

  CharDataMode m_CharDataMode;

  UT_ByteBuf * m_pBB;

  HTML_Parser * m_pHTML;

  class ABI_EXPORT TokenStack
    {
    public:
      TokenStack ();
      ~TokenStack ();

      bool reset ();

      bool push (int token);
      int pop (); // returns -1 on failure

      bool child_of_head ();
      bool child_of_body ();
      bool descendant_of (int token);

    private:
      bool grow ();

      int * m_stack;

      UT_uint32 m_count;
      UT_uint32 m_max;
    };

  TokenStack m_TokenStack;

  class ABI_EXPORT TextState
    {
    public:
      TextState ();
      ~TextState ();

      enum BlockStyle
      {
	bs_Normal = 0,
	bs_Heading1,
	bs_Heading2,
	bs_Heading3,
	bs_Heading4,
	bs_Heading5,
	bs_Heading6,
	bs_FixedNormal,
	bs_FixedHeading1,
	bs_FixedHeading2,
	bs_FixedHeading3,
	bs_FixedHeading4,
	bs_FixedHeading5,
	bs_FixedHeading6
      };

      enum ScriptStyle
      {
	ss_Normal = 0,
	ss_Super,
	ss_Sub
      };

      bool reset (BlockStyle bs = bs_Normal, bool truncate = true);

      bool push ();
      bool pop ();

      void setBold (bool bold = true)               { m_Text.bold = bold; }
      void setItalic (bool italic = true)           { m_Text.italic = italic; }
      void toggleItalic ()                          { m_Text.italic = (m_Text.italic ? false : true); }
      void setUnderline (bool underline = true)     { m_Text.underline = underline; }
      void setLineThrough (bool linethrough = true) { m_Text.linethrough = linethrough; }
      void setOverline (bool overline = true)       { m_Text.overline = overline; }

      void setFontFamily (const char * font_family)
	{
	  if (m_Text.font_family) free (m_Text.font_family);
	  m_Text.font_family = (font_family ? UT_strdup (font_family) : 0);
	}
      void setFontSize (const char * font_size) // Going to assume that font-size is <int>"pt"
	{
	  if (m_Text.font_size) free (m_Text.font_size);
	  m_Text.font_size = (font_size ? UT_strdup (font_size) : 0);
	}
      void scaleFontSize (float ratio);

      void setScriptStyle (ScriptStyle script_style = ss_Normal) { m_Text.script_style = script_style; }

      void setForeground (const char * color) // color is "" or 6-char hex-string e.g. "d6725c4"
	{
	  if (color)
	    {
	      for (int i = 0; i < 6; i++) m_Text.fg[i] = color[i];
	      m_Text.fg[6] = 0;
	    }
	  else
	    m_Text.fg[0] = 0;
	}
      void setBackground (const char * color) // color is "" or 6-char hex-string e.g. "d6725c4"
	{
	  if (color)
	    {
	      for (int i = 0; i < 6; i++) m_Text.bg[i] = color[i];
	      m_Text.bg[6] = 0;
	    }
	  else
	    m_Text.bg[0] = 0;
	}

      void defineStyles (IE_Imp_HTML * imp);

      char * getStyle () const { return m_style; }
      char * getProps (); // This string is maintained internally

    private:
      struct Text
      {
	bool bold;
	bool italic;
	bool underline;
	bool linethrough;
	bool overline;

	char * font_family;
	char * font_size;

	ScriptStyle script_style;

	char fg[7];
	char bg[7];
      };

      Text m_Text;

      bool grow ();

      Text * m_stack;

      UT_uint32 m_count;
      UT_uint32 m_max;

      char * m_style;

      HTML_StyleString m_props;
    };

  TextState m_TextState;

  UT_Error m_error;
};

#endif /* IE_IMP_HTML_H */
