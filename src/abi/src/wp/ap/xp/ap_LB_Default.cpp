/* AbiWord
 * Copyright (C) 1998-2001 AbiSource, Inc.
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


// ********************************************************************************
// ********************************************************************************
// *** THIS FILE DEFINES THE DEFAULT KEYBOARD AND MOUSE BINDINGS FOR AbiWord 1. ***
// *** To define bindings for other emulations, clone this file and change the  ***
// *** various settings.  See ap_LoadBindings.cpp for more information.         ***
// ********************************************************************************
// ********************************************************************************

#include "ut_assert.h"
#include "ut_types.h"
#include "ev_EditBits.h"
#include "ev_EditBinding.h"
#include "ev_EditMethod.h"
#include "ev_NamedVirtualKey.h"
#include "ap_LoadBindings.h"
#include "ap_LB_Default.h"

#define DEFLEN(x) UT_uint32 x ## _len = NrElements(x)

// NOTE: on Win32 we cannot get ALT-TAB (but we can get ALT-F4 :-)

#define _S		| EV_EMS_SHIFT
#define _C		| EV_EMS_CONTROL
#define _A		| EV_EMS_ALT

/*****************************************************************
******************************************************************
** load top-level (non-prefixed) builtin bindings for the mouse
******************************************************************
*****************************************************************/

#define _CU		EV_EMC_UNKNOWN
#define _CT		EV_EMC_TEXT
#define _CM		EV_EMC_MISSPELLEDTEXT
#define _CL		EV_EMC_LEFTOFTEXT
#define _CR		EV_EMC_RIGHTOFTEXT
#define _CI		EV_EMC_IMAGE
#define _CZ		EV_EMC_IMAGESIZE
#define _CF		EV_EMC_FIELD
#define _CH		EV_EMC_HYPERLINK
#define _CV		EV_EMC_REVISION
#define _CTV		EV_EMC_VLINE
#define _CTH		EV_EMC_HLINE

#define _B0		| EV_EMB_BUTTON0
#define _B1		| EV_EMB_BUTTON1
#define _B2		| EV_EMB_BUTTON2
#define _B3		| EV_EMB_BUTTON3
#define _B4		| EV_EMB_BUTTON4
#define _B5		| EV_EMB_BUTTON5

