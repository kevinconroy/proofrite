/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 * Copyright (C) 2001-2002 Hubert Figuiere
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

/*****************************************************************
******************************************************************
** IT IS IMPORTANT THAT THIS FILE ALLOW ITSELF TO BE INCLUDED
** MORE THAN ONE TIME.  Each time you add an entry to the top-half
** of this file be sure to add a corresponding entry to the other
** half and be sure to add an entry to each of the other platforms.
******************************************************************
*****************************************************************/

#ifndef AP_COCOADIALOG_ALL_H
#define AP_COCOADIALOG_ALL_H

#	define DEFAULT_BUTTON_WIDTH	85

#	include "xap_CocoaDlg_MessageBox.h"
#	include "xap_CocoaDlg_FileOpenSaveAs.h"
#	include "xap_CocoaDlg_Print.h"
#   include "xap_CocoaDlg_PrintPreview.h"
#	include "xap_CocoaDlg_WindowMore.h"
#	include "xap_CocoaDlg_FontChooser.h"
#	include "xap_CocoaDlg_About.h"
#	include "xap_CocoaDlg_Zoom.h"
#	include "xap_CocoaDlg_Insert_Symbol.h"
#	include "xap_CocoaDlg_Language.h"
#   include "xap_CocoaDlg_PluginManager.h"
#   include "xap_CocoaDlg_ClipArt.h"
#   include "xap_CocoaDlg_Encoding.h"
#	include "xap_CocoaDlg_Password.h"
#	include "xap_CocoaDlg_Image.h"

#	include "ap_CocoaDialog_Replace.h"
#	include "ap_CocoaDialog_Break.h"
#	include "ap_CocoaDialog_Goto.h"
#   include "ap_CocoaDialog_PageNumbers.h"
#   include "ap_CocoaDialog_PageSetup.h"
#	include "ap_CocoaDialog_Paragraph.h"
#	include "ap_CocoaDialog_Options.h"
#	include "ap_CocoaDialog_Spell.h"
#	include "ap_CocoaDialog_Styles.h"
#	include "ap_CocoaDialog_Tab.h"
#	include "ap_CocoaDialog_Insert_DateTime.h"
#	include "ap_CocoaDialog_WordCount.h"
#	include "ap_CocoaDialog_Field.h"
#	include "ap_CocoaDialog_Lists.h"
#	include "ap_CocoaDialog_Columns.h"
#	include "ap_CocoaDialog_Tab.h"
#   include "ap_CocoaDialog_ToggleCase.h"
#   include "ap_CocoaDialog_Background.h"
#   include "ap_CocoaDialog_New.h"
#   include "ap_CocoaDialog_HdrFtr.h"
#	include "ap_CocoaDialog_InsertBookmark.h"
#	include "ap_CocoaDialog_InsertHyperlink.h"
#	include "ap_CocoaDialog_MetaData.h"
#	include "ap_CocoaDialog_MarkRevisions.h"
#	include "ap_CocoaDialog_ListRevisions.h"
#ifdef HAVE_CURL
#	include "ap_CocoaDialog_Download_File.h"
#endif
	// ... add new dialogs here ...

#else

	DeclareDialog(XAP_DIALOG_ID_MESSAGE_BOX,	XAP_CocoaDialog_MessageBox)
	DeclareDialog(XAP_DIALOG_ID_FILE_OPEN,		XAP_CocoaDialog_FileOpenSaveAs)
	DeclareDialog(XAP_DIALOG_ID_FILE_SAVEAS,	XAP_CocoaDialog_FileOpenSaveAs)
//PORT	DeclareDialog(XAP_DIALOG_ID_PRINT,			XAP_CocoaDialog_Print)
	DeclareDialog(XAP_DIALOG_ID_PRINTTOFILE,	XAP_CocoaDialog_FileOpenSaveAs)
//PORT	DeclareDialog(XAP_DIALOG_ID_FONT,			XAP_CocoaDialog_FontChooser)
//PORT	DeclareDialog(XAP_DIALOG_ID_LANGUAGE,		XAP_CocoaDialog_Language)
//PORT	DeclareDialog(XAP_DIALOG_ID_WINDOWMORE,		XAP_CocoaDialog_WindowMore)
//PORT	DeclareDialog(XAP_DIALOG_ID_ZOOM,			XAP_CocoaDialog_Zoom)
//PORT	DeclareDialog(XAP_DIALOG_ID_INSERT_SYMBOL,  XAP_CocoaDialog_Insert_Symbol)
	DeclareDialog(XAP_DIALOG_ID_INSERT_PICTURE,	XAP_CocoaDialog_FileOpenSaveAs)

	DeclareDialog(XAP_DIALOG_ID_ABOUT,			XAP_CocoaDialog_About)

