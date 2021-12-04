/* AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
 * Copyright (C) 2001-2002 William Lachance (wlach@interlog.com)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
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

/* See bug 1764
 * This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef IE_IMP_WP_H
#define IE_IMP_WP_H

#include <stdio.h>
#include "ie_imp.h"

#include "ut_string.h"
#include "ut_string_class.h"

#include "ut_growbuf.h"
#include "ut_mbtowc.h"
#include "pd_Document.h"
#include "fl_AutoNum.h"

// The importer/reader for WordPerfect 6 documents.

#define WP_WORDPERFECT6789_EXPECTED_MAJOR_VERSION 2
#define WP_WORDPERFECT_DOCUMENT_FILE_TYPE 10
#define WP_FONT_TABLE_SIZE_GUESS 10
#define WP_FONT_NAME_MAX_LENGTH 256

#define WP_HEADER_PRODUCT_TYPE_OFFSET 8
#define WP_HEADER_FILE_TYPE_OFFSET 9
#define WP_HEADER_MAJOR_VERSION_OFFSET 10
#define WP_HEADER_MINOR_VERSION_OFFSET 11
#define WP_HEADER_ENCRYPTION_POSITION 12
#define WP_HEADER_DOCUMENT_POINTER_POSITION 4
#define WP_HEADER_DOCUMENT_SIZE_POSITION 20
#define WP_HEADER_INDEX_HEADER_POSITION 14

#define WP_INDEX_HEADER_NUM_INDICES_POSITION 2
#define WP_INDEX_HEADER_INDICES_POSITION 14
#define WP_INDEX_HEADER_ELEMENT_CHILD_PACKET_BIT 1
#define WP_INDEX_HEADER_GRAPHICS_BOX_STYLE 65

#define WP_INDEX_HEADER_PRINTER_SELECTION_DESCRIPTOR_POOL 0x23
#define WP_INDEX_HEADER_DESIRED_FONT_DESCRIPTOR_POOL 0x55
#define WP_INDEX_HEADER_INITIAL_FONT_DESCRIPTOR_POOL 0x25
#define WP_INDEX_HEADER_SYLE_DATA_DESCRIPTOR_POOL 0x30
#define WP_INDEX_HEADER_PREFIX_TIME_STAMP_DESCRIPTOR_POOL 0x5E
#define WP_INDEX_HEADER_UNDO_INFORMATION_DESCRIPTOR_POOL 0x77 // WordPerfect 6.1
#define WP_INDEX_HEADER_SHARED_PERSONAL_FILE_DATES_DESCRIPTOR_POOL 0x34
#define WP_INDEX_HEADER_DOCUMENT_SETTINGS_DESCRIPTOR_POOL 0x02
#define WP_INDEX_HEADER_NEXT_TOTAL_PAGE_COUNT_DESCRIPTOR_POOL 0x10
#define WP_INDEX_HEADER_WORLD_WIDE_WEB_DESCRIPTOR_POOL 0x6D
#define WP_INDEX_HEADER_EXTENDED_DOCUMENT_SUMMARY_DESCRIPTOR_POOL 0x12
#define WP_INDEX_HEADER_CHECK_AS_YOU_GO_DESCRIPTOR_POOL 0x4E

#define WP_INDEX_HEADER_OUTLINE_STYLE 49 // 0x31
#define WP_INDEX_HEADER_OUTLINE_STYLE_ARABIC_NUMBERING 0
#define WP_INDEX_HEADER_OUTLINE_STYLE_LOWERCASE_NUMBERING 1
#define WP_INDEX_HEADER_OUTLINE_STYLE_UPPERCASE_NUMBERING 2
#define WP_INDEX_HEADER_OUTLINE_STYLE_LOWERCASE_ROMAN_NUMBERING 3
#define WP_INDEX_HEADER_OUTLINE_STYLE_UPPERCASE_ROMAN_NUMBERING 4

#define WP_UNDO_GROUP_SIZE 5
#define WP_ATTRIBUTE_ON_GROUP_SIZE 3
#define WP_ATTRIBUTE_OFF_GROUP_SIZE 3

#define WP_CHARACTER_GROUP_FONT_FACE_CHANGE 26 // 0x1a
#define WP_CHARACTER_GROUP_FONT_SIZE_CHANGE 27 // 0x1b

#define WP_STYLE_GROUP_PARASTYLE_BEGIN_ON_PART1 4 // 0x04
#define WP_STYLE_GROUP_PARASTYLE_BEGIN_OFF_PART1 5 // 0x05
#define WP_STYLE_GROUP_PARASTYLE_BEGIN_ON_PART2 6 // 0x06
#define WP_STYLE_GROUP_PARASTYLE_BEGIN_OFF_PART2 7 // 0x07
#define WP_STYLE_GROUP_PARASTYLE_END_ON 8 // 0x08
#define WP_STYLE_GROUP_PARASTYLE_END_OFF 9 // 0x09

#define WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_BULLETED_NUMBERING 0
#define WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_ARABIC_NUMBERING 256
#define WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_LOWERCASE_NUMBERING 3
#define WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_LOWERCASE_ROMAN_NUMBERING 769

#define WP_CHARACTER_GROUP_PARAGRAPH_NUMBER_ON 50 // 0x32
#define WP_CHARACTER_GROUP_PARAGRAPH_NUMBER_OFF 51 // 0x33
#define WP_CHARACTER_GROUP_TABLE_DEFINITION_ON 0x2A
#define WP_CHARACTER_GROUP_TABLE_DEFINITION_OFF 0x2B
#define WP_CHARACTER_GROUP_TABLE_COLUMN 0x2C

#define WP_DISPLAY_NUMBER_REFERENCE_GROUP_PARAGRAPH_NUMBER_DISPLAY_ON 12
#define WP_DISPLAY_NUMBER_REFERENCE_GROUP_PARAGRAPH_NUMBER_DISPLAY_OFF 13

#define WP_BOX_GROUP_NUM_RESERVED_BYTES 14
#define WP_BOX_GROUP_OVERRIDE_FLAGS_BOX_CONTENT 8192

#define WP_NUM_LIST_LEVELS 8
// These are the defaults for generating list text
#define WP_PARAGRAPH_STYLE_MARGIN_LEFT_INCREMENT 0.5f // I have no idea if this is correct, but it seems to look reasonably good
#define WP_PARAGRAPH_STYLE_TEXT_INDENT_DECREMENT -0.3f // I have no idea if this is correct, but it seems to look reasonably good
// Character properties
class ABI_EXPORT WordPerfectTextAttributes
{
 public:

   WordPerfectTextAttributes();
   ~WordPerfectTextAttributes() {}

   // text attributes
   bool	m_extraLarge;
   bool	m_veryLarge;
   bool	m_large;
   bool m_smallPrint;
   bool	m_finePrint;
   bool m_superScript;
   bool m_subScript;
   bool m_outline;
   bool m_italics;
   bool m_shadow;
   bool m_redLine;
   bool m_bold;
   bool m_strikeOut;
   bool m_underLine;
   bool m_smallCaps;
   bool m_Blink;
   bool m_reverseVideo;
   // font stuff
   UT_uint16 m_fontSize;
};

struct ABI_EXPORT WordPerfectFontDescriptor
{
   WordPerfectFontDescriptor();
   ~WordPerfectFontDescriptor();

   int m_packetID;

   UT_uint16 m_characterWidth;
   UT_uint16 m_ascenderHeight;
   UT_uint16 m_xHeight;
   UT_uint16 m_descenderHeight;
   UT_uint16 m_italicsAdjust;
   UT_Byte m_primaryFamilyId; // family id's are supposed to be one unified element, but I split them up to ease parsing
   UT_Byte m_primaryFamilyMemberId;
   
   UT_Byte m_scriptingSystem;
   UT_Byte m_primaryCharacterSet;
   UT_Byte m_width;
   UT_Byte m_weight; 
   UT_Byte m_attributes;
   UT_Byte m_generalCharacteristics;
   UT_Byte m_classification;
   UT_Byte m_fill; // fill byte
   UT_Byte m_fontType;
   UT_Byte m_fontSourceFileType;
   char *m_fontName; // is this platform indep? oh yes it is, I think.
};

// Paragraph Properties (set using group WP_TOP_PARAGrAPH_GROUP)
struct ABI_EXPORT WordPerfectParagraphProperties
{
   WordPerfectParagraphProperties();
   //float m_lineHeight; // originally in "signed WPU" 0.0=default
   unsigned int m_lineSpacing; // d301
   // (TODO: leftHotZone) d302
   // TODO: rightHotZone) d303
   // (TODO: tab set definitions 0xd304)
   enum ParagraphJustification { left, full, center, right, fullAllLines, reserved };
   ParagraphJustification m_justificationMode;
   // (TODO hyphenationOn 0xd306
   // (TODO:leadingAdjustment) originally in "signed WPU" d307
   // (TODO: generated text?! 0xd308-0xd309)
   // (TODO: spacing after paragraph 0xd30a)
   // (TODO: indent first line of paragraph) 0xd30b
   // (TODO: left margin adjustment) 0xd30c
   // (TODO: right margin adjustment) 0xd30d
   // (TODO: outline define) 0xd30e
   // (TODO: paragraph border) 0xd30f
   // (TODO: define math columns) 0xd310
   // (TODO: math on/off) 0xd311
   // (TODO: line numbering def'n) 0xd312
   // (TODO: force odd/even/new) 0xd313
   // (TODO: endnotes print here) 0xd314
   // (TODO: endnotes print here end) 0xd315
   // (TODO: define marked text) 0xd316
   // (TODO: define drop cap) 0xd317
   // (TODO: paragraph text direction) 0xd318
   // (TODO: asian mapping) 0xd319
   // (TODO: paragraph character count) 0xd31a
};

struct WordPerfectHeaderPacket
{
   WordPerfectHeaderPacket(unsigned int PID, UT_uint8 type, long packetPosition, bool hasChildren);
   unsigned int m_PID;
   UT_uint8 m_type;
   long m_packetPosition;
   bool m_hasChildren;
};

class ABI_EXPORT WordPerfectListDefinition
{
 public:
   WordPerfectListDefinition(UT_uint16 outlineHash, UT_uint8 *packetNumberingMethods=0); // update list types based on information from a wordperfect outline define packet
   UT_uint16 getOutlineHash() { return m_outlineHash; }
   void setListID(int level, UT_uint32 id) { m_listIDs[level] = id; }
   UT_uint32 getListID(int level) { return m_listIDs[level]; }
   UT_uint16 getListNumber(int level) { return m_currentListNumbers[level]; }
   List_Type getListType(int level) { return m_listTypes[level]; }
   bool isLevelNumbered(int level) { return m_bIsNumberedList[level]; }
   UT_String getListDelim(int level) { return m_listDelim[level]; }
   
   void setListRightDelimText(int level, UT_String rightDelimText) { UT_String_sprintf(m_listDelim[level], "%%L%s", rightDelimText.c_str()); }
   void resetListIDsAndNumbers() { for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++) { m_listIDs[i]=0; m_currentListNumbers[i]=0; } }
   void updateListTypes(UT_uint16 *numberingMethods); // update list types based on information from a wordperfect outlining group
   void incrementLevelNumber(int level) { m_currentListNumbers[level]++; }
	
 private:
   UT_uint16 m_outlineHash; // we're not actually hashing, but we use the hash to identify the outline style
   UT_uint32 m_listIDs[WP_NUM_LIST_LEVELS];
   List_Type m_listTypes[WP_NUM_LIST_LEVELS];
   bool m_bIsNumberedList[WP_NUM_LIST_LEVELS];
   UT_uint16 m_currentListNumbers[WP_NUM_LIST_LEVELS];
   UT_String m_listDelim[WP_NUM_LIST_LEVELS];
};

class ABI_EXPORT IE_Imp_WordPerfect_Sniffer : public IE_ImpSniffer
{
	friend class IE_Imp;
	friend class IE_Imp_WordPerfect;

public:
	IE_Imp_WordPerfect_Sniffer(const char * name);
	virtual ~IE_Imp_WordPerfect_Sniffer() {}

	virtual UT_Confidence_t recognizeContents (const char * szBuf,
					    UT_uint32 iNumbytes);
	virtual UT_Confidence_t recognizeSuffix (const char * szSuffix);
	virtual bool getDlgLabels (const char ** szDesc,
							   const char ** szSuffixList,
							   IEFileType * ft);
	virtual UT_Error constructImporter (PD_Document * pDocument,
										IE_Imp ** ppie);
};

class ABI_EXPORT IE_Imp_WordPerfect : public IE_Imp
{
public:
	IE_Imp_WordPerfect(PD_Document * pDocument);
	~IE_Imp_WordPerfect(); 

	virtual UT_Error	importFile(const char * szFilename);
	virtual void		pasteFromBuffer(PD_DocumentRange * pDocRange,
						UT_uint8 * pData, UT_uint32 lenData, const char * szEncoding = 0);
 protected:
   UT_Error _parseHeader();
   UT_Error _parseIndexHeader();
   UT_Error _parseFontDescriptorPacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer);
   UT_Error _parseDocumentInformationDescriptorPacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer);
   UT_Error _parseOutlineStylePacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer);
   UT_Error _handleBoxGroupTemplate(int boxGroupTemplatePID);
   UT_Error _handleBoxGroupContent(int boxContentPID);
   UT_Error _handleGraphicsData(int graphicPID);
   UT_Error _parseDocument();
   UT_Error _insertCharacter(UT_UCS4Char ucs);
   UT_Error _insertSpace();
   UT_Error _insertHyphen();
   UT_Error _handleHardEndOfLine();
   UT_Error _handleEndOfLineGroup();
   UT_Error _handlePageGroup();
   UT_Error _handleColumnGroup();
   UT_Error _handleParagraphGroup();
   UT_Error _handleParagraphGroupJustification();
   UT_Error _handleOutlineDefine();
   UT_Error _handleSetNumberGroup();
   UT_Error _handleNumberingMethodGroup();
   UT_Error _handleDisplayNumberReferenceGroup();
   UT_Error _handleIncrementNumberGroup();
   UT_Error _handleDecrementNumberGroup();
   UT_Error _handleStyleGroup();
   UT_Error _handleMergeGroup();
   UT_Error _handleBoxGroup();
   UT_Error _handleTabGroup();
   UT_Error _handlePlatformGroup();
   UT_Error _handleFormatterGroup();
   UT_Error _handleCharacterGroup();
   UT_Error _handleCrossReferenceGroup();
   UT_Error _handleHeaderFooterGroup();
   UT_Error _handleFootEndNoteGroup();
   UT_Error _handleFontFaceChange();
   UT_Error _handleFontSizeChange();
   UT_Error _handleExtendedCharacter();
   UT_Error _handleUndo();
   UT_Error _handleAttributeOn();
   UT_Error _handleAttributeOff();
   UT_Error _handleVariableGroupHeader(long &startPosition, UT_uint8 &subGroup, UT_uint16 &size, UT_uint8 &flags);
   UT_Error _skipGroup(long startPosition, UT_uint16 groupSize);
   UT_Error _appendCurrentTextProperties();
   UT_Error _appendCurrentParagraphProperties();
   UT_Error _appendCurrentListProperties();
   WordPerfectListDefinition * _getListDefinition(UT_uint16 outlineHash);
   UT_Error _updateDocumentListDefinition(WordPerfectListDefinition *listDefinition, int level);
   UT_Error _flushText();
   UT_Error _flushParagraph();
   UT_Error _appendSection();
   
 private:
   FILE *m_importFile;
   UT_uint32 m_documentEnd;
   UT_uint32 m_documentPointer;
   UT_uint16 m_indexPointer;
   bool m_undoOn;
   bool m_bParagraphChanged;
   bool m_bParagraphExists;
   bool m_bInSection;
   bool m_bSectionChanged;
   bool m_bParagraphInSection;
   bool m_bFirstMargin;
   bool m_bTextPropertiesChanged;
   enum WordPerfectParagraphStyleState { notInStyle, beginBeforeNumbering, beginNumbering, beginDisplayReferencing, beginAfterNumbering, styleBody, end };
   WordPerfectParagraphStyleState m_paragraphStyleState;
   bool m_bPutativeListHasParagraphNumber;
   UT_uint32 m_currentListTag;
   UT_String m_rightListDelim; // (AFAIK WP doesn't do left delimiters on lists?)
   bool m_bEnteringList;
   
   UT_UCS4_mbtowc m_Mbtowc;
   UT_GrowBuf m_textBuf;
   UT_Vector m_fontDescriptorList;
   UT_Vector m_headerPacketList;
   UT_Vector m_wordPerfectDispatchBytes;
   UT_Vector m_listDefinitionList;
   WordPerfectTextAttributes m_textAttributes;
   WordPerfectParagraphProperties m_paragraphProperties;

   int m_numDeferredParagraphBreaks;
   
   float m_leftMargin;
   float m_rightMargin;
   bool m_bLeftMarginSet;
   bool m_bRightMarginSet;
   UT_uint8 m_numberOfColumns;
   bool m_bColumnsSet;
   
   UT_uint8 m_currentListLevel; // WordPerfect list levels start at 0, Abi list levels start at 1
   UT_uint16 m_currentOutlineHash;
   
   float m_paragraphStyleTextIndent;
   float m_paragraphStyleMarginLeft;

   int m_iCurrentTableRow;
   int m_iCurrentTableColumn;
};

struct ABI_EXPORT WordPerfectByteTag
{
   WordPerfectByteTag( UT_uint8 byte, UT_Error (IE_Imp_WordPerfect::*func)() );
   UT_uint8 m_byte;
   UT_Error (IE_Imp_WordPerfect::*m_func) () ;
}; 

#endif /* IE_IMP_WP_H */