ap_bs_Mouse MouseTable[] =
{

	// TODO some of these bindings are what i think they
	// TODO should be and some are just for testing until
	// TODO the full features are implemented.  some i've
	// TODO just filled in some guesses, but never used.

//	Button-0 (no buttons pressed)
//  { context	{ click	dblclick	drag,				dbldrag,	release,	doublerelease	}},
	{_CU _B0,	{ "",	"",			"cursorDefault",	"",			"",			""				}},
	{_CT _B0,	{ "",	"",			"cursorIBeam",		"",			"",			""				}},
	{_CL _B0,	{ "",	"",			"cursorRightArrow",	"",			"",			""				}},
	{_CM _B0,	{ "",	"",			"cursorIBeam",		"",			"",			""				}},
	{_CI _B0,	{ "",	"",			"cursorImage",		"",			"",			""				}},
	{_CZ _B0,	{ "",	"",			"cursorImageSize",	"",			"",			""				}},
	{_CF _B0,	{ "",	"",			"cursorDefault",	"",			"",			""				}},
	{_CR _B0,	{ "",	"",			"cursorDefault",	"",			"",			""				}},
	{_CH _B0,	{ "",	"",			"hyperlinkStatusBar",	"",			"",			"",				}},
	{_CTV _B0,	{ "",	"",			"cursorVline",	"",			"",			"",				}},
	{_CTH _B0,	{ "",	"",			"cursorHline",	"",			"",			"",				}},


//	Button-1, Image-context
//  { context	{ click				doubleclick		drag,		dbldrag,		release,	doublerelease }},
	{_CI _B1,	{ "selectObject",	"selectObject",	"",			"",				"",			""	}},
	{_CI _B1 _C,{ "",				"",				"dragImage","",				"dropImage",""	}},
	{_CF _B1,	{ "warpInsPtToXY",	"selectObject",	"",			"",				"",			""	}},
	{_CF _B1,	{ "warpInsPtToXY",	"selectObject",	"",			"",				"",			""	}},
	
//	Button-1, Text-context
//  { context	{ click				doubleclick		drag,		dbldrag,		release,	doublerelease	}},
	{_CT _B1,	{ "warpInsPtToXY",	"selectWord",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"		}},
	{_CT _B1 _S,{ "extSelToXY",		"",				"dragToXY", "",				"endDrag",	"endDrag"		}},
	{_CT _B1 _C,{ "",		"",		       	"dragSelectionBegin",	       	"dragSelectionBegin",		        "dragSelectionEnd",	"dragSelectionEnd"		}},


//	Button-1, Left-of-Text-context (left-margin)
//  { context	{ click				doubleclick		drag,		dbldrag,		release,	doublerelease	}},
	{_CL _B1,	{ "selectLine",		"selectBlock",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"		}},

//	Button-1, Misspelled-Word-Text-context
//  { context	{ click				doubleclick		drag,		dbldrag,		release,	doublerelease	}},
	{_CM _B1,	{ "warpInsPtToXY",	"selectWord",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"		}},
	{_CM _B1 _S,{ "extSelToXY",		"",				"dragToXY", "",				"endDrag",	"endDrag"		}},
	{_CM _B1 _C,{ "selectWord",		"",				"",			"",				"endDrag",	"endDrag"		}},
	{_CR _B1,	{ "selectLine",		"selectBlock",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"		}},

//  button-1, hyperlink context
	{_CH _B1,	{ "warpInsPtToXY",	"hyperlinkJump",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"	}},
	{_CV _B1,	{ "warpInsPtToXY",	"selectWord",	"dragToXY",	"dragToXYword",	"endDrag",	"endDrag"		}},

//	Button-1, Image-context
//  { context	{ click				doubleclick		drag,		dbldrag,	release,		doublerelease	}},
	{_CZ _B1,	{ "",				"",				"resizeImage",	"",		"endResizeImage",	""				}},
//	{_CI _B1,	{ "selectImage",	"editImage",	"moveImage","",			"endImageMove",	""				}},

//	Button-1, TableLine-context

	{_CTV _B1,	{ "beginVDrag",		 "clearSetCols", "dragVline",	"",		"endDragVline",	""				}},
	{_CTH _B1,	{ "beginHDrag",		 "clearSetRows", "dragHline",	"",		"endDragHline",	""				}},


//	Button-1, ImageSize-context
//  { context	{ click				doubleclick		drag,		dbldrag,	release,		doublerelease	}},
//	{_CI _B1,	{ "startImageSize",	"",				"dragImageSize","",		"endImageSize",	""				}},

//	Button-1, Field-context
//  { context	{ click				doubleclick		drag,	dbldrag,	release,	doublerelease	}},
//	{_CI _B1,	{ "selectField",	"editField",	"",		"",			"",			""				}},

//	Button-2, Text-context
//  { context	{ click				doubleclick		drag,		dbldrag,		release,	doublerelease	}},

// special key binding for X11-style middle mouse selection (not to be confused with the clipboard)
	{_CT _B2,	{ "pasteSelection",	"",				"",			"",				"",			""				}},
	{_CH _B2,	{ "pasteSelection",	"",				"",			"",				"",			""				}},


//	Button-3, context menus
//  { context	{ click					dblclick	drag,	dbldrag,	release,	doublerelease	}},
	//{_CU _B3,	{ "contextDefault",		"",			"",		"",			"",			""				}},
	{_CT _B3,	{ "contextText",		"",			"",		"",			"",			""				}},
	//{_CL _B3,	{ "contextLeftOfText",	"",			"",		"",			"",			""				}},
	{_CM _B3,	{ "contextMisspellText","",			"",		"",			"",			""				}},
	{_CI _B3,	{ "contextImage",		"",			"",		"",			"",			""				}},
	//{_CZ _B3,	{ "contextImageSize",	"",			"",		"",			"",			""				}},
	//{_CF _B3,	{ "contextField",		"",			"",		"",			"",			""				}},

	{_CH _B3,	{ "contextHyperlink",		"",			"",		"",			"",			""				}},

	{_CV _B3,	{ "contextRevision",		"",			"",		"",			"",			""				}},

//  Button-4, Mouse wheel (3 lines up)... yes, a hack.
	{_CU _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CU _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CT _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CT _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CL _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CL _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CR _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CM _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CM _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CI _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CI _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CZ _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CZ _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CF _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CF _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},
	{_CH _B4,	{ "scrollWheelMouseUp",		"scrollWheelMouseUp",			"",		"",			"",			""				}},
	{_CH _B4 _C,{ "zoomIn",		            "zoomIn",           			"",		"",			"",			""				}},


//  Button-5, Mouse wheel (3 lines down)
	{_CU _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CU _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CT _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CT _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CL _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CL _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CM _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CM _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CI _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CI _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CZ _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CZ _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CF _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CF _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},
	{_CH _B5,	{ "scrollWheelMouseDown",		"scrollWheelMouseDown",			"",		"",			"",			""				}},
	{_CH _B5 _C,{ "zoomOut",		            "zoomOut",           			"",		"",			"",			""				}},

#if defined(PT_TEST) || defined(FMT_TEST) || defined(UT_TEST)
//  { context		{ click			doubleclick		drag,		dbldrag,	release,	doublerelease	}},
	{_CU _B3 _A,	{ FN_TEST_DUMP,	"",				"",			"",			"",			""				}},
#endif
};

DEFLEN(MouseTable);

#undef _CT
#undef _CL

#undef _B1
#undef _B2
#undef _B3
#undef _B4
#undef _B5

/*****************************************************************
******************************************************************
** load top-level (non-prefixed) builtin bindings for the NamedVirtualKeys
******************************************************************
*****************************************************************/

ap_bs_NVK NVKTable[] =
{
//	{nvk,				{ none,					_S,					_C,				_S_C,
//  					  _A,					_A_S,				_A_C,			_A_C_S				}},
	{EV_NVK_BACKSPACE,	{ "delLeft", 			"delLeft",			"delBOW",		"",
						  "",					"",					"",				""					}},
	{EV_NVK_SPACE,		{ "insertSpace",		"insertSpace",		"togglePlain",	"insertNBSpace",
						  "insertNBZWSpace",	"insertZWJoiner",					"",				""					}},
	{EV_NVK_TAB,		{ "insertTab",			"",					"cycleWindows",	"cycleWindowsBck",
						  "",					"",					"",				""					}},
	{EV_NVK_RETURN,		{ "insertParagraphBreak", "insertLineBreak", "insertPageBreak", "insertColumnBreak",
						  "insertSectionBreak",	"",					"",				""					}},
//	{EV_NVK_ESCAPE,		{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
	{EV_NVK_PAGEUP,		{ "warpInsPtPrevScreen","extSelScreenUp",   "warpInsPtPrevPage",	"extSelPageUp",
						  "",					"",					"warpInsPtBOP",	""					}},
	{EV_NVK_PAGEDOWN,	{ "warpInsPtNextScreen","extSelScreenDown",	"warpInsPtNextPage",	"extSelPageDown",
						  "",					"",					"warpInsPtEOP",	""					}},
	{EV_NVK_END,		{ "warpInsPtEOL",		"extSelEOL",		"warpInsPtEOD",	"extSelEOD",
						  "",					"",					"",				""					}},
	{EV_NVK_HOME,		{ "warpInsPtBOL",		"extSelBOL",		"warpInsPtBOD",	"extSelBOD",
						  "",					"",					"",				""					}},
	{EV_NVK_LEFT,		{ "warpInsPtLeft",		"extSelLeft",		"warpInsPtBOW",	"extSelBOW",
						  "toggleUnIndent",		"",					"",				""					}},
	{EV_NVK_UP,			{ "warpInsPtPrevLine",	"extSelPrevLine",	"warpInsPtBOB",	"extSelBOB",
						  "",					"",					"",				""					}},
	{EV_NVK_RIGHT,		{ "warpInsPtRight",		"extSelRight",		"warpInsPtEOW",	"extSelEOW",
						  "toggleIndent",		"",					"",				""					}},
	{EV_NVK_DOWN,		{ "warpInsPtNextLine",	"extSelNextLine",	"warpInsPtEOB",	"extSelEOB",
						  "",					"",					"",				""					}},
	{EV_NVK_MENU_SHORTCUT,	{ "contextMenu",	"",					"",				"",
						  "",					"",					"",				""					}},
    {EV_NVK_INSERT,     { "toggleInsertMode",   "paste",            "copy",         "",
						  "",					"",					"",				""					}},
	{EV_NVK_DELETE,		{ "delRight",			"cut",				"delEOW",		"",
						  "",					"",					"",				""					}},
//	{EV_NVK_HELP,		{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
	{EV_NVK_F1,			{ "helpContents",					"",					"",				"",
						  "",					"",					"",				""					}},
//	{EV_NVK_F2,			{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
	{EV_NVK_F3,			{ "findAgain",			"rotateCase",		"",				"",
						  "",					"",					"",				""					}},
	{EV_NVK_F4,			{ "",					"",					"closeWindow",	"",
						  "querySaveAndExit",	"",					"",				""					}},
//	{EV_NVK_F5,			{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
//	{EV_NVK_F6,			{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
	{EV_NVK_F7,			{ "dlgSpell",			"",					"",				"",
						  "",					"",					"",				""					}},
//	{EV_NVK_F8,			{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
//	{EV_NVK_F9,			{ "",					"",					"",				"",
//						  "",					"",					"",				""					}},
	{EV_NVK_F10,		{ "",					"contextMenu",		"",				"",
						  "",					"",					"",				""					}},
	{EV_NVK_F11,		{ "viewFullScreen",					"",					"",				"",
						  "",					"",					"",				""					}},
	{EV_NVK_F12,		{ "cycleInputMode",		"",					FN_TEST_FTR,				"",
						  FN_TEST_DUMP,			        "",					"",				""					}},
// 	{EV_NVK_F13,		{
// 	{EV_NVK_F14,		{
// 	{EV_NVK_F15,		{
// 	{EV_NVK_F16,		{
// 	{EV_NVK_F17,		{
// 	{EV_NVK_F18,		{
// 	{EV_NVK_F19,		{
// 	{EV_NVK_F20,		{
// 	{EV_NVK_F21,		{
// 	{EV_NVK_F22,		{
// 	{EV_NVK_F23,		{
// 	{EV_NVK_F24,		{
// 	{EV_NVK_F25,		{
// 	{EV_NVK_F26,		{
// 	{EV_NVK_F27,		{
// 	{EV_NVK_F28,		{
// 	{EV_NVK_F29,		{
// 	{EV_NVK_F30,		{
// 	{EV_NVK_F31,		{
// 	{EV_NVK_F32,		{
// 	{EV_NVK_F33,		{
// 	{EV_NVK_F34,		{
// 	{EV_NVK_F35,		{

};

DEFLEN(NVKTable);

/*****************************************************************
******************************************************************
** load top-level prefixed builtin bindings for the NamedVirtualKeys
******************************************************************
*****************************************************************/

ap_bs_NVK_Prefix NVKTable_P[] =
{
//	{nvk,						{ none,					_S,					_C,				_S_C,
//  							  _A,					_A_S,				_A_C,			_A_C_S	}},

	{EV_NVK_DEAD_GRAVE,			{ "deadgrave",			"deadgrave",		"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_ACUTE,			{ "deadacute",			"deadacute",		"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_CIRCUMFLEX,	{ "deadcircumflex",		"deadcircumflex",	"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_TILDE,			{ "deadtilde",			"deadtilde",		"",	"", "", "", "",	""	}},
	{EV_NVK_DEAD_MACRON,		{ "deadmacron",			"deadmacron",		"",	"", "", "",	"", ""	}},
	{EV_NVK_DEAD_BREVE,			{ "deadbreve",			"deadbreve",		"",	"", "", "",	"",	""	}},
	{EV_NVK_DEAD_ABOVEDOT,		{ "deadabovedot",		"deadabovedot",		"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_DIAERESIS,		{ "deaddiaeresis",		"deaddiaeresis",	"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_DOUBLEACUTE,	{ "deaddoubleacute",	"deaddoubleacute",	"",	"", "",	"",	"",	""	}},
	{EV_NVK_DEAD_CARON,			{ "deadcaron",			"deadcaron",		"",	"", "", "", "", ""	}},
	{EV_NVK_DEAD_CEDILLA,		{ "deadcedilla",		"deadcedilla",		"",	"", "", "",	"",	""	}},
	{EV_NVK_DEAD_OGONEK,		{ "deadogonek",			"deadogonek",		"",	"", "",	"",	"",	""	}},
};

DEFLEN(NVKTable_P);

/*****************************************************************
******************************************************************
** load top-level (non-prefixed) builtin bindings for the non-nvk
** (character keys).  note that SHIFT-state is implicit in the
** character value and is not included in the table.  note that
** we do not include the ASCII control characters (\x00 -- \x1f
** and others) since we don't map keystrokes into them.
******************************************************************
*****************************************************************/

ap_bs_Char CharTable[] =
{
//	{char, /* desc   */ { none,					_C,					_A,				_A_C				}},
	{0x21, /* !      */ { "insertData",			"",					"",				""					}},
	{0x22, /* "      */ { "insertData",			"",					"",				""					}},
	{0x23, /* #      */ { "insertData",			"",					"",				""					}},
	{0x24, /* $      */ { "insertData",			"",					"",				""					}},
	{0x25, /* %      */ { "insertData",			"",					"",				""					}},
	{0x26, /* &      */ { "insertData",			"",					"",				""					}},
	{0x27, /* '      */ { "insertData",			"",					"",				""					}},
	{0x28, /* (      */ { "insertData",			"",					"",				""					}},
	{0x29, /* )      */ { "insertData",			"",					"",				""					}},
	{0x2a, /* *      */ { "insertData",			"viewPara",			"",				""					}},
	{0x2b, /* +      */ { "insertData",			"",					"",				""					}},
	{0x2c, /* ,      */ { "insertData",			"",					"",				""					}},
	{0x2d, /* -      */ { "insertData",			"toggleSub",		"zoomOut",				""					}},
	{0x2e, /* .      */ { "insertData",			"",					"",				""					}},
	{0x2f, /* /      */ { "insertData",			"",					"",				""					}},
	{0x30, /* 0      */ { "insertData",			"",					"",				""					}},
	{0x31, /* 1      */ { "insertData",			"singleSpace",		"setStyleHeading1",				""					}},
	{0x32, /* 2      */ { "insertData",			"doubleSpace",		"setStyleHeading2",				""					}},
	{0x33, /* 3      */ { "insertData",			"",					"setStyleHeading3",				""					}},
	{0x34, /* 4      */ { "insertData",			"",					"",				""					}},
	{0x35, /* 5      */ { "insertData",			"middleSpace",		"",				""					}},
	{0x36, /* 6      */ { "insertData",			"",					"",				""					}},
	{0x37, /* 7      */ { "insertData",			"",					"",				""					}},
	{0x38, /* 8      */ { "insertData",			"",					"",				""					}},
	{0x39, /* 9      */ { "insertData",			"",					"",				""					}},
	{0x3a, /* :      */ { "insertData",			"",					"",				""					}},
	{0x3b, /* ;      */ { "insertData",			"",					"",				""					}},
	{0x3c, /* <      */ { "insertData",			"",					"",				""					}},
	{0x3d, /* =      */ { "insertData",			"toggleSuper",		"zoomIn",				""					}},
	{0x3e, /* >      */ { "insertData",			"",					"",				""					}},
	{0x3f, /* ?      */ { "insertData",			"",					"",				""					}},
	{0x40, /* @      */ { "insertData",			"",					"",				""					}},
	{0x41, /* A      */ { "insertData",			"selectAll",		"",				""					}},
	{0x42, /* B      */ { "insertData",			"toggleBold",		"",				""					}},
	{0x43, /* C      */ { "insertData",			"copy",				"",				""					}},
	{0x44, /* D      */ { "insertData",			"dlgFont",			"",				""					}},
	{0x45, /* E      */ { "insertData",			"alignCenter",		"",				""					}},
	{0x46, /* F      */ { "insertData",			"find",				"",				""					}},
	{0x47, /* G      */ { "insertData",			"go",				"",				""					}},
	{0x48, /* H      */ { "insertData",			"replace",			"",				""					}},
	{0x49, /* I      */ { "insertData",			"toggleItalic",		"",				""					}},
	{0x4a, /* J      */ { "insertData",			"alignJustify",		"",				""					}},
	{0x4b, /* K      */ { "insertData",			"toggleStrike",		"",				""					}},
	{0x4c, /* L      */ { "insertData",			"alignLeft",		"",				""					}},
	{0x4d, /* M      */ { "insertData",			"insSymbol",		"",				""					}},
	{0x4e, /* N      */ { "insertData",			"toolbarNew",		"",				""					}},
	{0x4f, /* O      */ { "insertData",			"fileOpen",			"",				""					}},
	{0x50, /* P      */ { "insertData",			"print",			"",				""					}},
	{0x51, /* Q      */ { "insertData",			"querySaveAndExit",	"",				""					}},
	{0x52, /* R      */ { "insertData",			"alignRight",		"",				""					}},
	{0x53, /* S      */ { "insertData",			"fileSave",			"",				""					}},
	{0x54, /* T      */ { "insertData",			"toggleOline",		"",				""					}},
	{0x55, /* U      */ { "insertData",			"toggleUline",		"",				""					}},
	{0x56, /* V      */ { "insertData",			"paste",			"",				"pasteSpecial"					}},
	{0x57, /* W      */ { "insertData",			"closeWindow",		"",				""					}},
	{0x58, /* X      */ { "insertData",			"cut",				"",				""					}},
	{0x59, /* Y      */ { "insertData",			"redo",				"",				""					}},
	{0x5a, /* Z      */ { "insertData",			"undo",				"",				""					}},
	{0x5b, /* [      */ { "insertData",			"editHeader",					"",				""					}},
	{0x5c, /* \      */ { "insertData",			"removeHeader",					"",				""					}},
	{0x5d, /* ]      */ { "insertData",			"editFooter",					"",				""					}},
	{0x5e, /* ^      */ { "insertData",			"removeFooter",					"",				""					}},
	{0x5f, /* -      */ { "insertData",			"",					"",				""					}},
	{0x60, /* `      */ { "insertData",			"",					"",				""					}},
	{0x61, /* a      */ { "insertData",			"selectAll",		"",				""					}},
	{0x62, /* b      */ { "insertData",			"toggleBold",		"",				""					}},
	{0x63, /* c      */ { "insertData",			"copy",				"",				""					}},
	{0x64, /* d      */ { "insertData",			"dlgFont",			"",				""					}},
	{0x65, /* e      */ { "insertData",			"alignCenter",		"",				""					}},
	{0x66, /* f      */ { "insertData",			"find",				"",				""					}},
	{0x67, /* g      */ { "insertData",			"go",				"",				""					}},
	{0x68, /* h      */ { "insertData",			"replace",			"",				""					}},
	{0x69, /* i      */ { "insertData",			"toggleItalic",		"",				""					}},
	{0x6a, /* j      */ { "insertData",			"alignJustify",		"",				""					}},
	{0x6b, /* k      */ { "insertData",			"toggleStrike",		"",				""					}},
	{0x6c, /* l      */ { "insertData",			"alignLeft",		"",				""					}},
	{0x6d, /* m      */ { "insertData",			"insSymbol",		"",				""					}},
	{0x6e, /* n      */ { "insertData",			"toolbarNew",		"",				""					}},
	{0x6f, /* o      */ { "insertData",			"fileOpen",			"",				""					}},
	{0x70, /* p      */ { "insertData",			"print",			"",				""					}},
	{0x71, /* q      */ { "insertData",			"querySaveAndExit",	"",				""					}},
	{0x72, /* r      */ { "insertData",			"alignRight",		"",				""					}},
	{0x73, /* s      */ { "insertData",			"fileSave",			"",				""					}},
	{0x74, /* t      */ { "insertData",			"toggleOline",		"",				""					}},
	{0x75, /* u      */ { "insertData",			"toggleUline",		"",				""					}},
	{0x76, /* v      */ { "insertData",			"paste",			"",				"pasteSpecial"					}},
	{0x77, /* w      */ { "insertData",			"closeWindow",		"",				""					}},
	{0x78, /* x      */ { "insertData",			"cut",				"",				""					}},
	{0x79, /* y      */ { "insertData",			"redo",				"",				""					}},
	{0x7a, /* z      */ { "insertData",			"undo",				"",				""					}},
	{0x7b, /* {      */ { "insertData",			"",					"",				""					}},
	{0x7c, /* |      */ { "insertData",			"",					"",				""					}},
	{0x7d, /* }      */ { "insertData",			"",					"",				""					}},
	{0x7e, /* ~      */ { "insertData",			"",					"",				""					}},

//	Here are bindings for the portion of Latin-1 with the high-bit set.
//	I'm taking the list from /usr/include/X11/keysymdef.h, so I think
//	that the set is reasonably complete.
//
//	I don't know how to test these on my en-US system with my en-US keyboard,
//	but I think they will work.
//
//	TODO For now I just bound them all to "insertData" which will cause
//	TODO the character to be inserted into the document.  I'm wondering
//	TODO if some of these (e.g., paragraph and section) should be bound
//	TODO to some other functions -- but rather than try guessing, let's
//	TODO wait and let some of our European friends comment.

//	{char, /* desc           */ { none,				_C,					_A,				_A_C				}},

	{0xa0, /* nbs            */ { "insertNBSpace",	"",					"",				""					}},
	{0xa1, /* exclamdown     */ { "insertData",		"",					"",				""					}},
	{0xa2, /* cent           */ { "insertData",		"",					"",				""					}},
	{0xa3, /* sterling       */ { "insertData",		"",					"",				""					}},
	{0xa4, /* currency       */ { "insertData",		"",					"",				""					}},
	{0xa5, /* yen            */ { "insertData",		"",					"",				""					}},
	{0xa6, /* brokenbar      */ { "insertData",		"",					"",				""					}},
	{0xa7, /* section        */ { "insertData",		"",					"",				""					}},
	{0xa8, /* diaeresis      */ { "insertData",		"",					"",				""					}},
	{0xa9, /* copyright      */ { "insertData",		"",					"",				""					}},
	{0xaa, /* ordfeminine    */ { "insertData",		"",					"",				""					}},
	{0xab, /* guillemotleft  */ { "insertData",		"",					"",				""					}},
	{0xac, /* notsign        */ { "insertData",		"",					"",				""					}},
	{0xad, /* hyphen         */ { "insertData",		"",					"",				""					}},
	{0xae, /* registered     */ { "insertData",		"",					"",				""					}},
	{0xaf, /* macron         */ { "insertData",		"",					"",				""					}},
	{0xb0, /* degree         */ { "insertData",		"",					"",				""					}},
	{0xb1, /* plusminus      */ { "insertData",		"",					"",				""					}},
	{0xb2, /* twosuperior    */ { "insertData",		"",					"",				""					}},
	{0xb3, /* threesuperior  */ { "insertData",		"",					"",				""					}},
	{0xb4, /* acute          */ { "insertData",		"",					"",				""					}},
	{0xb5, /* mu             */ { "insertData",		"",					"",				""					}},
	{0xb6, /* paragraph      */ { "insertData",		"",					"",				""					}},
	{0xb7, /* periodcentered */ { "insertData",		"",					"",				""					}},
	{0xb8, /* cedilla        */ { "insertData",		"",					"",				""					}},
	{0xb9, /* onesuperior    */ { "insertData",		"",					"",				""					}},
	{0xba, /* masculine      */ { "insertData",		"",					"",				""					}},
	{0xbb, /* guillemotright */ { "insertData",		"",					"",				""					}},
	{0xbc, /* onequarter     */ { "insertData",		"",					"",				""					}},
	{0xbd, /* onehalf        */ { "insertData",		"",					"",				""					}},
	{0xbe, /* threequarters  */ { "insertData",		"",					"",				""					}},
	{0xbf, /* questiondown   */ { "insertData",		"",					"",				""					}},
	{0xc0, /* Agrave         */ { "insertData",		"",					"",				""					}},
	{0xc1, /* Aacute         */ { "insertData",		"",					"",				""					}},
	{0xc2, /* Acircumflex    */ { "insertData",		"",					"",				""					}},
	{0xc3, /* Atilde         */ { "insertData",		"",					"",				""					}},
	{0xc4, /* Adiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xc5, /* Aring          */ { "insertData",		"",					"",				""					}},
	{0xc6, /* AE             */ { "insertData",		"",					"",				""					}},
	{0xc7, /* Ccedilla       */ { "insertData",		"",					"",				""					}},
	{0xc8, /* Egrave         */ { "insertData",		"",					"",				""					}},
	{0xc9, /* Eacute         */ { "insertData",		"",					"",				""					}},
	{0xca, /* Ecircumflex    */ { "insertData",		"",					"",				""					}},
	{0xcb, /* Ediaeresis     */ { "insertData",		"",					"",				""					}},
	{0xcc, /* Igrave         */ { "insertData",		"",					"",				""					}},
	{0xcd, /* Iacute         */ { "insertData",		"",					"",				""					}},
	{0xce, /* Icircumflex    */ { "insertData",		"",					"",				""					}},
	{0xcf, /* Idiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xd0, /* ETH            */ { "insertData",		"",					"",				""					}},
	{0xd1, /* Ntilde         */ { "insertData",		"",					"",				""					}},
	{0xd2, /* Ograve         */ { "insertData",		"",					"",				""					}},
	{0xd3, /* Oacute         */ { "insertData",		"",					"",				""					}},
	{0xd4, /* Ocircumflex    */ { "insertData",		"",					"",				""					}},
	{0xd5, /* Otilde         */ { "insertData",		"",					"",				""					}},
	{0xd6, /* Odiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xd7, /* multiply       */ { "insertData",		"",					"",				""					}},
	{0xd8, /* Ooblique       */ { "insertData",		"",					"",				""					}},
	{0xd9, /* Ugrave         */ { "insertData",		"",					"",				""					}},
	{0xda, /* Uacute         */ { "insertData",		"",					"",				""					}},
	{0xdb, /* Ucircumflex    */ { "insertData",		"",					"",				""					}},
	{0xdc, /* Udiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xdd, /* Yacute         */ { "insertData",		"",					"",				""					}},
	{0xde, /* THORN          */ { "insertData",		"",					"",				""					}},
	{0xdf, /* ssharp         */ { "insertData",		"",					"",				""					}},
	{0xe0, /* agrave         */ { "insertData",		"",					"",				""					}},
	{0xe1, /* aacute         */ { "insertData",		"",					"",				""					}},
	{0xe2, /* acircumflex    */ { "insertData",		"",					"",				""					}},
	{0xe3, /* atilde         */ { "insertData",		"",					"",				""					}},
	{0xe4, /* adiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xe5, /* aring          */ { "insertData",		"",					"",				""					}},
	{0xe6, /* ae             */ { "insertData",		"",					"",				""					}},
	{0xe7, /* ccedilla       */ { "insertData",		"",					"",				""					}},
	{0xe8, /* egrave         */ { "insertData",		"",					"",				""					}},
	{0xe9, /* eacute         */ { "insertData",		"",					"",				""					}},
	{0xea, /* ecircumflex    */ { "insertData",		"",					"",				""					}},
	{0xeb, /* ediaeresis     */ { "insertData",		"",					"",				""					}},
	{0xec, /* igrave         */ { "insertData",		"",					"",				""					}},
	{0xed, /* iacute         */ { "insertData",		"",					"",				""					}},
	{0xee, /* icircumflex    */ { "insertData",		"",					"",				""					}},
	{0xef, /* idiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xf0, /* eth            */ { "insertData",		"",					"",				""					}},
	{0xf1, /* ntilde         */ { "insertData",		"",					"",				""					}},
	{0xf2, /* ograve         */ { "insertData",		"",					"",				""					}},
	{0xf3, /* oacute         */ { "insertData",		"",					"",				""					}},
	{0xf4, /* ocircumflex    */ { "insertData",		"",					"",				""					}},
	{0xf5, /* otilde         */ { "insertData",		"",					"",				""					}},
	{0xf6, /* odiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xf7, /* division       */ { "insertData",		"",					"",				""					}},
	{0xf8, /* oslash         */ { "insertData",		"",					"",				""					}},
	{0xf9, /* ugrave         */ { "insertData",		"",					"",				""					}},
	{0xfa, /* uacute         */ { "insertData",		"",					"",				""					}},
	{0xfb, /* ucircumflex    */ { "insertData",		"",					"",				""					}},
	{0xfc, /* udiaeresis     */ { "insertData",		"",					"",				""					}},
	{0xfd, /* yacute         */ { "insertData",		"",					"",				""					}},
	{0xfe, /* thorn          */ { "insertData",		"",					"",				""					}},
	{0xff, /* ydiaeresis     */ { "insertData",		"",					"",				""					}},
};

DEFLEN(CharTable);

/*****************************************************************
******************************************************************
** put it all together and load the default bindings.
******************************************************************
*****************************************************************/

bool ap_LoadBindings_Default(AP_BindingSet * pThis, EV_EditBindingMap * pebm)
{
	pThis->_loadMouse(pebm,MouseTable,MouseTable_len);
	pThis->_loadNVK(pebm,NVKTable,NVKTable_len,NVKTable_P,NVKTable_P_len);
	pThis->_loadChar(pebm,CharTable,CharTable_len,NULL,0);

	return true;
}