//PORT	DeclareDialog(AP_DIALOG_ID_REPLACE,			AP_CocoaDialog_Replace)
//PORT	DeclareDialog(AP_DIALOG_ID_FIND,			AP_CocoaDialog_Replace)
//PORT    DeclareDialog(AP_DIALOG_ID_HDRFTR,          AP_CocoaDialog_HdrFtr)
//PORT    DeclareDialog(AP_DIALOG_ID_BACKGROUND,      AP_CocoaDialog_Background)
//PORT	DeclareDialog(AP_DIALOG_ID_GOTO,			AP_CocoaDialog_Goto)
	DeclareDialog(AP_DIALOG_ID_BREAK,			AP_CocoaDialog_Break)
//PORT	DeclareDialog(AP_DIALOG_ID_SPELL,			AP_CocoaDialog_Spell)
//PORT	DeclareDialog(AP_DIALOG_ID_STYLES,			AP_CocoaDialog_Styles)
//PORT    DeclareDialog(AP_DIALOG_ID_PAGE_NUMBERS,    AP_CocoaDialog_PageNumbers)
//PORT	DeclareDialog(AP_DIALOG_ID_PARAGRAPH,		AP_CocoaDialog_Paragraph)
	DeclareDialog(AP_DIALOG_ID_OPTIONS,			AP_CocoaDialog_Options)
//PORT	DeclareDialog(AP_DIALOG_ID_TAB,				AP_CocoaDialog_Tab)
//PORT	DeclareDialog(AP_DIALOG_ID_INSERT_DATETIME,	AP_CocoaDialog_Insert_DateTime)
//PORT	DeclareDialog(AP_DIALOG_ID_WORDCOUNT,		AP_CocoaDialog_WordCount)
//PORT	DeclareDialog(AP_DIALOG_ID_FIELD,			AP_CocoaDialog_Field)
//PORT	DeclareDialog(AP_DIALOG_ID_LISTS,			AP_CocoaDialog_Lists)
//PORT	DeclareDialog(AP_DIALOG_ID_COLUMNS,			AP_CocoaDialog_Columns)
//PORT	DeclareDialog(AP_DIALOG_ID_TAB,				AP_CocoaDialog_Tab)
//PORT	DeclareDialog(AP_DIALOG_ID_FILE_PAGESETUP,  AP_CocoaDialog_PageSetup)
//PORT	DeclareDialog(AP_DIALOG_ID_TOGGLECASE,      AP_CocoaDialog_ToggleCase)
//PORT	DeclareDialog(AP_DIALOG_ID_FILE_NEW,        AP_CocoaDialog_New)
//PORT	DeclareDialog(XAP_DIALOG_ID_PLUGIN_MANAGER, XAP_CocoaDialog_PluginManager)
//PORT	DeclareDialog(XAP_DIALOG_ID_CLIPART,        XAP_CocoaDialog_ClipArt)
//PORT	DeclareDialog(XAP_DIALOG_ID_ENCODING,       XAP_CocoaDialog_Encoding)
	DeclareDialog(XAP_DIALOG_ID_FILE_IMPORT, XAP_CocoaDialog_FileOpenSaveAs)
	DeclareDialog(XAP_DIALOG_ID_FILE_EXPORT, XAP_CocoaDialog_FileOpenSaveAs)
	DeclareDialog(XAP_DIALOG_ID_INSERT_FILE, XAP_CocoaDialog_FileOpenSaveAs)
//PORT	DeclareDialog(XAP_DIALOG_ID_PASSWORD, XAP_CocoaDialog_Password)
//PORT 	DeclareDialog(AP_DIALOG_ID_INSERTBOOKMARK,	AP_CocoaDialog_InsertBookmark)
//PORT 	DeclareDialog(AP_DIALOG_ID_INSERTHYPERLINK,	AP_CocoaDialog_InsertHyperlink)
//PORT	DeclareDialog(XAP_DIALOG_ID_IMAGE, XAP_CocoaDialog_Image)
	DeclareDialog(AP_DIALOG_ID_METADATA,		AP_CocoaDialog_MetaData)
//PORT 	DeclareDialog(AP_DIALOG_ID_MARK_REVISIONS,	AP_CocoaDialog_MarkRevisions)
//PORT 	DeclareDialog(AP_DIALOG_ID_LIST_REVISIONS,	AP_CocoaDialog_ListRevisions)
#ifdef HAVE_CURL
	DeclareDialog(AP_DIALOG_ID_DOWNLOAD_FILE,	AP_CocoaDialog_Download_File)
#endif
 	// ... also add new dialogs here ...

#endif
